function A = umeyama(X, Y)
%  RALIGN - Rigid alignment of two sets of points in k-dimensional
%           Euclidean space.  Given two sets of points in
%           correspondence, this function computes the scaling,
%           rotation, and translation that define the transform TR
%           that minimizes the sum of squared errors between TR(X)
%           and its corresponding points in Y.  This routine takes
%           O(n k^3)-time.
% 
%  Inputs:
%    X - a k x n matrix whose columns are points 
%    Y - a k x n matrix whose columns are points that correspond to
%        the points in X
%  Outputs: 
%    c, R, t - the scaling, rotation matrix, and translation vector
%              defining the linear map TR as 
%  
%                        TR(x) = c * R * x + t
% 
%              such that the average norm of TR(X(:, i) - Y(:, i))
%              is minimized.
% 
% 
% 
% Copyright: Carlo Nicolini, 2013
% Code adapted from the Mark Paskin Matlab version
% from http://openslam.informatik.uni-freiburg.de/data/svn/tjtf/trunk/matlab/ralign.m 

[m, n] = size(X);

mx = mean(X, 2);              % Eqn. (34)
my = mean(Y, 2);              % Eqn. (35)

Xc = X - repmat(mx, [1, n]);
Yc = Y - repmat(my, [1, n]);

sx = mean(sum(Xc.^2, 1));     % Eqn. (36)
sy = mean(sum(Yc.^2, 1));     % Eqn. (37)

Sxy = Yc * Xc' ./ n;          % Eqn. (38)

[U, D, V] = svd(Sxy);

r = rank(Sxy);
d = det(Sxy);

S = eye(m);
if (r > m - 1) 
  if (det(Sxy) < 0)
    S(m, m) = -1;
  end
elseif (r == m - 1)
  if (det(U) * det(V) < 0)
    S(m, m) = -1;
  end
else
  warning('Insufficient rank in covariance to determine rigid transform');
  R = [1, 0; 0, 1];
  c = 1;
  t = [0; 0];
  return;
end

R = U * S * V';               % Eqn. (40)
c = trace(D * S) / sx;        % Eqn. (42)
t = my - c * R * mx;          % Eqn. (41)

A = eye(4,4);
A(1:3,1:3)=c*R;
A(1:3,4)=t;
