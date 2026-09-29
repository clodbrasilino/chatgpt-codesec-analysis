#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* snake_to_camel(char *snake_str) {
    char *p = snake_str;
    int capitalize_next = 1;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(snake_str);
    char *end = snake_str + len;

    while (p < end) {
        if (capitalize_next && islower((unsigned char)*p)) {
            *p = toupper((unsigned char)*p);
            capitalize_next = 0;
        } else if (*p == '_') {
            memmove(p, p + 1, end - p);
            --end;
            capitalize_next = 1;
            --p; // Adjust pointer to reprocess the newly capitalized character
        } else {
            capitalize_next = 0;
        }
        p++;
    }

    return snake_str;
}

int main() {
    char snake_case[] = "this_is_a_snake_case_string";
    printf("%s\n", snake_to_camel(snake_case));

    char test_case_0[] = "python_program";
    printf("%s\n", snake_to_camel(test_case_0));

    char test_case_1[] = "python_language";
    printf("%s\n", snake_to_camel(test_case_1));

    char test_case_2[] = "programming_language";
    printf("%s\n", snake_to_camel(test_case_2));

    return 0;
}