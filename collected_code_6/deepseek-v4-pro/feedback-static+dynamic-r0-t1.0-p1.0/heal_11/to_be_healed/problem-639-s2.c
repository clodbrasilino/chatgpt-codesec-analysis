#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAMES 100
#define NAME_LENGTH 50

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int sum_valid_name_lengths(char (*names)[NAME_LENGTH], int count) {
    int total = 0;
    
    for (int i = 0; i < count; i++) {
        names[i][NAME_LENGTH - 1] = '\0';
        if (names[i][0] != '\0' && !islower((unsigned char)names[i][0])) {
            size_t len = strnlen(names[i], NAME_LENGTH);
            if (len < NAME_LENGTH) {
                total += (int)len;
            }
        }
    }
    
    return total;
}

static void clear_input_buffer(void) {
    int c;
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char (*names)[NAME_LENGTH] = calloc(MAX_NAMES, sizeof(*names));
    if (names == NULL) {
        printf("Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    int count = 0;
    int scanf_result;
    
    printf("Enter number of names: ");
    scanf_result = scanf("%d", &count);
    if (scanf_result != 1) {
        printf("Invalid input\n");
        free(names);
        return EXIT_FAILURE;
    }
    
    clear_input_buffer();
    
    if (count <= 0 || count > MAX_NAMES) {
        printf("Invalid count\n");
        free(names);
        return EXIT_FAILURE;
    }
    
    for (int i = 0; i < count; i++) {
        printf("Enter name %d: ", i + 1);
        if (fgets(names[i], NAME_LENGTH, stdin) == NULL) {
            printf("Error reading input\n");
            free(names);
            return EXIT_FAILURE;
        }
        
        size_t len = strnlen(names[i], NAME_LENGTH);
        if (len > 0 && names[i][len - 1] == '\n') {
            names[i][len - 1] = '\0';
        } else if (len == NAME_LENGTH - 1 && names[i][len - 1] != '\n') {
            names[i][NAME_LENGTH - 1] = '\0';
            clear_input_buffer();
        } else if (len == NAME_LENGTH && names[i][len - 1] != '\n') {
            names[i][NAME_LENGTH - 1] = '\0';
            clear_input_buffer();
        }
        names[i][NAME_LENGTH - 1] = '\0';
    }
    
    int result = sum_valid_name_lengths(names, count);
    printf("Sum of lengths of valid names: %d\n", result);
    
    free(names);
    return EXIT_SUCCESS;
}