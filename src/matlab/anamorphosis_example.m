clear all;
close all;
L=8;
[C,col] = unitcube();
C(:,1:3) = C(:,1:3);
l=-30;
r=30;
b=-25;
t=25;
n=5;
f=100;

viewport=[0 0 1024 768];
P=glfrustum(l,r,b,t,n,f);
F = frustumcorners(l,r,b,t,n,f);
IP=inv(P);

% prepare anamorphically transformed vertices
AC = project(IP*IP,C);
AF = project(IP*IP,F);
% project anamorphically transformed vertices

ACP = project(P,AC);

for k=1:size(C,1)
    PIX(k,:)=ndctopix(ACP(k,:),viewport,f,n);
end

%% Make the plots
figure;
subplot(2,2,1);
scatter3(C(:,1),C(:,2),C(:,3),10*ones(size(C,1),1),col);
title({'Original points','world coords'});

subplot(2,2,2);
scatter3(AC(:,1),AC(:,2),AC(:,3),10*ones(size(C,1),1),col,'fr');
title({'Anamorphically transformed vertices','world coords'});

subplot(2,2,3);
scatter3(ACP(:,1),ACP(:,2),ACP(:,3),10*ones(size(C,1),1),col,'fr');
title({'Projection of anamorphically transformed vertices','proj coords'});

subplot(2,2,4);
scatter(PIX(:,1),PIX(:,2),'b.');
xlim([0 1024]);
ylim([0 768]);
title('Viewport of transformed vertices');
