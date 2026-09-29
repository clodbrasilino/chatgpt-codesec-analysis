#include <stdio.h>
#include <stdlib.h>

int count_digits(int num) {
    if (num == 0) {
        return 1;
    }
    
    unsigned int n;
    if (num == -2147483647 - 1) {
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

int main(int argc, char * const argv[]) {
    int number;
    if (argc != 2) {
        return 1;
    }
    
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val < -2147483647 - 1 || val > 2147483647) {
        return 1;
    }
    
    number = (int)val;
    printf("%d\n", count_digits(number));
    return 0;
}