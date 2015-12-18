function [ProjectionMatrix,ModelViewMatrix] = vrcamera(screen,eye_coords,H)   

[pa,pb,pc]=getScreenBorders(screen,H);

vr=(pb-pa)/norm(pb-pa);
vu=(pc-pa)/norm(pc-pa);
vn=cross(vr,vu)/norm(cross(vr,vu));

va=pa-eye_coords;
vb=pb-eye_coords;
vc=pc-eye_coords;

d=-dot(vn,va);

n=0.5;
f=1800;

l=(dot(vr,va))*n/d;
r=dot(vr,vb)*n/d;
b=dot(vu,va)*n/d;
t=dot(vu,vc)*n/d;

P=eye(4,4);

P(1,1)=  2*n/(r-l);
P(1,3)=  (r+l)/(r-l);
P(2,2)=  2*n/(t-b);
P(2,3)=  (t+b)/(t-b);
P(3,3)=  -(f+n)/(f-n);
P(3,4)=  -2*f*n/(f-n);
P(4,3)=  -1;

M=eye(4,4);
T=eye(4,4);

M(1:3,1)=vr;
M(1:3,2)=vu;
M(1:3,3)=vn;

T(1:3,4)=-eye_coords;

ProjectionMatrix=P*M'*T;

ModelViewMatrix=M'*T;

function y=affine3D(H,x)
if ( sum( size(x) == [1,1] ) )
	y=H(1:3,1:3)*x+H(1:3,4);
else
	error('Please put column vector as ordinary vectors')
end


function [pa,pb,pc]=getScreenBorders(screen,H)

w=screen.width;
h=screen.height;
fz=screen.focalDistance;

pa=[-w/2;-h/2;fz];
pb=[w/2;-h/2;fz];
pc=[-w/2;h/2;fz];

pa = affine3D(H,pa);
pb = affine3D(H,pb);
pc = affine3D(H,pc);

