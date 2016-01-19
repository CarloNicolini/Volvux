function H = getReflectionMatrix(N)
N=N(:);
I=eye(3);
H=I-2*N*(N');

