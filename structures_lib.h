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
//--------------------------------------------------------
void split_str(const string& s, char c,
           vector<string>& v) {
   string::size_type i = 0;
   string::size_type j = s.find(c);

   while (j != string::npos) {
      v.push_back(s.substr(i, j-i));
      i = ++j;
      j = s.find(c, j);

      if (j == string::npos)
         v.push_back(s.substr(i, s.length()));
   }
}
//---------------------------------------------------------
void save_learning(void){
    ofstream myfile;
    myfile.open("learning.txt");
    if (myfile.is_open()){
        for (int i = 0; i < qSize*qSize; i++){
            for (int j = 0; j < 4; j++){
                myfile << Q[i][j] << " ";
            }        
            myfile << "\n";
        }
        myfile.close();
        cout << "Learning Saved" << endl;
    }
    else cout << "Unable to open file";
    
}
  
//---------------------------------------------------------
void load_learning(void){
    string line;
    ifstream myfile;
    myfile.open("learning.txt");
    int temp;

    if (myfile.is_open()){
        for(int i = 0; i < qSize*qSize; i++){
            getline(myfile, line);
            vector<string> values;
            cout << line << endl;
            split_str(line, ' ', values);

            
            temp = atoi(values[0].c_str());
            cout << temp << " ";
            Q[i][0] = temp;
            
            temp = atoi(values[1].c_str());
            cout << temp << " ";
            Q[i][1] = temp;
            
            temp = atoi(values[2].c_str());
            cout << temp << " ";
            Q[i][2] = temp;
            
            temp = atoi(values[3].c_str());
            cout << temp << endl;
            Q[i][3] = temp;
        }
        myfile.close();
        cout << "Learning Loaded" << endl;
    }
    else cout << "Unable to open file";
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
                if(learning_mode == 0){
                    plot_labyrinth(i,j);
                }
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
            current_iteration = iteraciones;           
            iteraciones++;
            if(iteraciones==max_iteration_per_episode || (i == win_i && j == win_j) ){
                break;  // end of episode
            }                
            
    } while(!kbhit());
    episode++;
    print_Q();    
    //gets(dummy); 
 } while((episode<max_episode && !kbhit()));  //  aqui controlamos cuantos episodios queremos ejecutar para entrenar
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
//------------------------------------------------------------- 
void Q_player_server(void)  
{ 
 int new_i,new_j; 
 int iter;      
 int dice, max;
 int initial_state, new_state;  
     
 //do 
  //{ 
    //initial_state=random(qSize*qSize);   //  se escioge el estado inicial 
    //state_to_coor(initial_state,&i,&j); 
    //make_graph();          // estado fijo, buscamos columna diferente de -1 
    initial_state = coor_to_state(i_player,j_player); 
    cout << "The initial point is: new i: " << i_player <<"new j: "<< j_player<< endl;    
    do     
    {      
        dice=0; 
        max=Q[initial_state][dice]; 
        for(iter=1;iter<4;iter++){ 
            if(Q[initial_state][iter]>max){ 
                dice = iter; 
                max = Q[initial_state][dice];  
            }                  // buscamos el valor mas alto de valores Q   
        } 
        new_i=i_player; 
        new_j=j_player; 
        if(dice==0)new_i--; 
        else if(dice==1)new_j++; 
        else if(dice==2)new_i++; 
        else new_j--;                
        new_state = coor_to_state(new_i,new_j); 
        cout << "new i: " << i_player <<"new j: "<< j_player<< endl;  
        cout << "new state: "<< new_state <<endl; 
        plot_labyrinth(i_player,j_player);
        if(slow==1){
            delay(500);
            }
        initial_state=new_state; 
        i_player=new_i; 
        j_player=new_j;

        if(kbhit()){
            int key = getch();
            if(key == '6'){
                break;
            }
        } 
 
        if((i_player==win_i && j_player==win_j))break;  // end of episode 
    } while(!kbhit() ); 
    //episode++;  
    //gets(dummy);  
 //} while(episode<50);  //  aqui controlamos cuantos episodios queremos ejecutar para entrenar 
    //  for(i=0;i<qSize*qSize;i++) 
    //  for(j=0;j<4;j++)  Q[i][j] = Q[i][j]/10;   // reduce el tama?o de entradas en Q 
}
 
//-------------------------------------------------------------
