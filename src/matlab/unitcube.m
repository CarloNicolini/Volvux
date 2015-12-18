function [C,col]=unitcube(l)

if nargin < 1
    l=1;
end
% use homogeneous coordinates

% C=[+l +l +l 1;
%     +l -l +l 1;
%     -l +l +l 1;
%     -l -l +l 1;
%     +l +l -l 1;
%     +l -l -l 1;
%     -l +l -l 1;
%     -l -l -l 1];
n=4;
C=[];
col=[];
for x=linspace(-l,l,n)
    for y=linspace(-l,l,n)
        for z=linspace(-l,l,n)
            C=[C; [x,y,z,1]];
            col = [col;z];
        end
    end
end