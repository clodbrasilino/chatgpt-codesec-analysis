#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 256
#define CHARS_SIZE 128

void replace_chars(char *str, const char *old_chars, const char *new_chars) {
    if (str == NULL || old_chars == NULL || new_chars == NULL) {
        return;
    }
    
    size_t old_len = strnlen(old_chars, CHARS_SIZE);
    size_t new_len = strnlen(new_chars, CHARS_SIZE);
    
    if (old_len != new_len) {
        return;
    }
    
    for (size_t i = 0; str[i] != '\0'; i++) {
        for (size_t j = 0; j < old_len; j++) {
            if (str[i] == old_chars[j]) {
                str[i] = new_chars[j];
                break;
            }
        }
    }
}

void remove_newline(char *str, size_t max_size) {
    if (str == NULL) {
        return;
    }
    
    size_t len = strnlen(str, max_size);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char old_chars[CHARS_SIZE];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char new_chars[CHARS_SIZE];
    
    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return EXIT_FAILURE;
    }
    remove_newline(buffer, sizeof(buffer));
    
    printf("Enter characters to replace: ");
    if (fgets(old_chars, sizeof(old_chars), stdin) == NULL) {
        return EXIT_FAILURE;
    }
    remove_newline(old_chars, sizeof(old_chars));
    
    printf("Enter replacement characters: ");
    if (fgets(new_chars, sizeof(new_chars), stdin) == NULL) {
        return EXIT_FAILURE;
    }
    remove_newline(new_chars, sizeof(new_chars));
    
    replace_chars(buffer, old_chars, new_chars);
    
    printf("Result: %s\n", buffer);
    
    return EXIT_SUCCESS;
}