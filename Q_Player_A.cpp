// --------------------------
//Practica 6
// Q learner 
// Prof Oscar Chang
//  October 3, 2019
//--------------------------//        GLOBALS   -------------------
const int qSize = 21;
int win_i = 20;
int win_j = 20;
int i_player = 0;
int j_player = 0;
const double gamma = 0.8;
const double eps = 0.5;

int maze[qSize][qSize] =
        {   
            //0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20
            { 0,  0,  0,  0, -1,  0,  0, -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1,  0,  0},           // 0
			{-1, -1, -1,  0, -1,  0,  0, -1,  0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  0, -1},           // 1
			{ 0,  0, -1,  0, -1, -1,  0, -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1,  0,  0},           // 2
			{ 0, -1, -1,  0,  0,  0,  0, -1, -1, -1, -1, -1, -1, -1, -1, -1,  0,  0, -1,  0, -1},           // 3
			{ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1,  0,  0, -1,  0,  0},           // 4
            {-1, -1, -1, -1,  0,  0, -1, -1, -1, -1, -1, -1, -1,  0, -1, -1,  0,  0, -1, -1,  0},           // 5
            { 0,  0,  0, -1,  0,  0, -1,  0,  0,  0,  0,  0, -1,  0, -1,  0,  0,  0,  0,  0,  0},           // 6
            { 0, -1,  0, -1,  0, -1, -1,  0, -1, -1, -1,  0, -1,  0, -1,  0,  0,  0,  0,  0,  0},           // 7
            { 0, -1,  0, -1,  0,  0, -1,  0, -1,  0, -1,  0, -1,  0, -1,  0, -1, -1, -1, -1, -1},           // 8
            { 0, -1, -1, -1, -1,  0, -1,  0, -1,  0, -1,  0, -1,  0,  0,  0, -1,  0,  0,  0,  0},           // 9
            { 0,  0,  0,  0, -1,  0, -1,  0, -1,  0, -1,  0, -1, -1, -1,  0, -1,  0, -1, -1,  0},           // 10
            {-1, -1, -1,  0, -1,  0, -1,  0, -1,  0, -1,  0,  0,  0,  0,  0, -1,  0, -1, -1,  0},           // 11
            { 0,  0,  0,  0, -1,  0, -1,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1,  0, -1,  0,  0},           // 12
            { 0, -1, -1, -1, -1,  0, -1,  0, -1, -1, -1, -1, -1, -1, -1, -1, -1,  0, -1, -1, -1},           // 13
            { 0,  0,  0,  0,  0,  0, -1,  0, -1,  0,  0, -1,  0,  0,  0,  0, -1,  0,  0,  0,  0},           // 14
            {-1, -1, -1, -1, -1, -1, -1,  0, -1,  0,  0, -1,  0,  0,  0,  0, -1, -1, -1, -1,  0},           // 15
            { 0,  0,  0,  0,  0,  0,  0,  0, -1,  0,  0, -1,  0, -1,  0,  0,  0,  0,  0,  0,  0},           // 16
            { 0, -1, -1, -1, -1, -1, -1, -1, -1,  0,  0, -1,  0, -1,  0, -1, -1, -1, -1, -1, -1},           // 17
            { 0,  0,  0, -1,  0,  0,  0,  0,  0,  0,  0, -1,  0, -1,  0, -1,  0,  0,  0,  0,  0},           // 18
            { 0, -1,  0, -1,  0, -1, -1,  0, -1, -1,  0, -1,  0, -1,  0, -1,  0, -1, -1,  0,  0},           // 19
            { 0, -1,  0,  0,  0, -1, -1,  0, -1, -1,  0,  0,  0, -1,  0,  0,  0, -1, -1,  0,  0},           // 20
        };
//--

//-----------------------------------------------
#include <stdlib.h>
//#include <graphics.h>
#include <dos.h>
#include <conio.h>   
#include <stdio.h>
#include <iostream.h>
#include <time.h>
#include <windows.h>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <iomanip>
#include <ctime>
#include <list> 
#include <graphics.h>
#include <math.h>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector> 
#include <cstdlib>
#include <string>

using namespace std;
        
int Q[qSize*qSize][4];
int currentState;   
int episode = 1;
int max_episode = 25;
int current_iteration = 0;
int max_iteration_per_episode = 200;
char key;  
char dummy[1];
int draw_mode=1;
//1: poner nuevas paredes
//2: localizar objetivo
//3: localizar inicio

char str[1000];
int sig = 5;

bool pause = false;

void plot_labyrinth(int i_player, int j_player)                           ////       PLOT HIDDEN WEIGHTS
{
int i,j,sx,sy,x,y,color,scale; 
int temp; 
x=10;
scale=20;
   
   for(j=0;j<qSize;j++)  // 
     { 
      y=10;   
      sx = x+j*scale;             //   pesos[N_HID_1][N_IN];
      for(i=0;i<qSize;i++)
         {    
          sy = y+i*scale;
          temp=maze[i][j];  
          
          //timp= Entrada[counter];  
          color=LIGHTGRAY; 
          if(win_i==i && win_j==j){
              color=BLUE;
          }else if(i_player==i && j_player==j){
            color=GREEN;
          }else{
            if(temp==-1) color=RED;        // fROZEN
            if(temp==0) color=WHITE;          // HOT !    
          }
          setcolor(color); 
          setfillstyle(SOLID_FILL,color); 
          bar(sx,sy,sx+scale,sy+scale) ;
          //putpixel(sx,sy, color);      
          //y++;  
         }
       //x++;  
     }

    //Print Text
    int text_x = 500, text_y = 200;
    int x_step=275; 
    int y_step=25;
    
    int x_text = text_x;
    int y_text = text_y;
        
        setcolor(BLACK);
        bar(x_text+x_step,y_text,x_text+x_step+90,y_text+100);
        setcolor(BLUE);     
        settextstyle(3, HORIZ_DIR, 1);
        outtextxy(x_text,y_text,"Episodio Máximo: ");
        x_text=x_text+x_step;
        outtextxy(x_text,y_text,gcvt( max_episode,sig,str)); 
    
    x_text=text_x; 
    y_text=y_text+y_step;
    
        outtextxy(x_text,y_text,"Episodios Trancurridos: ");
        x_text=x_text+x_step;
        outtextxy(x_text,y_text,gcvt( episode,sig,str)); 
    
    x_text=text_x; 
    y_text=y_text+y_step;
        outtextxy(x_text,y_text,"Iteracion por Episodio Maxima: ");
        x_text=x_text+x_step;
        outtextxy(x_text,y_text,gcvt( max_iteration_per_episode,sig,str));
        
    x_text=text_x; 
    y_text=y_text+y_step;
        outtextxy(x_text,y_text,"Iteraciones por Episodio: ");
        x_text=x_text+x_step;
        outtextxy(x_text,y_text,gcvt( current_iteration+1,sig,str)); 
         
}

#include "structures_lib.h"
#include "draw_maze.h" 

//using namespace std;  
//--------------------------------------
int master_delay;
//--------------------------------------

void clear_screen(void)
{
    system("cls");
} 
//----------------------------------------
//    LOOP
//----------------------------------------


void loop(void)
{
     Q_learn_server();
     cout << "End training in episode "<< episode << endl; 
                        
     print_Q(); 
     cout << "Ready to play "<<endl; 
     gets(dummy);

    //  while (1)
    //  {
    //     Q_player_server();
    //     cout << "Play Again "<<endl; 
    //     gets(dummy); 
    //  }
     

}
//----------------------------------------
main()
{

    cout << "Q_learner_version_1.0  "<<endl<<endl; 
    Sleep(500);
    grafico();

    setcolor(LIGHTGRAY);
    bar(0,0,1400,900);  

    randomize();
    

    int prev_i, prev_j, i_p, j_p;
    bool first_k = false, second_k = false;
            
    //First stage define the maze and add new walls
    plot_labyrinth(i_player,j_player);
    make_graph();

    while(1){
     
       key=getch();
       switch (key) {
           case '1':{ //Cambio de modo a elegir la posicion del objetivo
                draw_mode=2;
                plot_labyrinth(i_player,j_player);
                make_graph();
                delay(100);
                } 
           break;
           case '2':{ //Cambio de modo a elegir la posicion de inicio
                draw_mode=3;
                plot_labyrinth(i_player,j_player);
                make_graph();
                delay(100);
                    } 
           break;
           case '3':{ //Inicio el entramiento
                fill_Q_matrix();
                Q_learn_server();
                cout << "End training in episode "<< episode << endl; 
                delay(100);
                    } 
           break;
           case '4':{ //Cargo Aprendizaje
                load_learning();
                delay(100);
                cout << "hasta aqui bien" << endl;
                fill_Q_matrix();
                Q_learn_server();
                cout << "End training in episode "<< episode << endl; 
                delay(100);
                    } 
           break;
           case '5':{ //Guardo el aprendizaje
                save_learning();
                delay(100);
                    } 
           break;
           case '6':{ //Permite mover al agente con el aprendizaje establecido
                Q_player_server();
                delay(100);
                } 
           break;           
                    
           case 'p':{ //Detiene el etrenamiento y continuo
               
                key = getch();
                
                if (key == 'p'){
                    fill_Q_matrix();
                    Q_learn_server();
                    cout << "End training in episode "<< episode << endl; 
                    delay(100);
                }

                    } 
           break;                      
       }
    }
    // print_Q();
        
    // Sleep(100);     
              

    closegraph();
    clrscr();
  
}

//--------------------------------------------------------