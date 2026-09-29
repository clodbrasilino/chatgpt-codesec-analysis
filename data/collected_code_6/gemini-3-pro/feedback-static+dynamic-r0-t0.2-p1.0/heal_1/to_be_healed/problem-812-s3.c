#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* abbreviate_road(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    const char* target = "road";
    const char* replacement = "rd.";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t target_len = strlen(target);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t replacement_len = strlen(replacement);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);

    size_t count = 0;
    const char* tmp = input;
    while ((tmp = strstr(tmp, target)) != NULL) {
        count++;
        tmp += target_len;
    }

    size_t new_len = input_len - (count * target_len) + (count * replacement_len);
    char* result = (char*)malloc(new_len + 1);
    if (result == NULL) {
        return NULL;
    }

    const char* current = input;
    char* dest = result;
    while ((tmp = strstr(current, target)) != NULL) {
        size_t len = tmp - current;
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(dest, current, len);
        dest += len;
        /* Possible weaknesses found:
         * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
         */
        strcpy(dest, replacement);
        dest += replacement_len;
        current = tmp + target_len;
    }
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(dest, current);

    return result;
}

int main(void) {
    const char* original = "The long road leads to another road.";
    char* abbreviated = abbreviate_road(original);

    if (abbreviated != NULL) {
        printf("Original: %s\n", original);
        printf("Abbreviated: %s\n", abbreviated);
        free(abbreviated);
    } else {
        fprintf(stderr, "Memory allocation failed or input was NULL.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}