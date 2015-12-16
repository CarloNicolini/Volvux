function y=ndc2pix(ndc,viewport,f,n)

offsetX=viewport(1);
offsetY=viewport(2);
w=viewport(3);
h=viewport(4);

y = [ (ndc(1)+1)*(w)+offsetX, (ndc(2)+1)*(h)+offsetY ];