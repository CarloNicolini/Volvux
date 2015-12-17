clear all;
close all;


l=-3;
r=3;

b=-2.5;
t=2.5;

n=6;
f=154.4;

% far fr
% FRUSTUM 2D
%  A          B
%  o__________o   (plane at -f)
%   \         /
%    \       /
% C   0_____0   D   (plane at -n)
%
%
%        o-----> +x
%        |
%        |
%        v +z
% A=[ f*(r-l)/(2*n) 0 -f ];
% B=[ -f*(r-l)/(2*n) 0 -f ];
% C=[ l 0 -n];
% D=[ r 0 -n];
% then the same can be made on y-axis just by changing r,l with t,b


p = [r 0 -n 1;
     l 0 -n 1;
     f*(r-l)/(2*n) 0 -f 1;
     -f*(r-l)/(2*n) 0 -f 1];

viewport = [0 0 1024 768];
P = glfrustum(l,r,b,t,n,f);
F = frustumcorners(l,r,b,t,n,f);
IP = inv(P);
Pp = project(P,p)
