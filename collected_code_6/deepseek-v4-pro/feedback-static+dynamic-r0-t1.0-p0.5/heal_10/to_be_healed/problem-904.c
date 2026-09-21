#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

bool is_even(int number) {
    return number % 2 == 0;
}

int main(void) {
    int test_number;
    unsigned int seed;
    FILE *urandom;
    
    /* Possible weaknesses found:
     * Flawfinder fopen: Check when opening files - can an attacker redirect it (via symlinks), force the opening of special file type (e.g., device files), move things around to create a race condition, control its ancestors, or change its contents? (CWE-362). (risk 2, misc)
     */
    urandom = fopen("/dev/urandom", "rb");
    if (urandom == NULL) {
        seed = (unsigned int)time(NULL) ^ (unsigned int)getpid();
    } else {
        if (fread(&seed, sizeof(seed), 1, urandom) != 1) {
            seed = (unsigned int)time(NULL) ^ (unsigned int)getpid();
        }
        fclose(urandom);
    }
    
    test_number = (int)(seed % 2001) - 1000;
    
    if (is_even(test_number)) {
        printf("%d is even\n", test_number);
        return 0;
    } else {
        printf("%d is odd\n", test_number);
        return 1;
    }
}