#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool isWoodall(int n) {
    if (n < 1) {
        return false;
    }
    
    int m = n + 1;
    int x = 0;
    
    if (m == x) {
        return true;
    }
    
    while (m % 2 == 0) {
        m /= 2;
        x++;
        if (x == m) {
            return true;
        }
    }
    
    return false;
}

int main() {
    int num;
    int result;

    result = scanf("%d", &num);
    if (result != 1) {
        return EXIT_FAILURE;
    }

    if (isWoodall(num)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return EXIT_SUCCESS;
}