#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Possible weaknesses found:
 *  Parameter 'tuple' can be declared as pointer to const [constParameterPointer]
 */
char* tuple_to_string(int *tuple, size_t len) {
    if (len == 0) return NULL;
    size_t string_length = len * 2 - 1; // spaces between numbers and null terminator
    char *result = (char *)malloc(string_length + 1);
    if (result == NULL) return NULL;

    for (size_t i = 0; i < len; ++i) {
        if (i != 0) {
            /* Possible weaknesses found:
             * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). Risk is low because the source is a constant character. (risk 1, buffer)
             */
            strcat(result, " ");
        }
        /* Possible weaknesses found:
         * Flawfinder sprintf: Does not check for buffer overflows (CWE-120). Use sprintf_s, snprintf, or vsnprintf. Risk is low because the source has a constant maximum length. (risk 2, buffer)
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        sprintf(result + strlen(result), "%d", tuple[i]);
    }
    return result;
}

int main() {
    int tuple[] = {1, 2, 3, 4};
    size_t len = sizeof(tuple) / sizeof(tuple[0]);

    char *str = tuple_to_string(tuple, len);
    if (str != NULL) {
        printf("%s\n", str);
        free(str);
    } else {
        printf("Conversion failed.\n");
    }

    return 0;
}