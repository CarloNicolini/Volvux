clear all
syms l r t b n f x y z L real

Corners = [l,b,-n,1;
l,t,-n,1;
r,b,-n,1;
r,t,-n,1;
l,b,-f,1;
l,t,-f,1;
r,b,-f,1;
r,t,-f,1];


Cube = [L L L 1;
    L -L L 1;
    -L L L 1;
    -L -L L 1;
    L L -L 1;
    L -L -L 1;
    -L L -L 1;
    -L -L -L 1];

P = [ 2*n/(r-l) 0       (r+l)/(r-l)  0;
      0     2*n/(t-b)   (t+b)/(t-b)  0;
      0     0       (n+f)/(n-f)  2*f*n/(n-f);
      0     0       -1           0];
  
IP = inv(P);

p = [ x y z 1];

AC = anamorphicdeform(P,p');