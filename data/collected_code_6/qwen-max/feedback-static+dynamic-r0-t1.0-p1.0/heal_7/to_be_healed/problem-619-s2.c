#include <stdio.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

void move_numbers(char *str, size_t str_len) {
    /* Possible weaknesses found:
     *  call to undeclared library function 'malloc' with type 'void *(unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  include the header <stdlib.h> or explicitly provide a declaration for 'malloc'
     */
    char *result = malloc(str_len + 1);
    if (result == NULL) return;
    char *temp = malloc(str_len + 1);
    if (temp == NULL) {
        /* Possible weaknesses found:
         *  include '<stdlib.h>' or provide a declaration of 'free'
         *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
         *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
         */
        free(result);
        return;
    }
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

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t temp_len = strlen(temp);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t result_len = strlen(result);

    if (result_len + temp_len + 1 <= str_len) {
        /* Possible weaknesses found:
         * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
         */
        strncat(result, temp, str_len - result_len - 1);
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t final_len = strlen(result);
    if (final_len < str_len) {
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(str, result, str_len);
        str[final_len] = '\0';
    } else {
        snprintf(str, str_len + 1, "%s", result);
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