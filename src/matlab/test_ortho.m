clear all
r=4;
l=-4;
t=5;
b=-5;
f=8;
n=0.5;

Portho = orthographicprojectionmatrix(r,l,t,b,n,f)
Ppersp = projectionmatrix(r,l,t,b,n,f);
% 
Portho2 = orthographicFromPerspective(Ppersp,f,n)

PO = [ 0.0211449            0            0     -3.03225;
           0    0.0267444            0      4.22439;
           0            0 -0.000133333           -1;
           0            0            0            1];

P = [3.17174 0.615555  3.03225        0;
       0  4.01166 -4.22439        0;
       0        0       1    -0.02;
       0        0       -1        0];
   
c = [0; 0; 0; 1];

ndc = P*c;
ndc = ndc(1:3)/ndc(4);

x=x(1:2);
