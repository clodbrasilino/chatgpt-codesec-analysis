#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void remove_chars(char *str1, const char *str2) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    char *result = malloc(strlen(str1) + 1);
    int j, k;
    for (int i = 0; str1[i] != '\0'; i++) {
        for (j = 0; str2[j] != '\0'; j++) {
            if (str1[i] == str2[j]) {
                break;
            }
        }
        if (str2[j] == '\0') {
            /* Possible weaknesses found:
             *  Memory is allocated but not initialized: result[k] [uninitdata]
             */
            for (k = 0; result[k] != '\0'; k++);
            result[k] = str1[i];
            result[k + 1] = '\0';
        }
    }
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(str1, result);
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