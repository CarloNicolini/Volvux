function [K,R,C] = getCameraIntrinsicExtrinsic(cameraMatrix)

[K,R,C,pp,pv]=decomposePmatrix(cameraMatrix);

%K(:,1)=-K(:,1);
R(1,:)=-R(1,:);

K(:,2)=-K(:,2);
R(2,:)=-R(2,:);

K(:,3)=-K(:,3);
R(3,:)=-R(3,:);
R = getRotationMatrix(-pi/2,[0 0 1])*R;
% Check that R is right handed, if not give warning
if dot(cross(R(:,1), R(:,2)), R(:,3)) < 0
    warning('Note that rotation matrix is left handed');
end
