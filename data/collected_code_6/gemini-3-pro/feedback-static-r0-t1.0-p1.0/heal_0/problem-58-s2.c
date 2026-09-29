#include <stdio.h>
#include <stdbool.h>

bool have_opposite_signs(int a, int b) {
    if ((a ^ b) < 0) {
        return true;
    }
    return false;
}

int main(void) {
    int num1 = 0;
    int num2 = 0;
    int result = 0;

    result = scanf("%d %d", &num1, &num2);
    if (result != 2) {
        printf("Invalid input\n");
        return 1;
    }

    if (have_opposite_signs(num1, num2)) {
        printf("The integers have opposite signs.\n");
    } else {
        printf("The integers do not have opposite signs.\n");
    }

    return 0;
}