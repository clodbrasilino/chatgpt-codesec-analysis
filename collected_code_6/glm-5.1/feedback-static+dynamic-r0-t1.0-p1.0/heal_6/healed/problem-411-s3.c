#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *snake_to_camel(const char *snake_str) {
    if (snake_str == NULL) return NULL;

    size_t len = strlen(snake_str);

    char *camel_str = malloc(len + 1);
    if (camel_str == NULL) return NULL;

    size_t i = 0;
    size_t j = 0;

    while (j < len) {
        if (snake_str[j] == '_') {
            j++;
            if (j < len && islower((unsigned char)snake_str[j])) {
                camel_str[i++] = toupper((unsigned char)snake_str[j++]);
            } else {
                camel_str[i++] = '_';
            }
        } else {
            camel_str[i++] = snake_str[j++];
        }
    }
    camel_str[i] = '\0';

    return camel_str;
}

int main(void) {
    const char *tests[] = {"android_tv", "google_pixel", "apple_watch", "convert_this_snake_case_string", NULL};
    
    for (int i = 0; tests[i] != NULL; i++) {
        char *output = snake_to_camel(tests[i]);
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