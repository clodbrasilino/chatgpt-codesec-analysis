#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *snake_to_camel(const char *snake_str) {
    char *camel_str = strdup(snake_str);
    int i, j;

    if (camel_str == NULL) {
        return NULL;
    }

    for (i = 0, j = 0; i < strlen(camel_str); ++i, ++j) {
        if (camel_str[i] == '_') {
            if (i + 1 < strlen(camel_str)) {
                camel_str[j] = toupper(camel_str[i + 1]);
                ++i;
            }
        } else {
            if (i == 0 && islower(camel_str[j])) {
                camel_str[j] = toupper(camel_str[j]);
            } else {
                camel_str[j] = camel_str[i];
            }
        }
    }
    camel_str[j] = '\0';

    return camel_str;
}

int main() {
    const char *test_cases[] = {"google_pixel", "android_tv", "apple_watch", "this_is_a_snake_case_string"};
    for (int k = 0; k < 4; ++k) {
        char *camel_str = snake_to_camel(test_cases[k]);

        if (camel_str != NULL) {
            printf("%s\n", camel_str);
            free(camel_str);
        } else {
            printf("Error converting string.\n");
        }
    }

    return 0;
}