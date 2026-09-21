#include <stdio.h>
#include <string.h>

void remove_odd_index_chars(char *str, size_t max_len) {
    if (str == NULL || max_len == 0) return;
    
    size_t i, j = 0;
    size_t str_len = strnlen(str, max_len);
    
    for (i = 0; i < str_len; i++) {
        if (i % 2 == 0) {
            str[j++] = str[i];
        }
    }
    if (j < max_len) {
        str[j] = '\0';
    } else {
        str[max_len - 1] = '\0';
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[32];
    /* Possible weaknesses found:
     *  The scope of the variable 'source' can be reduced. [variableScope]
     */
    const char *source = "abcdefghij";
    
    if (sizeof(str) > 0) {
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(str, source, sizeof(str) - 1);
        str[sizeof(str) - 1] = '\0';
    }
    
    printf("Original string: %s\n", str);
    remove_odd_index_chars(str, sizeof(str));
    printf("After removing odd-index characters: %s\n", str);
    
    return 0;
}