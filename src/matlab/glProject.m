function p = glProject(gl_ModelViewProjectionMatrix,gl_Viewport,gl_Vertex,znear,zfar)

% X is the world position vector
ndc = gl_ModelViewProjectionMatrix*gl_Vertex;
ndc = ndc/ndc(4);

%offsetX=0;
%offsetY=0;

xndc = ndc(1);
yndc = ndc(2);
zndc = ndc(3);

% http://www.songho.ca/opengl/gl_transform.html
x = gl_Viewport(1);
y = gl_Viewport(2);
w = gl_Viewport(3);
h = gl_Viewport(4);

p = [ w/2*xndc + (x + w/2) , h/2*yndc + (y+h/2),  (zfar-znear)/2*zndc + (zfar+znear)/2 ];