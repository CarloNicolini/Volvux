uniform float step;
varying vec3 texture_coordinate;
uniform float objSize;
//uniform float thickness;
//uniform float curvature;
varying vec4 pvertex;
uniform vec3 objOffset;
void main()
{
    vec4 v=gl_Vertex;
    // This is to rotate the object
    //v.xz = vec2(cos(step)*v.x+sin(step)*v.z,-sin(step)*v.x+cos(step)*v.z);
    // Compute the z position given x and y on a circular domain of radius 1 (diameter 2)
    texture_coordinate = vec3(((v.xz-objOffset.xz)/objSize+1.0)*0.5, ((v.y-objOffset.y)/objSize+1.0)*0.5);
    //texture_coordinate= vec3(   ((v.xz-objOffset.xz)/objSize+1.0)*0.5, ((v.y-objOffset.y)/objSize+1.0)*0.5);
    gl_Position = gl_ModelViewProjectionMatrix*v;
    pvertex = v;
}