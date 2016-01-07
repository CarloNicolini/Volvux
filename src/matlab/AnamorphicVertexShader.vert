uniform mat4 ANA;
void main()
{
vec4 v = gl_Vertex;
float z=v.z;
v.z = v.y;
v.y=z;
v = ANA*v;
gl_Position = gl_ModelViewProjectionMatrix*v;
gl_FrontColor = gl_Color;
}
