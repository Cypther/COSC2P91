//
//  calculate.c
//  Task 1
//  Created by Long Nguyen on 2015-01-31.
//

#include <stdio.h>



/*Function prototypes*/

//compare string function
int compareString(char*, char*);

//fucntion for factorial
long long factorial(int);

//fucntion for fibonacci
int fibonacci(int);

int main(int argc, const char * argv[]) {
    
    
    //checking how many arguments are passed in
    if (argc < 2){
        printf("Invalid Parameters\n");
        return -1;
    }
    
    char *first = argv[1];
    //char *second = argv[2];
    char *second = "factorial";
    char *third = "fibonacci";
    int result;
    
    result = compareString(first, second);
    
    int number = atoi(argv[2]); // getting the second argument which should be a number
    
    
    if (result == 0) {
        
        // return if the number is less than zero or greater than 21
        if(number < 0 || number > 21){
            printf("It will only work on at least domain [1..20] for factorial!");
            return -1;
        }else{
            // do the factorial function
            printf("%d! = %lld\n", number, factorial(number));
        
        }
        
    }
    
    result = compareString(first, third);
    
    if (result == 0) {
        
        // return if the number is less than zero or greater than 75
        if(number < 0 || number > 75){
            printf("It will only work on at least domain [1..75] for fibonacci!");
            return -1;
        }else{
        
            // do the factorial fibonacci
            fibonacci(number);
        }
        
    }
    
    return 0;
}


//comparing two strings functino with pointers
int compareString(char *first, char *second)
{
    while(*first==*second)
    {
        if ( *first == '\0' || *second == '\0' )
            break;
        
        first++;
        second++;
    }
    if( *first == '\0' && *second == '\0' )
        return 0;
    else
        return -1;
}

//factorial function
long long factorial(int n)
{
    int i;
    long result = 1;
    
    for (i = 1; i <= n; i++)
        result = result * i;
    
    return result;
}


//fibonacci fucntion
int fibonacci(int number)
{
    
    long long n = number;
    long long  first = 1, second = 1, next = 0;
    int i;
    
    for ( i = 0 ; i < n ; i++ )
    {
        if ( i <= 1 )
            next = i;
        else
        {
            next = first + second;
            first = second;
            second = next;
        }
    }
    
    printf("fib(%lld) = %lld\n",n, next);
    
    return 0;
    
}



