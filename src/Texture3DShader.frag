const vec3 X = vec3(1.0,0.0,0.0);
const vec3 Y = vec3(0.0,1.0,0.0);
const vec3 Z = vec3(0.0,0.0,1.0);
varying vec3 texture_coordinate;
uniform sampler3D my_color_texture;
uniform vec4 uniformColor;
void main()
{
    vec4 uniformColor = vec4(1.0,1.0,1.0,1.0);
    vec4 finalColor;
    //finalColor = (texture3D(my_color_texture, texture_coordinate+X)+texture3D(my_color_texture-X, texture_coordinate))*0.5
    //        +(texture3D(my_color_texture, texture_coordinate+Y)+texture3D(my_color_texture-Y, texture_coordinate))*0.5
    //        +(texture3D(my_color_texture, texture_coordinate+Z)+texture3D(my_color_texture-Z, texture_coordinate))*0.5;
    if ( texture_coordinate.x <=0.0 || texture_coordinate.x >= 1.0 || texture_coordinate.z <= 0.0 || texture_coordinate.z >= 1.0 )
        gl_FragColor =vec4(0.0,0.0,0.0,1.0); //Can be uniformColor to color again the thing
    else
        gl_FragColor = uniformColor*texture3D(my_color_texture, texture_coordinate);
}
