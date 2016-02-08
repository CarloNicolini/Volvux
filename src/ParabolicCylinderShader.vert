varying vec3 texture_coordinate;
uniform float curvature;
uniform float zToXYTextureRatio;
void main()
{
    vec4 v=gl_Vertex;
    v.y = curvature*(v.y*v.y)-curvature;
    texture_coordinate = vec3(((v.xy+1.0)*0.5),v.z*zToXYTextureRatio);
    gl_Position = gl_ModelViewProjectionMatrix*v;
}
