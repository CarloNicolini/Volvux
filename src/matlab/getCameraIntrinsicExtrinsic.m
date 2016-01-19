function [K,R,C] = getCameraIntrinsicExtrinsic(cameraMatrix)

[K,R,C,pp,pv]=decomposePmatrix(cameraMatrix);
% If K(3,3) isn't -1 negate the 3rd column because OpenGL camera looks down z axis
%if K(3,3)>0
%    K(:,3) = -K(:,3);
%end

% This we need because of OpenGL convention

%K(:,2)=-K(:,2); %working (sembra meglio)

% For example, consider a camera matrix that was calibrated with the origin
% in the top-left and the y-axis pointing downward, but you prefer a bottom-left origin
% with the y-axis pointing upward. To convert, you'll first negate the image y-coordinate a
% nd then translate upward by the image height, h. 
% The resulting intrinsic matrix K' is given by:
%K = [1 0 0; 0 1 768; 0 0 1]*[1 0 0; 0 -1 0; 0 0 1]*K;
RR = getRotationMatrix(-pi,[1,0,0]);

% Camera looks down z axis
%R(:,3)=-R(:,3);
%K(:,3)=-K(:,3);

% Check that R is right handed, if not give warning
if dot(cross(R(:,1), R(:,2)), R(:,3)) < 0
    warning('Note that rotation matrix is left handed');
end
