clear all;
close all;
[C,col] = unitcube();

l=-30;
r=30;
b=-25;
t=25;
n=5;
f=100;

P=glfrustum(l,r,b,t,n,f);

IP=inv(P);

%R(1:3,1) = -R(1:3,1);

% prepare anamorphically transformed vertices
for k=1:size(C,1)
    AnaC(k,:)=project(IP,project(IP,C(k,:)'));
end

% project anamorphically transformed vertices
for k=1:size(C,1)
    CCP(k,:)=project(P,AnaC(k,:)');
end

figure; grid off;
scatter3(AnaC(:,1),AnaC(:,2),AnaC(:,3),10*ones(size(C,1),1),col,'fr');
title('Anamorphically transformed vertices');

figure; grid off;
scatter3(CCP(:,1),CCP(:,2),CCP(:,3),10*ones(size(C,1),1),col,'fr');
title('Projection of anamorphically transformed vertices');
hold off;

viewport=[0 0 1024 768];

for k=1:size(C,1)
    PIX(k,:)=ndctopix(CCP(k,:),viewport,f,n);
end
figure;
scatter(PIX(:,1),PIX(:,2));
title('Viewport of transformed vertices');