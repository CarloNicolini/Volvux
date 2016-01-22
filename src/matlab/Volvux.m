% Load the calibration data
clear all;
% X3D=[ 0 0 0 1 ;
%     -35.5  35.5     0     1 ;
%     35.5 35.5    0    1 ;
%     35.5 -35.5     0     1 ;
%     -35.5 -35.5     0     1 ;
%     -25  25  10   1 ;
%     25 25 10  1 ;
%     25 -25  10   1 ;
%     -25 -25  10   1 ;
%     ];
% x2D=[ 512 384   1 ;
%     419 474   1 ;
%     409 294   1 ;
%     589 294   1 ;
%     589 474   1 ;
%     449 441   1 ;
%     449 321   1 ;
%     569 321   1 ;
%     569 441   1 ;
%     ];

WB=70;
WT=50;
HZ=-10;

X3D = [ 0	0	0;
        -WT/2 -WT/2 HZ;
        +WT/2 -WT/2 HZ;
        +WT/2 +WT/2 HZ;
        -WT/2 +WT/2 HZ;
        -WB/2 -WB/2  0;
        +WB/2 -WB/2  0;
        +WB/2 +WB/2  0;
        -WB/2 +WB/2  0;
        ];
    
X3D=[X3D ones(9,1)];
x2D = [512 374;
438 301;
581 299;
580 445;
439 443;
401 264;
621 265;
617 485;
403 486 ];
x2D=[x2D ones(9,1)];

%% Compute the camera matrix P
[P,A,U,S,V] = homography(x2D',X3D');

%% Evaluate camera error
for i=1:9
    p(:,i) = P*(X3D(i,:)');
    p(:,i) = p(:,i)/p(3,i);
end

err=0;
for i=1:9
    err = err + norm(p(:,i)-x2D(i,:)');
end
fprintf('Camera matrix error = %f\n',err);

%% Compute the OpenGL matrices from the camera matrix with znear and zfar
%% specified
znear=1;
zfar=1E6;
gl_Viewport=[0 0 1024 768];
[K,R,C] = getCameraIntrinsicExtrinsic(P);

[gl_Projection_matrix,gl_Modelview_matrix] = getOpenGLMatrices(K,R,C,gl_Viewport(3),gl_Viewport(4),znear,zfar);

gl_MVP = gl_Projection_matrix*gl_Modelview_matrix;
gl_IMVP = inv(gl_MVP);

%% Make the anamorphic transformation to delete the projection of helicoid points
% ANA = [1   0  0  0;
%      0   1  0  0;
%      0   0  1  0;
%      0   0  -1/norm(gl_Modelview_matrix(1:3,4))  1];
% 
% HELICOIDp = project(inv(ANA),[HELICOID ones(size(HELICOID,1),1)]);

 
% Now project the helicoid points in a PTB window
% To check if calibration is OK
VisualizeCalibration(gl_Projection_matrix,gl_Modelview_matrix,X3D(:,1:3),x2D(:,1:2));

% To show the HELICOID DOTS
%HELICOID=load('../../data/objmodels/helicoid.vert');
%VisualizeHelicoid(gl_Projection_matrix,gl_Modelview_matrix,HELICOID(:,1:3),eye(4));