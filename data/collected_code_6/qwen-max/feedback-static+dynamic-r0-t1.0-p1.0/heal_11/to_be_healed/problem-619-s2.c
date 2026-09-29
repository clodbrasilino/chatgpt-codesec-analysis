#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void move_numbers(char *str, size_t str_len) {
    char *result = malloc(str_len + 1);
    if (result == NULL) return;
    char *temp = malloc(str_len + 1);
    if (temp == NULL) {
        free(result);
        return;
    }
    int j = 0, k = 0;

    for (size_t i = 0; i < str_len; i++) {
        if (isdigit((unsigned char)str[i]) && j < str_len) {
            result[j++] = str[i];
        } else if (k < str_len) {
            temp[k++] = str[i];
        }
    }

    temp[k] = '\0';
    result[j] = '\0';

    if (j + k + 1 <= str_len) {
        /* Possible weaknesses found:
         * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
         */
        strncat(result, temp, str_len - j + 1);
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t final_len = strlen(result);
    if (final_len < str_len) {
        memmove(str, result, final_len + 1);
    } else {
        snprintf(str, str_len + 1, "%.*s", (int)str_len, result);
    }

    free(result);
    free(temp);
}

int main() {
    char str[] = "a2b3c4d5e6";
    move_numbers(str, sizeof(str) - 1);
    printf("%s\n", str);
    return 0;
}