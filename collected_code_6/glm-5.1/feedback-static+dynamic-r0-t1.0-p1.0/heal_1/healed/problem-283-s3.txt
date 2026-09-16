#include <stdio.h>
#include <stdlib.h>

int check_digit_frequency(long long n) {
    if (n < 0) {
        return 0;
    }
    
    int freq[10] = {0};
    long long temp = n;
    
    if (temp == 0) {
        freq[0] = 1;
    } else {
        while (temp > 0) {
            freq[temp % 10]++;
            temp /= 10;
        }
    }
    
    for (int i = 0; i < 10; i++) {
        if (freq[i] > i) {
            return 0;
        }
    }
    
    return 1;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    char *endptr;
    long long val = strtoll(argv[1], &endptr, 10);
    
    if (*endptr != '\0' || endptr == argv[1]) {
        fprintf(stderr, "Invalid input: not a valid number\n");
        return EXIT_FAILURE;
    }
    
    if (check_digit_frequency(val)) {
        printf("1\n");
    } else {
        printf("0\n");
    }
    
    return EXIT_SUCCESS;
}