#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUFFER_SIZE 256
#define CHARS_SIZE 128

void replace_chars(char *str, size_t str_size, const char *old_chars, size_t old_size, const char *new_chars, size_t new_size) {
    if (str == NULL || old_chars == NULL || new_chars == NULL || str_size == 0) {
        return;
    }
    
    size_t old_len = strnlen(old_chars, old_size);
    size_t new_len = strnlen(new_chars, new_size);
    
    if (old_len != new_len) {
        return;
    }
    
    size_t str_len = strnlen(str, str_size);
    if (str_len == str_size) {
        str[str_size - 1] = '\0';
        str_len = str_size - 1;
    }
    
    for (size_t i = 0; i < str_len; i++) {
        for (size_t j = 0; j < old_len; j++) {
            if (str[i] == old_chars[j]) {
                str[i] = new_chars[j];
                break;
            }
        }
    }
}

void remove_newline(char *str, size_t max_size) {
    if (str == NULL || max_size == 0) {
        return;
    }
    
    size_t len = strnlen(str, max_size);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    } else if (len == max_size) {
        str[max_size - 1] = '\0';
    }
}

bool read_input(char *buffer, size_t size, const char *prompt) {
    if (buffer == NULL || size == 0) {
        return false;
    }
    
    printf("%s", prompt);
    if (fgets(buffer, size, stdin) == NULL) {
        return false;
    }
    
    remove_newline(buffer, size);
    return true;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char old_chars[CHARS_SIZE] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char new_chars[CHARS_SIZE] = {0};
    
    if (!read_input(buffer, sizeof(buffer), "Enter a string: ")) {
        return EXIT_FAILURE;
    }
    
    if (!read_input(old_chars, sizeof(old_chars), "Enter characters to replace: ")) {
        return EXIT_FAILURE;
    }
    
    if (!read_input(new_chars, sizeof(new_chars), "Enter replacement characters: ")) {
        return EXIT_FAILURE;
    }
    
    replace_chars(buffer, sizeof(buffer), old_chars, sizeof(old_chars), new_chars, sizeof(new_chars));
    
    printf("Result: %s\n", buffer);
    
    return EXIT_SUCCESS;
}