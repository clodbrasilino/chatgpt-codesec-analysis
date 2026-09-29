#include <stdio.h>
#include <string.h>
#include <stddef.h>

void remove_chars(char *str1, const char *str2, size_t len1) {
    /* Possible weaknesses found:
     *  variable-sized object may not be initialized
     *  variable-sized object may not be initialized except with an empty initializer
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char result[len1 + 1] = {0};
    for (size_t i = 0; i < len1 && str1[i] != '\0'; i++) {
        int found = 0;
        for (size_t j = 0; str2[j] != '\0' && !found; j++) {
            if (str1[i] == str2[j]) {
                found = 1;
            }
        }
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (!found && strlen(result) < len1) {
            /* Possible weaknesses found:
             * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
             */
            strncat(result, &str1[i], 1);
        }
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t result_len = strlen(result);
    if (result_len <= len1) {
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(str1, result, len1);
        str1[len1 - 1] = '\0';
    }
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str1[100] = "hello world";
    const char *str2 = "lo";
    remove_chars(str1, str2, sizeof(str1) - 1);
    printf("%s\n", str1);
    return 0;
}