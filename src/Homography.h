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

#ifndef _HOMOGRAPHY_H_
#define _HOMOGRAPHY_H_

#include <iostream>
#include <vector>
#include <Eigen/Core>
#include <Eigen/StdVector>
#include <Eigen/SVD>
#include <Eigen/Geometry>

using namespace std;
using namespace Eigen;

// IMPORTANT http://eigen.tuxfamily.org/dox/group__TopicStlContainers.html
typedef std::vector<Eigen::Vector4d, Eigen::aligned_allocator<Eigen::Vector4d> > stlalignedvector4d;

/*
#ifdef __WIN32
#define EIGEN_DONT_Eigen::VectorIZE
#define EIGEN_DISABLE_UNALIGNED_ARRAY_ASSERT
#define EIGEN_DONT_ALIGN_STATICALLY
#endif
*/
//EIGEN_DEFINE_STL_VECTOR_SPECIALIZATION(Vector3d)
//EIGEN_DEFINE_STL_VECTOR_SPECIALIZATION(Vector4d)

/**
 * @brief The CameraDirectLinearTransformation class
 */
class CameraDirectLinearTransformation
{
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    CameraDirectLinearTransformation();
    // Utility constructors
    CameraDirectLinearTransformation(const std::vector<Eigen::Vector3d> &x, const stlalignedvector4d &X, const Vector4i &gl_Viewport, double x0=0.0, double y0=0.0, int width=640, int height=480, double znear=0.1, double zfar=1000.0);

    void init(const std::vector<Eigen::Vector3d> &x, const stlalignedvector4d &X, const Vector4i &gl_Viewport, double znear = 0.1, double zfar = 1000.0);

    std::vector<Vector3d> loadImages(const string &filename);
    stlalignedvector4d loadWorldCoords(const string &filename);

    double getReprojectionError(const Eigen::Matrix<double, 3, 4> &P, const vector<Vector3d> &x, const stlalignedvector4d &X);
    double getReprojectionErrorOpenGL(const Eigen::Projective3d &P, const Eigen::Affine3d &MV, const Vector4i &viewport, const vector<Vector3d> &x, const stlalignedvector4d &X);

    void decomposePMatrix(const Eigen::Matrix<double,3,4> &P);

    void computeOpenGLMatrices(const Vector4i& gl_viewport, double znear, double zfar);

    const Eigen::Matrix<double,3,4> &getCameraMatrix();
    const Eigen::Vector3d &getCameraCenter() const;
    const Eigen::Vector3d &getCameraPositionWorld() const;
    const Eigen::Affine3d &getOpenGLModelViewMatrix();
    const Eigen::Projective3d &getOpenGLProjectionMatrix();
    const Eigen::Projective3d &getOpenGLModelViewProjectionInverseMatrix() const;
    const Eigen::Projective3d &getOpenGLProjectionInverseMatrix() const;
    const Eigen::Affine3d &getOpenGLModelViewInverseMatrix() const;
    void info();

private:
    void rq3(const Matrix3d &A, Matrix3d &R, Matrix3d& Q);
    /**
     * @brief P The matrix x = P X that projects 3D world homogenous points to their images
     */
    Eigen::Matrix<double,3,4> P;
    /**
     * @brief R The orthogonal rotation matrix obtained decomposing P, it's part of the extrinsic pose P= K [R t]
     */
    Eigen::Matrix3d R;
    /**
     * @brief K The intrinsic matrix P = K [R t]
     */
    Eigen::Matrix3d K;
    /**
     * @brief t The camera center in camera coordinates
     */
    Eigen::Vector3d C;

    /**
     * @brief t
     */
    Eigen::Vector3d t;

    /**
     * @brief principalPoint The principal point
     */
    Vector2d principalPoint;
    /**
     * @brief principalVector
     */
    Vector3d principalVector;
    /**
     * @brief gl_ModelView_Matrix
     */
    Affine3d gl_ModelView_Matrix;
    /**
     * @brief gl_Projection_Matrix
     */
    Projective3d gl_Projection_Matrix;
    /**
     * @brief ModelViewProjectionMatrix The OpenGL matrix computed starting from P
     */
    Eigen::Projective3d gl_ModelViewProjection_Matrix;
    /**
     * @brief gl_ModelViewInverse_Matrix
     */
    Eigen::Affine3d gl_ModelViewInverse_Matrix;
    /**
     * @brief gl_ProjectionInverse_Matrix
     */
    Eigen::Projective3d gl_Projection_Inverse_Matrix;
    /**
     * @brief gl_ModelViewProjectionInverse_Matrix
     */
    Eigen::Projective3d gl_ModelViewProjectionInverse_Matrix;

    /**
     * @brief points2D The measured projected points
     */
    std::vector<Eigen::Vector3d> points2D;

    /**
     * @brief points3D The corresponding world points
     */
    stlalignedvector4d points3D;
};

#endif
