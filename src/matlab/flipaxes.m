function [R,K] = flipaxes(R,K,inverStruct)

switch invertStruct.R1
    case 'r1'
        R(1,:)=-R(1,:);
    case 'r2'
        R(2,:)=-R(2,:);
    case 'r3'
        R(3,:)=-R(3,:);
    case 'c1'
        R(:,1)=-R(:,1);
    case 'c2'
        R(:,2)=-R(:,2);
    case 'c3'
        R(:,3)=-R(:,3);
end

switch invertStruct.R2
    case 'r1'
        R(1,:)=-R(1,:);
    case 'r2'
        R(2,:)=-R(2,:);
    case 'r3'
        R(3,:)=-R(3,:);
    case 'c1'
        R(:,1)=-R(:,1);
    case 'c2'
        R(:,2)=-R(:,2);
    case 'c3'
        R(:,3)=-R(:,3);
end

switch invertStruct.R3
    case 'r1'
        R(1,:)=-R(1,:);
    case 'r2'
        R(2,:)=-R(2,:);
    case 'r3'
        R(3,:)=-R(3,:);
    case 'c1'
        R(:,1)=-R(:,1);
    case 'c2'
        R(:,2)=-R(:,2);
    case 'c3'
        R(:,3)=-R(:,3);
end

switch invertStruct.K1
    case 'k1'
        K(1,:)=-K(1,:);
    case 'r2'
        K(2,:)=-K(2,:);
    case 'r3'
        K(3,:)=-K(3,:);
    case 'c1'
        K(:,1)=-K(:,1);
    case 'c2'
        K(:,2)=-K(:,2);
    case 'c3'
        K(:,3)=-K(:,3);
end

switch invertStruct.K2
    case 'k1'
        K(1,:)=-K(1,:);
    case 'r2'
        K(2,:)=-K(2,:);
    case 'r3'
        K(3,:)=-K(3,:);
    case 'c1'
        K(:,1)=-K(:,1);
    case 'c2'
        K(:,2)=-K(:,2);
    case 'c3'
        K(:,3)=-K(:,3);
end

switch invertStruct.K3
    case 'k1'
        K(1,:)=-K(1,:);
    case 'r2'
        K(2,:)=-K(2,:);
    case 'r3'
        K(3,:)=-K(3,:);
    case 'c1'
        K(:,1)=-K(:,1);
    case 'c2'
        K(:,2)=-K(:,2);
    case 'c3'
        K(:,3)=-K(:,3);
end