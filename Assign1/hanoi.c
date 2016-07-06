//
//  hanoi.c
//  Task 4
//  Created by Long Nguyen on 2015-02-04.
//

#include <stdio.h>

/*Tower of Hanoi structures which has four members, 3 arrays and a move.
 Each array is set to hold 50 disks max.
 I set it up for 50 to be safe, but I don't think you'll even want to
 wait to watch 20 disks move around the screen, let alone 50*/
struct towersOfHanoi{
    int towerA[50];
    int towerB[50];
    int towerC[50];
    int moves;
};

/*Function prototypes*/

/* The moveDisks function move the disk to either tower A or B or C */
void moveDisks(struct towersOfHanoi *towers, int numberOfDisks, char from, char to);

/* hanoiRecursion fuction recursively selects the right disk to move and calls the moveDisk function
 to move the disk to that tower*/
void hanoiRecursion(struct towersOfHanoi *towers, int num, int numberOfDisks, char, char, char);

/* printTowers function prints all the disks in the there towers which are set up as arrays*/
void printTowers(struct towersOfHanoi *towers, int numberOfDisks);

/*These functions are use to print, I broke them up so the code looks much cleaner to read
 whileSpaces will print the number of white spaces needed
 tab will print the tabs which is 8 spaces
 right and left square brackets just prints the bracket*/
void printWhiteSpaces(int whiteSpaceNeeded);
void printTab(int spaces);
void printRightSquareBracket();
void printLeftSquareBracket();


int main(int argc, const char * argv[]) {
    
    
    struct towersOfHanoi Towers;
    int i;
    
    
    int numberOfDisks;
    
    //testing
    //printf("\nEnter number of plates:");
    //scanf("%d", &numberOfDisks);
    
    
    //checking how many arguments are passed in
    if (argc < 1){
        printf("Invalid Parameters");
        return -1;
    }
    
    //passing in the input from the command-line argv and chaning it to an integer
    numberOfDisks = atoi(argv[1]);
    
    
    printf("\nInitial\n\n");
    
    /* Initialized the Towers struct, only the first tower.
     Only initializing tower A with the largest disk first*/
    int j = numberOfDisks;
    for (i = 0; i <numberOfDisks; i++) {
        Towers.towerA[i] = j;
        Towers.towerB[i] = 0;
        Towers.towerC[i] = 0;
        j-=1;//decrementing j by one
    }
	Towers.moves = 0;
    
    //function to print the tower in the current state when it is initialized.
    printTowers(&Towers, numberOfDisks);
    
    //calling the hanoiRecuresion function and passing in the number of disks and the tower struct
    hanoiRecursion(&Towers, numberOfDisks, numberOfDisks, 'A', 'C', 'B');
    
    printf("\n%d moves\n", Towers.moves);
    
    return 0;
    
}

/* MoveDisks function gets the address of the Tower in memeory to be move,
 and moves the disk to the correct tower*/

void moveDisks(struct towersOfHanoi *towers, int numberOfDisks, char from, char to){
    
    int i;
    
    //Stores the value of the element in the tower to be moved
    int diskValues = 0;
    
    /* starting from the top of the tower in the for loop,
     if it's the correct tower, set the
     last/top of the array/tower to zero
     this is kind of like a stack, by
     poping off the last element(setting to zero)
     */
    for (i = numberOfDisks-1; i>=0; i--) {
        if (from == 'A' && towers->towerA[i] != 0){
            diskValues = towers->towerA[i];
            towers->towerA[i] = 0;
            break;
        }
        if (from == 'B' && towers->towerB[i] != 0){
            diskValues = towers->towerB[i];
            towers->towerB[i] = 0;
            break;
        }
        if (from == 'C' && towers->towerC[i] != 0){
            diskValues = towers->towerC[i];
            towers->towerC[i] = 0;
            break;
        }
    }
    
    /* starting from the bottom of the tower/first element
     and pushing the value of the thing in "diskValues" to
     the correct tower/array
     */
    for (i = 0; i<numberOfDisks; i++) {
        if (to == 'A' && towers->towerA[i] == 0){
            towers->towerA[i] = diskValues;
            break;
        }
        
        if (to == 'B' && towers->towerB[i] == 0){
            towers->towerB[i] = diskValues;
            break;
        }
        if (to == 'C' && towers->towerC[i] == 0){
            towers->towerC[i] = diskValues;
            break;
        }
    }
    
    //increment the move by one
    towers->moves = towers->moves+1;
    
}

/* hanoiRecursion recursively selects the right disks to move
 
 I used the recursive algorithm pseudo codefrom the assignment
 which is:
 
 "The basic recursive algorithm is simple:
 move(n, from, to)→
 if n=1 move disc from from to to
 else move n-1 from from to other
 move 1 from from to to
 move n-1 from other to to"
 
 in my hanoiRecursion function
 
 */
void hanoiRecursion(struct towersOfHanoi *towers, int num, int numberOfDisks, char fromPeg, char toPeg, char auxPeg)
{
    if (num == 1)
    {
        printf("\n Move 1 from %c to %c\n", fromPeg, toPeg);
        moveDisks(towers,numberOfDisks, fromPeg, toPeg);
        printTowers(towers, numberOfDisks);
        return;
    }
    else
    {
        hanoiRecursion(towers, num - 1, numberOfDisks, fromPeg, auxPeg, toPeg);
        printf("\n Move 1 from %c to %c\n", fromPeg, toPeg);
        moveDisks(towers, numberOfDisks, fromPeg, toPeg);
        printTowers(towers, numberOfDisks);
        hanoiRecursion(towers, num - 1, numberOfDisks, auxPeg, toPeg, fromPeg);
    }
    return;
}


/* printTowers function prints the stuct towersOfHanio disk location.
 This function works by passing in the address of the tower and the number of disks
 in the tower.
 */

void printTowers(struct towersOfHanoi *towers, int numberOfDisks){
    
    int i = 0; // variable for "for loop"
    int diskValuesOfMove = 0; //holds the value of the disk being moved
    int diskValuesTowerA = 0; //holds the value of the disk in tower A
    int diskValuesTowerB = 0; //holds the value of the disk in tower B
    int diskValuesTowerC = 0; //holds the value of the disk in tower C
    
    /*calculating the distance needed between towers,
     so it looks aesthetically pleasing if there are a lot of disks*/
    int towerDistance = numberOfDisks*2;
    
    //Starting from the top of the tower(end of the array) and printing n-1 disks
    for (i = numberOfDisks-1; i>= 0; i--) {
        
        //first Tower
        if (towers->towerA[i] != 0) //check if the first tower is not zero/null
        {
            //getting the value from towerA to store in "diskValuesOfMove"
            diskValuesOfMove = towers->towerA[i];
            
            //getting the value from towerA and store in "diskValuesTowerA"
            diskValuesTowerA = towers->towerA[i];
            
            /*calucating how much spaces(tabs) to be used by subtracting the differents
             and calling the tab function*/
            printTab(towerDistance-diskValuesTowerA);
            
            /*Printing the square bracket*/
            printRightSquareBracket();
            
            /*Printing numbers of spaces needed between the right square bracket*/
            printWhiteSpaces(diskValuesOfMove);
            
            printf("|");
            
            /*Printing numbers of spaces needed between the right square bracket*/
            printWhiteSpaces(diskValuesOfMove);
            printLeftSquareBracket();
        }
        else
        {
            /*getting towerA value and seeing how much (tab)spaces to print*/
            diskValuesTowerA = towers->towerA[i];
            
            /*calculating by subtracting the differents between towerA and the towerDistance*/
            printTab(towerDistance-diskValuesTowerA);
            printf("|");
        }
        
        //Second Tower
        
        /*The second tower is basically the same algorithm as the first tower
         so I'm not going to comment every single line*/
        if (towers->towerB[i] != 0)
        {
            diskValuesOfMove = towers->towerB[i];
            diskValuesTowerB = towers->towerA[i];
            printTab(towerDistance-(diskValuesTowerB+diskValuesOfMove));
            
            printRightSquareBracket();
            printWhiteSpaces(diskValuesOfMove);
            printf("|");
            printWhiteSpaces(diskValuesOfMove);
            printLeftSquareBracket();
        }
        else
        {
            diskValuesTowerB = towers->towerA[i];
            printTab(towerDistance-diskValuesTowerB);
            printf("|");
        }
        
        //Third Tower
        
        /*The Tower tower is basically the same algorithm as the first tower
         so I'm not going to comment every single line*/
        if (towers->towerC[i] != 0)
        {
            diskValuesOfMove = towers->towerC[i];
            diskValuesTowerC = towers->towerB[i];
            printTab(towerDistance-(diskValuesOfMove+diskValuesTowerC));
            printRightSquareBracket();
            printWhiteSpaces(diskValuesOfMove);
            printf("|");
            printWhiteSpaces(diskValuesOfMove);
            printLeftSquareBracket();
        }
        else
        {
            diskValuesTowerC = towers->towerB[i];
            printTab(towerDistance-diskValuesTowerC);
            printf("|");
        }
        printf("\n");
        
    }
    
    //printing the lines at the end
    for (i = 0; i < numberOfDisks*8 ; i++) {
        //printf("%d",numberOfDisks*6);
        printf("=");
    }
    printf("\n");
}

/*These functions help with printing,
 I broke them up so it will be easier to read the
 printTowers function.
 These frunctions are pretty much self explanatory
 by the name of the function*/

void printRightSquareBracket(){
    char rightSquareBracket='[';
    printf("%c",rightSquareBracket);
}


void printLeftSquareBracket(){
    char leftSquareBracket=']';
    printf("%c",leftSquareBracket);
}

void printTab(int spaces){
    int i = 0;
    for (i=0; i<spaces; i++) {
        printf(" ");
    }
}

void printWhiteSpaces(int whiteSpaceNeeded){
    int i;
    for (i =0; i < whiteSpaceNeeded-1; i++) {
        printf(" ");
    }
    
}