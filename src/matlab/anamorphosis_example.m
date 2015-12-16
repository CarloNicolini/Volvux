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
F = frustumcorners(l,r,b,t,n,f);
IP=inv(P);

% prepare anamorphically transformed vertices
for k=1:size(C,1)
    AnaC(k,:)=project(IP*IP,C(k,:)');
end

% project anamorphically transformed vertices
for k=1:size(C,1)
    CCP(k,:)=project(P,AnaC(k,:)');
    %CCP(k,1) = CCP(k,1)/(f*(r-l));
    %CCP(k,2) = CCP(k,2)/(f*(t-b));
end

viewport=[0 0 1024 768];

for k=1:size(C,1)
    PIX(k,:)=ndctopix(CCP(k,:),viewport,f,n);
end

%% Make the plots
figure;
subplot(2,2,1);
scatter3(C(:,1),C(:,2),C(:,3),10*ones(size(C,1),1),col);
title({'Original points','world coords'});

subplot(2,2,2);
scatter3(AnaC(:,1),AnaC(:,2),AnaC(:,3),10*ones(size(C,1),1),col,'fr');
title({'Anamorphically transformed vertices','world coords'});

subplot(2,2,3);
scatter3(CCP(:,1),CCP(:,2),CCP(:,3),10*ones(size(C,1),1),col,'fr');
title({'Projection of anamorphically transformed vertices','proj coords'});

subplot(2,2,4);
scatter(PIX(:,1),PIX(:,2),'b.');
xlim([0 1024]);
ylim([0 768]);
title('Viewport of transformed vertices');
