#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_range(char *str, size_t left, size_t right) {
    while (left < right) {
        char temp = str[left];
        str[left] = str[right];
        str[right] = temp;
        left++;
        right--;
    }
}

void reverse_words(char *str) {
    if (str == NULL) {
        return;
    }

    size_t length = strnlen(str, 1024);
    if (length == 0) {
        return;
    }

    reverse_range(str, 0, length - 1);

    size_t start = 0;
    for (size_t i = 0; i <= length; i++) {
        if (str[i] == ' ' || str[i] == '\0') {
            if (i > start) {
                reverse_range(str, start, i - 1);
            }
            start = i + 1;
        }
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[1024];
    buffer[sizeof(buffer) - 1] = '\0';
    
    if (fgets(buffer, sizeof(buffer) - 1, stdin) == NULL) {
        return EXIT_FAILURE;
    }
    buffer[sizeof(buffer) - 1] = '\0';

    size_t len = strnlen(buffer, sizeof(buffer));
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    reverse_words(buffer);
    
    printf("%s\n", buffer);
    
    return EXIT_SUCCESS;
}