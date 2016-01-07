uniform mat4 ANA;
void main()
{
    vec4 v = gl_Vertex;
    gl_Position = gl_ModelViewProjectionMatrix*v;
    gl_FrontColor = gl_Color;
}
