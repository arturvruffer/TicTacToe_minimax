#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

//Prototypes
int minimax(char *board, int depth, int isMaximizing);
void ai_move();
int checkTie();


char board[10];    //Array of 9 characters and 0
char player;
char ai;

int gameRunning = 1;
char winner;

void init(){
    //Initialise board with empty characters
    for (int i= 0; i < 9; i++){
        board[i] = ' ';
    }
}


void print_board(){
    printf("\n");
    for (int i = 0; i < 9; i++){
        printf(" %c ", board[i]);
        if (i != 2 && i != 5 && i != 8){
            printf("|");
        }
        if ((i + 1) % 3 == 0 && i != 8){
            printf("\n---+---+---\n");
        }
    }
    printf("\n");
}

//Returns 1 if field is occupied
//Returns 0 if field is vacant
int field_occ(int field){
    if (field == -1){
        return 1; 
    }
    if (board[field] == ' '){
        return 0;
    }
    return 1;
}


//Makes the player's move on the board
void player_move(){
    int chosen_field = -1; //field_occ(-1) always returns 1 (true)

    //Asks user for input until they enter a valid field
    while (field_occ(chosen_field)){
        printf("\nEnter field[0-8]: ");
        scanf("%d", &chosen_field);
    }
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    board[chosen_field] = player;
}


//0: no win; 1: win
//Saves winner in winner variable
int checkWin(){
    winner = 0;
    char temp;  //Content of last checked field used for comparison


    //Checks for Wins in all three rows
    for (int row = 0; row < 3; row++){
        if (field_occ(row*3)){    
            temp = board[row * 3];  //Sets temp to the first element of the tested row

            //printf("Checking row %d\n", row);

            for (int col = 0; col < 3; col++){
                if (board[row * 3 + col] != temp){
                    break;
                }
                temp = board[row * 3 + col];

                //Returns Win if for loop has run 3 times without breaking
                if (col == 2){
                    winner = board[row *3];
                    return 1;
                }
            }
        }
    }

    //Checks for wins in all three columns
    for (int col = 0; col < 3; col++){
        if (field_occ(col)){
            temp = board[col];  //Sets temp to first element of tested column

            //printf("Checking col %d\n", col);

            for (int row = 0; row < 3; row++){
                if (board[row * 3 + col] != temp){
                    break;
                }
                temp = board[row * 3 + col];

                //Returns win if all three rows of a column have been compared
                if (row == 2){
                    winner = board[col];
                    return 1;
                }
            }
        }   
    }

    //Checks Diagonals for wins
    if (board[4] != ' '){
        if (board[0] == board[4] && board[4] == board[8]){
            winner = board[0];
            return 1;
        }
        if (board[6] == board[4] && board[4] == board[2]){
            winner = board[6];
            return 1;
        }
    }
    return 0;   //Returns 0 if no win was found
}


//Main game loop.
//Returns 0 for tie and 1 for a winner
int game(char cur_player){
    if (cur_player == player){
        player_move();
        //print_board();
        if (checkWin()){
            return 1;
        }
        //printf("Player has made a move\n");
    }
    if (cur_player == ai){
        ai_move();
        printf("\nThe AI has made a move!\n");
        print_board();
        if (checkWin()){
            return 1;
        }
    }
    //Check for tie
    if (checkTie()){
        return 0;
    }

    //Recursively call game loop function switching cur_player
    if (cur_player == 'X'){
        return game('O');
    }
    if (cur_player == 'O'){
        return game('X');
    }
}


//Returns 1 if game is tied
int checkTie(){
    int occ_spots = 0;    //Counts amount of occupied fields
    for (int i = 0; i < 9; i++){
        occ_spots = occ_spots + field_occ(i);
    }
    if (occ_spots == 9){
        return 1;
    }
    else{
        return 0;
    }
}



//Uses the minimax function for determining the best move
void ai_move(){
    int bestScore = -10000;
    int bestMove;
    for (int i = 0; i < 9; i++){
        //Check if spot is available
        if (field_occ(i) == 0){
            board[i] = ai;                      //Make move
            int score = minimax(board, 0, 0);   //Returns score of this move
            board[i] = ' ';                     //Undo move
            if (score > bestScore){
                bestScore = score;
                bestMove = i;
            }
        }
    }
    board[bestMove] = ai;   //Make the best move
}


//This function takes an input of a winner and returns the player's wanted score
int returnScoreOfWinner(){
    if (winner == ai){
        return 1;           //The ai is the maximizing player
    }
    if (winner == player){
        return -1;          //Player is the minimizing player
    }
}


int minimax(char *board, int depth, int isMaximizing){    
    if (checkWin()){    //Win = 1 = True
        return returnScoreOfWinner();
    }
    if (checkTie()){
        return 0;
    }

    if (isMaximizing){
        int bestScore = -10000;
        for (int i = 0; i < 9; i++){
            //Check if spot is available
            if (field_occ(i) == 0){
                board[i] = ai;
                int score = minimax(board, depth + 1, 0);
                board[i] = ' ';
                if (score > bestScore){
                    bestScore = score;
                }
            }
        }
    return bestScore;
    } else {
        int bestScore = 10000;
        for (int i = 0; i < 9; i++){
            //Check if spot is available
            if (field_occ(i) == 0){
                board[i] = player;
                int score = minimax(board, depth + 1, 1);
                board[i] = ' ';
                if (score < bestScore){
                    bestScore = score;
                }
            }
        }
    return bestScore;
    }
}


int main(void){
    init();

    char input;
    printf("Hello and welcome to TicTacToe! \nDo you want to play as [X] or as [O]? ");
    while (player != 'X' && player != 'O'){
        scanf("%c", &input);
        if (input == 'X' || input == 'O' || input == 'X' || input == 'O'){
            if (input == 'X' || input == 'x'){
                player = 'X';
                ai = 'O';
                printf("\n\nAlright. It's your turn then: \n\n");
            } else {
                player = 'O';
                ai = 'X';
            }
        }
    }
        

    if(player == 'X'){
        print_board();
    }

    if (game('X')){
        print_board();
        printf("\n%c has won the game!\n\n", winner);
    }
    else {
        print_board();
        printf("\nThe game ended in a tie!\n\n");
    }
}




