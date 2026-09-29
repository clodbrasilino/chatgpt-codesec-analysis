#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *camel_to_snake(const char *camel) {
    if (camel == NULL) return NULL;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(camel);
    char *snake = (char *)malloc(len * 2 + 1);
    if (snake == NULL) return NULL;

    snake[0] = '\0';
    for (size_t i = 0; i < len; ++i) {
        if (isupper(camel[i])) {
            if (i > 0 && camel[i-1] != '_') {
                /* Possible weaknesses found:
                 * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). Risk is low because the source is a constant character. (risk 1, buffer)
                 */
                strcat(snake, "_");
            }
            char lower = tolower(camel[i]);
            /* Possible weaknesses found:
             * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
             */
            strncat(snake, &lower, 1);
        } else {
            /* Possible weaknesses found:
             * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
             */
            strncat(snake, &camel[i], 1);
        }
    }

    return snake;
}

int main() {
    const char *camel = "ThisIsCamelCase";
    char *snake = camel_to_snake(camel);
    if (snake != NULL) {
        printf("%s\n", snake);
        free(snake);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }

    return 0;
}