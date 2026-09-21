#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool isUndulating(int num) {
    if (num < 100) {
        return false;
    }

    int d1 = num % 10;
    int d2 = (num / 10) % 10;

    if (d1 == d2) {
        return false;
    }

    num /= 100;

    while (num > 0) {
        if (num % 10 != d1) {
            return false;
        }
        num /= 10;

        if (num > 0) {
            if (num % 10 != d2) {
                return false;
            }
            num /= 10;
        }
    }

    return true;
}

int main(void) {
    int input;
    
    if (scanf("%d", &input) != 1) {
        return EXIT_FAILURE;
    }

    if (isUndulating(input)) {
        printf("The number is undulating.\n");
    } else {
        printf("The number is not undulating.\n");
    }

    return EXIT_SUCCESS;
}