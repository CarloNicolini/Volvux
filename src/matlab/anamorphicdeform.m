function y=anamorphicdeform(P,x)

IP=inv(P);

y=project(IP*IP,x);

