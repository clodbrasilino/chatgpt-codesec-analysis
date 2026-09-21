#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char* snake_to_camel(const char *snake_str, size_t len) {
    char *result = (char *)malloc(len + 1);
    if (!result) return NULL;
    int i, j = 0;
    for (i = 0; i < len; i++) {
        if (snake_str[i] == '_') {
            i++;
            if (i < len) {
                result[j++] = toupper(snake_str[i]);
            }
        } else {
            result[j++] = snake_str[i];
        }
    }
    result[j] = '\0';
    return result;
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char snake_case_str[16] = "python_program";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(snake_case_str);
    char *camel_case_str = snake_to_camel(snake_case_str, len);
    printf("%s\n", camel_case_str);
    free(camel_case_str);

    /* Possible weaknesses found:
     *  Buffer is accessed out of bounds: snake_case_str [bufferAccessOutOfBounds]
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). Risk is low because the source is a constant string. (risk 2, buffer)
     */
    strcpy(snake_case_str, "program_language");
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(snake_case_str);
    camel_case_str = snake_to_camel(snake_case_str, len);
    printf("%s\n", camel_case_str);
    free(camel_case_str);

    snprintf(snake_case_str, sizeof(snake_case_str), "python_language");
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(snake_case_str);
    camel_case_str = snake_to_camel(snake_case_str, len);
    printf("%s\n", camel_case_str);
    free(camel_case_str);

    return 0;
}