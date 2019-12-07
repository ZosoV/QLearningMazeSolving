
// --------------------------
//Maze Solving
//Joseph Gonzalez
//Oscar Guarnizo 
//Andres Banda
//Fabricio Crespo
//Yachay Tech
//-------------------------------------
//    inicia el modo grafico             
//-------------------------------------    
void grafico(void)
{
    int    GraphDriver;  /* The Graphics device driver */
    int    GraphMode;    /* The Graphics mode value */
    int    ErrorCode;    /* Reports any graphics errors */
   
    initgraph(&GraphDriver, &GraphMode, "");

    ErrorCode = graphresult();            /* Read result of initialization*/
    if( ErrorCode != grOk )              /* Error occured during init    */
    {
       printf(" Graphics System Error: %s", grapherrormsg( ErrorCode ) );
       exit( 1 );
    }
}



//--------------------------------------------------------------------------------------------
HWND GetConsoleHwnd(void)
   {
       #define MY_BUFSIZE 1024 // Buffer size for console window titles.
       HWND hwndFound;         // This is what is returned to the caller.
       char pszNewWindowTitle[MY_BUFSIZE]; // Contains fabricated
                                           // WindowTitle.
       char pszOldWindowTitle[MY_BUFSIZE]; // Contains original
                                           // WindowTitle.

       // Fetch current window title.

       GetConsoleTitle(pszOldWindowTitle, MY_BUFSIZE);

       // Format a "unique" NewWindowTitle.

       wsprintf(pszNewWindowTitle,"%d/%d",
                   GetTickCount(),
                   GetCurrentProcessId());

       // Change current window title.

       SetConsoleTitle(pszNewWindowTitle);

       // Ensure window title has been updated.

       Sleep(40);

       // Look for NewWindowTitle.

       hwndFound=FindWindow(NULL, pszNewWindowTitle);

       // Restore original window title.

       SetConsoleTitle(pszOldWindowTitle);

       return(hwndFound);
}    

//-----------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------


void Get_Square(int px, int py, int* i, int* j){
    *i=(px)/20+1;
    *j=(py)/20+1;
    }

int make_graph(){
    POINT cursorPosition;
    int mX, mY, i, j;
    int limitXlabyrinth = 420, limitYlabyrinth = 420;
    HWND hwnd = GetConsoleHwnd();

    if( hwnd != NULL){
        cout << "is not null = "<< endl;
    }


    
    if (ScreenToClient(hwnd, &cursorPosition))
    {   
        while (!kbhit()){
            GetCursorPos(&cursorPosition);
            mX = cursorPosition.x;
            mY = cursorPosition.y;
            mX = mX - 20;
            mY = mY - 30;
            // mY = mY-20;
            //mY = mY-70;
            //mX = mX-80;
            
            if( mX > 0 && mX < limitXlabyrinth && mY > 0 && mY < limitYlabyrinth){
                Get_Square(mX, mY, &i, &j);
                setcolor(RED); 
                if (GetAsyncKeyState(VK_LBUTTON)){
                    if(draw_mode==1){
                        if(maze[j-1][i-1]==0){
                            setcolor(RED);
                            maze[j-1][i-1]=-1;
                        }else if(maze[j-1][i-1]==-1){
                            setcolor(WHITE);
                            maze[j-1][i-1]=0;  
                        }
                    }else if(draw_mode==2){
                        if(maze[j-1][i-1]==0){
                            setcolor(WHITE);
                            bar((win_j+1)*20-10, (win_i+1)*20-10, (win_j+1)*20+10, (win_i+1)*20+10);
                            setcolor(BLUE);
                            win_i=j-1;
                            win_j=i-1;
                        }
                    }else if(draw_mode==3){
                        if(maze[j-1][i-1]==0){
                            setcolor(WHITE);
                            bar((j_player+1)*20-10, (i_player+1)*20-10, (j_player+1)*20+10, (i_player+1)*20+10);
                            setcolor(GREEN);
                            i_player=j-1;
                            j_player=i-1;
                        }
                    }
                    bar(i*20-10, j*20-10, i*20+10, j*20+10);
                }
            }

            delay(100);
        }
    }
        return 0;
}
