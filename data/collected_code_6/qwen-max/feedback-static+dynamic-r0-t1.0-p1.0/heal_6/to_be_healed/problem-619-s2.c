#include <stdio.h>
#include <string.h>
#include <ctype.h>

void move_numbers(char *str, size_t str_len) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char result[str_len + 1];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char temp[str_len + 1];
    int j = 0, k = 0;

    for (size_t i = 0; i < str_len; i++) {
        if (isdigit(str[i]) && j < str_len) {
            result[j++] = str[i];
        } else if (k < str_len) {
            temp[k++] = str[i];
        }
    }

    temp[k] = '\0';
    result[j] = '\0';

    size_t temp_len = strnlen(temp, str_len);
    size_t result_len = strnlen(result, str_len);

    if (result_len + temp_len + 1 <= str_len) {
        /* Possible weaknesses found:
         * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
         */
        strncat(result, temp, str_len - result_len - 1);
    }

    size_t final_len = strnlen(result, str_len);
    if (final_len < str_len) {
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(str, result, str_len);
        str[final_len] = '\0';
    } else {
        /* Possible weaknesses found:
         * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
         */
        strcpy(str, result);
    }
}

int main() {
    char str[] = "a2b3c4d5e6";
    move_numbers(str, sizeof(str) - 1);
    printf("%s\n", str);
    return 0;
}