#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char* snake_to_camel(char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int i, len = strlen(str);
    char *result = malloc((len + 1) * sizeof(char));
    if (result == NULL) return NULL;

    /* Possible weaknesses found:
     *  Value stored to 'i' is never read [deadcode.DeadStores]
     */
    for (i = 0, result[0] = '\0'; *str; str++) {
        if (*str == '_') {
            str++;
            if (*str) {
                /* Possible weaknesses found:
                 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
                 */
                char temp[2];
                temp[0] = toupper(*str);
                temp[1] = '\0';
                /* Possible weaknesses found:
                 * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
                 */
                strcat(result, temp);
            }
        } else {
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char temp[2];
            temp[0] = *str;
            temp[1] = '\0';
            /* Possible weaknesses found:
             * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
             */
            strcat(result, temp);
        }
    }
    return result;
}

int main() {
    char input[] = "this_is_snake_case";
    char *output = snake_to_camel(input);

    if (output != NULL) {
        printf("Camel case: %s\n", output);
        free(output);
    } else {
        printf("Memory allocation failed.\n");
    }

    return 0;
}