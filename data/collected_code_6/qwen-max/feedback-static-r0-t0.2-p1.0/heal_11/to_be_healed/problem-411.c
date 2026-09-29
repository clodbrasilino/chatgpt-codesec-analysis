#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

char *snake_to_camel(const char *snake_str) {
    if (!snake_str) return NULL;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(snake_str);
    char *camel_str = (char *)malloc(len + 1);
    if (!camel_str) return NULL;
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(camel_str, snake_str);

    regex_t regex;
    regmatch_t matches[2];
    if (regcomp(&regex, "_([a-z])", REG_EXTENDED | REG_NEWLINE) != 0) {
        free(camel_str);
        return NULL;
    }

    for (size_t i = 0; i < len; ) {
        if (regexec(&regex, camel_str + i, 2, matches, 0) == 0) {
            for (size_t j = i + matches[1].rm_so; j < len; ++j) {
                camel_str[j] = camel_str[j + 1];
            }
            camel_str[i + matches[1].rm_so - 1] = toupper((unsigned char)camel_str[i + matches[1].rm_so - 1]);
            --len;
            i += matches[1].rm_so;
        } else {
            i++;
        }
    }

    regfree(&regex);
    camel_str[len] = '\0';
    return camel_str;
}

int main() {
    const char *snake_str = "this_is_a_snake_case_string";
    char *camel_str = snake_to_camel(snake_str);
    if (camel_str) {
        printf("Camel case: %s\n", camel_str);
        free(camel_str);
    } else {
        printf("Failed to convert to camel case.\n");
    }
    return 0;
}