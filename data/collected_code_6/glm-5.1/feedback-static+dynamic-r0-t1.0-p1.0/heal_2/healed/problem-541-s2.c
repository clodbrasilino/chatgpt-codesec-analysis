#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int is_abundant(int num) {
    if (num <= 1) {
        return 0;
    }

    int sum = 1;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            sum += i;
            if (i != num / i) {
                sum += num / i;
            }
        }
    }

    return sum > num;
}

int main(int argc, char * const * const argv) {
    if (argc == 2) {
        char *endptr;
        errno = 0;
        long long_val = strtol(argv[1], &endptr, 10);
        if (errno != 0 || endptr == argv[1] || *endptr != '\0' || long_val < INT_MIN || long_val > INT_MAX) {
            return 1;
        }
        int number = (int)long_val;
        
        if (number <= 0) {
            return 1;
        }
        
        printf("%d\n", is_abundant(number));
    } else {
        int number;
        if (scanf("%d", &number) != 1) {
            return 1;
        }
        
        if (number <= 0) {
            return 1;
        }
        
        printf("%d\n", is_abundant(number));
    }

    return 0;
}