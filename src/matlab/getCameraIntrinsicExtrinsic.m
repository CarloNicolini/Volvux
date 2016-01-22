function [K,R,C] = getCameraIntrinsicExtrinsic(cameraMatrix)

[K,R,C,pp,pv]=decomposePmatrix(cameraMatrix);
K = [1 0 0; 0 -1 768; 0 0 1]*K;
K(:,1)=-K(:,1);
R(1,:)=-R(1,:);

K(:,2)=-K(:,2);
R(2,:)=-R(2,:);

K(:,3)=-K(:,3);
R(:,3)=-R(:,3);

if det(R)<0
    R=-R;
end



% Check that R is right handed, if not give warning
if det(R)<0
    warning('Note that rotation matrix is left handed');
end
