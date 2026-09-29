#include <stdio.h>
#include <stdlib.h>

int count_divisors(int n) {
    if (n == 0) {
        return 0;
    }
    if (n < 0) {
        /* Possible weaknesses found:
         *  Either the condition 'val<-2147483648' is redundant or there is signed integer overflow for expression '-n'. [integerOverflowCond]
         *  Integer overflow
         */
        n = -n;
    }
    int count = 0;
    int i;
    for (i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            if (i * i == n) {
                count += 1;
            } else {
                count += 2;
            }
        }
    }
    return count;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    
    if (*endptr != '\0' || endptr == argv[1]) {
        fprintf(stderr, "Error: Invalid integer format\n");
        return EXIT_FAILURE;
    }
    
    /* Possible weaknesses found:
     *  Assuming that condition 'val<-2147483648' is not redundant
     */
    if (val > 2147483647 || val < -2147483648) {
        fprintf(stderr, "Error: Integer overflow\n");
        return EXIT_FAILURE;
    }
    
    /* Possible weaknesses found:
     *  n is assigned '(int)val' here.
     */
    int n = (int)val;
    /* Possible weaknesses found:
     *  Calling function 'count_divisors', 1st argument 'n' value is -2147483648
     */
    printf("Number of divisors: %d\n", count_divisors(n));
    
    return EXIT_SUCCESS;
}