#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

bool is_even(int number) {
    return number % 2 == 0;
}

int main(void) {
    unsigned int seed;
    /* Possible weaknesses found:
     * Flawfinder fopen: Check when opening files - can an attacker redirect it (via symlinks), force the opening of special file type (e.g., device files), move things around to create a race condition, control its ancestors, or change its contents? (CWE-362). (risk 2, misc)
     */
    FILE *urandom = fopen("/dev/urandom", "rb");
    if (urandom) {
        if (fread(&seed, sizeof(seed), 1, urandom) != 1) {
            fclose(urandom);
            return EXIT_FAILURE;
        }
        fclose(urandom);
    } else {
        return EXIT_FAILURE;
    }
    
    /* Possible weaknesses found:
     * Flawfinder srand: This function is not sufficiently random for security-related functions such as key and nonce creation (CWE-327). Use a more secure technique for acquiring random values. (risk 3, random)
     */
    srand(seed);
    
    int test_number = rand() % 100;
    bool result = is_even(test_number);
    
    if (result) {
        return EXIT_SUCCESS;
    }
    
    return EXIT_FAILURE;
}