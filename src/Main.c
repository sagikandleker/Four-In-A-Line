
#include "Main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#define YEL  "\x1B[33m"
#define RED  "\x1B[31m"
#define BLU  "\x1B[34m"
#define RESET "\x1B[0m"

//TODO -> 
// if input is no integer (Invalid input, bye-bye!)
// if input is 1.4 (for example) put to 1 and after that exit(1) with ERROR to "."

char cells[] = {'1',' ','2',' ','3',' ','4',' ','5',' ','6',' ','7'};
char matrix[6][7];
char playerFlag;
char colorFlag;
bool end = false;
int colum;
Stack playersMoves;
int temprow;
int movesCounter = 0;
int flagWinner = 0;


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

void PlayerX(){

        printf("Player X, please enter a column number (or 0 to undo): ");
        playerFlag = 'X';
        scanf("%d", &colum);
        printf("\n");
        put(colum);
}

void PlayerO(){

        printf("Player O, please enter a column number (or 0 to undo): ");
        playerFlag = 'O';
        scanf("%d", &colum);
        printf("\n");
        put(colum);
}

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
    
    printf(" %s\n\n", cells,"\n");
}

void put(int colum)
{
    if(colum == -1)
    {
        exit(1);
    }
    
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
            scanf("%d", &colum);
            put(colum);
        }
        
    }

    else if(colum >= 1 && colum<= 7)

    {

        for(int i = 5; i > -1; i--)
        {       
             
            if(matrix[i][colum-1] != 'X' && matrix[i][colum-1] != 'O')
            { 
                matrix[i][colum-1] = playerFlag;
                Stack_Push(&playersMoves, colum);
                movesCounter++;
                if(movesCounter > 6)
                {
                    temprow = i;
                    gameOver();
                }
                break;
            }

            if(matrix[0][colum-1] == 'X' || matrix[0][colum-1] == 'O')
            {
                printf("Invalid input, this column is full. Please choose another one: "); 
                scanf("%d", &colum);
                put(colum);
                break;
            }      
        }
    }
    else
    {
        printf("Invalid input, the number must be between 1 to 7: ");
        scanf("%d", &colum);
        put(colum);
    }
}

void undo(int delete)
{
     for(int i = 0; i < 6; i++)
        {       
             
            if(matrix[i][delete-1] == 'X' || matrix[i][delete-1] == 'O')
            { 
                matrix[i][delete-1] = ' ';
                break;
            }
        }
}

void gameOver()
{

    // Right
   for(int i = colum; i < colum+3 ;i++)
    {
        if (matrix[temprow][colum-1] != matrix[temprow][i] || i == 7 || i == -1) break;
        flagWinner++; 
    }
    Winner();
                  
    // Left
    for(int i = colum-2; i > colum-5 ;i--)
    {
        if (matrix[temprow][colum-1] != matrix[temprow][i] || i == 7 || i == -1) break;
        flagWinner++;
    }
    Winner();

    // Down
    for(int i = temprow+1; i < temprow+4; i++)
    {
        if (matrix[temprow][colum-1] != matrix[i][colum-1] || i == 6) break;
        flagWinner++;
    }

    // Diagonal top right.
    for(int i = temprow-1, j = colum; i > temprow-4, j < colum+3; i--, j++)
    {
        if (matrix[temprow][colum-1] != matrix[i][j] || i == 6 || j ==7) break;
        flagWinner++;
    }
    Winner();

     // Diagonal top left.
    for(int i = temprow-1, j = colum-2; i > temprow-4, j > colum-5; i--, j--)
    {
        if (matrix[temprow][colum-1] != matrix[i][j] || i == 6 || j ==7) break;
        flagWinner++;
    }
    Winner();

    // Diagonal down left.
    for(int i = temprow+1, j = colum-2; i < temprow+4, j > colum-5; i++, j--)
    {
        if (matrix[temprow][colum-1] != matrix[i][j] || i == 6 || j ==7) break;
        flagWinner++;
    }
    Winner();

    // Diagonal down right.
    for(int i = temprow+1, j = colum; i < temprow+4, j < colum+3; i++, j++)
    {
        if (matrix[temprow][colum-1] != matrix[i][j] || i == 6 || j ==7) break;
        flagWinner++;
    }
    Winner(); 
}

void Winner()
{
    if(flagWinner == 3)
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
