function drawReference(win,d)

glBegin(GL_LINES);
glColor3d(1,0,0);
glVertex3d(0,0,0);
glVertex3d(d,0,0);


glColor3d(0,1,0);
glVertex3d(0,0,0);
glVertex3d(0,d,0);

glColor3d(0,0,1);
glVertex3d(0,0,0);
glVertex3d(0,0,d);
glEnd();
