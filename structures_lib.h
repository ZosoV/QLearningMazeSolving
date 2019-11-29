// #include "draw_maze.h" 
//----------------------------------------------------------------------------------------------------     
void print_Q(void)
{
 int i,j;
    
    printf("This is the Q Matrix:\n \n");
    for(i = 0; i < qSize*qSize ; i++)
        {
        cout << setw(5) << i;
        for(j = 0; j < 4; j++)
            {
            cout << setw(5) << Q[i][j];   
			if(j < qSize - 1)cout << "  ";  // separador de de columnas 
		} // j
        cout << "\n";
	} // i
    cout << "\n";
}
void print_R(int in, int jn)
{
 int i,j;   
    for(i = 0; i < qSize ; i++){
        for(j = 0; j < qSize; j++){
            if(maze[i][j]==-1) cout << setw(4) << "x";  
            else if(i==in && j==jn)  cout << setw(4) << "*";
            else  cout << setw(4) << "o";
		}
        cout << "\n";
	}
    cout << "\n";
}
//--------------------converters-----------------------------------------------------------
int coor_to_state(int i, int j){
    return i*qSize+j;
}
void state_to_coor(int state, int *i, int *j){
    *i = state/qSize;
    *j = state%qSize;
}
//------------------llenar la matriz Q con las restricciones del problema--------------------
void fill_Q_matrix(void){
    for(int i=0; i<qSize; i++){
        for(int j=0; j<qSize; j++){
            if(i==0)Q[coor_to_state(i,j)][0]=-500;                                  //up
            if(j==qSize-1)Q[coor_to_state(i,j)][1]=-500;                              //right
            if(i==qSize-1)Q[coor_to_state(i,j)][2]=-500;                              //down
            if(j==0)Q[coor_to_state(i,j)][3]=-500;                                  //left

            if(i-1>=0){if (maze[i-1][j]==-1) Q[coor_to_state(i,j)][0]=-500;}           //up
            if(j+1<=qSize-1){if (maze[i][j+1]==-1) Q[coor_to_state(i,j)][1]=-500;}       //right
            if(i+1<=qSize-1){if (maze[i+1][j]==-1) Q[coor_to_state(i,j)][2]=-500;}       //down
            if(j-1>=0){if (maze[i][j-1]==-1) Q[coor_to_state(i,j)][3]=-500;}           //left
        } 
    }
}

//---------------------------------------------------------
void Q_learn_server(void) 
{
 int i,j,new_i,new_j;
 int iter,iteraciones;     
 int temp, dice, max, max_iter, opciones;
 int initial_state, new_state;
 float femp;

double epsilon = eps;
 episode=1;
    
 do
  {
    do
    {
        initial_state=random(qSize*qSize);   //  se escioge el estado inicial
        state_to_coor(initial_state,&i,&j);
        temp=maze[i][j];   
    } while(temp==-1);               // estado fijo, buscamos columna diferente de -1 

    iteraciones=0;
    do    
       {     
            do
            {
                opciones = rand();
                if (opciones < epsilon){
                    dice=0;
                    max=Q[initial_state][dice];
                    for(iter=1;iter<4;iter++){
                        if(Q[initial_state][iter]>max){
                            dice = iter;
                            max = Q[initial_state][dice]; 
                        }                  // buscamos el valor mas alto de valores Q  
                    }
                }else{
                    dice=random(4);   //  se escioge el estado inicial
                }
                plot_labyrinth(i,j);
                new_i=i;
                new_j=j;
                temp=Q[initial_state][dice];
                if(dice==0)new_i--;
                else if(dice==1)new_j++;
                else if(dice==2)new_i++;
                else new_j--;
            } while(temp<-499);               // estado fijo, buscamos columna diferente de -1 
                        
            new_state = coor_to_state(new_i,new_j);
            max=Q[new_state][0];
            system("cls");     
            for(iter=1;iter<4;iter++)
            {
            if(Q[new_state][iter]>max) max = Q[new_state][iter];                  // buscamos el valor mas alto de valores Q  
            }
            femp=max;                                                    //  para convertir a float
            if(i==win_i && j==win_j){
                Q[initial_state][dice]= 100 + gamma*femp;
            }else{
                Q[initial_state][dice]= 0 + gamma*femp;
            }
            if(Q[initial_state][dice]<=0)Q[initial_state][dice]=Q[initial_state][dice]-2;
            initial_state=new_state;
            i=new_i;
            j=new_j; 
            iteraciones++;
            if(iteraciones==200)break;  // end of episode
    } while(1);
    episode++;
    print_Q();    
    //gets(dummy); 
 } while(episode<25);  //  aqui controlamos cuantos episodios queremos ejecutar para entrenar
    //  for(i=0;i<qSize*qSize;i++)
    //  for(j=0;j<4;j++)  Q[i][j] = Q[i][j]/10;   // reduce el tama�o de entradas en Q
} 
//-------------------------------------------------------------

//function for printing the elements in a list 
void showlist(list <int> g) 
{ 
    list <int> :: iterator it; 
    for(it = g.begin(); it != g.end(); ++it) 
        cout << '\t' << *it; 
    cout << '\n'; 
} 
//-------------------------------------------------------------
void Q_player_server(void) 
{
 int i,j;     
 int max;
 int initial_state, next_state;  
 list<int> final_path;
 
    //initial_state=random(qSize);
    //initial_state = 2; 
    cout << "Insert the initial state = " <<endl; 
    cin >> initial_state;
    next_state = initial_state;
    
    system("cls");     
    cout << "search begins at = "<< initial_state <<endl; 
    final_path.push_back(next_state);

    print_Q();
    do
       {   
            max=Q[next_state][0];  // valor en columna 0
            j=0;
            for(i=1;i<qSize;i++)
            {
             if(Q[next_state][i]>max)
                   {
                       max = Q[next_state][i];      // buscamos el valor mas alto de valores Q
                       j=i;
                   }           
            }
           
            cout << "The max found Q guide is = "<< max <<" in column "<< j <<endl;  
               
            next_state = j;
  
            //gets(dummy);
            
            final_path.push_back(next_state);
            
      if(next_state==8)break;  // end of search
    } while(1);
    
    cout << "\n The final path is: "; 
    showlist(final_path);     
    episode++;    
    //gets(dummy); 
} 
//-------------------------------------------------------------
