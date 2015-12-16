function Po=orthographicFromPerspective(Pp,f,n)

Po=zeros(4,4);

Po=[ Pp(1,1)/n,  0,           0,               -Pp(1,3);
     0,          Pp(2,2)/n,   0,               -Pp(2,3);
     0,          0,           2*Pp(3,3)/(f+n), Pp(3,3);
     0,          0,           0,                1];
