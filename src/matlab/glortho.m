 function P = glortho(l,r,b,t,n,f)


P = [ 2/(r-l)   0       0         -(r+l)/(r-l);
      0     2/(t-b)     0,        -(t+b)/(t-b);
      0     0       -2/(f-n)  -(f+n)/(f-n);
      0     0       0         1 ];