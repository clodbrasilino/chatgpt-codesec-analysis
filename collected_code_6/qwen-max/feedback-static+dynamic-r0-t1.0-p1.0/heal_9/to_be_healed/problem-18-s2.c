#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_chars(char *str1, const char *str2) {
    size_t len1 = strnlen(str1, 100);
    char *result = malloc(len1 + 1);
    if (result == NULL) {
        return;
    }
    result[0] = '\0';
    size_t result_len = 0;

    for (size_t i = 0; i < len1; i++) {
        int should_copy = 1;
        for (size_t j = 0; str2[j] != '\0'; j++) {
            if (str1[i] == str2[j]) {
                should_copy = 0;
                break;
            }
        }
        if (should_copy) {
            if (result_len < len1) {
                result[result_len++] = str1[i];
            } else {
                break;
            }
        }
    }
    result[result_len] = '\0';

    size_t new_len = strnlen(result, 100);
    if (new_len <= 100) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(str1, result, new_len + 1);
    }
    free(result);
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str1[100] = "hello world";
    const char *str2 = "lo";
    remove_chars(str1, str2);
    printf("%s\n", str1);
    return 0;
}