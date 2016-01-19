function [gl_Projection, gl_ModelView,K,R,C,pp,pv] = getOpenGLMatrices(K,R,C,width,height,near,far)

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