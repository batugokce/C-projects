/* Explanations *************************************************************************************************************************************
|
| This file implements CengBook, which is a realistic simulation of a mini social-media application.
|
****************************************************************************************************************************************************/




/* Includes ****************************************************************************************************************************************/

#include "Utilities.h"

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***************************************************************************************************************************************************/




/* Macro Definitions *******************************************************************************************************************************/

#define AUTHOR ( "Batuhan Gokce" )  /* Author's name */  /* TODO: Replace with your name */

/***************************************************************************************************************************************************/




/* Global Variable Definitions *********************************************************************************************************************/

BookPtr bookPtr ;

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

#if   defined(_WIN16) || defined(_WIN32) || defined(_WIN64)

  char operatingSystem[] = "Windows" ;  /* This is a Windows environment.                            */

#elif defined(__linux__)

  char operatingSystem[] = "Linux"   ;  /* This is a Linux environment (any GNU/Linux distribution). */

#elif defined(__APPLE__)

  char operatingSystem[] = "MacOSX"  ;  /* This is a Mac OS X environment.                           */

#endif

/***************************************************************************************************************************************************/




/* Functions ***************************************************************************************************************************************/

void printUsage ( String applicationName )
{
  NL ;

  printf( "Usage: %s <MaxNumberOfUsers> <MaxUserNameLength> <MaxNumberOfFriendsPerUser>\n\n" , applicationName ) ;
}

/*=================================================================================================================================================*/

void printBanner ( void )
{
  NL ;

  printf( "*******************************************************************************" "\n"          ) ;
  printf( "* CengBook                                                                    *" "\n"          ) ;
  printf( "* by %-72s *"                                                                    "\n" , AUTHOR ) ;
  printf( "*******************************************************************************" "\n"          ) ;
}

/*=================================================================================================================================================*/

void printMenu ( void )
{
  NL ;

  printf( "*******************************************************************************" "\n" ) ;
  printf( "Help                       : Print this menu"                                    "\n" ) ;
  printf( "List                       : List all users"                                     "\n" ) ;
  printf( "Plot                       : Create a plot of CengBook (requires GraphViz)"      "\n" ) ;
  printf( "Quit                       : Exit application"                                   "\n" ) ;
  printf( "-------------------------------------------------------------------------------" "\n" ) ;
  printf( "Register   <user>          : Create a new user and add it to CengBook"           "\n" ) ;
  printf( "Delete     <user>          : Delete user from CengBook"                          "\n" ) ;
  printf( "Find       <user>          : Search CengBook for user, display user information" "\n" ) ;
  printf( "Connect    <user1> <user2> : Add a connection from user1 to user2"               "\n" ) ;
  printf( "Disconnect <user1> <user2> : Remove connection from user1 to user2"              "\n" ) ;
  printf( "Path       <user1> <user2> : Find shortest path from user1 to user2"             "\n" ) ;
  printf( "-------------------------------------------------------------------------------" "\n" ) ;
  printf( "Sort <abc|pop> <asc|desc>  : Sort all users (alphabetically or by popularity)"   "\n" ) ;
  printf( "*******************************************************************************" "\n" ) ;
}

/*=================================================================================================================================================*/

void commandHelp ( void )
{
	printMenu();
}

/*=================================================================================================================================================*/

void commandList ( void )
{
	int i = 0;
	
	if ( bookPtr->userPointers[0] == NULL ) { printf("\n  CengBook is empty"); }
	
	else {
		while (i < getMaxNumberOfUsers() && bookPtr->userPointers[i] != NULL ){
			int j = 16 - strlen( bookPtr->userPointers[i]-> name );	
			int k = 0;

			printf("\n  %s",(bookPtr->userPointers[i])-> name );
	
			while ( k < j ) { printf(" "); k++; }
		
			printf(": %d Follower(s) , %d Friend(s)", bookPtr->userPointers[i]-> numberOfFollowers
								  , bookPtr->userPointers[i]-> numberOfFriends );

			i++;			
		}
	}

	NL;
}

/*=================================================================================================================================================*/

void commandPlot ( void )
{
  /*-----------------------------------------------------------------------------------------------------------------------------------------------*/

  UserPtr   userPtr             , friendPtr              ;
  int       userIndex           , friendIndex            ;
  String    runDotSystemCommand , openImageSystemCommand ;

  FILE    * file = fopen( "CengBook.dot" , "w" )         ;

  /*-----------------------------------------------------------------------------------------------------------------------------------------------*/

  fprintf( file , "digraph CengBook"                                                       "\n"                            ) ;
  fprintf( file , "{"                                                                      "\n"                            ) ;
  fprintf( file , "  graph [label=\"CengBook\\nNumber of users = %d\" , labelloc=t] ;"     "\n\n" , bookPtr->numberOfUsers ) ;
  fprintf( file , "  node  [shape=ellipse , fontcolor=black , color=red , penwidth=2.0] ;" "\n\n"                          ) ;
  fprintf( file , "  edge  [color=blue , penwidth=2.0] ;"                                  "\n\n"                          ) ;

  /*-----------------------------------------------------------------------------------------------------------------------------------------------*/

  for ( userIndex = 0 ; userIndex < bookPtr->numberOfUsers ; userIndex++ )
  {
    userPtr = bookPtr->userPointers[ userIndex ] ;

    fprintf( file , "  %s [label=\"%s\\n%d Friend(s)\\n%d Follower(s)\"] ;\n" ,
             userPtr->name                                                    ,
             userPtr->name                                                    ,
             userPtr->numberOfFriends                                         ,
             userPtr->numberOfFollowers                                       ) ;
  }

  if ( bookPtr->numberOfUsers > 0 )  { fprintf( file , "\n" ) ; }

  /*-----------------------------------------------------------------------------------------------------------------------------------------------*/

  for ( userIndex = 0 ; userIndex < bookPtr->numberOfUsers ; userIndex++ )
  {
    userPtr = bookPtr->userPointers[ userIndex ] ;

    for ( friendIndex = 0 ; friendIndex < userPtr->numberOfFriends ; friendIndex++ )
    {
      friendPtr = userPtr->friendPointers[ friendIndex ] ;

      fprintf( file , "  %s -> %s ;\n" , userPtr->name , friendPtr->name ) ;
    }
  }

  /*-----------------------------------------------------------------------------------------------------------------------------------------------*/

  fprintf( file , "}\n" ) ;
  fclose ( file         ) ;

  /*-----------------------------------------------------------------------------------------------------------------------------------------------*/

  if ( strcmp( operatingSystem , "Windows" ) == 0 )
  {
    runDotSystemCommand    = "CMD /C dot -Tgif CengBook.dot -o CengBook.gif" ;
    openImageSystemCommand = "CMD /C START CengBook.gif"                     ;
  }
  else  /* Assumption: Linux */
  {
    runDotSystemCommand    = "dot -Tgif CengBook.dot -o CengBook.gif"        ;
    openImageSystemCommand = "xdg-open CengBook.gif &"                       ;
  }

  if ( system( runDotSystemCommand    ) ) ;  /* "if" statement is used to eliminate warning about unused return value of "system" call */
  if ( system( openImageSystemCommand ) ) ;  /* "if" statement is used to eliminate warning about unused return value of "system" call */

  NL ;  I2 ;  printf( "Plot prepared\n" ) ;

  /*-----------------------------------------------------------------------------------------------------------------------------------------------*/
}

/*=================================================================================================================================================*/

void commandQuit ( void )
{
	deallocateBook ( bookPtr );
	
	printf("\n  Have a nice day\n\n");
	exit( 0 );
}

/*=================================================================================================================================================*/

void commandRegister ( String userName )
{
	int i = 0, j = 0, max = getMaxUserNameLength();
	
	
	if ( strlen(userName) > max ) { NL; I2; printf("User name is longer than %d characters!",max); NL; return;}
	
	while ( j < bookPtr->numberOfUsers ) {
		
		if ( strcmp( userName , bookPtr->userPointers[j]->name ) == 0 ) {
			NL; I2; printf("User '%s' already registered!",userName); NL;
			return;
		}
		j++;	
	}



	while ( bookPtr->userPointers[i] != NULL ) { i++; }

	if ( i < getMaxNumberOfUsers() ) {
		bookPtr -> userPointers[i] = allocateUser( userName );
		bookPtr -> numberOfUsers++;
	

		printf("\n  User '%s' registered successfully\n",userName);
	}
	else {
		printf("\n  CengBook is full, cannot register any new users!\n");
	}

}

/*=================================================================================================================================================*/

void commandDelete ( String userName )
{
	int i = 0, j = 0, k = 0;
	int max = getMaxNumberOfUsers();
	UserPtr user = getUserPtrByName ( bookPtr , userName );

	if ( user == NULL ) { NL; I2; printf("User '%s' not found in CengBook!",userName); NL; }

	else {
		NL;

		while ( i < max && bookPtr->userPointers[i] != NULL ){
			if ( removeConnection ( bookPtr->userPointers[i] , user ) ) {
				printf("  User '%s' is removed from friends of user '%s'\n",userName,bookPtr->userPointers[i]-> name);
			}

			i++;
			
		}


		while ( j < max && user->friendPointers[j] != NULL ){

			if ( isConnected( user , user->friendPointers[j] ) ) {
				printf("  User '%s' is discounted from followers of user '%s'\n",userName,user->friendPointers[j]->name);
				removeConnection ( user , user->friendPointers[j] );
				
			}
		}


		I2;
	
		k = getUserIndexByPtr ( bookPtr , getUserPtrByName ( bookPtr , userName ) );
		deallocateUser ( getUserPtrByName ( bookPtr , userName ) );



		while ( k + 1 < max && bookPtr->userPointers[k+1] != NULL  ) {

			bookPtr->userPointers[k] = bookPtr->userPointers[k+1];

			k++;

		}

		bookPtr->userPointers[k] = NULL;
		bookPtr->numberOfUsers--;

		printf("User '%s' is deleted from CengBook\n",userName);
	}


}

/*=================================================================================================================================================*/

void commandFind ( String userName )
{
	UserPtr user = getUserPtrByName ( bookPtr , userName );
	
	if ( user == NULL ) { NL; I2; printf("User '%s' not found in CengBook!\n",userName); }
	else { NL; printUser( user ); }
	
}

/*=================================================================================================================================================*/

void commandConnect ( String userName1 , String userName2 )
{
	int i = 0,j = 0, k = 0;
	UserPtr user1 = getUserPtrByName ( bookPtr , userName1 );
	UserPtr user2 = getUserPtrByName ( bookPtr , userName2 );

	if ( user1 == NULL || user2 == NULL ) {
		NL;
		if ( user1 == NULL ) { I2; printf("User '%s' not found in CengBook!",userName1); NL; j=1; }
		if ( user2 == NULL ) { I2; printf("User '%s' not found in CengBook!",userName2); NL; j=1; }
		return ;
	}

	if ( user1 == user2) { NL; I2; printf("Connection to self is not allowed!"); NL; return ; }
	
	while ( user1 -> friendPointers[k] != NULL ) {
		if ( user1 -> friendPointers[k] == user2 ) {
			NL; I2;
			printf("User '%s' is already connected to user '%s'!\n",user1->name,user2->name);
			return;
		}
		k++;
	}	
	
	if ( !j ) {

		while ( i < getMaxNumberOfFriendsPerUser () ){
			if ( user1->friendPointers[i] == NULL ) { break; }
			i++;
		}
		if ( i == getMaxNumberOfFriendsPerUser () ) { printf("\n  Friend capacity of user '%s' is full!",userName1); }
	
		else {
			user1->friendPointers[i] = user2;
			user1->numberOfFriends++;
			user2->numberOfFollowers++;
			printf("\n  User '%s' successfully connected to user '%s'",userName1,userName2);
		}
	}

	NL;
}

/*=================================================================================================================================================*/

void commandDisconnect ( String userName1 , String userName2 )
{
	int i = 0, j = 0;
	UserPtr user1 = getUserPtrByName ( bookPtr , userName1 );
	UserPtr user2 = getUserPtrByName ( bookPtr , userName2 );

	if ( user1 == NULL || user2 == NULL ) {
		NL;
		if ( user1 == NULL ) { I2; printf("User '%s' not found in CengBook!",userName1); NL; j=1; }
		if ( user2 == NULL ) { I2; printf("User '%s' not found in CengBook!",userName2); NL; j=1; }
		return;
	}

	if ( user1 == user2) { NL; I2; printf("Disconnecting from self is not allowed!"); NL; return ; }

	if ( !j ) {
		while ( i < getMaxNumberOfFriendsPerUser () && user1->friendPointers[i] != NULL) {

			if ( compareByName ( user1->friendPointers[i] , user2 ) == 0 ) {
				break;
			}

			i++;
		} 

		if ( i == getMaxNumberOfFriendsPerUser () || user1->friendPointers[i] == NULL ) {
			NL; I2; printf("User '%s' and user '%s' are not connected!",userName1,userName2);
		}
		else {
			while ( (i+1) < getMaxNumberOfFriendsPerUser () && user1->friendPointers[i+1] != NULL) {

				user1->friendPointers[i] = user1->friendPointers[i+1];
				i++;
			}
			user1->friendPointers[i] = NULL;

			user1->numberOfFriends--;
			user2->numberOfFollowers--;
			NL; I2; printf("User '%s' successfully disconnected from user '%s'",userName1,userName2);
		}
	}

	NL;
}

/*=================================================================================================================================================*/

void commandPath ( String userName1 , String userName2 )
{
	int i = 1;
	
	UserPtr user1 = getUserPtrByName ( bookPtr , userName1 );
	UserPtr user2 = getUserPtrByName ( bookPtr , userName2 );
	UserPtrArray path;


	if ( user1 == NULL || user2 == NULL ) {
		NL;
		if ( user1 == NULL ) { I2; printf("User '%s' not found in CengBook!",userName1); NL;}
		if ( user2 == NULL ) { I2; printf("User '%s' not found in CengBook!",userName2); NL;}
		return;
	}

	if ( user1 == user2 ) { NL; I2; printf("Path to self queried!"); NL; return; }

	path = shortestPath ( bookPtr , user1 , user2 );

	if ( path != NULL ) {

		NL; I2; printf("'%s'",path[0]->name);		

		while ( path[i] != NULL ) {
			printf(" -> '%s'",path[i]->name);
			i++;
		}
	}
	
	else { NL; printf("  There is no path from user '%s' to user '%s'",userName1,userName2); }


	NL;
}

/*=================================================================================================================================================*/

void commandSort ( String criterion , String order )
{
	int asc,j = 0;
	int (*fp) ( UserPtr , UserPtr );
	
	if      ( strcmp(criterion,"abc") == 0)   { fp = compareByName; }
	else if ( strcmp(criterion,"pop") == 0)   { fp = compareByPopularity; }
	else    { NL; I2; printf("Invalid sort criterion '%s'!",criterion); j=1; }

	if ( strcmp(order,"asc") == 0)         { asc = 1; }
	else if ( strcmp(order,"desc") == 0)   { asc = 0; }
	else { NL; I2; printf("Invalid sort order '%s'!",order); j=1; }

	if ( j ) { NL; return ; }
	
	sortBook( bookPtr , fp , asc );
	
	NL; I2;
	
	if ( fp == compareByName ) {
		if  ( asc == 1 ){ printf("CengBook sorted 'alphabetically' in 'ascending' order"); }
		else            { printf("CengBook sorted 'alphabetically' in 'descending' order"); }
	}
	else if ( fp == compareByPopularity ) {
		if  ( asc == 1 ){ printf("CengBook sorted 'by popularity' in 'ascending' order");  }
		else            { printf("CengBook sorted 'by popularity' in 'descending' order");  }
	}	
	
	NL;
}

/*=================================================================================================================================================*/

void processInput ( String input )
{
  int         i                                                    ;
  int         numberOfTokens = 0                                   ;
  StringArray tokens         = tokenize( input , &numberOfTokens ) ;
  String      command                                              ;

  if ( numberOfTokens < 1 )  { return ; }

  command = tokens[0] ;

  for ( i = 0 ; i < strlen( command ) ; i++ )  { if ( ( command[i] >= 'A' ) && ( command[i] <= 'Z' ) )  { command[i] += 'a' - 'A' ; } }

  if      ( strcmp( command , "help"       ) == 0 )  { if ( numberOfTokens == 1 ) { commandHelp      (                       ) ;  return ; } }
  else if ( strcmp( command , "list"       ) == 0 )  { if ( numberOfTokens == 1 ) { commandList      (                       ) ;  return ; } }
  else if ( strcmp( command , "plot"       ) == 0 )  { if ( numberOfTokens == 1 ) { commandPlot      (                       ) ;  return ; } }
  else if ( strcmp( command , "quit"       ) == 0 )  { if ( numberOfTokens == 1 ) { commandQuit      (                       ) ;  return ; } }
  else if ( strcmp( command , "register"   ) == 0 )  { if ( numberOfTokens == 2 ) { commandRegister  ( tokens[1]             ) ;  return ; } }
  else if ( strcmp( command , "delete"     ) == 0 )  { if ( numberOfTokens == 2 ) { commandDelete    ( tokens[1]             ) ;  return ; } }
  else if ( strcmp( command , "find"       ) == 0 )  { if ( numberOfTokens == 2 ) { commandFind      ( tokens[1]             ) ;  return ; } }
  else if ( strcmp( command , "connect"    ) == 0 )  { if ( numberOfTokens == 3 ) { commandConnect   ( tokens[1] , tokens[2] ) ;  return ; } }
  else if ( strcmp( command , "disconnect" ) == 0 )  { if ( numberOfTokens == 3 ) { commandDisconnect( tokens[1] , tokens[2] ) ;  return ; } }
  else if ( strcmp( command , "path"       ) == 0 )  { if ( numberOfTokens == 3 ) { commandPath      ( tokens[1] , tokens[2] ) ;  return ; } }
  else if ( strcmp( command , "sort"       ) == 0 )  { if ( numberOfTokens == 3 ) { commandSort      ( tokens[1] , tokens[2] ) ;  return ; } }
  else                                               { NL ;  I2 ;  printf( "Invalid command!\n" ) ;                               return ;   }

  /* If we reach here, the user must have provided incorrect number of arguments to a valid command */

  command[0] += 'A' - 'a' ;

  NL ;  I2 ;  printf( "Incorrect number of arguments provided for the command '%s'!\n" , command ) ;
}

/***************************************************************************************************************************************************/




/* Main Function ***********************************************************************************************************************************/

int main ( int argc , char * argv[] )
{
  char input [ MAX_INPUT_LENGTH ] ;

  if ( argc < 4 )  { printUsage( argv[0] ) ;  return 0 ; } /*argv[0] - prog ismi*/

  configureCengBook( /* maxNumberOfUsers          */ atoi( argv[1] ) , /*atoi int e cevirir*/
                     /* maxUserNameLength         */ atoi( argv[2] ) , 
                     /* maxNumberOfFriendsPerUser */ atoi( argv[3] ) ) ;

  bookPtr = allocateBook() ;

  if ( bookPtr == NULL )  { NL ;  printf( "Error: Cannot allocate memory to store CengBook! Exiting!\n\n" ) ;  exit( 0 ) ; }

  printBanner() ;
  printMenu  () ;

  while ( TRUE )
  {
    NL                        ;  /* New line     */
    printf( "[CENGBOOK] > " ) ;  /* Print prompt */

    if ( fgets( input , MAX_INPUT_LENGTH , stdin ) == NULL )  /* Read input line, 'fgets' is safer than 'gets'. */
    {
      /* In the following two lines, the "if" statements surrounding the "freopen" function calls are used to eliminate warnings. */

      if   ( strcmp( operatingSystem , "Windows" ) == 0 )  { if ( freopen( "CON"      , "r" , stdin ) == NULL ) ; }
      else /* Assumption:               Linux          */  { if ( freopen( "/dev/tty" , "r" , stdin ) == NULL ) ; }

      continue ;
    }

    processInput( input ) ;  /* Tokenize and process the input command */
  }

  return 0 ;
}

/***************************************************************************************************************************************************/
