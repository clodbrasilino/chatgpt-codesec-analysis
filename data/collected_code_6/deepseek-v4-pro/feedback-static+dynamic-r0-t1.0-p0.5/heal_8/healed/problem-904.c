#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

bool is_even(int number) {
    return number % 2 == 0;
}

int main(void) {
    int test_number;
    unsigned int seed;
    FILE *urandom;
    
    urandom = fopen("/dev/urandom", "rb");
    if (urandom == NULL) {
        seed = (unsigned int)time(NULL) ^ (unsigned int)getpid();
    } else {
        if (fread(&seed, sizeof(seed), 1, urandom) != 1) {
            seed = (unsigned int)time(NULL) ^ (unsigned int)getpid();
        }
        fclose(urandom);
    }
    
    srand(seed);
    test_number = rand() % 2001 - 1000;
    
    if (is_even(test_number)) {
        printf("%d is even\n", test_number);
        return 0;
    } else {
        printf("%d is odd\n", test_number);
        return 1;
    }
}