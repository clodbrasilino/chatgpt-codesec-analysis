#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *snake_to_camel(const char *input)
{
    if (input == NULL)
        return NULL;

    size_t len = 0;
    for (const char *p = input; *p; ++p) {
        if (*p != '_') ++len;
    }
    if (len == 0) {
        char *empty = malloc(1);
        if (empty) empty[0] = '\0';
        return empty;
    }
    char *output = malloc(len + 1);
    if (!output)
        return NULL;

    int capitalize = 1;
    size_t pos = 0;
    for (const char *p = input; *p; ++p) {
        if (*p == '_') {
            capitalize = 1;
        } else {
            unsigned char c = (unsigned char)*p;
            if (capitalize) {
                output[pos++] = (char)toupper(c);
                capitalize = 0;
            } else {
                output[pos++] = (char)tolower(c);
            }
        }
    }
    output[pos] = '\0';
    return output;
}

int main(void)
{
    const char *tests[] = {
        "android_tv",
        "google_pixel",
        "apple_watch",
        NULL
    };
    for (int i = 0; tests[i]; ++i) {
        char *result = snake_to_camel(tests[i]);
        if (result) {
            printf("%s\n", result);
            free(result);
        } else {
            printf("(null)\n");
        }
    }
    return 0;
}