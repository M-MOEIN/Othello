// here we try to find every valid move on a given map !
// reward map added 
#include <stdio.h>

#define WHITE '2'
#define BLACK '1'
#define EMPTY '0'

struct move{
    int row;
    int col;
    double reward; // just a big negetive numebr
};

void printBoard(char  board[8][8]){

    for ( int i=0; i<8; i++, putchar(10))
        for ( int j=0; j<8; j++,putchar(' '))
            putchar(board[i][j]);
    putchar('\n');
}

double rewardFor (int row , int col, double rewardBoard[4][4]){//gets row and col and returns reward value on that position
    while ( row > 3 || col > 3){
        if (row > 3) 
            row = 7 - row; 

        if (col > 3) 
            col = 7 - col; 
    }
    return rewardBoard[row][col];
}

void possibleMoves (char board[8][8] , int row , int col , char turn , double rewardBoard[4][4] , struct move * bestMove){
    char opositColor = (turn == BLACK) ? WHITE : BLACK;
    
    for (int i = -1; i<= 1; i++)
        for (int j= -1; j<=1 ; j++){
            double reward = 0;
            short int tempRow = row;
            short int tempCol = col;
            short int flag = 0;
            do{
                tempCol+=j;
                tempRow+=i;

                if ( board[tempRow][tempCol] == opositColor ){
                    flag = 1;
                    reward += rewardFor(tempRow , tempCol , rewardBoard);
                }
                    
                if ( board[tempRow][tempCol] == turn)
                    break;

                if ( ( board[tempRow][tempCol] == EMPTY  && flag == 0 ) || board[tempRow][tempCol] == '*' )
                    break;
                if (  board[tempRow][tempCol] == EMPTY  && flag == 1){
                    board[tempRow][tempCol] = '*';
                    printf("%d,%d  %d,%d  reward=%lf\n", tempRow+1, tempCol+1 , row+1 , col+1 , reward);
                    if ( bestMove->reward < reward ){
                        bestMove -> row = tempRow;
                        bestMove ->col = tempCol;
                        bestMove->reward = reward ;
                    }
                    break;
                }

            }while ( tempRow>=0 && tempRow<8 &&  tempCol>=0 && tempCol<8 );

        }
}
void findPiece(char board[8][8] , char turn , double rewardBoard[4][4] , struct move * bestMove ){ // ex. if turn = '2' finds white piesec for finding possible moves
    for (int i=0; i<8; i++)
        for (int j=0; j<8 ; j++)
            if ( board[i][j] == turn )
                possibleMoves(board , i , j , turn , rewardBoard , bestMove );
}

int main(){
    struct move bestMove ;
    bestMove.reward = -10000;
    char board[8][8] = {
        {'0' , '0' , '0', '0' , '0' , '0', '0' , '0'},
        {'0' , '0' , '0', '0' , '1' , '0', '0' , '0'},
        {'0' , '0' , '2', '1' , '2' , '2', '2' , '0'},
        {'0' , '2' , '2', '2' , '2' , '0', '1' , '0'},
        {'0' , '1' , '2', '1' , '1' , '1', '0' , '0'},
        {'0' , '0' , '2', '2' , '0' , '0', '0' , '0'},
        {'0' , '0' , '0', '0' , '0' , '0', '0' , '0'},
        {'0' , '0' , '0', '0' , '0' , '0', '0' , '0'}
    };
    double rewardBoard [4][4]={ 
                        {16.16, -3.03, 0.99 , 0.43}
                        ,{-4.12, -1.81 , -0.08 , -0.27}
                        ,{ 1.33 , -0.04 , 0.51 , 0.07}
                        ,{ 0.63 , -0.18 , -0.04 , -0.01} };

    puts ("INITIAL BOARD IS");
 //   printBoard(board);

    findPiece(board , BLACK , rewardBoard , &bestMove);

    puts("POSSIBLE MOVES FOR BLACK ARE MARKED BY * ");
    putchar(10);
    printBoard(board);

    puts("best move will be");
    printf("\n%d %d\n" , bestMove.row + 1, bestMove.col + 1);
    return 0;
}