#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *snake_to_camel(const char *input)
{
    char *result;
    size_t len;
    size_t ri;
    size_t i;
    int upper;

    if (input == NULL) {
        return NULL;
    }

    len = strlen(input);
    result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    ri = 0;
    upper = 1;
    for (i = 0; i < len; i++) {
        unsigned char c = (unsigned char)input[i];
        if (c == '_') {
            upper = 1;
            continue;
        }
        if (upper) {
            result[ri++] = (char)toupper(c);
            upper = 0;
        } else {
            result[ri++] = (char)c;
        }
    }
    result[ri] = '\0';

    printf("%s\n", result);
    fflush(stdout);

    return result;
}

int main(void)
{
    const char *tests[] = {
        "android_tv",
        "google_pixel",
        "apple_watch",
        "convert_this_snake_case_string",
        "hello_world_example",
        "another_test_case",
        "nounderscores",
        ""
    };
    size_t count = sizeof(tests) / sizeof(tests[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        char *camel = snake_to_camel(tests[i]);
        if (camel == NULL) {
            fprintf(stderr, "Conversion failed for input: %s\n", tests[i]);
            return EXIT_FAILURE;
        }
        free(camel);
    }

    return EXIT_SUCCESS;
}