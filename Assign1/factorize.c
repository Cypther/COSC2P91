//
//  factorize.c
//  Task 2
//
//  Created by Long Nguyen on 2015-01-31.
//


/*Function prototypes*/

//fucntion for factorial
void primeFactors();
void factors();


#include <stdio.h>

int main(int argc, const char * argv[]) {
    
    
    int number;

    //loop until zero is end to end the program
    do {
       
      printf("1. Factors \n");
      printf("2. Prime Factors \n");
      printf("0. Stop \n");
        
      scanf("%d", &number);
        
        
        if (number == 1) {
            factors();
        }
        
        if (number == 2) {
            primeFactors();
        }
        
        
        
    } while (number != 0);
    
    
}

/* primeFactor function check what number will factor
   into the number that the user input, by checking if the 
   number is odd using modulo operator and check if it's a prime
   number */

void primeFactors(){

    int div, number;
    
    div = 2;
    
    printf("Enter a number to know its prime factor: ");
    scanf("%d",&number);
    
    printf("Number to factorize: %d\n", number);
    
    while(number!=0){
        if(number%div!=0)
            div = div + 1;
        else {
            number = number / div;
            printf("%d\t",div);
            if(number==1)
                break;
        }
    }

    printf("\n");

}


/* Factor function check what number will factor
 into the number that the user input, by checking if the
 number is even using modulo operator and if the user's number is 
 divisible by an odd number */


void factors(){
    
    int div, number;
    
    div = 1;
    
    printf("Number to factorize: ");
    scanf("%d",&number);
    
    printf("Number to factorize: %d\n", number);
    
    while(div <= number){
        if(number%div==0){
            //div = div + 1;
            printf("%d\t",div);
            div = div + 1;
        }else{
          div = div + 1;
        }
    }
    
    printf("\n");
    
}

