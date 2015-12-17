clear all;
close all;
L=12;
[C,col] = unitcube();
C(:,1:3) = C(:,1:3)*L;
n=10.0;
f=800.0;
viewport=[0 0 1024 768];


P=[ 0.432733 -0.00877564   0.0413784           0;
          0    0.583897   0.0833579           0;
          0           0    -1.02532    -20.2532;
          0           0          -1           0];

IP=inv(P);
% prepare anamorphically transformed vertices
AC = project(IP,C);
%AC(:,1) = AC(:,1)/max(AC(:,1));
%AC(:,2) = AC(:,2)/max(AC(:,2));

% project anamorphically transformed vertices


ACP = project(P,AC);

PIX = ndctopix(ACP,viewport,f,n);

%% Make the plots
figure;
subplot(2,2,1);
scatter3(C(:,1),C(:,2),C(:,3),10*ones(size(C,1),1),col);
axis square;
title({'Original points','world coords'});

subplot(2,2,2);
scatter3(AC(:,1),AC(:,2),AC(:,3),10*ones(size(C,1),1),col,'fr');
axis square;
title({'Anamorphically transformed vertices','world coords'});

subplot(2,2,3);
scatter3(ACP(:,1),ACP(:,2),ACP(:,3),10*ones(size(C,1),1),col,'fr');
axis square;
title({'Projection of anamorphically transformed vertices','proj coords'});

subplot(2,2,4);
scatter(PIX(:,1),PIX(:,2),ones(size(C,1),1)*5,C(:,3),'.');
axis square;
%xlim([0 1024]);
%ylim([0 768]);
title('Viewport of transformed vertices');
