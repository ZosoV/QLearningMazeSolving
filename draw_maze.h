
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

//---------------------------------------------------------------------------------------


void Get_Square(int px, int py, int* i, int* j){
    *i=(px)/20+1;
    *j=(py)/20+1;
    }

int make_graph(){
    POINT cursorPosition;
    int mX, mY, i, j;
    
     while (1){
        GetCursorPos(&cursorPosition);
        mX = cursorPosition.x;
        mY = cursorPosition.y;
        // mY = mY-20;
        mY = mY-70;
        mX = mX-80;
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
        delay(100);
        if(kbhit()){ 
        getch();  
        break;}
        }
        return 0;
}
