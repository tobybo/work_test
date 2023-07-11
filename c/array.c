#include "stdio.h"
#include "stdlib.h"
#include "string.h"


struct players {
    char firstName[20];
    char lastName[20];
    char country[20];
    int scores[1];
    char *cards[1];
};

void createPlayers(struct players currentPlayers[]){
    int numPlayers;
    int numRounds;

    //Get input
    printf("How many players are there? ");
    scanf("%d", &numPlayers);
    printf("How many rounds are there? ");
    scanf("%d", &numRounds);

    //Allocate array of structures
    int* ptr1 = (int*)&currentPlayers;
    ptr1 = (int *) malloc ( sizeof ( struct players ) * numPlayers);

    //Allocate scores int array
    int* ptr2 = (int *)&currentPlayers[0].scores;
    ptr2 = malloc(numRounds * sizeof(int));

    //Allocate cards string array (array of pointers to char array)
    int* ptr3 = (int*)&currentPlayers[0].cards;
    ptr3 = (int *)malloc(sizeof(int) * numPlayers);
    for( int i = 0; i < numPlayers; i++ )
        currentPlayers[0].cards[i] = malloc( 3 * sizeof *currentPlayers[0].cards[i] );

    //Set scores[2] to 12
    currentPlayers[0].scores[2] = 12;
}

struct players playerList[1];
int main(){
    createPlayers(playerList);
    printf("%d", playerList[0].scores[2]);
}
