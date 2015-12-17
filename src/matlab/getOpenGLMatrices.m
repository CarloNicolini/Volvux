function [gl_Projection, gl_ModelView] = getOpenGLMatrices(cameraMatrix)

[K,R,Pc,pp,pv]=decomposePmatrix(cameraMatrix);