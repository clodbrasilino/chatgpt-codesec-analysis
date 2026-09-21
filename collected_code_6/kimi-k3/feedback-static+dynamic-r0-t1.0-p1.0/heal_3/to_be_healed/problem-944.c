#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void extract_numbers(const char *str) {
    if (str == NULL) {
        fprintf(stderr, "Error: NULL string provided\n");
        return;
    }
    
    size_t i = 0;
    
    while (str[i] != '\0') {
        if (isdigit((unsigned char)str[i])) {
            size_t start = i;
            while (str[i] != '\0' && isdigit((unsigned char)str[i])) {
                i++;
            }
            printf("Number: %.*s, Position: %zu\n", (int)(i - start), str + start, start);
        } else {
            i++;
        }
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    input[strcspn(input, "\n")] = '\0';
    
    extract_numbers(input);
    
    return EXIT_SUCCESS;
}