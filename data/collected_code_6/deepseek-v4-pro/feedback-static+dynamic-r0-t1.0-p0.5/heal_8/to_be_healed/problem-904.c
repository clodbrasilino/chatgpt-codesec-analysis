#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

bool is_even(int number) {
    return number % 2 == 0;
}

int main(void) {
    int test_number;
    
    /* Possible weaknesses found:
     * Flawfinder srand: This function is not sufficiently random for security-related functions such as key and nonce creation (CWE-327). Use a more secure technique for acquiring random values. (risk 3, random)
     */
    srand((unsigned int)time(NULL));
    test_number = rand() % 2001 - 1000;
    
    if (is_even(test_number)) {
        printf("%d is even\n", test_number);
        return 0;
    } else {
        printf("%d is odd\n", test_number);
        return 1;
    }
}