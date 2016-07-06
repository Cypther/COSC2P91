//
//  client.c
//  Assign3
//
//  Created by Long Nguyen on 2015-03-12.
//  Copyright (c) 2015 Long Nguyen. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PoolQueue.h"

/* function prototypes */
void optionsSelect(int choices, PoolQueue *groups, PoolQueue *getGroupTemp);

int main(int argc, const char * argv[]) {
    
     int number; // integer entered by user
    
     PoolQueue *groups = PQcreatePoolQueue();
     PoolQueue *getGroupTemp = PQcreatePoolQueue();
    
    //Looping until user enter an option, or zero to quit the program
    
    do {
        printf( "1. Add One       2. Add Two         3. Add Three        4. Add Four\n" );
        printf( "5. Remove One    6. Remove Two      7. Remove Three     8. Remove Four\n" );
        printf( "                 9. Test Options    0. Quit                           \n" );
        scanf( "%d", &number);
        //printf( "\n");
        optionsSelect(number, groups, getGroupTemp);
    } while (number != 0);

    return 0;
}

/*switch case for selection*/

void optionsSelect(int choices, PoolQueue *groups, PoolQueue *getGroupTemp) {
    
    char strNameFirst[80];
    char strNameSecond[80];
    char strNameThird[80];
    char strNameFourth[80];
    
    switch (choices) {
        case 1 : // Add One
            
            printf( "Enter Name: ");
            scanf("%s", strNameFirst);
            PQaddSingle(strNameFirst, groups);
            
            break;
        case 2: //Add Two
            
            printf( "First: ");
            scanf("%s", strNameFirst);
            printf( "Second: ");
            scanf("%s", strNameSecond);
            PQaddPair(strNameFirst, strNameSecond, groups);
            
            break;
        case 3: //Add Three
            
            printf( "First: ");
            scanf("%s", strNameFirst);
            printf( "Second: ");
            scanf("%s", strNameSecond);
            printf( "Third: ");
            scanf("%s", strNameThird);
            PQaddTriple(strNameFirst, strNameSecond, strNameThird, groups);
            
            break;
        case 4: //Add Four
            
            printf( "First: ");
            scanf("%s", strNameFirst);
            printf( "Second: ");
            scanf("%s", strNameSecond);
            printf( "Third: ");
            scanf("%s", strNameThird);
            printf( "Fourth: ");
            scanf("%s", strNameFourth);
            PQaddQuartet(strNameFirst, strNameSecond, strNameThird, strNameFourth, groups);
            
            break;
        case 5: //Remove One
            PQremoveSingle((void*)getGroupTemp, groups);
            break;
        case 6://Remove Two
            PQremovePair((void*)getGroupTemp, groups);
            break;
        case 7:// Remove Three
            PQremoveTriple((void*)getGroupTemp, groups);
            break;
        case 8:// Remove Four
            PQremoveQuartet((void*)getGroupTemp, groups);
            break;
        case 9: //Test Options
            
            //ternary operator
            printf( "One: %s\n", (PQhasSingle(groups) == 1) ? "true":"false" );
            printf( "Two: %s\n", (PQhasPair(groups) == 1) ? "true":"false" );
            printf( "Three: %s\n", (PQhasTriple(groups) == 1) ? "true":"false" );
            printf( "Four: %s\n", (PQhasQuartet(groups) == 1) ? "true":"false" );
            int total = PQcount(groups);
            printf("Count: %d\n", total);
            printf("\n");
            //printPerson(groups);
            
            break;
        default:
            break;
    }
    
}