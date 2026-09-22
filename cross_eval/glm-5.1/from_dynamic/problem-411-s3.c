#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *snake_to_camel(const char *snake_str) {
    size_t len = strlen(snake_str);
    char *camel_str = malloc(len + 1);
    if (camel_str == NULL) {
        return NULL;
    }

    size_t i = 0;
    for (size_t j = 0; j < len; j++) {
        if (j == 0) {
            camel_str[i++] = toupper((unsigned char)snake_str[j]);
        } else if (snake_str[j] == '_') {
            j++;
            if (j < len) {
                camel_str[i++] = toupper((unsigned char)snake_str[j]);
            }
        } else {
            camel_str[i++] = snake_str[j];
        }
    }
    camel_str[i] = '\0';

    return camel_str;
}

int main(void) {
    const char *test_cases[] = {
        "android_tv",
        "google_pixel",
        "apple_watch",
        "convert_this_snake_case_string",
        NULL
    };

    for (int i = 0; test_cases[i] != NULL; i++) {
        char *output = snake_to_camel(test_cases[i]);
        if (output != NULL) {
            printf("%s\n", output);
            free(output);
        } else {
            fprintf(stderr, "Conversion failed\n");
            return 1;
        }
    }

    return 0;
}