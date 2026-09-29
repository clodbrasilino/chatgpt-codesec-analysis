#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int is_lucid(int num) {
    if (num <= 1) {
        return 0;
    }
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return 0;
        }
    }
    return 1;
}

int get_lucid_number(int n) {
    if (n < 2) {
        return -1;
    }
    for (int i = n; i >= 2; i--) {
        if (is_lucid(i)) {
            return i;
        }
    }
    return -1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    
    long val = strtol(argv[1], NULL, 10);
    if (val > INT_MAX || val < INT_MIN) {
        return EXIT_FAILURE;
    }
    
    int n = (int)val;
    int result = get_lucid_number(n);
    
    if (result == -1) {
        printf("-1\n");
    } else {
        printf("%d\n", result);
    }
    
    return EXIT_SUCCESS;
}