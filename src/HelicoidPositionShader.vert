uniform float step;
uniform float objSize;
uniform vec3 objOffset;
//uniform float thickness;
//uniform float curvature;
varying vec3 texture_coordinate;
varying vec4 pvertex;

vec2 rotateZ(vec2 P, float angle)
{
	mat2 R = mat2(cos(angle),-sin(angle),
						sin(angle), cos(angle));
	vec2 PR = R*P;
	
	return PR;
}

void main()
{
    vec4 v=gl_Vertex;
	//if (v.z>120)
		//v.z=120;
    // This is to rotate the object
	v.xy = rotateZ(v.xy, step);
    // Compute the z position given x and y on a circular domain of radius 1 (diameter 2)
    texture_coordinate = vec3(((v.xy-objOffset.xy)/objSize+1.0)*0.5, ((v.z-objOffset.z)/objSize+1.0)*0.5);
    //texture_coordinate= vec3(   ((v.xz-objOffset.xz)/objSize+1.0)*0.5, ((v.y-objOffset.y)/objSize+1.0)*0.5);
    gl_Position = gl_ModelViewProjectionMatrix*v;
    pvertex = v;
}
