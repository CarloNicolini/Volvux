clear all;
%close all;

X=[ 0        0     0   1 ;
    -35.5   35.5   0   1 ;
     35.5   35.5   0   1 ;
     35.5  -35.5   0   1 ;
    -35.5  -35.5   0   1 ;
    -25     25    15   1 ;
     25     25    15   1 ;
     25    -25    15   1 ;
    -25    -25    15   1 ];

x=[ 512 384   1 ;
    419 474   1 ;
    409 294   1 ;
    589 294   1 ;
    589 474   1 ;
    449 441   1 ;
    449 321   1 ;
    569 321   1 ;
    569 441   1 ];

[P,A,U,S,V] = homography(x',X');

Pcpp=[-0.000526867  -0.00425901   0.00270392     0.794751;
 -0.00431719 -0.000275423   0.00125992     0.606896;
-9.00724e-07  -7.1911e-07  4.30476e-06   0.00157439];

% Evaluate camera error
for i=1:9
p(:,i) = P*(X(i,:)');
p(:,i) = p(:,i)/p(3,i);
end

err=0;
for i=1:9
    err = err + norm(p(:,i)-x(i,:)');
end
fprintf('Camera matrix error = %f\n',err);

% figure;
% hold on;
% scatter(x(:,1),x(:,2),'r');
% scatter(p(1,:)',p(2,:));
% legend({'original','recosntructed'});
% hold off;

gl_Viewport=[0 0 1024 768];
[gl_Projection_matrix,gl_Modelview_matrix] = getOpenGLMatrices(P,1024,768,0.5,1500);

gl_MVProj = gl_Projection_matrix*gl_Modelview_matrix;
% Evaluate OpenGL camera error
for i=1:size(x,1)
    pgl(i,:)=glProject(gl_MVProj,gl_Viewport,X(i,:)');
end

errGL=0;
for i=1:9
    errGL = errGL + norm(pgl(i,:)-x(i,1:2));
end

% viewport transformation
%figure;
close all;
hold on;
scatter(x(:,1),x(:,2),'fr');
scatter(pgl(:,1),pgl(:,2),'or');
delta = pgl(:,1:2) - x(:,1:2);
quiver(x(:,1),x(:,2),delta(:,1),delta(:,2),0);
xlim([0 gl_Viewport(3)]);
ylim([0 gl_Viewport(4)]);
legend({'original','reconstructed GL'});
%hold off;

U=umeyama(x',[pgl ones(9,1)]');