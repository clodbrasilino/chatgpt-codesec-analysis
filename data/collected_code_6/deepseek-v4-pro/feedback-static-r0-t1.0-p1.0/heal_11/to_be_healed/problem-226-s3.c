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
    char str[32] = {0};
    const char source[] = "abcdefghij";
    
    size_t copy_len = (sizeof(source) <= sizeof(str)) ? sizeof(source) - 1 : sizeof(str) - 1;
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(str, source, copy_len);
    str[copy_len] = '\0';
    
    printf("Original string: %s\n", str);
    remove_odd_index_chars(str, sizeof(str));
    printf("After removing odd-index characters: %s\n", str);
    
    return 0;
}