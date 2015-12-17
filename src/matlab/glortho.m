function P = glortho(l,r,b,t,n,f)

w = r-l;
h = t-b;

P = [ 2/w   0       0         -(r+l)/(w);
      0     2/h     0,        -(t+b)/(h);
      0     0       -2/(f-n)  -(f+n)/(f-n);
      0     0       0         1 ];