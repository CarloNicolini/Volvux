function C=frustumcorners(l,r,b,t,n,f)

corners_nearplane = [l b -n 1;
    l t -n 1;
    r b -n 1;
    r t -n 1];

rfar = f*(r-l)/(2*n);
lfar = -f*(r-l)/(2*n);

tfar = f*(t-b)/(2*n);
bfar = -f*(t-b)/(2*n);

corners_far_plane  = [lfar bfar -f 1;
    lfar tfar -f 1;
    rfar bfar -f 1;
    rfar tfar -f 1];
C = [corners_nearplane; corners_far_plane];