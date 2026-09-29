#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define INPUT_BUFFER_SIZE 1024

void print_numbers_with_positions(const char *str) {
    int i = 0;
    int in_number = 0;
    int start_pos = 0;
    
    while (str[i] != '\0') {
        if (isdigit((unsigned char)str[i])) {
            if (!in_number) {
                start_pos = i;
                in_number = 1;
            }
        } else {
            if (in_number) {
                printf("Number: ");
                for (int j = start_pos; j < i; j++) {
                    putchar(str[j]);
                }
                printf(", Position: %d\n", start_pos);
                in_number = 0;
            }
        }
        i++;
    }
    
    if (in_number) {
        printf("Number: ");
        for (int j = start_pos; j < i; j++) {
            putchar(str[j]);
        }
        printf(", Position: %d\n", start_pos);
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_BUFFER_SIZE];
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    input[sizeof(input) - 1] = '\0';
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    } else {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }
    
    print_numbers_with_positions(input);
    
    return 0;
}