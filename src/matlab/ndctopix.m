function y=ndc2pix(x,viewport,f,n)

offsetX=viewport(1);
offsetY=viewport(2);
w=viewport(3);
h=viewport(4);

for i=1:size(x,1)
    ndc = x(i,:);
    y(i,:) = [ (ndc(1)+1)*(w)+offsetX, (ndc(2)+1)*(h)+offsetY ];
end