#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int find_nth_carol(int n, unsigned long long *result) {
    if (result == NULL) {
        return -1;
    }
    if (n <= 0) {
        return -1;
    }
    
    /* Possible weaknesses found:
     *  Assuming that condition 'n>63' is not redundant
     */
    if (n > 63) {
        return -1;
    }
    
    /* Possible weaknesses found:
     *  Shift
     *  Shifting 64-bit value by 64 bits is undefined behaviour. See condition at line 14. [shiftTooManyBits]
     */
    unsigned long long power_of_two = 1ULL << (n + 1);
    
    if (power_of_two > ULLONG_MAX / 2) {
        return -1;
    }
    
    *result = power_of_two * (power_of_two - 2) - 1;
    return 0;
}

int main(void) {
    int n;
    unsigned long long carol_number;
    
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (find_nth_carol(n, &carol_number) != 0) {
        fprintf(stderr, "Invalid input or overflow\n");
        return EXIT_FAILURE;
    }
    
    printf("%d-th Carol number: %llu\n", n, carol_number);
    return EXIT_SUCCESS;
}