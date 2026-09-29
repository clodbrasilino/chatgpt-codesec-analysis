#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int extract_numbers(const char *str, size_t max_len) {
    if (str == NULL) {
        fprintf(stderr, "Error: NULL string provided\n");
        return -1;
    }
    
    if (max_len == 0) {
        fprintf(stderr, "Error: Invalid length\n");
        return -1;
    }
    
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    
    if (len == max_len && str[len - 1] != '\0') {
        fprintf(stderr, "Error: String not null-terminated within bounds\n");
        return -1;
    }
    
    size_t i = 0;
    
    while (i < len) {
        if (isdigit((unsigned char)str[i])) {
            size_t start = i;
            while (i < len && isdigit((unsigned char)str[i])) {
                i++;
            }
            
            size_t num_len = i - start;
            if (num_len > INT_MAX) {
                fprintf(stderr, "Error: Number too long\n");
                return -1;
            }
            
            if (printf("Number: %.*s, Position: %zu\n", (int)num_len, str + start, start) < 0) {
                fprintf(stderr, "Error: Output error\n");
                return -1;
            }
        } else {
            i++;
        }
    }
    
    return 0;
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
    
    size_t len = strnlen(input, sizeof(input));
    if (len == sizeof(input)) {
        fprintf(stderr, "Error: Input too long\n");
        return EXIT_FAILURE;
    }
    
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        /* Possible weaknesses found:
         *  Variable 'len' is assigned a value that is never used. [unreadVariable]
         */
        len--;
    }
    
    if (extract_numbers(input, sizeof(input)) != 0) {
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}