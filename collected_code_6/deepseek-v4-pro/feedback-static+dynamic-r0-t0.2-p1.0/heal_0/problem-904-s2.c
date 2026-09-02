#include <stdbool.h>
#include <stdio.h>

bool is_even(int number) {
    return number % 2 == 0;
}

int main(void) {
    int test_numbers[] = {0, 1, 2, -3, -4, 42, 101};
    size_t count = sizeof(test_numbers) / sizeof(test_numbers[0]);
    
    for (size_t i = 0; i < count; i++) {
        printf("%d is %s\n", test_numbers[i], 
               is_even(test_numbers[i]) ? "even" : "odd");
    }
    
    return 0;
}