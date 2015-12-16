function a = rescaleanamorph(l,r,b,t,n,f,C)
x=C(1);
y=C(2);
z=C(3);

anascale = [ -(((l + r)*(l - r))/(4*n^2) - (x*(l - r)^2)/(4*n^2) - ((f + n)*(l + r))/(4*f*n^2) + (z*(l + r)*(f - n))/(4*f*n^2))/((f - n)/(2*f*n) + (f + n)^2/(4*f^2*n^2) - (z*(f + n)*(f - n))/(4*f^2*n^2)), ...
            ((y*(b - t)^2)/(4*n^2) - ((b + t)*(b - t))/(4*n^2) + ((f + n)*(b + t))/(4*f*n^2) - (z*(b + t)*(f - n))/(4*f*n^2))/((f - n)/(2*f*n) + (f + n)^2/(4*f^2*n^2) - (z*(f + n)*(f - n))/(4*f^2*n^2)),...
            -((f + n)/(2*f*n) - (z*(f - n))/(2*f*n))/((f - n)/(2*f*n) + (f + n)^2/(4*f^2*n^2) - (z*(f + n)*(f - n))/(4*f^2*n^2)),...
            1];
a = C./anascale;
a = a/a(4);