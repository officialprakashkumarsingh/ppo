#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Seed the random number generator with the current time
    srand(time(NULL));
    
    // Generate and print a random number between 1 and 100
    int randomNumber = (rand() % 100) + 1;
    printf("Random number: %d\n", randomNumber);
    
    return 0;
}