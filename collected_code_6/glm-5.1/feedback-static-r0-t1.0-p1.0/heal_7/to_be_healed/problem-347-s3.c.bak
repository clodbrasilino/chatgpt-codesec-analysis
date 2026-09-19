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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    if (argc != 3) {
        return EXIT_FAILURE;
    }
    
    char *endptr1;
    char *endptr2;
    long val1 = strtol(argv[1], &endptr1, 10);
    long val2 = strtol(argv[2], &endptr2, 10);
    
    if (val1 <= 0 || val2 <= 0 || *endptr1 != '\0' || *endptr2 != '\0') {
        return EXIT_FAILURE;
    }
    
    printf("%llu\n", count_squares((int)val1, (int)val2));
    
    return EXIT_SUCCESS;
}