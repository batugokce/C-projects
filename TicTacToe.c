/* Explanations *************************************************************************************************************************************
|
| The Tic-Tac-Toe board has 9 cells. We will assume that the cell numbering is as follows:
|
|   c0 | c1 | c2
|   ------------
|   c3 | c4 | c5
|   ------------
|   c6 | c7 | c8
|
****************************************************************************************************************************************************/




/* Includes ****************************************************************************************************************************************/

#include "Utilities.h"

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>   /* For standard input/output functions */

/***************************************************************************************************************************************************/




/* Definitions *************************************************************************************************************************************/

#define AUTHOR  ( "Batuhan Gokce" )  /* Author's name                                   */

#define EMPTY   ( ' '             )  /* Label for empty cells                           */
#define PLAYER1 ( 'X'             )  /* Label for player 1 and cells marked by player 1 */
#define PLAYER2 ( 'O'             )  /* Label for player 2 and cells marked by player 2 */

/***************************************************************************************************************************************************/




/* Type Definitions ********************************************************************************************************************************/

typedef unsigned char boolean ;

/***************************************************************************************************************************************************/




/* Global Variables ********************************************************************************************************************************/

char c0=EMPTY , c1=EMPTY , c2=EMPTY , c3=EMPTY , c4=EMPTY , c5=EMPTY , c6=EMPTY , c7=EMPTY , c8=EMPTY ;  /* Cells of the Tic-Tac-Toe board */
int playing;

/***************************************************************************************************************************************************/




/* Functions ***************************************************************************************************************************************/

/* Initializes the global variables. */

void initializeGlobalVariables ( void )
{
  /* TODO */
  /* ...  */
}

/*=================================================================================================================================================*/

/* Prints a banner including the author name. */

void printBanner ( void )
{
  printf(                                                                                   "\n"          ) ;
  printf( "*******************************************************************************" "\n"          ) ;
  printf( "* Tic-Tac-Toe                                                                 *" "\n"          ) ;
  printf( "* by %-72s *"                                                                    "\n" , AUTHOR ) ;
  printf( "*******************************************************************************" "\n"          ) ;
}

/*=================================================================================================================================================*/

/* Prints the current board configuration. */

void printBoard ( void )
{
	printf("\n    Cells                  Board\n"		);
	printf(".-----------.          .-----------.\n"		);
	printf("| 0 | 1 | 2 |          | %c | %c | %c |\n",c0,c1,c2);
	printf("|-----------|          |-----------|\n"		);
	printf("| 3 | 4 | 5 |          | %c | %c | %c |\n",c3,c4,c5);
	printf("|-----------|          |-----------|\n"		);
	printf("| 6 | 7 | 8 |          | %c | %c | %c |\n"  ,c6,c7,c8);
	printf("'-----------'          '-----------'\n"	);
}

/*=================================================================================================================================================*/

/* Gets the next move of "player", and marks it on the board.                     */
/* Loops (and asks again) if the input is not valid, or if the cell is not empty. */

void getNextMove ( char player )
{	

	boolean isInpTrue=FALSE;

	do
	{
		playing = -1;
		printf("\nPlayer %c, enter your next move (0-8) : ",player);

		if (scanf("%d",&playing))
		{	

			if (playing==0 || playing==1 || playing==2 || playing==3 || playing==4 || playing==5 || playing==6 || playing==7 || playing==8) /* checks if input is between 0-8 or not*/

			{
				if ((playing == 0 && c0 != EMPTY) || (playing == 1 && c1 != EMPTY) || (playing == 2 && c2 != EMPTY) || (playing == 3 && c3 != EMPTY) || (playing == 4 && c4 != EMPTY) || (playing == 5 && c5 != EMPTY) || (playing == 6 && c6 != EMPTY) || (playing == 7 && c7 != EMPTY) || (playing == 8 && c8 != EMPTY)) /* checks if cell is empty or not*/
				{
					printf("\nCell is not empty! Please try again.\n");
					clearInputBuffer(); /* if cell is full, it prints an error to user and clears the buffer*/
				}
				else 
				{
					clearInputBuffer(); /* if input is true, it clears the buffer and makes the variable true to terminate the loop*/
					isInpTrue = TRUE;

					if (player=='O')    /*it puts O or X depending the variable 'player'*/
					{
						switch (playing)
						{
							case 0: 
								c0='O';
								break;
							case 1:
								c1='O';
								break;
							case 2:
								c2='O';
								break;
							case 3:
								c3='O';
								break;
							case 4:
								c4='O';
								break;
							case 5:
								c5='O';
								break;
							case 6:
								c6='O';
								break;
							case 7:
								c7='O';
								break;
							case 8:
								c8='O';
								break;
						}
					}
					else if (player=='X')
					{
						switch (playing)
						{
							case 0: 
								c0='X';
								break;
							case 1:
								c1='X';
								break;
							case 2:
								c2='X';
								break;
							case 3:
								c3='X';
								break;
							case 4:
								c4='X';
								break;
							case 5:
								c5='X';
								break;
							case 6:
								c6='X';
								break;
							case 7:
								c7='X';
								break;
							case 8:
								c8='X';
								break;
						}
					}
				}				
			}	
			else 
			{
				printf("\nIncorrect input! Please try again.\n"); /*if input is incorrect, it prints an error and clears the buffer*/
				clearInputBuffer();
			}
		}
		else
		{
			printf("\nIncorrect input! Please try again.\n");
			clearInputBuffer();
		}

	} while (!isInpTrue); /*if input is correct, loop is terminated*/

}

/*=================================================================================================================================================*/

/* Checks if one of the players wins the game, or if the board is full and the game ended with a draw. Prints how the game ended. */
/* Returns TRUE if the game ended, otherwise, does not print anything and just returns FALSE.                                     */

boolean checkAndPrintGameResult ( void )
{
	if (c0 == c1 && c1 == c2 && c0 != EMPTY)  /*row*/
	{
		printf("\nPlayer %c WINS (top row)!\n",c0);
		return TRUE;
	}
	else if (c3 == c4 && c4 == c5 && c3 != EMPTY)
	{
		printf("\nPlayer %c WINS (middle row)!\n",c3);
		return TRUE;
	}
	else if (c6 == c7 && c7 == c8 && c6 != EMPTY)
	{
		printf("\nPlayer %c WINS (bottom row)!\n",c6);
		return TRUE;
	}
	else if (c0 == c3 && c0 == c6 && c0 != EMPTY)  /*column*/
	{
		printf("\nPlayer %c WINS (left column)!\n",c0);
		return TRUE;
	}
	else if (c1 == c4 && c4 == c7 && c1 != EMPTY)
	{
		printf("\nPlayer %c WINS (middle column)!\n",c1);
		return TRUE;
	}
	else if (c2 == c5 && c5 == c8 && c2 != EMPTY)
	{
		printf("\nPlayer %c WINS (right column)!\n",c2);
		return TRUE;
	}
	else if (c0 == c4 && c4 == c8 && c0 != EMPTY)  /*diagonal*/
	{
		printf("\nPlayer %c WINS (primary diagonal)!\n",c0);
		return TRUE;
	}
	else if (c2 == c4 && c4 == c6 && c2 != EMPTY)
	{
		printf("\nPlayer %c WINS (second diagonal)!\n",c2);
		return TRUE;
	}
	else
	{
		if (c0 != EMPTY && c1 != EMPTY && c2 != EMPTY && c3 != EMPTY && c4 != EMPTY && c5 != EMPTY && c6 != EMPTY && c7 != EMPTY && c8 != EMPTY)
		{
			printf("\nDRAW!\n");
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
}


/***************************************************************************************************************************************************/




/* Main Function ***********************************************************************************************************************************/

/* Initializes the global variables.                                                                                                          */
/* Prints banner.                                                                                                                             */
/* Randomly chooses one of the players to start first.                                                                                        */
/* Asks each player to make a move in turn until the game finishes (prints the board configuration each time before a player makes her move). */
/* Prints the game result.                                                                                                                    */
/* Prints a goodbye message.                                                                                                                  */
/* Prints the number of random numbers that were generated during the game play.                                                              */

int main ( void )
{
  char currentPlayer = ( ( randomIntegerMinMaxUnBiased( 0 , 1 ) == 0 ) ? PLAYER1 : PLAYER2 ) ;

  initializeGlobalVariables() ;
  printBanner              () ;
  printBoard               () ;

  do
  {
    getNextMove( currentPlayer ) ;
    printBoard (               ) ;


    if   ( currentPlayer == PLAYER1 )  { currentPlayer = PLAYER2 ; }
    else                               { currentPlayer = PLAYER1 ; }
  }
  while ( checkAndPrintGameResult() == FALSE ) ;

  printf( "\nGood game. Have a nice day!\n" ) ;

  printf( "\n%d random numbers were generated during the game play.\n\n" , numberOfRandomNumbersGenerated ) ;

  return 0 ;
}

/***************************************************************************************************************************************************/
