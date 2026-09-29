#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool is_even(int number);

bool is_even(int number) {
    return (number % 2 == 0);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    int test_number = (int)strtol(argv[1], NULL, 10);
    
    if (is_even(test_number)) {
        printf("True\n");
    } else {
        printf("False\n");
    }
    
    return EXIT_SUCCESS;
}