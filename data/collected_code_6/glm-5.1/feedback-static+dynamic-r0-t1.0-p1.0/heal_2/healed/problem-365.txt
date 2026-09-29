#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int count_digits(int num) {
    if (num == 0) {
        return 1;
    }
    
    unsigned int n;
    if (num == INT_MIN) {
        n = (unsigned int)num;
    } else if (num < 0) {
        n = (unsigned int)(-num);
    } else {
        n = (unsigned int)num;
    }
    
    int count = 0;
    while (n > 0) {
        count++;
        n /= 10;
    }
    return count;
}

int main(int argc, char const * const argv[]) {
    int number;
    if (argc != 2) {
        return 1;
    }
    
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val < INT_MIN || val > INT_MAX) {
        return 1;
    }
    
    number = (int)val;
    printf("%d\n", count_digits(number));
    return 0;
}