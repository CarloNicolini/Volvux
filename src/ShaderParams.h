#ifndef SHADERPARAMS_H
#define SHADERPARAMS_H


struct ShaderParams
{
    glsl::glShader *shader;
};


struct ParabolaParameters : ShaderParams
{
    double curvature;
    double centerX,centerY,centerZ;
};

struct ParabolicCylinderParameters : ShaderParams
{
    double curvature;
    double centerX,centerY,centerZ;
};

struct EllipticCylinderParameters : ShaderParams
{
    double axisX,axisZ;
    double height;
};

struct EllipsoidParameters : ShaderParams
{
    double axisX,axisY,axisZ;
};

struct ConeParameters : ShaderParams
{
    double c;
};

struct CubeParameters : ShaderParams
{
    double edge;
};

#endif // SHADERPARAMS_H

