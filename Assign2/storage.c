//
//  storage.c
//  LinkedList
//
// Name: Long Nguyen: Student # 5427059
//

#include <stdio.h>
#include <stdlib.h>
#include "storage.h"


/* funcation to insert a new value into the listed list
 in ascending sorted order
 */

void insert( ListNodePtr *sPtr, int value ){
    
    //If there's a duplicate value return one, zero for no duplicates
    if(searchForNumber(sPtr, value)==1 || value == 0){
        return;
    }
    
    ListNodePtr newPtr; // pointer to new node
    ListNodePtr previousPtr; // pointer to previous node in the linked list
    ListNodePtr currentPtr; // pointer to current node in list in the linked list
    
    newPtr = malloc(sizeof(ListNode)); // allocates memory for the new node and points to it
    
    if (newPtr != NULL) { //cheacking if space is available
        newPtr->data = value; // place value in the node's data
        newPtr->nextPtr = NULL; //New linked list node does not point to another node yet
        
        previousPtr = NULL; //assigning previous pointer to null
        currentPtr = *sPtr; //current points to the linked list being passed in the function
        
        // loop to find the correct location in the listed list in ascending order
        while (currentPtr != NULL && value > currentPtr->data) {
            previousPtr = currentPtr; //assigning prevouse to current
            currentPtr = currentPtr->nextPtr; // incrementing current to next node
        }
        
        // insert new node at beginning of the listed list the "fist Node"
        if (previousPtr == NULL) {
            newPtr->nextPtr = *sPtr;
            *sPtr = newPtr;
        }else{ // inserting new node in between previous and current node
            previousPtr->nextPtr = newPtr;
            newPtr->nextPtr = currentPtr;
        }
    }else{//else there are no memory available print out an error messge
        printf( "%c was not inserted because no memory available!\n", value );
    }
}//end insert function




/* Return 1 if the listed list is empty, 0 otherwise
 
 */
int isEmpty( ListNodePtr sPtr )
{
    if (sPtr == NULL){
        return 1;
    }else{
        return 0;
    }
} // end isEmpty function



/* Print data in the linked list 
   and delete the data after being printed
   using free function to free up memory
 */
void printList( ListNodePtr *currentPtr )
{
    ListNodePtr tempPtr; // temporary node pointer
    
    // if list is empty
    if ( *currentPtr == NULL ) {
        printf("List is empty.\n\n");
    }else{
        printf("\nPrint Linked list:\n");
        
        // while linked list not null
        while (*currentPtr != NULL) {
            //printing out the value of the linked list
            printf( "%d \n", (*currentPtr)->data );
            tempPtr = *currentPtr; //temp node to hold the current point
            *currentPtr = (*currentPtr)->nextPtr; //current pointer, points to next node
            free(tempPtr); //freeing the memory
        }
    }
} // end printList function


/* Searching for duplicate numbers in the linked list
 * If there is a duplicate return 1, else return o
 *
 */

int searchForNumber(ListNodePtr *sPtr, int number){
    
    ListNodePtr pIterator = *sPtr;
    
    while (pIterator != NULL) {
        
        if (number == pIterator->data) {
            //   printf("%d",pIterator->data);
            //printf("There was a match\n\n");
            return 1;
            // return pProductIterator;
        }
        pIterator = pIterator->nextPtr;
    }
    //printf("%d Wasn't Found!\n\n", number);
    return 0;
} // end searchForNumber function

//function not use
/* Deleting the a listed list elements
 void delete( ListNodePtr *sPtr )
 {
 ListNodePtr tempPtr; // temporary node pointer
 
 while ( *sPtr  != NULL) {
 tempPtr = *sPtr;
 *sPtr = (*sPtr)->nextPtr;
 //printf("Deleting the node %d\n\n", tempPtr->data);
 free(tempPtr); //freeing the memory
 }
 
 } // end delete function*/

