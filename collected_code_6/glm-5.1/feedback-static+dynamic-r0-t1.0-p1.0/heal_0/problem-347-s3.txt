#include <stdio.h>
#include <stdlib.h>

unsigned long long count_squares(int m, int n) {
    if (m <= 0 || n <= 0) {
        return 0;
    }
    
    if (m < n) {
        int temp = m;
        m = n;
        n = temp;
    }
    
    unsigned long long count = 0;
    while (n > 0) {
        count += (unsigned long long)m * n;
        m--;
        n--;
    }
    
    return count;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        return EXIT_FAILURE;
    }
    
    long val1 = strtol(argv[1], NULL, 10);
    long val2 = strtol(argv[2], NULL, 10);
    
    if (val1 <= 0 || val2 <= 0) {
        return EXIT_FAILURE;
    }
    
    printf("%llu\n", count_squares((int)val1, (int)val2));
    
    return EXIT_SUCCESS;
}