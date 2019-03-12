// Inverse Integer

#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<dos.h>

#define arrRow 3
#define arrCol 3

#define selectCell 0x70
#define noSelectCell 0x07

#define Up 72
#define Down 80
#define Left  77
#define Right 75
#define Enter 13
#define e 101
#define p 112

//----------------------------- Global Variable
int row = 0, col = 0, flag = 0, flagExitOrPlayAgain=0, arrPlayerRowCol_old[2][2];// Col ==> x, Row ==> y
int oPlayer = 0, xPlayer = 0, flagOPlayer = 0, flagXPlayer = 0;
char Player[2][2] = {{'1','o'},{'2','x'}}, key;
int flagEnter = 0, indexPlayer = 0, sum = 0;
char arr[arrRow][arrCol] = {{'o', 'o', 'o'},{ ' ', ' ', ' '},{ 'x', 'x', 'x'}};
int arrPlayer[arrRow][arrCol] = {{3, 3, 3}, {0, 0, 0}, {4,4,4}};
int arrSucess[4][3] ={{4,4,4},{4,4,4},{4,4,4},{4,4,4}};//No of row and column for each player

//----------------------------- Function
void initializePlayAgain(void);
void askExitOrPlayAgain(void);
void print(void);
int move(void);
int win(int sum);
void checkMovedAllI(void);


//------------------------------- Main
int main(){



   do{
		print();
	   flag = move();
	   if(flag == 0)
			checkMovedAllI();
   }while(flag != -100);

   //	getch();
	return 0;
}

//-----------------------------------   Print Game
void print(){
	int i, j;
	clrscr();
	printf("Player 1 is o \nPlayer 2 is x \n\n  Hint: Player 1 plays first\n\n\n");
	for(i = 0; i < arrRow+1; i++){//arrRow+1 to draw ---- 4 times
		for(j = 0; j < 19; j++){
			  printf("-");
		}
		if(i !=3){
			printf("\n");
			for(j = 0; j < arrCol; j++){ // To print column
				if(i == row && j == col)
					textattr(selectCell);
				cprintf("|  %c  ", arr[i][j]);
				textattr(noSelectCell);
			}
			printf("|\n");
		}
	}

	if(flagExitOrPlayAgain == 1){ // To display
		win(sum);


	}
}
//----------------------------------
int move(){

	if(flagExitOrPlayAgain != 1){
		key = getch();
		if(key == NULL){
			key = getch();
	   //	printf("%d", ch); getch;
			if(key == Up){
		  //	printf("Up");
				if(row <=0)
					row = 0;
				else
					row--;
			}else if(key == Down){
		   //	printf("Down");
				if(row >= arrRow-1)
					row = arrRow-1;
				else
					row++;
			}else if(key == Right){
		   //	printf("right");
				if(col <= 0)
					col = 0;
				else
					col--;
			}else if(key == Left){
		   //	printf("Left");
				if(col >= arrCol-1)
					col = arrCol-1;
				else
					col++;
			}


		}else if(key == Enter){
	   //	printf("%d", indexPlayer);
			if(indexPlayer == 0 && arr[row][col] == 'x'){// To check if this is player 1 and take x of player 2
		   //	delay(1000);
				printf("Round: Player 1");
				delay(1000);
				return 0;
			} else if(indexPlayer == 1 && arr[row][col] == 'o'){//To Prevent player 2 to take o of player1
		  //	delay(1000);
				printf("Round: Player 2");
				delay(1000);
				return 0;
			}
			if(flagEnter == 0 && arrPlayer[row][col] != 0){ // To click x or o and remove it
				arr[row][col] =' ';
				arrPlayer[row][col] = 0;
				arrPlayerRowCol_old[indexPlayer][0] = row;
				arrPlayerRowCol_old[indexPlayer][1] = col;

				flagEnter = 1;
			} else if(  flagEnter == 1 &&arrPlayer[row][col] == 0){// Click enter for 2nd time to place xo
				arr[row][col] = Player[indexPlayer][1]; //'o'

				if(arrPlayerRowCol_old[indexPlayer][0] == row && arrPlayerRowCol_old[indexPlayer][1] == col) {
				//To check if he doesn't move x or o then doesnt change weight
				}else{
					arrPlayer[row][col] = Player[indexPlayer][0];//'1'
				}
				flagEnter = 0;
				if(indexPlayer == 0)
					indexPlayer = 1;
				else
					indexPlayer = 0;
			}
		}
	}

	 if(key == e){

		return -100;
	}else if(key == p){
		initializePlayAgain();
		return 0;
	}else{
		return 0;
	}
   //	delay(1000);
   //	return 0;

}
//----------------------- Check
void checkMovedAllI(){
	int i, j,sumDiagonal1=0, sumDiagonal2=0;
	for(i = 0; i < arrRow; i++){
		for(j = 0; j < arrCol; j++){
			if(arrPlayer[i][j] == 3){
				oPlayer++;
			}else if(arrPlayer[i][j] == 4){
				xPlayer++;
			}

			sum += arrPlayer[i][j];
			flag = win(sum);


		}
		sum = 0;
		if(flag != -100){
			sumDiagonal1 += arrPlayer[i][i];
			flag = win(sumDiagonal1);
		}
		if(flag != -100){
			sumDiagonal2 += arrPlayer[i][arrRow - i - 1];
			flag = win(sumDiagonal2);
		}
	}
	  //Summation For Column

		if(flag != -100){
			for(i = 0; i < arrCol; i++){
				sum = 0;
			for(j = 0; j < arrRow; j++){
				sum += arrPlayer[j][i];
				flag = win(sum);
			}
		  //	printf("\n flag = %d sum = %d", flag, sum);delay(1000);
			sum = 0;

		}

	}
	// To check if players move from initial cell to another one or they move to the same cell
	if(oPlayer == 0){
	  //	printf("Player O Moved");
		flagOPlayer = 1;
	}
	if(xPlayer == 0){
	   //	printf("Player X Moved");
		flagXPlayer =1;
	}
	oPlayer = 0;
	xPlayer = 0;

}

//---------------------- Who is winner

int win(int sum){
	// printf("sum = %d \n", sum);delay(1000);
	if(flagXPlayer == 1 && sum == 50*3){// '2' ascii is 50
		printf("\nPlayer 2 is the winner\n");
		askExitOrPlayAgain();
		return -100;
	}else if(flagOPlayer == 1 && sum == 49*3){// '1' ascii is 49
		printf("\nPlayer 1 is the winner \n");
		askExitOrPlayAgain();
		return -100;
	}
	return 0;
}

//----------------
void askExitOrPlayAgain(){
	printf("\n Press e to Exit :)");
	printf("\n Press p to Play again :)");
	flagExitOrPlayAgain = 1;
	key = getch();

}


//---------------

void initializePlayAgain(){

	char arr1[arrRow][arrCol] = {{'o', 'o', 'o'},{ ' ', ' ', ' '},{ 'x', 'x', 'x'}};
	int arrPlayer1[arrRow][arrCol] = {{3, 3, 3}, {0, 0, 0}, {4,4,4}};
	int arrSucess1[4][3] ={{4,4,4},{4,4,4},{4,4,4},{4,4,4}};//No of row and column

	sum = 0;
	row = 0;
	col = 0;
	flag = 0;
	flagExitOrPlayAgain=0;

   oPlayer = 0;
   xPlayer = 0;
   flagOPlayer = 0;
   flagXPlayer = 0;

   flagEnter = 0;
   indexPlayer = 0;

   memcpy(arr, arr1, sizeof arr1);
   memcpy(arrPlayer, arrPlayer1, sizeof arrPlayer1);
   memcpy(arrSucess, arrSucess1, sizeof arrSucess1);



}