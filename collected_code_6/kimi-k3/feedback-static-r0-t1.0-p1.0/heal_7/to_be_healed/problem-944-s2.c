#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <limits.h>

void print_numbers_with_positions(const char *str) {
    if (str == NULL) {
        return;
    }
    
    size_t i = 0;
    while (str[i] != '\0') {
        if (isdigit((unsigned char)str[i])) {
            size_t start = i;
            while (str[i] != '\0' && isdigit((unsigned char)str[i])) {
                i++;
            }
            if (i - start <= INT32_MAX) {
                printf("Number: %.*s, Position: %zu\n", (int)(i - start), str + start, start);
            }
        } else {
            i++;
        }
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    size_t len = strnlen(input, sizeof(input));
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }
    
    print_numbers_with_positions(input);
    
    return 0;
}