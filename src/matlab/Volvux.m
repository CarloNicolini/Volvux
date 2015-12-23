function Volvux

% Load the calibration data
X3D=[ 0 0 0 1 ;
    -35.5  35.5     0     1 ;
    35.5 35.5    0    1 ;
    35.5 -35.5     0     1 ;
    -35.5 -35.5     0     1 ;
    -25  25  10   1 ;
    25 25 10  1 ;
    25 -25  10   1 ;
    -25 -25  10   1 ;
    ];

x2D=[ 512 384   1 ;
    419 474   1 ;
    409 294   1 ;
    589 294   1 ;
    589 474   1 ;
    449 441   1 ;
    449 321   1 ;
    569 321   1 ;
    569 441   1 ;
    ];

%% Compute the camera matrix P
[P,A,U,S,V] = homography(x2D',X3D');


%% Compute the OpenGL matrices from the camera matrix with znear and zfar specified
znear=1;
zfar=1E6;
gl_Viewport=[0 0 1024 768];
[gl_Projection_matrix,gl_Modelview_matrix] = getOpenGLMatrices(P,gl_Viewport(3),gl_Viewport(4),znear,zfar);
gl_MVP = gl_Projection_matrix*gl_Modelview_matrix;
gl_IMVP = inv(gl_MVP);
HELICOID=load('~/workspace/Volvux/data/objmodels/helicoid.vert');

%% Make the anamorphic transformation to delete the projection of helicoid points 

ANA = [1   0  0  0;
     0   1  0  0;
     0   0  1  0;
     0   0  -1/norm(gl_Modelview_matrix(1:3,4))  1];
HELICOIDp = project(inv(ANA),[HELICOID ones(size(HELICOID,1),1)]);
 


% Now project the helicoid points in a PTB window
VisualizeHelicoid(gl_Projection_matrix,gl_Modelview_matrix,HELICOIDp);