#include <stdio.h>
#include <stdbool.h>

bool is_even(int num) {
    return num % 2 == 0;
}

int main(void) {
    int test_num = 4;
    printf("%d\n", is_even(test_num));
    return 0;
}