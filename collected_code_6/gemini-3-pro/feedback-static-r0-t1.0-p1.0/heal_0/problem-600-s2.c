#include <stdio.h>
#include <stdbool.h>

bool is_even(int num) {
    return (num & 1) == 0;
}

int main(void) {
    int num;
    
    if (scanf("%d", &num) != 1) {
        return 1;
    }

    if (is_even(num)) {
        printf("Even\n");
    } else {
        printf("Odd\n");
    }

    return 0;
}