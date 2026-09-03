#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

bool is_even(int number) {
    return number % 2 == 0;
}

int main(void) {
    srand(time(NULL));
    int test_number = rand() % 100;
    bool result = is_even(test_number);
    
    if (result) {
        return EXIT_SUCCESS;
    }
    
    return EXIT_FAILURE;
}