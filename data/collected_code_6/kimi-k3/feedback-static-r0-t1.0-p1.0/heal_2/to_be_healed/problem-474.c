#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void replace_chars(char *str, size_t str_size, const char *old_chars, size_t old_size, const char *new_chars, size_t new_size) {
    if (str == NULL || old_chars == NULL || new_chars == NULL) {
        return;
    }
    
    size_t old_len = strnlen(old_chars, old_size);
    size_t new_len = strnlen(new_chars, new_size);
    
    if (old_len != new_len) {
        return;
    }
    
    size_t str_len = strnlen(str, str_size);
    for (size_t i = 0; i < str_len; i++) {
        for (size_t j = 0; j < old_len; j++) {
            if (str[i] == old_chars[j]) {
                str[i] = new_chars[j];
                break;
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
        return EXIT_FAILURE;
    }
    
    size_t len = strnlen(buffer, sizeof(buffer));
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    
    printf("Enter characters to replace: ");
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char old_chars[128];
    if (fgets(old_chars, sizeof(old_chars), stdin) == NULL) {
        return EXIT_FAILURE;
    }
    
    len = strnlen(old_chars, sizeof(old_chars));
    if (len > 0 && old_chars[len - 1] == '\n') {
        old_chars[len - 1] = '\0';
    }
    
    printf("Enter replacement characters: ");
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char new_chars[128];
    if (fgets(new_chars, sizeof(new_chars), stdin) == NULL) {
        return EXIT_FAILURE;
    }
    
    len = strnlen(new_chars, sizeof(new_chars));
    if (len > 0 && new_chars[len - 1] == '\n') {
        new_chars[len - 1] = '\0';
    }
    
    replace_chars(buffer, sizeof(buffer), old_chars, sizeof(old_chars), new_chars, sizeof(new_chars));
    
    printf("Result: %s\n", buffer);
    
    return EXIT_SUCCESS;
}