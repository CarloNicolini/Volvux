x=[512 384   1;
419 474   1;
409 294   1;
589 294   1;
589 474   1;
449 441   1;
449 321   1;
569 321   1;
569 441   1]

X =[0 0 0 1;
-35.5  35.5     0     1;
35.5 35.5    0    1;
 35.5 -35.5     0     1;
-35.5 -35.5     0     1;
-25  25  15   1;
25 25 15  1;
 25 -25  15   1;
-25 -25  15   1];

A = homography(x,X);