
#include "Main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#define ROWS 6
#define COLUMS 7
#define YEL  "\x1B[33m"
#define RED  "\x1B[31m"
#define BLU  "\x1B[34m"
#define RESET "\x1B[0m"

char matrix[ROWS][COLUMS];
char playerFlag;
bool end = false;
int colum;
int temprow;
int flagWinner = 0;
Stack playersMoves;

void main()
{
    Stack_Init(&playersMoves);
    Stack_Top(&playersMoves);

    printf("Welcome!\n\n");

    while(!end)
    {
        if(Stack_Full(&playersMoves) == 1)
        {
            printMatrix();
            printf("It's a tie!");
            exit(1);
        }
        printMatrix();
        PlayerX();
        printMatrix();
        PlayerO();
   
    }
}

//X's turn
void PlayerX(){

        printf("Player X, please enter a column number (or 0 to undo): ");
        playerFlag = 'X';
        put();
}

//Y's turn
void PlayerO(){

        printf("Player O, please enter a column number (or 0 to undo): ");
        playerFlag = 'O';
        put();
}

// Print the Matrix.
void printMatrix()
{
     for(int i = 0; i < 6; i++)
     {
        printf(BLU"|"RESET);
            for(int j = 0; j < 7; j++)
            {
                if(matrix[i][j] == 'O')
                {
                    printf(YEL"%c"RESET,matrix[i][j]);
                    printf(BLU"|"RESET);
                }
                else if(matrix[i][j] == 'X')
                {
                   printf(RED"%c"RESET,matrix[i][j]);
                   printf(BLU"|"RESET);
                }
                else
                {
                   printf("%c", matrix[i][j]);
                   printf(BLU"|"RESET);
                }
            }
        printf("\n");
     }
    
    printf(" 1 2 3 4 5 6 7\n");

}

// Give to the players put the coins.
void put()
{
 
    if(scanf("%d", &colum) != 1)
    {
            printf("\nInvalid input, bye-bye!");
            exit(1);
    }
    
    // Send to undo function if player choose '0'.
    else if(colum == 0)
    {
        if(Stack_Top(&playersMoves) != -1)
        {
            undo(Stack_Top(&playersMoves));
            Stack_Pop(&playersMoves);
        }
        else
        {
            printf("Board is empty - can't undo! Please choose another colum: \n");
            put();
        }   
    }

    else if(colum >= 1 && colum <= 7)
    {

        for(int i = 5; i > -1; i--)
        {  
             
            if(matrix[i][colum-1] != 'X' && matrix[i][colum-1] != 'O')
            { 
                matrix[i][colum-1] = playerFlag;
                Stack_Push(&playersMoves, colum);

                if((Stack_Size(&playersMoves)) > 6)
                {

                    temprow = i;
                    gameOver();
                }
                break;
            }

            if(matrix[0][colum-1] == 'X' || matrix[0][colum-1] == 'O')
            {
                printf("Invalid input, this column is full. Please choose another one: "); 
                put();
                break;
            }      
        }
    }
    else
    {
        printf("Invalid input, the number must be between 1 to 7: ");

        put();
        
    }
}

// Undo function to get back to the last situation. (When player do '0').
void undo(int pull)
{
     for(int i = 0; i < 6; i++)
        {       
             
            if(matrix[i][pull-1] == 'X' || matrix[i][pull-1] == 'O')
            { 
                matrix[i][pull-1] = ' ';
                break;
            }
        }
}

// Check if the game is finished (The function going from the last coin and check all the sides).
void gameOver()
{

    gameOver_Down();
    gameOver_Diagonal_TopRight_DownLeft();
    gameOver_Diagonal_TopLeft_DownRight();
    gameOver_Right_Left();

}

void gameOver_Down()
{

    for(int i = temprow+1; i < temprow+4; i++)
    {
        if (matrix[temprow][colum-1] != matrix[i][colum-1] || i == 6) break;
        else 
            flagWinner++;
    }
    Winner();
}

void gameOver_Diagonal_TopRight_DownLeft()
{

for(int i = temprow+1, j = colum-2; i < temprow+4, j > colum-5; i++, j--)
    {
        if (matrix[temprow][colum-1] != matrix[i][j] || i == 6 || j == -1) break;
        else
            flagWinner++;    
    }

for(int i = temprow-1, j = colum; i > temprow-4, j < colum+3; i--, j++)
    {
        if (matrix[temprow][colum-1] != matrix[i][j] || i == -1 || j == 7) break;
        else
            flagWinner++;
        
    }

    Winner();
}

void gameOver_Diagonal_TopLeft_DownRight()
{

    for(int i = temprow+1, j = colum; i < temprow+4, j < colum+3; i++, j++)
    {
          if (matrix[temprow][colum-1] != matrix[i][j] || i == 6 || j == 7) break;
          else
            flagWinner++;
    }

    for(int i = temprow-1, j = colum-2; i > temprow-4, j > colum-5; i--, j--)
    {
        if (matrix[temprow][colum-1] != matrix[i][j] || i == -1 || j == -1) break;
        else
            flagWinner++;
    }

    Winner();
}

void gameOver_Right_Left()
{

    for(int i = colum; i < colum+3 ;i++)
    {
        if (matrix[temprow][colum-1] != matrix[temprow][i] || i == 7 ) break;
        else
            flagWinner++;
    }
                  
    for(int i = colum-2; i > colum-5 ;i--)
    {
        if (matrix[temprow][colum-1] != matrix[temprow][i]  || i == -1) break;
        else
            flagWinner++;
    }
    Winner();

}


// Declares the winner.
void Winner()
{

    if(flagWinner >= 3)
    {
        printMatrix();
        printf("Player %c wins!", playerFlag);
        exit(1);
    }
    else
    {
        flagWinner = 0;
    } 
}
