//
//  fractions.c
//  Task 3
//
//  Created by Long Nguyen on 2015-01-31.
//


/*Function prototypes*/
void fraction(int numerator, int denominator);

//finding the GCD of the two numbers
int gcd(int numerator, int denominator);

#include <stdio.h>

int main(int argc, const char * argv[]) {

     int numerator, denominator;
    
    //loop until zero is end to end the program
    do {
        
        /*denominator is automatically initialized to 1
         intill the user's change it to something else
         */
        numerator = 0;
        denominator = 1;
        printf("Enter fraction (0 to end): ");
        
        //getting the user's inputs
        scanf("%d/%d", &numerator, &denominator);
        fraction(numerator, denominator);
        
        
        
        
    } while (numerator != 0);
    
    return 0;

}

void fraction(int numerator, int denominator){
    
    //error message if the user tries to divides by zero
    if (denominator == 0) {
        printf("Denominator can't be zero!\n");
        return;
    }

    //variables for sorting the new lowest Numerator and Denominator
    int lowestNumerator, lowestDenominator;
    
    
    /*calculations finding the GCD of numerator and denominator and
     then dividing both the numerator and denominator by the GCD */
    
    lowestNumerator = numerator / gcd(numerator, denominator);
    lowestDenominator = denominator / gcd(numerator, denominator);
    
    //Displaying the results
    
    if (denominator == 1) {
        printf("%d/%d\n", lowestNumerator, lowestDenominator);
    }else{
    
        printf("%d/%d\n", lowestNumerator, lowestDenominator);
    }




}


/*gcf (greatest common divisor) function return gcd of two numbers that's passed in*/
int gcd(int numerator, int denominator)
{
    int gcd, remainder;
    
    while (numerator != 0)
    {
        remainder = denominator % numerator;
        denominator = numerator;
        numerator = remainder;
    }
    
    gcd = denominator;
    
    return gcd;
}//end gcd function
