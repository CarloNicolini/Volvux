function C=frustumcorners(l,r,b,t,n,f)
C = [l,b,-n,1;
l,t,-n,1;
r,b,-n,1;
r,t,-n,1;
l,b,-f,1;
l,t,-f,1;
r,b,-f,1;
r,t,-f,1];
