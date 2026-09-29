#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

char *snake_to_camel(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = strlen(input);
    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t src_pos = 0;
    size_t dst_pos = 0;

    while (src_pos < len) {
        if (input[src_pos] == '_') {
            src_pos++;
            if (src_pos < len && isalpha((unsigned char)input[src_pos])) {
                result[dst_pos++] = toupper((unsigned char)input[src_pos]);
                src_pos++;
            }
        } else {
            result[dst_pos++] = input[src_pos];
            src_pos++;
        }
    }

    result[dst_pos] = '\0';
    return result;
}

int main(void) {
    const char *test_cases[] = {
        "hello_world",
        "snake_case_string",
        "convert_this_to_camel",
        "alreadycamel",
        "multiple__underscores",
        "_leading_underscore",
        "trailing_underscore_",
        "with_1_number",
        "android_tv",
        "google_pixel",
        "apple_watch",
        NULL
    };

    for (int i = 0; test_cases[i] != NULL; i++) {
        char *converted = snake_to_camel(test_cases[i]);
        if (converted != NULL) {
            printf("%s\n", converted);
            free(converted);
        } else {
            printf("%s -> (conversion failed)\n", test_cases[i]);
        }
    }

    return 0;
}