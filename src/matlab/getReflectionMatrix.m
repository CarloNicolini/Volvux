function H = getReflectionMatrix(N)

H=eye(3)-2*N*N';
