#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Possible weaknesses found:
 *  Parameter 'digits' can be declared as pointer to const [constParameterPointer]
 */
char* largestNumber(int *digits, int size) {
    char **str_digits = (char **)malloc(size * sizeof(char *));
    for (int i = 0; i < size; ++i) {
        str_digits[i] = (char *)malloc(2 * sizeof(char));
        /* Possible weaknesses found:
         * Flawfinder sprintf: Does not check for buffer overflows (CWE-120). Use sprintf_s, snprintf, or vsnprintf. Risk is low because the source has a constant maximum length. (risk 2, buffer)
         */
        sprintf(str_digits[i], "%d", digits[i]);
    }

    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - 1 - i; ++j) {
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char temp[10];
            /* Possible weaknesses found:
             *  too few arguments to function call, expected 2, have 1
             * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
             *  too few arguments to function 'strcmp'; expected 2, have 1
             *  Uninitialized variable: temp [uninitvar]
             */
            if (strcmp(strcat(strcat(temp, str_digits[j]), str_digits[j + 1])) <= strcmp(strcat(strcat(temp, str_digits[j + 1]), str_digits[j]))) {
                char *t = str_digits[j];
                str_digits[j] = str_digits[j + 1];
                str_digits[j + 1] = t;
            }
        }
    }

    char *result = (char *)malloc((size * 2 + 1) * sizeof(char));
    result[0] = '\0';
    for (int i = 0; i < size; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
         */
        strcat(result, str_digits[i]);
        free(str_digits[i]);
    }
    free(str_digits);

    return result;
}

int main() {
    int digits[] = {3, 30, 34, 5, 9};
    int size = 5;
    char *result = largestNumber(digits, size);
    printf("%s\n", result);
    free(result);
    return 0;
}