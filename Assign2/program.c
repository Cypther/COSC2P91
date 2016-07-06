//
//  program.c
//  Assign2
//
//  Name: Long Nguyen: Student # 5427059
//

#include <stdio.h>
#include <stdlib.h>
#include "storage.h"

int main(int argc, const char * argv[]) {

    
    ListNodePtr startPtr = NULL; //initially there are no nodes
    int number; // integer entered by user
    
    
    //Looping until user enter in at least one number or the linked list has one data in it
    
    do {
        printf( "Enter a number: " );
        scanf( "%d", &number);
        insert( &startPtr, number ); // insert item in list
    } while (number != 0 || isEmpty(startPtr)==1);
    
    //printing out the lisked list
    printList(&startPtr);
    //delete(&startPtr);
    
    //print out again to see if the values are deleted
    printf( "\n" );
    printList( &startPtr );

    
    
    
    return 0;
}