clear all;
close all;

X=[ 0 0 0 1 ;
-35.5  35.5     0     1 ;
35.5 35.5    0    1 ;
 35.5 -35.5     0     1 ;
-35.5 -35.5     0     1 ;
-25  25  10   1 ;
25 25 10  1 ;
 25 -25  10   1 ;
-25 -25  10   1 ;
];

%figure;
%scatter3(X(:,1),X(:,2),X(:,3),'f'); xlabel('x'); ylabel('y'); zlabel('z'); text(X(:,1)+0.1,X(:,2)+0.1,X(:,3)+0.1, cellstr(num2str([(1:9)'])) );

x=[ 512 384   1 ;
419 474   1 ;
409 294   1 ;
589 294   1 ;
589 474   1 ;
449 441   1 ;
449 321   1 ;
569 321   1 ;
569 441   1 ;
];

%figure;
%scatter(x(:,1),x(:,2),'f'); xlabel('w'); ylabel('h');  text(x(:,1)+0.5,x(:,2)+0.5, cellstr(num2str([(1:9)'])) );

znear=0.01;
zfar=1E6;
gl_Viewport=[0 0 1024 768];

%% Compute the camera matrix P
[P,A,U,S,V] = homography(x',X');

% Camera matrix as computed from Eigen C++ Homography.cpp
Pcpp=[
-0.000526864  -0.00425899   0.00405595     0.794746;
 -0.00431717 -0.000275421   0.00188994     0.606893;
-9.00719e-07 -7.19104e-07  6.45729e-06   0.00157438 ];
P=Pcpp;
%% Evaluate camera error
for i=1:9
    p(:,i) = P*(X(i,:)');
    p(:,i) = p(:,i)/p(3,i);
end

err=0;
for i=1:9
    err = err + norm(p(:,i)-x(i,:)');
end
fprintf('Camera matrix error = %f\n',err);

%% Compute the OpenGL matrices
[gl_Projection_matrix,gl_Modelview_matrix] = getOpenGLMatrices(P,gl_Viewport(3),gl_Viewport(4),znear,zfar);

gl_MVProj = gl_Projection_matrix*gl_Modelview_matrix;
% Evaluate OpenGL camera error

HELICOID=load('~/workspace/Volvux/data/objmodels/helicoid.vert');

% for i=1:size(HELICOID,1)
%     x = HELICOID(i,:);
%     x = [getRotationMatrix(pi/2,[1,0,0])*x'; 1];
%     HELICOID(i,:)=x(1:3);
% end
%figure;
%scatter3(HELICOID(:,1),HELICOID(:,2),HELICOID(:,3),'.');
%xlabel('x');
%ylabel('y');
%zlabel('z');
%axis square;

for i=1:size(HELICOID,1)
    hh = HELICOID(i,:);
    pHELICOID(i,:)=glProject(gl_MVProj,gl_Viewport,[x 1]',znear,zfar);
end
figure;
scatter(pHELICOID(:,1),pHELICOID(:,2),ones(size(pHELICOID,1),1),pHELICOID(:,3));
title('Projected helicoid');
xlim([0 1024]);
ylim([0 768]);
colorbar;
 
 for i=1:size(x,1)
     pgl(i,:)=glProject(gl_MVProj,gl_Viewport,X(i,:)',znear,zfar);
 end
% 
 errGL=0;
 for i=1:9
     errGL = errGL + norm(pgl(i,1:2)-x(i,1:2));
 end

% viewport transformation
% close all;
figure;
hold on;
scatter(x(:,1),x(:,2),'fr');
scatter(pgl(:,1),pgl(:,2),'or');
delta = pgl(:,1:2) - x(:,1:2);
text(x(:,1)+2,x(:,2)+2,cellstr(num2str([(1:9)'])),'Color',[0 0 1] );
text(pgl(:,1)-10,pgl(:,2)-10,cellstr(num2str([(1:9)'])),'Color',[1 0 0] );
quiver(x(:,1),x(:,2),delta(:,1),delta(:,2),0);
xlim([0 gl_Viewport(3)]);
ylim([0 gl_Viewport(4)]);
legend({'original','reconstructed GL'});
hold off;

%U=umeyama(x',[pgl ones(9,1)]');