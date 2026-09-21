#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* snake_to_camel(const char* snake_str) {
    if (snake_str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(snake_str);
    if (len == 0) {
        char* empty_str = (char*)malloc(1);
        if (empty_str == NULL) {
            return NULL;
        }
        empty_str[0] = '\0';
        return empty_str;
    }

    char* camel_str = (char*)malloc(len + 1);
    if (camel_str == NULL) {
        return NULL;
    }

    size_t j = 0;
    int capitalize_next = 1; 

    for (size_t i = 0; i < len; ++i) {
        if (snake_str[i] == '_') {
            capitalize_next = 1;
        } else {
            if (capitalize_next) {
                camel_str[j++] = toupper((unsigned char)snake_str[i]);
                capitalize_next = 0;
            } else {
                camel_str[j++] = tolower((unsigned char)snake_str[i]);
            }
        }
    }
    camel_str[j] = '\0';

    return camel_str;
}

int main(void) {
    const char* test_strings[] = {
        "hello_world",
        "this_is_a_test",
        "alreadyCamel",
        "trailing_underscore_",
        "_leading_underscore",
        "",
        NULL
    };

    for (size_t i = 0; i < sizeof(test_strings) / sizeof(test_strings[0]); ++i) {
        if (test_strings[i] == NULL) {
            break;
        }
        char* result = snake_to_camel(test_strings[i]);
        if (result != NULL) {
            printf("%s -> %s\n", test_strings[i], result);
            free(result);
        } else {
            fprintf(stderr, "Memory allocation failed for: %s\n", test_strings[i]);
        }
    }

    return 0;
}