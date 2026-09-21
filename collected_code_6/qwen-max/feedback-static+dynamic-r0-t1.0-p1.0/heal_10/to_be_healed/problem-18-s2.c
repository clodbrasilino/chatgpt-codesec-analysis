#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_chars(char *str1, const char *str2) {
    size_t len1 = strnlen(str1, 100);
    char *result = malloc(len1 + 1);
    if (!result) {
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
        if (should_copy && result_len < len1) {
            result[result_len++] = str1[i];
        }
    }
    result[result_len] = '\0';

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(str1, result, len1 + 1);
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