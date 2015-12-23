function [gl_Projection, gl_ModelView,K,R,C,pp,pv] = getOpenGLMatrices(cameraMatrix,width,height,near,far,invertStruct)

[K,R,C,pp,pv]=decomposePmatrix(cameraMatrix);

% If K(3,3) isn't -1 negate the 3rd column because OpenGL camera looks down z axis
if K(3,3)>0
    K(:,3) = -K(:,3);
end
% This we need because of OpenGL convention
K(:,2)=-K(:,2); %working
R(1,:)=-R(1,:); %working
R=-R;

% Check that R is right handed, if not give warning
if dot(cross(R(:,1), R(:,2)), R(:,3)) < 0
    warning('Note that rotation matrix is left handed');
end

% K is now in the form
% K = [a    s   -x0 ;
%      0    b   -y0 ;
%      0    0   -1 ];

% Make a Persp matrix like this

% Persp = [a     s     -x0     0;
%          0     b     -y0     0;
%          0     0      A      B;
%          0     0      -1     0];

A = near+far;
B = near*far;

Persp = [K(1,1)    K(1,2)    K(1,3)   0;
    0         K(2,2)    K(2,3)   0;
    0         0         A        B;
    0         0         -1       0];

% The new third row preserve the ordering of Z-values while mapping -near and -far
% onto themselves (after normalizing by w).
% The result is that points between the clipping planes
% remain between clipping planes after multiplication by Persp.

l=0;
r=width;
b=0;
t=height;

NDC = glortho(l,r,b,t,near,far);

gl_Projection = NDC*Persp;
T = -R*C;
gl_ModelView = eye(4,4);
gl_ModelView(1:3,1:3) = R;
gl_ModelView(1:3,4)= -R*C;
%
% K
% R
% C
% T
% NDC
% Persp
% gl_Projection
% gl_ModelView
% C
% pp
% pv