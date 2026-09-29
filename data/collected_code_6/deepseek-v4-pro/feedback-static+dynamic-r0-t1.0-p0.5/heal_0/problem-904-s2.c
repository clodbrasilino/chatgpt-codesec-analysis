#include <stdbool.h>

bool is_even(int number) {
    return number % 2 == 0;
}

int main(void) {
    int test_number = 42;
    
    if (is_even(test_number)) {
        return 0;
    }
    
    return 1;
}