#include <stdbool.h>
#include <stdlib.h>

bool is_even(int number) {
    return number % 2 == 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    int test_number = 0;
    
    if (argc > 1) {
        test_number = atoi(argv[1]);
    } else {
        test_number = 42;
    }
    
    if (is_even(test_number)) {
        return 0;
    }
    
    return 1;
}