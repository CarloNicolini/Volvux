varying vec3 texture_coordinate;
uniform float curvature;
uniform float zToXYTextureRatio;
void main()
{
    vec4 v=gl_Vertex;
    v.z = curvature*(v.x*v.x)-curvature;
    v.z = -v.z;
    texture_coordinate = vec3(((v.xy+1.0)*0.5),v.z*zToXYTextureRatio);
    gl_Position = gl_ModelViewProjectionMatrix*v;
}
