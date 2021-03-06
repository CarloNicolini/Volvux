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
    void init(const std::vector<Eigen::Vector3d> &x, const stlalignedvector4d &X, bool decomposeProjectionMatrix = false, bool computeOpenGLMatrices = false, double x0 = 0.0, double y0 = 0.0, int width = 1024, int height = 768, double znear = 0.1, double zfar = 1000.0);

    double getReprojectionError(const Eigen::Matrix<double, 3, 4> &P, const vector<Vector3d> &x, const stlalignedvector4d &X);
    double getReproductionErrorOpenGL(const Eigen::Projective3d &P, const Eigen::Affine3d &MV, const Vector4i &viewport, const vector<Vector3d> &x, const stlalignedvector4d &X);

    const Eigen::Vector3d &getCameraCenter() const;
    // For backward compatibility
    const Eigen::Vector3d &getCameraPositionWorld() const
    {
        return getCameraCenter();
    }

    void computeOpenGLProjectionMatrix(double x0, double y0, double width, double height, double znear, double zfar, bool windowCoordsYUp=false);

    void computeOpenGLModelViewMatrix(const Eigen::Matrix3d &Rot, const Vector3d &trans);

    void decomposePMatrix(const Eigen::Matrix<double,3,4> &P);

    const Eigen::Matrix<double,3,4> &getProjectionMatrix()
    {
        return this->P;
    }

    const Eigen::Matrix3d &getIntrinsicMatrix()
    {
        eigen_assert(DecompositionComputed && "You did not asked for the P matrix decomposition, explicitly ask in constructor");
        return this->K;
    }

    const Eigen::Matrix3d &getRotationMatrix()
    {
        eigen_assert(DecompositionComputed && "You did not asked for the P = K[R,t] matrix decomposition, explicitly ask in constructor");
        return R;
    }

    const Eigen::Affine3d &getOpenGLModelViewMatrix()
    {
        eigen_assert(DecompositionComputed && "You did not asked for the P = K[R t] matrix decomposition, explicitly ask in constructor");
        eigen_assert(ModelViewProjectionInitialized && "You did not asked for the OpenGL ModelViewProjection matrix to be computed, explicitly ask in constructor and provide appropriate parameters");
        return this->gl_ModelView_Matrix;
    }

    const Eigen::Projective3d &getOpenGLProjectionMatrix()
    {
        eigen_assert(DecompositionComputed && "You did not asked for the P = K[R t] matrix decomposition, explicitly ask in constructor");
        eigen_assert(ModelViewProjectionInitialized && "You did not asked for the OpenGL ModelViewProjection matrix to be computed, explicitly ask in constructor and provide appropriate parameters");
        return this->gl_Projection_Matrix;
    }

    /**
     * @brief CameraDirectLinearTransformation::getT
     * @return The location of the world origin in camera coordinates.
     *  The sign of tx,ty,tz should reflect where the world origin appears in the camera (left/right of center, above/below center, in front/behind camera, respectively).
     */
    const Eigen::Vector3d & getT()
    {
        eigen_assert(DecompositionComputed && "You did not asked for the P = K[R t] matrix decomposition, explicitly ask in constructor");
        eigen_assert(ModelViewProjectionInitialized && "You did not asked for the OpenGL ModelViewProjection matrix to be computed, explicitly ask in constructor and provide appropriate parameters");
        return t;
    }

    const Eigen::Projective3d &getOpenGLModelViewProjectionMatrix()
    {
        eigen_assert(DecompositionComputed && "You did not asked for the P = K[R t] matrix decomposition, explicitly ask in constructor");
        eigen_assert(ModelViewProjectionInitialized && "You did not asked for the OpenGL ModelViewProjection matrix to be computed, explicitly ask in constructor and provide appropriate parameters");
        return this->gl_ModelViewProjection_Matrix;
    }

    const Vector2d &getPrincipalPoint()
    {
        eigen_assert(DecompositionComputed && "You did not asked for the P = K[R t] matrix decomposition, explicitly ask in constructor");
        return this->principalPoint;
    }

    const Vector3d &getPrincipalAxis()
    {
        eigen_assert(DecompositionComputed && "You did not asked for the P = K[R t] matrix decomposition, explicitly ask in constructor");
        return this->principalVector;
    }

    const Eigen::Projective3d &getOpenGLModelViewProjectionInverseMatrix()
    {
        eigen_assert(DecompositionComputed && "You did not asked for the P = K[R t] matrix decomposition, explicitly ask in constructor");
        eigen_assert(ModelViewProjectionInitialized && "You did not asked for the OpenGL ModelViewProjection matrix to be computed, explicitly ask in constructor and provide appropriate parameters");
        return gl_ModelViewProjectionInverse_Matrix;
    }

    const Eigen::Projective3d &getOpenGLProjectionInverseMatrix()
    {
        eigen_assert(DecompositionComputed && "You did not asked for the P = K[R t] matrix decomposition, explicitly ask in constructor");
        eigen_assert(ModelViewProjectionInitialized && "You did not asked for the OpenGL ModelViewProjection matrix to be computed, explicitly ask in constructor and provide appropriate parameters");
        return gl_ProjectionInverse_Matrix;
    }

    const Eigen::Affine3d &getOpenGLModelViewInverseMatrix()
    {
        eigen_assert(DecompositionComputed && "You did not asked for the P = K[R t] matrix decomposition, explicitly ask in constructor");
        eigen_assert(ModelViewProjectionInitialized && "You did not asked for the OpenGL ModelViewProjection matrix to be computed, explicitly ask in constructor and provide appropriate parameters");
        return gl_ModelViewInverse_Matrix;
    }

    const Projective3d &getOpenGLOrthographicProjectionMatrix()
    {
        eigen_assert(DecompositionComputed && "You did not asked for the P = K[R t] matrix decomposition, explicitly ask in constructor");
        eigen_assert(ModelViewProjectionInitialized && "You did not asked for the OpenGL ModelViewProjection matrix to be computed, explicitly ask in constructor and provide appropriate parameters");
        return this->gl_Orthographic_Projection_Matrix;
    }

    void build_opengl_projection_for_intrinsics(double znear, double zfar);

public:
    void info();
    std::vector<Eigen::Vector3d> points2D;
    stlalignedvector4d points3D;

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

    // OpenGL computed matrices
    /**
     * @brief gl_ModelView_Matrix
     */
    Affine3d gl_ModelView_Matrix;
    /**
     * @brief gl_Projection_Matrix
     */
    Projective3d gl_Projection_Matrix;

    /**
     * @brief gl_Orthographic_Projection_Matrix
     */
    Projective3d gl_Orthographic_Projection_Matrix;

    /**
     * @brief ModelViewProjectionMatrix The OpenGL matrix computed starting from P
     */
    Eigen::Projective3d gl_ModelViewProjection_Matrix;

    // and their inverses
    /**
     * @brief gl_ModelViewInverse_Matrix
     */
    Eigen::Affine3d gl_ModelViewInverse_Matrix;
    /**
     * @brief gl_ProjectionInverse_Matrix
     */
    Eigen::Projective3d gl_ProjectionInverse_Matrix;
    /**
     * @brief gl_ModelViewProjectionInverse_Matrix
     */
    Eigen::Projective3d gl_ModelViewProjectionInverse_Matrix;

    Eigen::Vector4i viewport;

    bool ModelViewProjectionInitialized;
    bool DecompositionComputed;
};

#endif
