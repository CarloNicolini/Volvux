function decomposePmatrix(P)

M=P(1:3,1:3);
m3 = M(3,:)';

P123 = [P(:,2),P(:,3),P(:,4)];
P023 = [P(:,1),P(:,3),P(:,4)];
P013 = [P(:,1),P(:,2),P(:,4)];
P012 = [P(:,1),P(:,2),P(:,3)];

X = det(P123);
Y = -det(P023);
Z = det(P013);
T = -det(P012);

C = [X,Y,Z]/T;

princ_point = (M*m3);
princ_point = princ_point/princ_point(end); princ_point=princ_point(1:2);

princ_vector = det(M)*m3;
princ_vector = princ_vector/norm(princ_vector);

R = eye(3,3);
[K,R] = rq3(M);
K=K/K(3,3);
t=-R*C;

