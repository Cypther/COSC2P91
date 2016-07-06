//
//  storage.h
//  Assign2
//
//  Name: Long Nguyen: Student # 5427059
//
//

#ifndef Assign2_storage_h
#define Assign2_storage_h



//structure 
struct listNode {
    int data; // each listNode contains a number integer
    struct listNode *nextPtr; // pointer to next node in the linked list
};


//synonym for listNode struct
typedef struct listNode ListNode;
// synonym for ListNode
typedef ListNode *ListNodePtr;


/* function prototypes */
void insert( ListNodePtr *sPtr, int value );
void printList( ListNodePtr *currentPtr );
//void delete( ListNodePtr *sPtr); //function not use
int isEmpty( ListNodePtr sPtr );
int searchForNumber(ListNodePtr *sPtr, int item);


#endif
