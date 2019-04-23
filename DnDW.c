/* Explanations *************************************************************************************************************************************
|
| - The dungeon consists of a "start" room, an "exit" room, one room with "gold", one or more rooms with "wumpuses", and zero or more empty rooms.
| - "Start" and "exit" rooms are empty.
| - Other rooms can be empty, or can contain only a single entity (either gold, or wumpus). A room cannot contain more than one entities.
| - At the beginning of the game, the player sets the total number of rooms, and also the number of wumpuses.
| - Player starts in room "start".
| - All rooms are magical, and they all have 2 doors.
| - Doors might appear randomly in North, East, South or West directions.
| - Doors lead to randomly selected other rooms.
| - If the player visits the room with the gold, the player grabs the gold.
| - If the player visits a room with a wumpus in it, the wumpus eats the player, and the game finishes.
| - If the player visits the "exit" room, the game finishes. If the player has the gold with her, this is a successful finish.
|
****************************************************************************************************************************************************/




/* Includes ****************************************************************************************************************************************/

#include "Utilities.h"

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>   /* For standard input/output functions */

/***************************************************************************************************************************************************/




/* Definitions *************************************************************************************************************************************/

#define AUTHOR       ( "Batuhan Gökçe" )  /* Author's name                                                                   */

#define MIN_ROOMS    (  2              )  /* Minimum number of magical rooms in the dungeon (excluding start and exit rooms) */
#define MAX_ROOMS    (  8              )  /* Maximum number of magical rooms in the dungeon (excluding start and exit rooms) */
#define MIN_WUMPUSES (  1              )  /* Minimum number of wumpuses in the dungeon                                       */
#define MAX_WUMPUSES (  4              )  /* Maximum number of wumpuses in the dungeon                                       */

#define START        ( 'S'             )  /* Label for the start room                                                        */
#define EXIT         ( 'X'             )  /* Label for the exit room                                                         */
#define GOLD         ( 'G'             )  /* Label for the single room containing the gold                                   */
#define WUMPUS       ( 'W'             )  /* Label for room(s) containing a wumpus                                           */
#define EMPTY        ( 'E'             )  /* Label for empty room(s)                                                         */

/***************************************************************************************************************************************************/




/* Type Definitions ********************************************************************************************************************************/

typedef unsigned char boolean ;

/***************************************************************************************************************************************************/




/* Global Variables ********************************************************************************************************************************/

int     numberOfMagicalRooms                            ;
int     numberOfWumpuses                                ;
int     currentRoomNo=0                                 ;
boolean playerFoundGold                                 ;
char    r0 , r1 , r2 , r3 , r4 , r5 , r6 , r7 , r8 , r9 ; /* r0 is start room, r1 is exit room, others are magical rooms (at most 8 magical rooms) */
int roomNo=0,totalRoom;
boolean trueRoom=FALSE,trueWumpus=FALSE; /*in order to check if input is true or not*/
int numberOfEmpty;
boolean finishWumpus=FALSE,finishEmpty=FALSE;

/***************************************************************************************************************************************************/




/* Helper (Minor) Functions ************************************************************************************************************************/

/* The input is the room number, and the return value is the label for the room. */

char getRoomInformation ( int roomNo )
{
  switch ( roomNo )
  {
    default :
    case 0  : return r0 ;
    case 1  : return r1 ;
    case 2  : return r2 ;
    case 3  : return r3 ;
    case 4  : return r4 ;
    case 5  : return r5 ;
    case 6  : return r6 ;
    case 7  : return r7 ;
    case 8  : return r8 ;
    case 9  : return r9 ;
  }
}

/*=================================================================================================================================================*/

/* The input is the room label. The function prints out the information associated with the label. */

void printRoomInformation1 ( char room )
{
  switch ( room )
  {
    case START  : printf( "START"  ) ;  break ;
    case EXIT   : printf( "EXIT"   ) ;  break ;
    case GOLD   : printf( "GOLD"   ) ;  break ;
    case WUMPUS : printf( "WUMPUS" ) ;  break ;
    case EMPTY  : printf( "EMPTY"  ) ;  break ;
  }
}

/*=================================================================================================================================================*/

/* The input is the room number. The function prints out the information associated with the room. */

void printRoomInformation2 ( int roomNo )
{
  switch ( roomNo )
  {
    case 0 : printRoomInformation1( r0 ) ;  break ;
    case 1 : printRoomInformation1( r1 ) ;  break ;
    case 2 : printRoomInformation1( r2 ) ;  break ;
    case 3 : printRoomInformation1( r3 ) ;  break ;
    case 4 : printRoomInformation1( r4 ) ;  break ;
    case 5 : printRoomInformation1( r5 ) ;  break ;
    case 6 : printRoomInformation1( r6 ) ;  break ;
    case 7 : printRoomInformation1( r7 ) ;  break ;
    case 8 : printRoomInformation1( r8 ) ;  break ;
    case 9 : printRoomInformation1( r9 ) ;  break ;
  }
}

/*=================================================================================================================================================*/

/* The input is the direction. The function prints out the direction as a word, as an acronym and also displays an arrowhead. */

void printDirection ( int direction )
{
  switch ( direction )
  {
    case 0 : printf( "NORTH (N) ^" ) ;  break ;
    case 1 : printf( "EAST (E) >"  ) ;  break ;
    case 2 : printf( "SOUTH (S) v" ) ;  break ;
    case 3 : printf( "WEST (W) <"  ) ;  break ;
  }
}

/***************************************************************************************************************************************************/




/* Functions ***************************************************************************************************************************************/

/* Prints a banner including the author name. */

void printBanner ( void )
{
	printf("\n*******************************************************************************");
	printf("\n* Dungeons and Dragons with Wumpuses                                          *");
	printf("\n* by %s                                                            *",AUTHOR);
	printf("\n*******************************************************************************\n");
	
}

/*=================================================================================================================================================*/

/* Initializes all global variables.                                                                                    */
/* The number of magical rooms and the number of wumpuses are set by the player as part of the configuration process.   */
/* All possible errors in input should be handled by clearing the input buffer and asking the user again for the input. */

void configureWorld ( void )
{

	int erooms=0,wrooms=0,w1=0,e1=0; /*erooms:numberofEmptyrooms - wrooms:numberofWumpuses , e1 and w1 are for just convenience*/
	printf("\nLet's configure the DnDW World first!\n");
	
	do
	{
		printf("Enter number of magical rooms [%d,%d] : ",MIN_ROOMS,MAX_ROOMS);
		if (scanf("%d",&numberOfMagicalRooms))
		{
			if (numberOfMagicalRooms >= 2 && numberOfMagicalRooms <= 8) /*checks if input is true*/
			{
				trueRoom = TRUE;    /*if it is true input, variable becomes true to exit the loop*/
			}
			else
			{
				printf("Incorrect input! Please try again.\n");
				clearInputBuffer(); /*if it is erroneous input, buffer is cleared*/
			}	
		}
		else
		{
			printf("Incorrect input! Please try again.\n");
			clearInputBuffer();	    /*if it is erroneous input, buffer is cleared*/
		}
	} while (!trueRoom); /* if variable is true, loop is terminated*/

	trueRoom = FALSE;

	do
	{
		printf("Enter number of wumpuses [%d,%d]      : ",MIN_WUMPUSES,MAX_WUMPUSES);
		if (scanf("%d",&numberOfWumpuses))
		{
			if (numberOfWumpuses >= 1 && numberOfWumpuses <= 4 && numberOfWumpuses <= numberOfMagicalRooms - 1) /*checking if input is true or not again*/
			{
				trueWumpus = TRUE;		
			}
			else
			{
				printf("Incorrect input! Please try again.\n");
				clearInputBuffer();
			}	
		}
		else
		{
			printf("Incorrect input! Please try again.\n");
			clearInputBuffer();	
		}
	} while (!trueWumpus);

	trueWumpus = FALSE;

	printf("Configuration is finished. Good luck with the game play!\n");
	
	numberOfEmpty = numberOfMagicalRooms - numberOfWumpuses - 1;

	r0 = START; /*assigns first three rooms*/
	r1 = EXIT;
	r2 = GOLD;

	erooms = numberOfEmpty;
	wrooms = numberOfWumpuses;
	totalRoom = erooms + wrooms + 3;

	while (roomNo <= numberOfMagicalRooms+1) 
	{    /* assigning all rooms respectively. firstly wumpuses, then empty rooms. if wumpuses are done,remaining rooms become empty*/
		switch (roomNo)
		{
			case 3:
				if (finishWumpus == FALSE){
					r3 = WUMPUS;
					w1++;
				}
				else if (finishEmpty == FALSE){
					r3 = EMPTY;
					e1++;
				}
				break;
			case 4:
				if (finishWumpus == FALSE){
					r4 = WUMPUS;
					w1++;
				}
				else if (finishEmpty == FALSE){
					r4 = EMPTY;
					e1++;
				}
				break;
			case 5:
				if (finishWumpus == FALSE){
					r5 = WUMPUS;
					w1++;
				}
				else if (finishEmpty == FALSE){
					r5 = EMPTY;
					e1++;
				}
				break;
			case 6:
				if (finishWumpus == FALSE){
					r6 = WUMPUS;
					w1++;
				}
				else if (finishEmpty == FALSE){
					r6 = EMPTY;
					e1++;
				}
				break;
			case 7:
				if (finishWumpus == FALSE){
					r7 = WUMPUS;
					w1++;
				}
				else if (finishEmpty == FALSE){
					r7 = EMPTY;
					e1++;
				}
				break;
			case 8:
				if (finishWumpus == FALSE){
					r8 = WUMPUS;
					w1++;
				}
				else if (finishEmpty == FALSE){
					r8 = EMPTY;
					e1++;
				}
				break;
			case 9:
				if (finishWumpus == FALSE){
					r9 = WUMPUS;
					w1++;
				}
				else if (finishEmpty == FALSE){
					r9 = EMPTY;
					e1++;
				}
				break;
		}


		roomNo++;

		if (w1 == wrooms)  /*checks if wumpuses are done or not*/
			finishWumpus = TRUE;
		else
			finishWumpus = FALSE;
		if (e1 == erooms)
			finishEmpty = TRUE;
		else
			finishEmpty = FALSE;
	}
}

/*=================================================================================================================================================*/

/* Prints the configured world. */

void printWorld ( void )
{
	int i=0;
	printf("\nDnD World:\n");
	printf("----------\n");

	while (i < totalRoom){                   /*prints all rooms respectively*/
	
		printf("Room %d : ",i);
		printRoomInformation2(i);
		printf("\n");
		i++;
	}




}

/*=================================================================================================================================================*/

/* Prints the current room information and the doors of the current room.                                               */
/* Gets player's door choice as one of 'N', 'E', 'S', 'W' (small letters should also be accepted).                      */
/* All possible errors in input should be handled by clearing the input buffer and asking the user again for the input. */
/* Prints where the doors were actually opening to.                                                                     */
/* Updates current room number.                                                                                         */
/* If the current room contains gold, lets the player know that she now has gold in her posession.                      */

void getNextMove ( void )
{
	int dir1,dir2,rand1,rand2;               /* for directions                */
	char k1='0',k2='0',b1='0',b2='0',dir;    /* for letters of directions     */
	boolean trueInp=FALSE;                   /* for checking if input is true */

	printf("\nYou are in Room %d",currentRoomNo); /* prints room information*/
	printf("\nRoom information : ");
	printRoomInformation2(currentRoomNo);

	dir1 = randomIntegerMaxUnBiased ( 3 );
	do
	{
		dir2 = randomIntegerMaxUnBiased ( 3 );
	} while (dir1 == dir2);

	printf("\nThere is a door to your ");     /*prints near rooms' information*/
	printDirection ( dir1 );
	printf("\nAnd, there is another door to your ");
	printDirection ( dir2 );
	printf("\nWhich one will you choose? : ");

	switch (dir1)  /*to assign letters for directions to variables*/
	{
		case 0:
			k1 = 'n';
			b1 = 'N';
			break;
		case 1:
			k1 = 'e';
			b1 = 'E';
			break;
		case 2:
			k1 = 's';
			b1 = 'S';
			break;
		case 3:
			k1 = 'w';
			b1 = 'W';
			break;
	}
	switch (dir2)
	{
		case 0:
			k2 = 'n';
			b2 = 'N';
			break;
		case 1:
			k2 = 'e';
			b2 = 'E';
			break;
		case 2:
			k2 = 's';
			b2 = 'S';
			break;
		case 3:
			k2 = 'w';
			b2 = 'W';
			break;
	}



	do  /*chooses near rooms randomly*/
	{
		rand1 = randomIntegerMaxUnBiased ( totalRoom-1 );
	} while (rand1 == currentRoomNo); /*if near room equals current room, another room is chosen*/


	do
	{
		rand2 = randomIntegerMaxUnBiased ( totalRoom-1 );
	} while (rand1 == rand2 || rand2 == currentRoomNo);



	do
	{
		clearInputBuffer();

		if (scanf(" %c",&dir))
		{
			if (dir == k1 || dir == b1 || dir == k2 || dir == b2)
			{
				trueInp = TRUE; /* if input is correct, variable become true to exit the loop */
			}
			else
			{
 				printf("Incorrect input! Please try again : ");
			}
	
		}
		else
		{
			printf("Incorrect input! Please try again : ");
		}

	} while (!trueInp); /* checks the input true or not. if it is erroneous input, clear buffer and ask input again. */


	printf("Room to your ");
	printDirection ( dir1 );
	printf(" was Room %d\n",rand1);


	printf("Room to your ");
	printDirection ( dir2 );
	printf(" was Room %d\n",rand2);

	if (dir == k1 || dir == b1)
		currentRoomNo = rand1;
	else
		currentRoomNo = rand2;

}

/*=================================================================================================================================================*/

/* Checks if the current room that the player is in is the exit room.                                           */
/* If so, checks if the player already has the gold or not, and prints out an appropriate message in each case. */
/* Also checks if the player is in a room with a wumpus.                                                        */
/* If so, informs the player about the unhappy ending of the game.                                              */
/* Returns TRUE if the game ended, otherwise, does not print anything and just returns FALSE.                   */

boolean checkAndPrintGameResult ( void )
{
	char state = getRoomInformation ( currentRoomNo );

	if (state == 'X') /*prints room information and checks if the game is finished*/
	{
		if (playerFoundGold)
		{
			printf("You are safely out of the dungeon with the GOLD! Congratulations!\n");
			return TRUE;
		}
		else 
		{
			printf("You are safely out of the dungeon, but you did not find the GOLD! Better luck next time!\n");
			return TRUE;
		}	
	}
	else if (state == 'G')
	{
		printf("You have GOLD now!\n");
		playerFoundGold = TRUE; /*if gold is found, variable becomes true*/
		return FALSE;
	}
	else if (state == 'W' )
	{
		printf("Wumpus is full, and you are in heaven! What a pity!\n");
		return TRUE;
	}
	else
	{
		return FALSE;
	}

}

/***************************************************************************************************************************************************/




/* Main Function ***********************************************************************************************************************************/

/* Prints banner.                                                                */
/* Configures the dungeon world.                                                 */
/* Prints the configured world.                                                  */
/* Asks the player to make a move until the game finishes .                      */
/* Prints the game result.                                                       */
/* Prints a goodbye message.                                                     */
/* Prints the number of random numbers that were generated during the game play. */

int main ( void )
{
	printBanner();
	configureWorld();
	printWorld();


	while (!checkAndPrintGameResult())  /*checks whether game is finished or not in every turn*/
	{
		getNextMove();

	}

	printf("\nGood game. Have a nice day!\n");


	printf( "\n%d random numbers were generated during the game play.\n\n" , numberOfRandomNumbersGenerated ) ;


	return 0;
}

/***************************************************************************************************************************************************/
