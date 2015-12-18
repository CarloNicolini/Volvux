close all;
clear all;
eye_coords = [0 0 -5];

T = eye(4); T(1:3,4)=-eye_coords';

P = [1   0  0  0;
     0   1  0  0;
     0   0  1  0;
     0   0  1/norm(eye_coords)  1];
P2 = P;%T'*P*inv(T);

% zfront=-5;
% SHzi = eye(4); SHz(3,4)=-1;
% 
% Sz = eye(4); Sz(3,3)=-zfront/(1+zfront);
% SHw = eye(4); SHz(4,3)=-1;
% SHz = eye(4); SHz(3,4)=1;
% 
% P = SHzi*Sz*SHw*SHz;

%P(1:3,3)=eye_coords';
[C,col] = unitcube();

% for i=1:size(C,1)
%     C(i,:) = (T*C(i,:)')';
% end


CP = project(inv(P2),C);

figure; hold on;
scatter3(CP(:,1),CP(:,2),CP(:,3),100*ones(size(C,1),1),col,'f');
scatter3(C(:,1),C(:,2),C(:,3),100*ones(size(C,1),1),'or');
axis square;
xlabel('x');
ylabel('y');
zlabel('z');
%ylim([-5,5]);
%xlim([-5,5]);
%zlim([-5,5]);
grid on;