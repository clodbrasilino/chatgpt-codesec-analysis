#include <stdio.h>
#include <stdlib.h>

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

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    
    long val = strtol(argv[1], NULL, 10);
    if (val > 2147483647 || val < -2147483648) {
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