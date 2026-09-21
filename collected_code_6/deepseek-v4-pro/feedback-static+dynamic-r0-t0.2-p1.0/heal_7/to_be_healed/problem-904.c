#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

bool is_even(int number) {
    return number % 2 == 0;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder srand: This function is not sufficiently random for security-related functions such as key and nonce creation (CWE-327). Use a more secure technique for acquiring random values. (risk 3, random)
     */
    srand(time(NULL));
    int test_number = rand() % 100;
    bool result = is_even(test_number);
    
    if (result) {
        return EXIT_SUCCESS;
    }
    
    return EXIT_FAILURE;
}