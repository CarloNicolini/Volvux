function P = homography(x,X)

n = size(x,2);

K=zeros(3,3); % intrinsic matrix
P=zeros(3,4);
R=zeros(3,3); % rotation matrix

glModelView = zeros(4,4);
glProjection = zeros(4,4);
glModelViewProjection = zeros(4,4);

A=zeros(2*n,12);
for i=1:n
    m = x(i,:);
    M = X(i,:);
    A(2*i,:) = [0,0,0,0,-m(3)*M, m(2)*M] ;
    A(2*i+1,:) = [ m(3)*M,0,0,0,0,-m(1)*M];
end

[U,S,V] = svd(A);
k=1;
for i=1:3
    for j=1:4
        t = V(k,11);
        P(i,j)=t;
        k=k+1;
    end
end