#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

void sortString(char *str, size_t max_len) {
    if (str == NULL) {
        return;
    }
    
    size_t len = strnlen(str, max_len);
    if (len == 0) {
        return;
    }
    
    for (size_t i = 0; i < len - 1; i++) {
        for (size_t j = 0; j < len - i - 1; j++) {
            if (str[j] > str[j + 1]) {
                char temp = str[j];
                str[j] = str[j + 1];
                str[j + 1] = temp;
            }
        }
    }
}

int main(void) {
    enum { INPUT_SIZE = 256 };
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_SIZE];
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    size_t len = strnlen(input, sizeof(input));
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }
    
    sortString(input, sizeof(input));
    
    printf("Sorted string: %s\n", input);
    
    return EXIT_SUCCESS;
}