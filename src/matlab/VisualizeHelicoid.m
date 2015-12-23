function VisualizeHelicoid(gl_Projection_Matrix, gl_ModelViewMatrix,data3D,data2D)
Screen('Preference', 'Verbosity', 0);
% Is the script running in OpenGL Psychtoolbox?
AssertOpenGL;
KbName('UnifyKeyNames');
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

glViewport(0, 0, RectWidth(winRect), RectHeight(winRect));

glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

% Animation loop: Run until key press...
cols = (data3D + repmat(max(data3D),size(data3D,1),1));
cols = cols./ repmat(max(cols),size(cols,1),1);

glPointSize(2);
rotangle=0;
count=1;
while true   
    % Setup cubes rotation around axis:
    glPushMatrix;
    % Clear out the backbuffer: This also cleans the depth-buffer for
    % proper occlusion handling:
    glClear;
    
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glColor3d(1,1,1);
    glBegin(GL_LINE_LOOP);
    glVertex3dv([-50,-50,0]);
    glVertex3dv([50,-50,0]);
    glVertex3dv([50,50,0]);
    glVertex3dv([-50,50,0]);
    glEnd();
    glPopAttrib();
    
    
    glBegin(GL_POINTS);
    glVertex3d(0,0,0);
    glEnd();
    glPopMatrix;
    
    % Draw dots quickly:
    glPushMatrix();
    %glRotated(90,1,0,0);
    glRotated(rotangle,0,0,1);
    moglDrawDots3D(win, data3D(count,:)', 5, [255 255 255]' , [0, 0, 0], 1, []);
    glPopMatrix();
    
    % Finish OpenGL rendering into PTB window and check for OpenGL errors.
    Screen('EndOpenGL', win);

    Screen('DrawDots',win,data2D',1,[255 0 255],[],2);
    for k=1:size(data2D,1)
        Screen('DrawText',win,['n=' num2str(k)], data2D(k,1)+5,data2D(k,2)+5,[255 255 255]);
    end
    Screen('DrawDots',win,[512 384]',[15],[0 255 0],[],2);
    Screen('DrawText',win,['Visualizing point ' num2str(count)],512,40,[255 255 255]);
    % Show rendered image at next vertical retrace:
    Screen('Flip', win);
    %im = Screen('GetImage',win);
    %imwrite(uint8((im(:,:,1)~=0)*255),'../../build/Debug/image.bmp');
    %break;
    % Switch to OpenGL rendering again for drawing of next frame:
    Screen('BeginOpenGL', win);
    
    % Check for keyboard press and exit, if so:
    [keyPressed, secs, keyCode] = KbCheck();
    if keyPressed
        if keyCode(KbName('q')) || keyCode(KbName('ESCAPE'))
            break;
        end
        if keyCode(KbName('a'))
            rotangle = rotangle+1;
        end
        if keyCode(KbName('z'))
            rotangle = rotangle-1;
        end
        if keyCode(KbName('c'))
            count=count+1;
            if count > size(data2D,1)
                count = 1;
            end
        end
    end
    while KbCheck
    end
end

% Shut down OpenGL rendering:
Screen('EndOpenGL', win);

% Close onscreen window and release all other ressources:
Screen('CloseAll');

% Well done!
return
