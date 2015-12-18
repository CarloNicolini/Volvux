clear all;
close all;
L=120;
[C,col] = unitcube();
C(:,1:3) = C(:,1:3)*L;
C(:,3) = C(:,3)+L; %translation

d = 800;

Pcam = [  0.432733 -0.00877564   0.0413784           0;
          0    0.583897   0.0833579           0;
          0           0    -1.02532    -20.2532;
          0           0          -1           0];
P = [1 0 0 0;
      0 1 0 0;
      0 0 1 0;
      0 0 1/d 1];

IP=inv(P);

AC=project(IP,C);

ACP=project(Pcam,C);

figure; hold on;
scatter3(C(:,1),C(:,2),C(:,3),'r');
scatter3(AC(:,1),AC(:,2),AC(:,3),10*ones(size(C,1),1),col,'f');
axis square;
hold off;

figure;
scatter3(ACP(:,1),ACP(:,2),ACP(:,3),10*ones(size(C,1),1),col,'f');
title('Projection of anamorphic transformed points');


% figure;
% subplot(2,1,1);
% scatter3(C(:,1),C(:,2),C(:,3),10*ones(size(C,1),1),col);
% axis square;
% title({'Original points','world coords'});
% 
% subplot(2,1,2);
% scatter3(AC(:,1),AC(:,2),AC(:,3),10*ones(size(C,1),1),col,'fr');
% axis square;
% title({'Anamorphically transformed vertices','world coords'});
