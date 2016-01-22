// This file is part of CNCSVision, a computer vision related library
// This software is developed under the grant of Italian Institute of Technology
//
// Copyright (C) 2010-2014 Carlo Nicolini <carlo.nicolini@iit.it>
//
//
// CNCSVision is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
//
// Alternatively, you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 2 of
// the License, or (at your option) any later version.
//
// CNCSVision is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License or the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License and a copy of the GNU General Public License along with
// CNCSVision. If not, see <http://www.gnu.org/licenses/>.

#include <iostream>
#include <fstream>
#include <stdexcept>
#include "Homography.h"

CameraDirectLinearTransformation::CameraDirectLinearTransformation()
{}


void CameraDirectLinearTransformation::init(const std::vector<Vector3d> &x, const stlalignedvector4d &X, const Vector4i &gl_Viewport, double znear, double zfar)
{
    points2D = x;
    points3D = X;
    if (x.size() != X.size() )
        throw std::logic_error("There must be the same number of correspondencies");

    // Reset all the matrices used in the class
    this->K.setZero();
    this->P.setZero();
    this->R.setZero();
    this->T.setZero();
    this->C.setZero();
    this->gl_ModelView_Matrix.setIdentity();
    this->gl_Projection_Matrix.matrix().setZero();
    this->gl_ModelViewProjection_Matrix.matrix().setZero();

    unsigned int n=x.size();
    Eigen::MatrixXd A;
    A.setZero(2*n,12);

    for ( unsigned int i=0; i<n; i++ )
    {
        Vector3d m = x.at(i);
        RowVector4d M = X.at(i).transpose();
        A.row(2*i) << 0,0,0,0, -m[2]*M, m[1]*M;
        A.row(2*i+1) << m[2]*M,0,0,0,0, -m[0]*M;
    }

    // http://my.safaribooksonline.com/book/-/9781449341916/4dot4-augmented-reality/id2706803

    JacobiSVD<MatrixXd> svd(A, ComputeFullV | ComputeFullU );
    // Copy the data in the last column of matrix V (the eigenvector with the smallest eigenvalue of A^T*A)
    // maintaining the correct order
    Eigen::MatrixXd V = svd.matrixV();
    int k=0;
    for (int i=0; i<3;i++)
    {
        for (int j=0; j<4; j++)
        {
            double t = svd.matrixV()(k,11);
            P(i,j)= t;
            ++k;
        }
    }

    // Compute the error using the camera matrix P
    this->getReprojectionError(P,this->points2D,this->points3D);

    this->decomposePMatrix(this->P);
    this->computeOpenGLMatrices(gl_Viewport,znear,zfar);
    // Compute the error using OpenGL pipeline matrices
    this->getReprojectionErrorOpenGL(gl_Projection_Matrix,gl_ModelView_Matrix,gl_Viewport,points2D,points3D);
}

/**
 * @brief CameraDirectLinearTransformation::decomposePMatrix
 * @param P
 */
void CameraDirectLinearTransformation::decomposePMatrix(const Eigen::Matrix<double,3,4> &P)
{
    Matrix3d M = P.topLeftCorner<3,3>();
    Vector3d m3 = M.row(2).transpose();
    // Follow the HartleyZisserman - "Multiple view geometry in computer vision" implementation chapter 3

    Matrix3d P123,P023,P013,P012;
    P123 << P.col(1),P.col(2),P.col(3);
    P023 << P.col(0),P.col(2),P.col(3);
    P013 << P.col(0),P.col(1),P.col(3);
    P012 << P.col(0),P.col(1),P.col(2);

    double X = P123.determinant();
    double Y = -P023.determinant();
    double Z = P013.determinant();
    double T = -P012.determinant();
    this->C << X/T,Y/T,Z/T;

    // Image Principal points computed with homogeneous normalization
    this->principalPoint = (M*m3).eval().hnormalized().head<2>();

    // Principal vector  from the camera centre C through pp pointing out from the camera.  This may not be the same as  R(:,3)
    // if the principal point is not at the centre of the image, but it should be similar.
    this->principalVector  =  (M.determinant()*m3).normalized();
    this->R = this->K = Matrix3d::Identity();
    this->rq3(M,this->K,this->R);
    K/=K(2,2); // EXTREMELY IMPORTANT TO MAKE THE K(2,2)==1 !!!
}

/**
 * @brief CameraDirectLinearTransformation::computeOpenGLMatrices
 * @param gl_viewport
 * @param znear
 * @param zfar
 */
void CameraDirectLinearTransformation::computeOpenGLMatrices(const Vector4i &gl_Viewport, double znear, double zfar)
{

    // Implementation of http://ksimek.github.io/2013/06/03/calibrated_cameras_in_opengl/
    // with inversion of second column on K and first row of R to match the inverted OpenGL axes when reprojected via the
    // light projector with a mirror
	
	/*
    // If K(3,3) isn't -1 negate the 3rd column because OpenGL camera looks down z axis
    if (K(2,2)>0)
        K.col(2) = -K.col(2);

    // This we need because of OpenGL convention
    K.col(1) = -K.col(1);

    Matrix3d ReflectKY,ReflectKX;
    ReflectKY << 1,     0,      0,
                 0,    -1,      768,
                 0,     0,      1;
	ReflectKX << -1, 0, 1024,
				 0, 1, 0,
		 		 0, 0, 1;

	this->K << (ReflectKY*K).eval();
	
	R.row(0) = -R.row(0);
    R=-R.eval(); // needed because otherwise the determinant is negative.
	*/

	R.row(0) = -R.row(0);
	K.col(1) = -K.col(1);
	R.row(1) = -R.row(1);

	K.col(2) = -K.col(2);

	if (R.determinant() < 0)
		R = -R.eval();


    double A = znear+zfar;
    double B = znear*zfar;

    Eigen::Projective3d Persp;
    Persp.matrix() << K(0,0), K(0,1), K(0,2), 0,
            0,      K(1,1), K(1,2), 0,
            0,      0,      A,      B,
            0,      0,     -1,      0;

    double l=gl_Viewport(0);
    double r=gl_Viewport(2);
    double b=gl_Viewport(1);
    double t=gl_Viewport(3);
    double f=zfar;
    double n=znear;

    Eigen::Affine3d NDC;
    NDC.matrix() << 2.0/(r-l),     0,           0,          -(r+l)/(r-l),
            0,             2.0/(t-b),   0,          -(t+b)/(t-b),
            0,             0,           -2/(f-n),    -(f+n)/(f-n),
            0,             0,           0,          1;

    // Compute the camera position
    this->T = -R*C;

    this->gl_Projection_Matrix = NDC*Persp;
    this->gl_ModelView_Matrix.matrix().topLeftCorner<3,3>().matrix() = R;
    this->gl_ModelView_Matrix.translation().matrix() << -R*C;
    this->gl_ModelViewProjection_Matrix = gl_Projection_Matrix*gl_ModelView_Matrix;

    //cout << "gl_Projection\n" << gl_Projection_Matrix.matrix() << endl;
    //cout << "gl_ModelView_Matrix\n" << gl_ModelView_Matrix.matrix() << endl;
    cout << "PERSP="  << Persp.matrix() << endl;
    cout << "NDC=" << NDC.matrix() << endl;

    // Compute the inverses
    this->gl_ModelViewInverse_Matrix = this->gl_ModelView_Matrix.inverse();
    this->gl_ModelViewProjectionInverse_Matrix = this->gl_ModelViewProjection_Matrix.inverse();
    this->gl_Projection_Inverse_Matrix = this->gl_Projection_Matrix.inverse();
}

/**
 * @brief CameraDirectLinearTransformation::rq3
 * Perform 3 RQ decomposition of matrix A and save them in matrix R and matrix Q
 * http://www.csse.uwa.edu.au/~pk/research/matlabfns/Projective/rq3.m
 * @param A
 * @param R
 * @param Q
 */
void CameraDirectLinearTransformation::rq3(const Matrix3d &_A, Matrix3d &R, Matrix3d& Q)
{
    Matrix3d A=_A; // to allow modification
    double eps=std::numeric_limits<double>::epsilon();
    double c = -A(2,2)/sqrt(pow(A(2,2),2)+pow(A(2,1),2));
    double s = A(2,1)/sqrt(pow(A(2,2),2)+pow(A(2,1),2));
    Matrix3d Qx,Qy,Qz;

    // Find rotation Qx to set A(3,2) to 0
    A(2,2) = A(2,2) + eps;
    Qx <<  1, 0, 0, 0, c, -s, 0, s, c;
    R = A*Qx;

    // Find rotation Qy to set A(3,1) to 0
    R(2,2) = R(2,2) + eps;
    c = R(2,2)/sqrt(pow(R(2,2),2)+pow(R(2,0),2));
    s = R(2,0)/sqrt(pow(R(2,2),2)+pow(R(2,0),2));
    Qy << c, 0, s, 0, 1, 0,-s, 0, c;
    R = R*Qy;

    // Find rotation Qz to set A(2,1) to 0
    R(1,1) = R(1,1) + eps;
    c = -R(1,1)/sqrt(pow(R(1,1),2)+pow(R(1,0),2));
    s =  R(1,0)/sqrt(pow(R(1,1),2)+pow(R(1,0),2));
    Qz << c, -s, 0, s, c, 0, 0, 0, 1;
    R = R*Qz;

    Q = Qz.transpose()*Qy.transpose()*Qx.transpose();

    // Adjust R and Q so that the diagonal elements of R are +ve
    for (int n=0; n<3; n++)
    {
        if (R(n,n)<0)
        {
            R.col(n) = - R.col(n);
            Q.row(n) = - Q.row(n);
        }
    }
}

/**
 * @brief CameraDirectLinearTransformation::loadImages Load the projected pixel coordinates points
 * @param filename
 * @return The pixel coordinates homogenized (3D because (u,v,1 ) )
 */
std::vector<Vector3d> CameraDirectLinearTransformation::loadImages(const string &filename)
{
    std::ifstream is;
    is.open(filename.c_str());
    std::vector<Vector3d> vals;
    double u,v;
    while( (is >> u ) &&  (is >> v)  )
    {
        vals.push_back(Vector3d(u,v,1.0));
    }
    //cerr << "Tot " << vals.size() << " image points" << endl;
    return vals;
}

/**
 * @brief CameraDirectLinearTransformation::loadWorldCoords Load the points of the 3D world
 * @param filename
 * @return The world coordinates in homogenized format (x,y,z,1)
 */
stlalignedvector4d CameraDirectLinearTransformation::loadWorldCoords(const string &filename)
{
    std::ifstream is;
    is.open(filename.c_str());
    stlalignedvector4d vals;
    double x,y,z;
    while( (is >> x ) &&  (is >> y) && (is >> z ) )
    {
        vals.push_back(Vector4d(x,y,z,1.0));
    }
    return vals;
}

/**
 * @brief getReprojectionError
 * @param P
 * @param x
 * @param X
 * @return
 */
double CameraDirectLinearTransformation::getReprojectionError(const Eigen::Matrix<double,3,4> &P, const vector<Vector3d> &x, const stlalignedvector4d &X)
{
    int n=x.size();
    double error=0.0;
    for (int i=0; i<n;i++)
    {
        Vector3d mr = P*X.at(i);
        mr/=mr(2);  // switch back to cartesian coordinates
        double d = ( Vector2d(mr.x(),mr.y()) - Vector2d(x.at(i).x(),x.at(i).y())).norm();
        //cerr << "[" << Vector2d(mr.x(),mr.y()).transpose()  << "],[" << Vector2d(x.at(i).x(),x.at(i).y()).transpose() << "]" << endl;
        error+=d;
    }
    error/=n;
    cerr << "Camera matrix error [px]=" << error << endl;
    return error;
}

/**
 * @brief getReproductionError
 * @param P
 * @param MV
 * @param Viewport
 * @param x
 * @return
 */
double CameraDirectLinearTransformation::getReprojectionErrorOpenGL(const Eigen::Projective3d &P, const Eigen::Affine3d &MV, const Vector4i &viewport, const vector<Vector3d> &x, const stlalignedvector4d &X)
{
    //cout << "== OPENGL REPRODUCTION ERROR ==" << endl;
    int n=x.size();
    double error=0.0;
    for (int i=0; i<n; i++)
    {
        Vector3d point = X.at(i).head<3>();
        Vector3d v = ( P*(MV*point).homogeneous() ).eval().hnormalized();

        Vector2d vPixel(viewport(0) + viewport(2)*(v.x()+1)/2,viewport(1) + viewport(3)*(v.y()+1)/2);
        //cerr << "[" << vPixel.transpose() << "] [" << x.at(i).head<2>().transpose() << "]" << endl;
        error += ( vPixel- x.at(i).head<2>() ).norm();
    }
    error/=n;
    cerr << "OpenGL error [px] =" << error << endl;
    return error;
}

/**
 * @brief CameraDirectLinearTransformation::getCameraCenter
 * @return
 */
const Eigen::Vector3d &CameraDirectLinearTransformation::getCameraCenter() const
{
    return this->C;
}

/**
 * @brief CameraDirectLinearTransformation::getOpenGLModelViewMatrix
 * @return
 */
const Eigen::Affine3d &CameraDirectLinearTransformation::getOpenGLModelViewMatrix()
{
    return this->gl_ModelView_Matrix;
}

/**
 * @brief CameraDirectLinearTransformation::getOpenGLProjectionMatrix
 * @return
 */
const Eigen::Projective3d &CameraDirectLinearTransformation::getOpenGLProjectionMatrix()
{
    return this->gl_Projection_Matrix;
}

/**
 * @brief CameraDirectLinearTransformation::getCameraMatrix
 * @return
 */
const Eigen::Matrix<double,3,4> &CameraDirectLinearTransformation::getCameraMatrix()
{
    return this->P;
}

void CameraDirectLinearTransformation::info()
{
    std::cout << "P=[\n" << this->P << " ]" << endl;
    std::cout << "K=[\n" <<this->K << " ]" << endl;
    std::cout << "R=[\n"<< this->R << " ]" << endl ;
    std::cout << "C=[ " << this->C.transpose() << " ]" <<endl;
    std::cout << "T=[ " << this->T.transpose() << " ]" <<endl;
    std::cout << "Principal point=[ " << this->principalPoint.transpose() << " ]" << endl;
    std::cout << "Principal axis=[ " << this->principalVector.transpose() << " ]" << endl;
    std::cout << "OpenGL Projection=[\n" << this->gl_Projection_Matrix.matrix() << "]" << endl;
    std::cout << "OpenGL ModelViewMatrix=[\n" << this->gl_ModelView_Matrix.matrix() << "]" << endl;
}

const stlalignedvector4d &CameraDirectLinearTransformation::getPoints3D() const
{
    return this->points3D;
}

//When putting these values in the projection matrix:
/*
P.row(0) << 3.53553E2, 3.39645E2, 2.77744E2, -1.44946E6;
P.row(1) << -1.03528E2, 2.33212E1, 4.59607E2, -6.32525E5;
P.row(2) << 7.07107E-1, -3.53553E-1, 6.12372E-1, -9.18559E2;
*/

//one should obtain the following values:
/*
Intrinsinc camera matrix=
0.0144213 -0.000328564   0.00343275
-1.0842e-19   0.00709935   0.00254141
      -0           -0  8.54968e-06

Extrinsic camera matrix=
0.0887467 -0.0363712   -0.99539
0.994285  0.0627698  0.0863546
0.0593396  -0.997365   0.041734

Camera Center C=-16.6029   255.09 -20.1428

Camera T= -9.29854 2.23552 256.243

Camera Principal axis= 0.0593396 -0.997365  0.041734

Camera Principal point= 401.506 297.252
OpenGL ModelView=
0.0887467  0.0363712    0.99539   -9.29854
0.994285 -0.0627698 -0.0863546    2.23552
0.0593396   0.997365  -0.041734    256.243
     0          0          0          1

OpenGL Projection=
3.83545e-05 8.73841e-07    0.999991           0
      0 2.95806e-05   -0.999989           0
      0           0     -1.0002    -0.20002
      0           0          -1           0

OpenGL ModelViewProjection=
0.0593433   0.997357 -0.0416955    256.241
-0.0593095  -0.997356   0.041731   -256.241
-0.0593514  -0.997565  0.0417423   -256.495
-0.0593396  -0.997365   0.041734   -256.243
*/
