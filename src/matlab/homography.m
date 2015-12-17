function [P,A,U,S,V] = homography(x,X)
% x is a matrix 3 x k
% X is a matrix 4 x k

if (size(x,2) ~= size(X,2))
	error('points are in different number');
end

n = size(x,2);

A=zeros(2*n,12);

for i=1:n-1
    m = x(:,i);
    M = X(:,i)';
    A(2*i,:) = [0 0 0 0 -m(3)*M, m(2)*M ];
    A(2*i+1,:) = [ m(3)*M 0 0 0 0 -m(1)*M ];
end

[U,S,V] = svd(A);

k=1;
for i=1:3
    for j=1:4
        t = V(k,12);
        P(i,j)=t;
        k=k+1;
    end
end
