function y=ndc2pix(p,viewport,f,n)

x=viewport(1);
y=viewport(2);
w=viewport(3);
h=viewport(4);

y(1) = w/2*p(1)+(x+w/2);
y(2) = h/2*p(2)+(y+h/2);
y(3) = (f-n)/2*p(3)+(f+n)/2;