function [K,R,C] = getCameraIntrinsicExtrinsic(cameraMatrix)

[K,R,C,pp,pv]=decomposePmatrix(cameraMatrix);

% %% OLD WORKING
if K(3,3)>0
	K(:,3)=-K(:,3);
end
% 
K(:,2)=-K(:,2);
K = [1 0 0; 0 -1 768; 0 0 1]*K;
R(1,:)=-R(1,:);
R=-R;
%%

% Check that R is right handed, if not give warning
if dot(cross(R(:,1), R(:,2)), R(:,3)) < 0
    warning('Note that rotation matrix is left handed');
end
