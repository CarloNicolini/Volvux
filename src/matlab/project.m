function y=project(P,x)
for i=1:size(x,1)
    y(i,:) = P*x(i,:)';
    y(i,:) = y(i,:)/y(i,4);
end