#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAMES 100

int sum_valid_name_lengths(char names[][50], int count) {
    int total = 0;
    
    for (int i = 0; i < count; i++) {
        if (names[i][0] != '\0' && !islower((unsigned char)names[i][0])) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            total += strlen(names[i]);
        }
    }
    
    return total;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char names[MAX_NAMES][50];
    int count = 0;
    
    printf("Enter number of names: ");
    if (scanf("%d", &count) != 1) {
        printf("Invalid input\n");
        return EXIT_FAILURE;
    }
    
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    getchar();
    
    if (count <= 0 || count > MAX_NAMES) {
        printf("Invalid count\n");
        return EXIT_FAILURE;
    }
    
    for (int i = 0; i < count; i++) {
        printf("Enter name %d: ", i + 1);
        if (fgets(names[i], 50, stdin) == NULL) {
            printf("Error reading input\n");
            return EXIT_FAILURE;
        }
        
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(names[i]);
        if (len > 0 && names[i][len - 1] == '\n') {
            names[i][len - 1] = '\0';
        }
    }
    
    int result = sum_valid_name_lengths(names, count);
    printf("Sum of lengths of valid names: %d\n", result);
    
    return EXIT_SUCCESS;
}