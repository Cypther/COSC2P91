//
//  PoolQueue.c
//  Assign3
//
//  Created by Long Nguyen on 2015-03-12.
//  Copyright (c) 2015 Long Nguyen. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>// for variadic functions
#include <string.h>
#include "PoolQueue.h"
#include "PoolQueue_private.h"

/* Creating the PoolQueue */

//Creates a handle for the client program
//Allocates whatevever memory is necessary for an initial state
PoolQueue *PQcreatePoolQueue() {
    PoolQueue *pool=(PoolQueue*)malloc(sizeof(PoolQueue));
    pool->grip=NULL;
    return pool;
}

/*******************************************************
 *                                                     *
 *  interface implements for adding to queue           *
 *                                                     *
 *******************************************************/

//These add one or more items to a Pool Queue
void PQaddSingle(void *item, PoolQueue *node){
    
    node->grip =_insertQaddSingle(item,node->grip);
    _printTofile(node->grip);

}
//adding two people in the group
void PQaddPair(void *first, void *second, PoolQueue *node){
    
    node->grip =_insertPQaddPair(first, second,node->grip);
    _printTofile(node->grip);

}
//adding three people in the group
void PQaddTriple(void *first, void *second, void *third, PoolQueue *node){
    
    node->grip =_insertPQaddTriple(first, second, third, node->grip);
    _printTofile(node->grip);

}
//adding four people to the group
void PQaddQuartet(void *first, void *second, void *third, void *fourth, PoolQueue *node){
    
    node->grip = _insertPQaddQuartet(first, second, third, fourth, node->grip);
    _printTofile(node->grip);

}

/*******************************************************
 *                                                     *
 *        helper functions for interface               *
 *        implements for adding to queue               *
 *                                                     *
 *******************************************************/

//inserting one into the group
PoolQueueGroup *_insertQaddSingle(void *item, PoolQueueGroup *node){

    PoolQueueGroup *n;

    if (node==NULL) {
        n=(PoolQueueGroup*)malloc(sizeof(PoolQueueGroup));
        n = _addMembersToGroup(1, item);
        printf("             Added ");
        _printPeopleInGroup(n);
        return n;
    }else{
        
        node->next=_insertQaddSingle(item,node->next);
        //_printTofile(node);
        return node;
    }
}
//inserting two into the group
PoolQueueGroup *_insertPQaddPair(void *first, void *second, PoolQueueGroup *node){

    PoolQueueGroup *n;
    
    if (node==NULL) {
        n=(PoolQueueGroup*)malloc(sizeof(PoolQueueGroup));
        n = _addMembersToGroup(2, first, second);
        printf("             Added ");
        _printPeopleInGroup(n);
        return n;
    }else{
        
        node->next=_insertPQaddPair(first, second,node->next);
        return node;
    }

}

//inserting three into the group
PoolQueueGroup *_insertPQaddTriple(void *first, void *second, void *third, PoolQueueGroup *node){
    
    PoolQueueGroup *n;
    
    if (node==NULL) {
        n=(PoolQueueGroup*)malloc(sizeof(PoolQueueGroup));
        n = _addMembersToGroup(3, first, second, third);
        printf("             Added ");
        _printPeopleInGroup(n);
        return n;
    }else{
        
        node->next= _insertPQaddTriple(first, second, third, node->next);
        return node;
    }
}

//inserting for four
PoolQueueGroup *_insertPQaddQuartet(void *first, void *second, void *third, void *fourth, PoolQueueGroup *node){
    
    PoolQueueGroup *n;
    
    if (node==NULL) {
        n=(PoolQueueGroup*)malloc(sizeof(PoolQueueGroup));
        n = _addMembersToGroup(4, first, second, third, fourth);
        printf("             Added ");
        _printPeopleInGroup(n);
        return n;
    }else{
        
        node->next= _insertPQaddQuartet(first, second, third, fourth, node->next);
        return node;
    }
}


//Variadic functions for adding members
PoolQueueGroup *_addMembersToGroup(int members, ...){
    
    PoolQueueGroup *n;
    n=(PoolQueueGroup*)malloc(sizeof(PoolQueueGroup));
    
    va_list listOfPeople;
    va_start(listOfPeople, members);
    int i;
    for (i = 1; i <= members; i++) {
        char *memberName = va_arg(listOfPeople, char*);
        char src[80];
        memset(src, '\0', sizeof(src));//clear the memory location.
        strcpy(src, memberName); //copying memberName to src
        
        switch (i) {
            case 1 :/*clear the memory before using it*/
                strcpy(n->first, src);
                memset(n->second, '\0', sizeof(src));
                memset(n->third, '\0', sizeof(src));
                memset(n->fourth, '\0', sizeof(src));
                n->removeFlag = 0;
                n->howManyMembers = i;
                continue;
            case 2:
    
                strcpy(n->second, src);
                memset(n->third, '\0', sizeof(src));
                memset(n->fourth, '\0', sizeof(src));
                n->removeFlag = 0;
                n->howManyMembers = i;
                continue;
            case 3:
                
                strcpy(n->third, src);
                memset(n->fourth, '\0', sizeof(src));
                n->removeFlag = 0;
                n->howManyMembers = i;
                continue;
            case 4:
                strcpy(n->fourth, src);
                n->removeFlag = 0;
                n->howManyMembers = i;
            default:
                break;
        }
    }
    va_end(listOfPeople);
    return n;
}


void _printPeopleInGroup(PoolQueueGroup *node){
    
    if (node==NULL){
        //return NULL;
    }else{
            printf("[");
            if(node->first[0] != '\0'){ //check if first value is null
                printf("%s",node->first);
            }
            if(node->second[0] != '\0'){ //check if first value is null
                printf(",%s",node->second);
            }
            if(node->third[0] != '\0'){ //check if first value is null
                printf(",%s",node->third);
            }
            if(node->fourth[0] != '\0'){ //check if first value is null
                printf(",%s",node->fourth);
            }
            printf("] \n");
    }
    //return NULL;
}


//If present (i.e. solveable), these load the requested number of records into a provided void pointer array
//Obviously, the client program might require a bit of coaxing, assuming the records have actual types
int PQremoveSingle(void **single, PoolQueue *node){

    int find = 0; //false for zere
    
    //casting single temp pointer
    PoolQueueGroup *temp = (PoolQueueGroup*)single;
    
    //if it can be removed
    find = _PQFindingToRemoveBoolean(1, node->grip);
    //printf("The value of find is %i\n", find);
    
    
    if (find == 1) {//if match found
        //printf("Found \n");
        //flaging the removed
        temp = _PQFlagToRemove(1, node->grip);
        _printTofile(temp);
        
        temp = _PQremovingGroup(temp);
        //_resetQueueFlags(node->grip);
        _printTofile(temp);
    }
    
    return 1;

} //Returns 0 if no single found


int PQremovePair(void **pair, PoolQueue *node){
    
    int find = 0; //false for zere
    int i;
    
    //casting single temp pointer
    PoolQueueGroup *temp = (PoolQueueGroup*)pair;
    
    //if it can be removed
    find = _PQFindingToRemoveBoolean(2, node->grip);
    //printf("The value of find is %i\n", find);
    
    
    if (find == 1) {//if match found
        //printf("Found \n");
        //flaging the removed
        temp = _PQFlagToRemove(2, node->grip);
        _printTofile(temp);
        temp = _PQremovingGroup(temp);
        for ( i = 1; i < 2; i++) {
            temp = _PQremovingGroup(temp);
            //printf("%d\n", i);
        }
        //_resetQueueFlags(node->grip);
        _printTofile(temp);
    }
    
    return 1;

}
int PQremoveTriple(void **triple, PoolQueue *node){
    
    
    int find = 0; //false for zere
    int i;
    
    //casting single temp pointer
    PoolQueueGroup *temp = (PoolQueueGroup*)triple;
    
    //if it can be removed
    find = _PQFindingToRemoveBoolean(3, node->grip);
    //printf("The value of find is %i\n", find);
    
    
    if (find == 1) {//if match found
        printf("Found 3\n");
        //flaging the removed
        temp = _PQFlagToRemove(3, node->grip);
        _printTofile(temp);
        for ( i = 1; i < 3; i++) {
            temp = _PQremovingGroup(temp);
            //printf("%d\n", i);
        }
        //_resetQueueFlags(node->grip);
        _printTofile(temp);
    }
    
    return 1;
    
}
int PQremoveQuartet(void **quartet, PoolQueue *node){
    
    int find = 0; //false for zere
    int i;
    
    //casting single temp pointer
    PoolQueueGroup *temp = (PoolQueueGroup*)quartet;
    
    //if it can be removed
    find = _PQFindingToRemoveBoolean(4, node->grip);
    //printf("The value of find is %i\n", find);
    
    
    if (find == 1) {//if match found
        //printf("Found \n");
        //flaging the removed
        temp = _PQFlagToRemove(4, node->grip);
        _printTofile(temp);
        _printTofile(temp);
        for ( i = 1; i < 4; i++) {
            temp = _PQremovingGroup(temp);
            //printf("%d\n", i);
        }
        _printTofile(temp);
    }
    
    return 1;
    
}

//forming new groups
PoolQueueGroup *_PQFormingNewGroup(int groupSizeNeed, PoolQueueGroup *node){
    
    int membersNeeded =  4 - groupSizeNeed;
    printf("I need %d members\n", membersNeeded);
    int counter = 0;
    
     //int n[10];

    PoolQueueGroup *tailPtr = node; // pointer to previous node in the linked list
    PoolQueueGroup *currentPtr = node; // pointer to current node in list in the linked list
    
    if (tailPtr == NULL) {//Node is empty so return it
        return NULL;
    }
    
    PoolQueueGroup *newNode;
    newNode=(PoolQueueGroup*)malloc(sizeof(PoolQueueGroup));
    
    // loop to find the correct location in the listed list to delete node
    while (tailPtr != NULL) {
        counter = tailPtr->howManyMembers;
        tailPtr->removeFlag = 1;//setting up flags
        //newNode->priority = tailPtr->priority;
        
        currentPtr = tailPtr->next;
        while (currentPtr != NULL) {
            
            if(counter == membersNeeded){
                currentPtr->removeFlag = 1; //setting flag to be removed
                printf("We found the group! %d\n", counter);
                printf("What group are we on %d\n", tailPtr->priority);
                return newNode;
            }else if (counter > membersNeeded){
                printf("Too much %d\n", counter);
                //reseting counter back to default value
                counter = tailPtr->howManyMembers;
                printf("How many do I have %d\n", counter);
            }
               counter += currentPtr->howManyMembers;
               currentPtr->removeFlag = 1; //setting flag to be removed
            
            printf("What group are we on %d\n", tailPtr->priority);
            printf("How many do I have %d\n", counter);
            
            currentPtr->removeFlag = 0; //setting flag back
            currentPtr = currentPtr->next; // incrementing current to next node*/
        }
        tailPtr->removeFlag = 0;//setting flag back
        tailPtr = tailPtr->next; // incrementing current to next node*/
       /* counter += currentPtr->howManyMembers;
        
        currentPtr = currentPtr->next; // incrementing current to next node*/
    }
    
    
    printf("Group not found! \n");
    newNode = currentPtr;
    return newNode;

}

/**************************************
 
 looking in the a group in the queue and returning the node
 
 **************************************/

PoolQueueGroup *_PQFindingGroup(PoolQueueGroup *node){
    
    PoolQueueGroup *currentPtr = node; // pointer to current node in list in the linked list
    
    PoolQueueGroup *newNode;
    newNode=(PoolQueueGroup*)malloc(sizeof(PoolQueueGroup));
    
    // loop to find the correct location in the listed list to delete node
    while (currentPtr != NULL ) {
        currentPtr = currentPtr->next; // incrementing current to next node
    }
    //currentPtr->removeFlag = 1; //setting the flag to be remeoved
    newNode = currentPtr;
    
    return newNode;

}

//removing from the queue

PoolQueueGroup *_PQremovingGroup(PoolQueueGroup *node){
    
    PoolQueueGroup *previousPtr; // pointer to previous node in the linked list
    PoolQueueGroup *currentPtr; // pointer to current node in list in the linked list
    PoolQueueGroup *headPtr; // pointer to the head node in list in the linked list
        
        previousPtr = NULL; //assigning previous pointer to null
        currentPtr = node; //current points to the linked list being passed in the function
        headPtr = node; // points to the first node in the linked list
        
        // loop to find the correct location in the listed list to delete node
        //while (currentPtr != NULL && currentPtr->removeFlag != 1) {
        while (currentPtr != NULL && currentPtr->removeFlag != 1) {
            
            previousPtr = currentPtr; //assigning prevouse to current
            currentPtr = currentPtr->next; // incrementing current to next node
        }
    
        // Deleting at the beginning of the listed list the "fist Node"
        if (previousPtr == NULL) {
            previousPtr = currentPtr;
            currentPtr = currentPtr->next;
            printf("             Removed ");
            _printPeopleInGroup(previousPtr);
            free(previousPtr);//freeing the first node
            previousPtr=NULL;//defensive style programming
            return currentPtr;

        }else{ //Deleting between previous and current node
            previousPtr->next = currentPtr->next;
            printf("             Removed ");
            _printPeopleInGroup(currentPtr);
            free(currentPtr);//free the node in between previous and current node
            currentPtr = NULL; //defensive style programming
        }
    return headPtr;
}

/*******************************************************
 *                                                     *
 *  interface implements for checking if the           *
 *  requested amount of members is in the queue        *
 *                                                     *
 *******************************************************/


//These return 1 if the Pool Queue *could* return the requested amount
int PQhasSingle(PoolQueue *node){
    

    int find = 0; //false for zere
    
    //printf("The value of find is %i\n", find);
    find = _PQFindingToRemoveBoolean(1, node->grip);
    //printf("The value of find is %i\n", find);
    
    
    if (find == 0) {//no match found reset the flags
        //printf("No Match found! \n");
        _resetQueueFlags(node->grip);
        _printTofile(node->grip);
    }
    return find; //Didn't find anything
    
}
int PQhasPair(PoolQueue *node){

    int find = 0; //false for zere
    
    //printf("The value of find is %i\n", find);
    find = _PQFindingToRemoveBoolean(2, node->grip);
    //printf("The value of find is %i\n", find);
    
    
    if (find == 0) {//no match found reset the flags
        //printf("No Match found! \n");
        _resetQueueFlags(node->grip);
        _printTofile(node->grip);
    }
    return find; //Didn't find anything
    

}
int PQhasTriple(PoolQueue *node){

    
    int find = 0; //false for zere
    
    //printf("The value of find is %i\n", find);
    find = _PQFindingToRemoveBoolean(3, node->grip);
    //printf("The value of find is %i\n", find);
    
    
    if (find == 0) {//no match found reset the flags
        //printf("No Match found! \n");
        _resetQueueFlags(node->grip);
        _printTofile(node->grip);
    }
    return find; //Didn't find anything if it's zero
    
    
}
int PQhasQuartet(PoolQueue *node){


    int find = 0; //false for zere
    
    //printf("The value of find is %i\n", find);
    find = _PQFindingToRemoveBoolean(4, node->grip);
    //printf("The value of find is %i\n", find);
    
    
    if (find == 0) {//no match found reset the flags
        //printf("No Match found! \n");
        _resetQueueFlags(node->grip);
        _printTofile(node->grip);
    }
    return find; //Didn't find anything if it's zero
    
    
    
}

/**************************************************
 *
 * Searching to remove from group by 
 * recursive calls and flaging
 *
 **************************************************/

PoolQueueGroup *_PQFlagToRemove(int groupSizeNeed, PoolQueueGroup *node){
    
    PoolQueueGroup *tempNode;
    tempNode=(PoolQueueGroup*)malloc(sizeof(PoolQueueGroup));

    
    if (node == NULL) {//Node is empty so return it
        return node; //base case
    }
        
        //printf("What group size %d\n", groupSizeNeed);
        if(node->howManyMembers == 1 && groupSizeNeed >= 1){
            node->next = _PQFlagToRemove(groupSizeNeed-1, node->next);
            node->removeFlag = 1;
            groupSizeNeed -=1;
            //printf("RemoveSize %d\n", removedSize);
        }
        
        if(node->howManyMembers == 2 && groupSizeNeed >= 2){
            //printf("Flag it Two True %d\n", node->removeFlag);
            node->next = _PQFlagToRemove(groupSizeNeed-2, node->next);
            node->removeFlag = 1;
            groupSizeNeed -=2;
        }
        
        if(node->howManyMembers == 3 && groupSizeNeed >= 3){
            //printf("Flag it Three True %d\n", node->removeFlag);
            node->next = _PQFlagToRemove(groupSizeNeed-3, node->next);
            node->removeFlag = 1;
            groupSizeNeed -=3;
        }
        
        if(node->howManyMembers == 4 && groupSizeNeed == 4){
            //printf("Flag it Four True %d\n", node->removeFlag);
            node->next = _PQFlagToRemove(groupSizeNeed-4, node->next);
            node->removeFlag = 1;
            groupSizeNeed -=4;
        }
        node->next = _PQFlagToRemove(groupSizeNeed, node->next);

    return node;
}

int _PQFindingToRemoveBoolean(int groupSizeNeed, PoolQueueGroup *node){
    
    int boolean = 1; //setting the flag true
    
    
    if (node == NULL) {//Node is empty so return it
        
        //if there is an extra person need, than can't make a group
        if (groupSizeNeed != 0 && node == NULL) {
            boolean = 0;// false if it can't make a group
            return boolean;
        }
        
        return boolean; //base case
    }
    
    //recursive calls and flaging for check to from groups
    
    if(node->howManyMembers == 1 && groupSizeNeed >= 1){
        node->removeFlag = 1;
        boolean = _PQFindingToRemoveBoolean(groupSizeNeed-1, node->next);
        groupSizeNeed -=1;
        //printf("RemoveSize %d\n", removedSize);
    }
    
    if(node->howManyMembers == 2 && groupSizeNeed >= 2){
        //printf("Flag it Two True %d\n", node->removeFlag);
        boolean = _PQFindingToRemoveBoolean(groupSizeNeed-2, node->next);
        node->removeFlag = 1;
        groupSizeNeed -=2;
    }
    
    if(node->howManyMembers == 3 && groupSizeNeed >= 3){
        //printf("Flag it Three True %d\n", node->removeFlag);
        boolean = _PQFindingToRemoveBoolean(groupSizeNeed-3, node->next);
        node->removeFlag = 1;
        groupSizeNeed -=3;
    }
    
    if(node->howManyMembers == 4 && groupSizeNeed == 4){
        //printf("Flag it Four True %d\n", node->removeFlag);
        boolean = _PQFindingToRemoveBoolean(groupSizeNeed-4, node->next);
        node->removeFlag = 1;
        groupSizeNeed -=4;
    }
    boolean = _PQFindingToRemoveBoolean(groupSizeNeed, node->next);


    return boolean;
}

/***********************************************
 *
 *
 *  resetting flags if the return value is zero
 *
 *
 **********************************************/



PoolQueueGroup *_resetQueueFlags(PoolQueueGroup *node){
    
    PoolQueueGroup *currentPtr = node; // pointer to current node in list in the linked list
    
    PoolQueueGroup *newNode;
    newNode=(PoolQueueGroup*)malloc(sizeof(PoolQueueGroup));
    
    // loop to find the correct location in the listed list to delete node
    while (currentPtr != NULL) {
        currentPtr->removeFlag = 0; //resetting flags to zero
        currentPtr = currentPtr->next; // incrementing current to next node
    }
    //currentPtr->removeFlag = 1; //setting the flag to be remeoved
    newNode = currentPtr;
    
    return newNode;

}

/* Function to look for how many members are in each group */
int _findHowManyMembers(int numbersTolookFor, PoolQueueGroup *node){
    
    PoolQueueGroup tempPtr; // temporary node pointer
    
    if (node==NULL){
        return 0;
    }else{
        
        while (node!= NULL) {
            if (node->howManyMembers == numbersTolookFor) {
                return 1;
            }
            tempPtr = *node; //temp node to hold the current point
            node = node->next; //current pointer, points to next node
        }
    }
    return 0;
    
}

/*****************************************************
 *                                                   *
 *  Find the total of all the groups                 *
 *                                                   *
 *****************************************************/

//Total # of items waiting (NOT # of groups!)
int PQcount(PoolQueue *node){

    int total;
    total = _PQcount(node->grip);
    //printf("The total is %d\n", total);
    return total;

}

int _PQcount(PoolQueueGroup *node){
    
    PoolQueueGroup tempPtr; // temporary node pointer
    int counter = 0;
    
    if (node==NULL){
        return 0;
    }else{
        
        while (node!= NULL) {
            //printf("The total is %d\n", counter);
            counter += node->howManyMembers;
            //printf("The total is %d\n", counter);
            tempPtr = *node; //temp node to hold the current point
            node = node->next; //current pointer, points to next node
        }
    }
    return counter;

}

/*****************************************************
 *                                                   *
 *  Printing to file                                 *
 *                                                   *
 *****************************************************/

void _printTofile(PoolQueueGroup *node){

    int counter = 1;
    if (node==NULL){
        return;
    }else{
        
        FILE *f = fopen("log.txt", "w");
        if (f == NULL)
        {
            printf("Error opening file!\n");
            exit(1);
        }
        
        // print some text //
        //const char *text = "Write this to the file";
        
        fprintf(f, "Flag: Priority :  Size :  Members \n");
        
        while (node!= NULL) {
            
            int flag = node->removeFlag;
            fprintf(f, "  %d  : ", flag);
            fprintf(f, "    %d : ", counter);
            //seting the priority of each group
            node->priority = counter;
            fprintf(f, "    %d : ", node->howManyMembers);
            if(node->first[0] != '\0'){ //check if first value is null
                const char *first = node->first;
                fprintf(f, "%s, ", first);
            }
            if(node->second[0] != '\0'){ //check if first value is null
                const char *second = node->second;
                fprintf(f, "%s, ", second);
            }
            if(node->third[0] != '\0'){ //check if first value is null
                const char *third = node->third;
                fprintf(f, "%s, ", third);
            }
            if(node->fourth[0] != '\0'){ //check if first value is null
                const char *fourth = node->fourth;
                fprintf(f, "%s ", fourth);
            }
            counter++;
                fprintf(f, "\n");
            
            node = node->next; //current pointer, points to next node
        }
     fclose(f);
    }

}


//Shorthand for clearing out a Pool Queue
//Frees both the pointer *and* its allocated contents!
void PQdisposeOfPoolQueue(PoolQueue *condemned){
    _PQdestroyNode(condemned->grip);

}
//Note: Doesn't presume that the actual items added via PQaddSingle, etc. need to be freed
//i.e. if client is storing Students, this function does not free the memory for those students; only the wrappers
//Last note: To be clear, this isn't resetting the Pool Queue for use; it's deallocating even the handle itself


PoolQueueGroup *_PQdestroyNode(PoolQueueGroup *node){
    
    char src[80];
    memset(src, '\0', sizeof(src));//clear the memory location.
    
    memset(node->first, '\0', sizeof(src));
    memset(node->second, '\0', sizeof(src));
    memset(node->third, '\0', sizeof(src));
    memset(node->fourth, '\0', sizeof(src));
    node->removeFlag = 0;
    node->howManyMembers = 0;
    node->priority = 0;
    node->next = NULL;
    free(node);
    node = NULL;
    return node;
}
