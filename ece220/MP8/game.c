#include "game.h"

//Sahil Shah
//sahils2
game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure)
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));
    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct
    mygame->rows = rows;//set the number of rows
    mygame->cols = cols;//set the number of cols
    mygame->score = 0;//set the score to zero
    //loops thru the 1D array and assign -1 to each cell
    int i,j;
    for(i=0;i<rows;i++){
      for(j=0;j<cols;j++){
        mygame->cells[i*cols+j] = -1;
      }
    }
    return mygame;
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any
	memory previously allocated is not lost in this function.
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

	 //YOUR CODE STARTS HERE:  Re-initialize all other variables in game struct
   (*_cur_game_ptr)->rows = new_rows;
   (*_cur_game_ptr)->cols = new_cols;
   (*_cur_game_ptr)->score = 0;
   //loop thru the 1D array and reset the specific cells to -1
   int i,j;
   for(i=0;i<new_rows;i++){
     for(j=0;j<new_cols;j++){
       (*_cur_game_ptr)->cells[i*new_cols+j] = -1;
     }
   }
	return;
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
{
    //YOUR CODE STARTS HERE
    const int MAX_COL = (cur_game)->cols;//number of columns specified by the game struct
    if(row>=0 && row<(cur_game->rows)){ //check if row is in bounds
      if(col>=0 && col<(cur_game->cols)){//check if col is in bounds
        return &(cur_game->cells[row*MAX_COL + col]);//return the address of the specfic cell
      }
    }
    return NULL;//else, return null
}
//passes testes and visual test
int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can
   not merge twice in one turn. If sliding the tiles up does not cause any
   cell to change value, w is an invalid move and return 0. Otherwise, return 1.
*/
{
    //YOUR CODE STARTS HERE
    //struct members, rows and cols
    const int ROW = (cur_game)->rows;
    const int COL = (cur_game)->cols;
    int last_combined_row = -1;
    int flag = 1; //validity flag for each move
    int i,j,k;//loops variables
    for(j=0;j<COL;j++){
      last_combined_row = -1;//reset the last_combined flag
      for(i=0;i<ROW;i++){//loop to slide up
          if((cur_game)->cells[i*COL+j] != -1){//if the cell is not empty//DO MERGE HERE!
            for(k=i-1;k>=0;k--){
              if((cur_game)->cells[k*COL+j] == -1){//if the cell above (i.e the target cell) is empty
                cur_game->cells[k*COL+j]=cur_game->cells[(k+1)*COL+j];//put the current row cell into the target row (target row == destination)
                cur_game->cells[(k+1)*COL+j]= -1;//clear current row;
                flag=1;//valid move
              }
              //if current row != last_combined row...start of merge
              if((k+1)*COL+j != last_combined_row){
                  if(cur_game->cells[(k)*COL+j] == cur_game->cells[(k+1)*COL+j]){//if val in target row == val current row
                      cur_game->cells[(k)*COL+j]*=2;//assign the target row to the sum of the two
                      cur_game->score+=cur_game->cells[(k)*COL+j];
                      cur_game->cells[(k+1)*COL+j]=-1;//set the current row to empty
                      last_combined_row=(k)*COL+j;//set last_combined_row to target row
                      flag=1;
                  }
              }
            }
        }
    }
  }

    return flag;
};

int move_s(game * cur_game)
{ //slide down
    //YOUR CODE STARTS HERE//YOUR CODE STARTS HERE
    const int ROW = cur_game->rows;
    const int COL = cur_game->cols;
    int last_combined_row=-1;
    int flag=0;
    int i,j,k;//loop variables
    for(j=0;j<COL;j++)
    {
        last_combined_row=-1;
        for(i=0;i<ROW;i++)
        {
            if((cur_game)->cells[i*COL+j] != -1)
            {//if the current cell is not empty
                for(k=i+1;k<ROW;k++)
                {//k is the index of the target row
                    if(cur_game->cells[k*COL+j]==-1)
                    {//if the target row is empty
                    cur_game->cells[k*COL+j] = cur_game->cells[(k-1)*COL+j];//put tile in current row into target row
                    cur_game->cells[(k-1)*COL+j]=-1;
                    flag=1;
                    }
                }
                for(k=ROW-1;k>i;k--){
                  if(cur_game->cells[(k)*COL+j] == cur_game->cells[(k-1)*COL+j] && (k-1)*COL+j != last_combined_row && cur_game->cells[(k)*COL+j]>0 && cur_game->cells[(k-1)*COL+j]>0){//if val in target row == val current row
                      cur_game->cells[(k)*COL+j]*=2;//assign the target row to the sum of the two
                      cur_game->score+=cur_game->cells[(k)*COL+j];
                      cur_game->cells[(k-1)*COL+j]=-1;//set the current row to empty
                      last_combined_row=(k)*COL+j;//set last_combined_row to target row
                      flag=1;
                }
            }
            for(k=i+1;k<ROW;k++)
            {//k is the index of the target row
                if(cur_game->cells[k*COL+j]==-1)
                {//if the target row is empty
                cur_game->cells[k*COL+j] = cur_game->cells[(k-1)*COL+j];//put tile in current row into target row
                cur_game->cells[(k-1)*COL+j]=-1;
                flag=1;
                }
            }

        }
      }
    }
    return flag;
};

int move_a(game * cur_game) //slide left
{
    //YOUR CODE STARTS HERE
    const int ROW = cur_game->rows;
    const int COL = cur_game->cols;
    int i,j,k;//loop variables
    int last_combined_col=-1;
    int flag=0;
    for(i=0;i<ROW;i++){
      last_combined_col=-1;
      for(j=0;j<COL;j++){
        if(cur_game->cells[i*COL+j] != -1){//if the current cell is not empty
          for(k=j-1;k>=0;k--){
            if((cur_game)->cells[i*COL+k] == -1){//check if the target col is empty
              cur_game->cells[i*COL+k]=cur_game->cells[i*COL+(k+1)];//put the current col cell into the target col (target col == destination)
              cur_game->cells[i*COL+(k+1)]= -1;//clear current col;
              flag=1;//valid move
            }
            //if current col != last combined col
            if(i*COL+(k+1) != last_combined_col){
              if(cur_game->cells[(i)*COL+k] == cur_game->cells[(i)*COL+(k+1)]){
                cur_game->cells[(i)*COL+k]*=2;//assign the target col to the sum of the two
                cur_game->score+=cur_game->cells[(i)*COL+k];
                cur_game->cells[(i)*COL+(k+1)]=-1;//set the current col to empty
                last_combined_col=(i)*COL+k;//set last_combined_col to target col
                flag=1;
              }
            }
          }
        }
      }
    }

    return flag;
};

int move_d(game * cur_game){ //slide to the right
  //YOUR CODE STARTS HERE
  const int ROW = cur_game->rows;
  const int COL = cur_game->cols;
  int i,j,k;//loop variables
  int last_combined_col=-1;
  int flag=0;
  for(i=0;i<ROW;i++){
    last_combined_col=-1;
    for(j=0;j<COL;j++){
      if(cur_game->cells[i*COL+j] != -1){//if the current cell is not empty
        for(k=j+1;k<COL;k++){
          if((cur_game)->cells[i*COL+k] == -1){//check if the target col is empty
            cur_game->cells[i*COL+k]=cur_game->cells[i*COL+(k-1)];//put the current col cell into the target col (target col == destination)
            cur_game->cells[i*COL+(k-1)]= -1;//clear current col;
            flag=1;//valid move
          }
        }
        for(k=COL-1;k>j;k--){
          if(cur_game->cells[(i)*COL+k] == cur_game->cells[i*COL+(k-1)] && i*COL+(k-1) != last_combined_col && cur_game->cells[(i)*COL+k]>0 && cur_game->cells[(i)*COL+(k-1)]>0){//if val in target row == val current row
              cur_game->cells[(i)*COL+k]*=2;//assign the target row to the sum of the two
              cur_game->score+=cur_game->cells[(i)*COL+k];
              cur_game->cells[i*COL+(k-1)]=-1;//set the current row to empty
              last_combined_col=(i)*COL+k;//set last_combined_row to target row
              flag=1;
        }
    }
    for(k=j+1;k<COL;k++){
      if((cur_game)->cells[i*COL+k] == -1){//check if the target col is empty
        cur_game->cells[i*COL+k]=cur_game->cells[i*COL+(k-1)];//put the current col cell into the target col (target col == destination)
        cur_game->cells[i*COL+(k-1)]= -1;//clear current col;
        flag=1;//valid move
      }
    }
      }
    }
  }

    return flag;
};

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1  there are possible legal moves, 0 if there are none.
 */
{
    const int ROW = cur_game->rows;
    const int COL = cur_game->cols;
    int i,j,a,b;//loop variables
    for(i=0;i<ROW;i++){
        for(j=0;j<COL;j++){
            if(cur_game->cells[i*COL+j] == -1)
                return 1;
        }
    }
    for(int a = 0; a < COL; a++)  //loops thru all cells
	{
		for(int b = 1; b < ROW; b++)  //loops thru all cells
		{
			if(cur_game->cells[b*COL+a] == cur_game->cells[COL*(b-1)+a] || cur_game->cells[b*COL+a] == cur_game->cells[COL*(b+1)+a])
				return 1; //if current index has same value as above or below it, set flag to valid
		}
	}
	for(int c = 0; c < ROW; c++)  //loops thru all cells
	{
		for(int d = 1; d < COL; d++)  //loops thru all cells
		{
			if(cur_game->cells[COL*(c)+d] == cur_game->cells[COL*(c)+d+1] || cur_game->cells[COL*(c)+d] == cur_game->cells[COL*(c)+d-1])
				return 1;//if current index has same value as to the left or right of it, set flag to valid
		}
	}
    return 0;
}


/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{

	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    if (cell_ptr == NULL){
        printf("Bad Cell Pointer.\n");
        exit(0);
    }


	//check for an empty cell
	int emptycheck = 0;
	int i;

	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}

    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game)
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;

	printf("\n\n\nscore:%d\n",cur_game->score);


	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char


    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  ");
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }

	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char

    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;

    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}

		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		}

		remake_game(&cur_game,rows,cols);

		move_success = 1;

    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }




    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game);
		 print_game(cur_game);
    }

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}
