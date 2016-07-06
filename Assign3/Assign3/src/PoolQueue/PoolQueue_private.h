//
//  PoolQueue_private.h
//  Assign3
//
//  Created by Long Nguyen on 2015-03-12.
//  Copyright (c) 2015 Long Nguyen. All rights reserved.
//

typedef struct PoolQueueGroup PoolQueueGroup;

struct PoolQueueGroup {
    int removeFlag; //flag for removing 
     int priority;
     int howManyMembers;
     char first[80];
     char second[80];
     char third[80];
     char fourth[80];
    struct PoolQueueGroup *next; //not sure
};

/* Function for adding to group */
PoolQueueGroup *_insertQaddSingle(void *item, PoolQueueGroup *node);
PoolQueueGroup *_insertPQaddPair(void *first, void *second, PoolQueueGroup *node);
PoolQueueGroup *_insertPQaddTriple(void *first, void *second, void *third, PoolQueueGroup *node);
PoolQueueGroup *_insertPQaddQuartet(void *first, void *second, void *third, void *fourth, PoolQueueGroup *node);


/*These return 1 if the Pool Queue *could* return the requested amount*/
int _findHowManyMembers(int numbersTolookFor, PoolQueueGroup *queue);


/* Variadic Functions for adding members */
PoolQueueGroup *_addMembersToGroup(int members, ...);

//Total # of items waiting (NOT # of groups!)
int _PQcount(PoolQueueGroup *node);

void _printPeopleInGroup(PoolQueueGroup *node);



//If present (i.e. solveable), these load the requested number of records into a provided void pointer array
//Obviously, the client program might require a bit of coaxing, assuming the records have actual types
PoolQueueGroup *_PQremovingGroup(PoolQueueGroup *queue); //Returns 0 if no single found


PoolQueueGroup *_PQFindingGroup(PoolQueueGroup *queue); //Returns 0 if no single found

PoolQueueGroup *_PQFormingNewGroup(int groupSizeNeed, PoolQueueGroup *queue);

PoolQueueGroup *_PQFlagToRemove(int groupSizeNeed, PoolQueueGroup *node);//flaging the queue

int _PQFindingToRemoveBoolean(int groupSizeNeed, PoolQueueGroup *node);//flaging the queue


PoolQueueGroup *_resetQueueFlags(PoolQueueGroup *node); //resetting all the flags

PoolQueueGroup *_PQdestroyNode(PoolQueueGroup *node); //free up memeory



int _PQremovePair(void **pair, PoolQueueGroup *queue); //Returns 0 if no pair found
int _PQremoveTriple(void **triple, PoolQueueGroup *queue); //Returns 0 if no triple found
int _PQremoveQuartet(void **quartet, PoolQueueGroup *queue); //Returns 0 if no quartet found
//Technically, "not zero" is what they return when successful, but I'd suggest simply 1
//Note: if remove fails, the data structure is NOT changed! It returns a 0, and does nothing else

void _printTofile(PoolQueueGroup *node); //print out to log

//Free the memory 
PoolQueueGroup *_PQdestroyNode(PoolQueueGroup *node);
