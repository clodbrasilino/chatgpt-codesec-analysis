#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char* snake_to_camel(char *snake_str) {
    char *p = snake_str;
    int capitalize_next = 1;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    char *output = (char *)malloc(strlen(snake_str) + 1);
    if (output == NULL) {
        return NULL;
    }
    int index = 0;

    while (*p) {
        if (*p == '_') {
            p++;
            capitalize_next = 1;
            continue;
        }
        if (capitalize_next && isalpha(*p)) {
            output[index] = toupper(*p);
            capitalize_next = 0;
        } else {
            output[index] = *p;
        }
        index++;
        p++;
    }
    output[index] = '\0';
    return output;
}

int main() {
    char snake_case[] = "this_is_a_snake_case_string";
    char *camel_case = snake_to_camel(snake_case);

    if (camel_case != NULL) {
        printf("%s\n", camel_case);
        free(camel_case);
    }

    return 0;
}