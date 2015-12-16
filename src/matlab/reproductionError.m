function e = reproductionError(A,x,X)

e = 0;

for i=1:size(x,1)
    e = e + norm( x(i,1:2) - size( hnormalized( A*X(i,:)')));
end
