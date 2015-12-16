function y=anamorphicdeform2(l,r,b,t,n,f,x)

P=glfrustum(l,r,b,t,n,f);

IP=inv(P);

for i=1:size(x,1)
    xp(i,:)=project(IP*IP,x(i,:)');
    xp(i,:) = rescaleanamorph(l,r,b,t,n,f,xp(i,:));
end

y = xp;