function P=glfrustum(l,r,b,t,n,f)

P = [ 2*n/(r-l) 0       (r+l)/(r-l)  0;
      0     2*n/(t-b)   (t+b)/(t-b)  0;
      0     0       (n+f)/(n-f)  2*f*n/(n-f);
      0     0       -1           0];
  