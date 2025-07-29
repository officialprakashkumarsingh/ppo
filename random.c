#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * Generates a random integer within a specified range.
 * 
 * @param min The minimum value of the range (inclusive).
 * @param max The maximum value of the range (inclusive).
 * @return A random integer between min and max.
 */
int getRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}

int main() {
    // Seed the random number generator with the current time
    srand(time(NULL));
    
    // Example usage of random number generation
    printf("Generating 10 random numbers between 1 and 100:\n");
    for (int i = 0; i < 10; i++) {
        int randomNum = getRandomNumber(1, 100);
        printf("Random number %d: %d\n", i + 1, randomNum);
    }
    
    return 0;
}