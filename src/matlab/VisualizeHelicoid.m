function VisualizeHelicoid(gl_Projection_Matrix, gl_ModelViewMatrix,data)
Screen('Preference', 'Verbosity', 0);
% Is the script running in OpenGL Psychtoolbox?
AssertOpenGL;

% Find the screen to use for display:
screenid=max(Screen('Screens'));

% Disable Synctests for this simple demo:
Screen('Preference','SkipSyncTests',2);

% Setup Psychtoolbox for OpenGL 3D rendering support and initialize the
% mogl OpenGL for Matlab wrapper:
InitializeMatlabOpenGL(1);

% Open a double-buffered full-screen window on the main displays screen.
[win , winRect] = Screen('OpenWindow', screenid,[],[0 0 1024 768]);

% Setup the OpenGL rendering context of the onscreen window for use by
% OpenGL wrapper. After this command, all following OpenGL commands will
% draw into the onscreen window 'win':
Screen('BeginOpenGL', win);

glMatrixMode(GL_PROJECTION);
glLoadMatrixd(gl_Projection_Matrix);

glMatrixMode(GL_MODELVIEW);
glLoadMatrixd(gl_ModelViewMatrix);

% Set background color to 'black':
glClearColor(0,0,0,0);
glColor3d(1,1,1);

glViewport(0, 0, RectWidth(winRect), RectHeight(winRect));

% Animation loop: Run until key press...
cols = (data + repmat(max(data),size(data,1),1));
cols = cols./ repmat(max(cols),size(cols,1),1);
%size(cols)
%cols = ind2rgb(cols(:,3),parula);
%size(cols)
glPointSize(0.01);
while true   
    % Setup cubes rotation around axis:
    glPushMatrix;
    % Clear out the backbuffer: This also cleans the depth-buffer for
    % proper occlusion handling:
    glClear;
    
    glBegin(GL_LINE_LOOP);
    glVertex3dv([-120,-120,0]);
    glVertex3dv([120,-120,0]);
    glVertex3dv([120,120,0]);
    glVertex3dv([-120,120,0]);
    glEnd();
    
    glRotated(90,1,0,0);
    % Draw dots quickly:
    moglDrawDots3D(win, data', 0.01, [255 255 255]' , [0, 0, 0], 1, []);
    glPopMatrix;
    
    % Finish OpenGL rendering into PTB window and check for OpenGL errors.
    Screen('EndOpenGL', win);

    % Show rendered image at next vertical retrace:
    Screen('Flip', win);
    im = Screen('GetImage',win);
    imwrite(im,'~/workspace/Volvux/src/matlab/image.bmp');
    %break;
    % Switch to OpenGL rendering again for drawing of next frame:
    Screen('BeginOpenGL', win);
    
    % Check for keyboard press and exit, if so:
    if KbCheck
        break;
    end;
end

% Shut down OpenGL rendering:
Screen('EndOpenGL', win);

% Close onscreen window and release all other ressources:
Screen('CloseAll');

% Reenable Synctests after this simple demo:
Screen('Preference','SkipSyncTests',1);

% Well done!
return
