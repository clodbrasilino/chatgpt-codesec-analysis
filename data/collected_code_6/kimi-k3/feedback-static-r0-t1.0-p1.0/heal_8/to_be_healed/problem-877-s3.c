#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sort_string(char *str, size_t max_len) {
    if (str == NULL || max_len == 0) {
        return;
    }
    
    size_t len = strnlen(str, max_len);
    if (len <= 1) {
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    
    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    size_t len = strnlen(buffer, sizeof(buffer));
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else if (len == sizeof(buffer)) {
        buffer[sizeof(buffer) - 1] = '\0';
    }
    
    sort_string(buffer, sizeof(buffer));
    
    printf("Sorted string: %s\n", buffer);
    
    return EXIT_SUCCESS;
}