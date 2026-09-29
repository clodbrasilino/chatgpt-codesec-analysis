#include <stdio.h>
#include <stdlib.h>

int max_occurring_divisor(int a, int b) {
    if (a <= 0 || b <= 0 || a > b) {
        return -1;
    }

    int *div_count = (int *)calloc(b + 1, sizeof(int));
    if (div_count == NULL) {
        return -1;
    }

    for (int i = a; i <= b; i++) {
        for (int j = 1; j * j <= i; j++) {
            if (i % j == 0) {
                div_count[j]++;
                if (j != i / j) {
                    div_count[i / j]++;
                }
            }
        }
    }

    int max_count = 0;
    int max_div = -1;

    for (int d = 1; d <= b; d++) {
        if (div_count[d] > max_count) {
            max_count = div_count[d];
            max_div = d;
        }
    }

    free(div_count);

    return max_div;
}

int main() {
    int a = 10;
    int b = 20;
    
    int result = max_occurring_divisor(a, b);
    
    if (result != -1) {
        printf("%d\n", result);
    } else {
        printf("Invalid input or memory allocation failed\n");
    }
    
    return 0;
}