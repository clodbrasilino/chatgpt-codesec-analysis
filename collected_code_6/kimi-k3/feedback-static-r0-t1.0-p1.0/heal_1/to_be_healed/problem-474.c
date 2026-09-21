#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void replace_chars(char *str, const char *old_chars, const char *new_chars) {
    if (str == NULL || old_chars == NULL || new_chars == NULL) {
        return;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t old_len = strlen(old_chars);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t new_len = strlen(new_chars);
    
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

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    
    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return EXIT_FAILURE;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(buffer);
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
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(old_chars);
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
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(new_chars);
    if (len > 0 && new_chars[len - 1] == '\n') {
        new_chars[len - 1] = '\0';
    }
    
    replace_chars(buffer, old_chars, new_chars);
    
    printf("Result: %s\n", buffer);
    
    return EXIT_SUCCESS;
}