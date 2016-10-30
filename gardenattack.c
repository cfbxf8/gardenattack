
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// Function Prototypes
void initGarden(char garden[][10]);
void printGarden(char garden[][10]);
int getCoordinate();
char getFlower();
int searchSurroundings(char garden[][10], int x, int y);
int placeFlower(char garden[][10]);

//Main body of code
int main()
{
//Randomizes based on time as seed
srand(time (NULL));

//Declare Variables
char garden[10][10];
int plays, points;
plays = points = 0;

//Create and Initialize Array
initGarden(garden);

printf("\n            GARDEN GAME!\n");

//Runs 5 turns of the game
for(plays =0; plays <5; ++plays)
{
	printf("\n		###Round %d###", (plays+1)); //Prints Round #
	
	printGarden(garden);//Prints garden Array
	
	points += placeFlower(garden); //Accumulates Points and runs placeFlower function
	
	printf("\n\n        Total points: %d", points); //Prints out total points every round
	

}

printGarden(garden); //Prints garden array for last time

printf("\n        Final Outcome %d points", points); //Prints Number of points for entire game

return 0;
}

//Traverses and assigns the array assingning good soil 30% of the time and bad soil 70%
void initGarden(char garden[][10])
{
int row, column;
for ( row = 0; row < 10; row++) {
	/* loop to get 10 by 10 array */
		for ( column = 0; column <10 ; column++ ) {
			int gp=0;
			gp = 1 + ( rand() % 10 ); //Randomizes
			if (gp<=7){ //Poor soil 70% of time
			garden[row][column]=',';
			}
			if (gp>7 & gp<=10){//Good soil 30% of time
			garden[row][column]='#';
			}
		}
}
}

//Prints the array
void printGarden(char garden[][10])
{
int row, column;
printf("\n\n   0 1 2 3 4 5 6 7 8 9\n");
printf("  _____________________\n");
for ( row = 0; row < 10; row++) {
	printf("%d| ", row);
		for ( column = 0; column <10 ; column++ ) {
			printf("%c ",garden[row][column]);
		}
	printf("|\n");
}
printf("  ---------------------");
}

//Scans in unser input and checks for number between 0 to 9 and returns this as a corrdinate
int getCoordinate()
{
int coord;

scanf("%d", &coord);

while (coord>9 || coord<0){
	printf("Coordinate out of range! Please pick a new coordinate: ");
	scanf("%d", &coord);
}

return coord;
}

//Prints the flower choices and prompts user for valid flower. Returns the Flower character.
char getFlower()
{
char Flower, garbage;
printf("\nChoices are:  Mundane Marigold(M), Bomb Blossom(B), or Radiant Rose(R)");
printf("\nFlower: ");

scanf("%c%c", &garbage, &Flower);

while (Flower != 'M' && Flower != 'B' && Flower != 'R')
{
	printf("\nInvalid flower selection! Please try again.");
	printf("\nFlower: ");
	scanf("%c%c", &garbage, &Flower);
}

return Flower;
}

//Function used for when a bomb blossom explodes and dies in poor soil.
//Function searches 8 spaces around the coordinates given.
//If space contains a flower, the play receives -1 point. Returns this.
//All Examined spaces will be changed to the '@' character.
//If space examined is not a valid space in the array, then it is passed over.
int searchSurroundings(char garden[][10], int x, int y)
{
int i=x-1;
int j=y-1;
int point=0;
//2 for loops to check 8 squares around coordinates
for ( i=x-1; i<=x+1; i++) {
	for ( j=y-1; j<=y+1; j++ ) {
		if (i<0 || j<0 || i>9 || j>9) //If statement to make sure doesn't go out of array
			continue;
		if (garden[i][j]=='M' || garden[i][j]=='B' || garden[i][j]=='R'){//if statement to check for flowers and deincrement point if yes
			point--;
		}
		garden[i][j]='@'; //Put @ sign for checked spaces
		}
}
return point;
}

//Function calls get coordinate twice, then calls getFlower to get the user's preferred flower.
//Function will then produce the outcome of the turn using a switch case for (M,B,R, or default).
//Function returns amount of points for the turn.
int placeFlower(char garden[][10])
{
int row, column;
printf("\nSelect row coordinate for flower(0-9): ");
row=getCoordinate();
printf("\nSelect column coordinate for flower(0-9): ");
column=getCoordinate();

printf("\nSelect a flower to place at row[%d], column[%d]", row, column);
char Flower=getFlower();

switch (Flower)
{
	//Mundane Marigold Case
	case 'M':{
		//Good Soil
		if (garden[row][column] =='#'){
			int bug=0;
			bug = 1 + ( rand() % 10 ); //Randomizes from 1 to 10
			if (bug<=5){//Bug Attack
				printf("\n        ###OUTCOME###");
				printf("\nA giant bug attacked the new flower!");
				printf("\nThe Mundane Marigold repeled the attack with its mundane-ness");
				printf("\nThe Mundane Marigold produced a beautiful bloom");
				printf("\n\nYou received 4 points this turn");
				printf("\n        ###END OUTCOME###");
					garden[row][column]='M';
					return 4;
			}
			else {//No Bug Attack
				printf("\n        ###OUTCOME###");
				printf("\nThe Mundane Marigold produced a beautiful bloom");
				printf("\n\nYou received 4 points this turn");
				printf("\n        ###END OUTCOME###");
					garden[row][column]='M';
					return 4;
			}
		}
		//Bad Soil
		else if (garden[row][column] ==','){	
			printf("\n        ###OUTCOME###");
			printf("\nThe Mundane Marigold produced a modest bloom");
			printf("\n\nYou received 1 points this turn");
			printf("\n        ###END OUTCOME###");
				garden[row][column]='M';
				return 1;
		}
		
		else{//For occupied dirt
			printf("\n		###OUTCOME###");
			printf("\nYou chose an occupied plot of dirt; you wasted your turn!");
			printf("\nYou received 0 points this turn");
			printf("\n		###END OUTCOME###");
				return 0;
		}
	}

//Bomb Blossom Case	
	case 'B':
	{
		//Good Soil
		if (garden[row][column] =='#'){
			int bug=0;
			bug = 1 + ( rand() % 10 ); //Randomizes from 1 to 10
			if (bug >=1 && bug<=5){//Bug Attack
				printf("\n        ###OUTCOME###");
				printf("\nA giant bug attacked the new flower!");
				printf("\nThe Bomb Blossom blew up the bug!");
				printf("\n\nYou received 5 points this turn");
				printf("\n        ###END OUTCOME###");
					garden[row][column]='@';
					return 5;
			}
			
			if (bug>=6 && bug<=10){//No Bug Attack
				printf("\n        ###OUTCOME###");
				printf("\nThe Bomb Blossom produced a beautiful bloom");
				printf("\n\nYou received 3 points this turn");
				printf("\n		###END OUTCOME###");
					garden[row][column]='B';
					return 3;
			}	
		}
		//Bad Soil
		else if (garden[row][column] ==','){
		int bomb= 1 + ( rand() % 3 ); //Randomizes from 1 to 3
			if (bomb==1){//Explosion upon death (one-third probability)
				int points=searchSurroundings(garden, row, column);
					printf("\n		###OUTCOME###");
					printf("\nThe Bomb Blossom blew up and died");
					printf("\n\nYou received %d points this turn", points);
					printf("\n		###END OUTCOME###");
						return points;
			}
			if (bomb==2 || bomb ==3);{//No explosion. (two-thirds probability)
				printf("\n		###OUTCOME###");
				printf("\nThe Bomb Blossom produced a modest bloom");
				printf("\n\nYou received 2 points this turn");
				printf("\n		###END OUTCOME###");
					garden[row][column]='B';
					return 2;
			}
		}
		
		else{//For occupied dirt
			printf("\n		###OUTCOME###");
			printf("\nYou chose an occupied plot of dirt; you wasted your turn!");
			printf("\nYou received 0 points this turn");
			printf("\n		###END OUTCOME###");
				return 0;
		}		
	}

//Radiant Rose Case	
	case 'R':{
		//Test for 50% chance of bug attack or 50% chance of flower death {mutually exclusive event}
		int bd=0;
		bd = 1 + ( rand() % 10 );
	
		//Good Soil
		if (garden[row][column] =='#'){
			if (bd >=1 && bd<=5){//Bug Attack
				printf("\n		###OUTCOME###");
				printf("\nA giant bug attacked the new flower!");
				printf("\nThe Radiant Rose was eaten by the bug!");
				printf("\n\nYou received 0 points this turn");
				printf("\n		###END OUTCOME###");
					garden[row][column]='X';
					return 0;
			}
			
			if (bd>=6 && bd<=10){//No Bug Attack
				printf("\n		###OUTCOME###");
				printf("\nThe Radiant Rose produced a beautiful bloom");
				printf("\n\nYou received 8 points this turn");
				printf("\n		###END OUTCOME###");
					garden[row][column]='R';
					return 8;
			}
		}

		//Bad Soil
		else if (garden[row][column] ==','){	
			if (bd >=1 && bd<=5){//Dies
				printf("\n		###OUTCOME###");
				printf("\nThe Radiant Rose wilted and died in the poor soil");
				printf("\n\nYou received 0 points this turn");
				printf("\n		###END OUTCOME###");
					garden[row][column]='?';
					return 0;
			}
			
			if (bd>=6 && bd<=10){//Lives
				printf("\n		###OUTCOME###");
				printf("\nThe Radiant Rose produced a modest bloom");
				printf("\n\nYou received 4 points this turn");
				printf("\n		###END OUTCOME###");
					garden[row][column]='R';
					return 4;
			}
		}

		else{//For occupied dirt
			printf("\n		###OUTCOME###");
			printf("\nYou chose an occupied plot of dirt; you wasted your turn!");
			printf("\nYou received 0 points this turn");
			printf("\n		###END OUTCOME###");
				return 0;
		}		
	}		
}
}