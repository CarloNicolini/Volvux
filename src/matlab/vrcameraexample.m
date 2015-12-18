clear all;
close all;
clc;

L=120;
[C,col] = unitcube(L);

screen.focalDistance = 0;
screen.width = 400;
%screen.height = 20;
screen.pixelWidth = 1024.0;
screen.pixelHeight = 768.0;

screen.height=screen.width*screen.pixelHeight/screen.pixelWidth;

eye_coords=[0; 0; -800];

gl_Viewport=[0,0,screen.pixelWidth,screen.pixelHeight];

% Translate the points
%C(:,3) = C(:,3) + screen.focalDistance;%ones(size(C,1),1);%C(:,3)+screen.focalDistance;

H=eye(4);
%H(1:3,1:3)=getRotationMatrix(pi/6,[1 0 0]');
[gl_ModelView_Projection,gl_ModelView]=vrcamera(screen,eye_coords,H);

% Make the anamorphic transformation
P = [1 0 0 -eye_coords(1);
      0 1 0 -eye_coords(2);
      0 0 1 eye_coords(3);
      0 0 1/norm(eye_coords) 1];

C = project(inv(P),C);

PC = zeros(size(C,1),2);
for i=1:size(C,1)
   PC(i,:) = glProject(gl_ModelView_Projection,gl_Viewport,C(i,:)');
end

figure;
scatter(PC(:,1),PC(:,2),'.');
%xlim([0 gl_Viewport(3)]);
%ylim([0 gl_Viewport(4)]);
title('projected points');