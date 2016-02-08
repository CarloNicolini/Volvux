const vec3 X = vec3(1.0,0.0,0.0);
const vec3 Y = vec3(0.0,1.0,0.0);
const vec3 Z = vec3(0.0,0.0,1.0);
varying vec3 texture_coordinate;
uniform sampler3D my_color_texture;
uniform vec4 uniformColor;
uniform float curvature;
uniform float thickness;
varying vec4 pvertex;

void main()
{
	vec4 uniformColor = vec4(1.0,1.0,1.0,1.0);
    vec4 finalColor = uniformColor*texture3D(my_color_texture, texture_coordinate);

    if ( texture_coordinate.x <=0.0 || texture_coordinate.x >= 1.0 || texture_coordinate.z <= 0.0 || texture_coordinate.z >= 1.0 )
        gl_FragColor =vec4(0.0,0.0,0.0,1.0); //Can be uniformColor to color again the thing
    
	
	float parametricSurfaceEquation = (pvertex.x*pvertex.x)/curvature;
    float normalLength = sqrt(1.0+(2.0*pvertex.x/curvature)*(2.0*pvertex.x/curvature));
    if ( abs((pvertex.y - parametricSurfaceEquation)/normalLength) <= thickness)
    {
		gl_FragColor = finalColor;
    }
    else
     {
		// color the vertices outside that small volume around the surface to black
        gl_FragColor = vec4(0.0,0.0,0.0,1.0);
     }
}
