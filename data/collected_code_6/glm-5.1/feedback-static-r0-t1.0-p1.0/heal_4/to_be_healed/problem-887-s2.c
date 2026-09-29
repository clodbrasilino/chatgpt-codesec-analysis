#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int is_odd(int num) {
    return num & 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    int num;
    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    
    if (*endptr != '\0' || endptr == argv[1]) {
        fprintf(stderr, "Error: Invalid integer format.\n");
        return EXIT_FAILURE;
    }
    
    if (val < INT_MIN || val > INT_MAX) {
        fprintf(stderr, "Error: Integer out of range.\n");
        return EXIT_FAILURE;
    }
    
    num = (int)val;
    
    if (is_odd(num)) {
        printf("%d is odd\n", num);
    } else {
        printf("%d is even\n", num);
    }
    
    return EXIT_SUCCESS;
}