#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <ctype.h>
#include <string.h>

char *snake_to_camel(const char *snake_str) {
    regex_t regex;
    regmatch_t matches[2];
    size_t len = strnlen(snake_str, 1024);
    char *camel_str = (char *)malloc(len + 1);
    if (!camel_str) return NULL;

    strncpy(camel_str, snake_str, len + 1);

    if (regcomp(&regex, "(_[a-z])", REG_EXTENDED | REG_NEWLINE) != 0) {
        free(camel_str);
        return NULL;
    }

    for (size_t i = 0; i < len; ) {
        if (regexec(&regex, camel_str + i, 2, matches, 0) == 0) {
            for (size_t j = matches[0].rm_eo - 1; j > i; --j) {
                camel_str[j] = camel_str[j + 1];
            }
            camel_str[matches[1].rm_so] = toupper((unsigned char)camel_str[matches[1].rm_so]);
            len -= 1;
        } else {
            break;
        }
    }

    regfree(&regex);
    return camel_str;
}

int main() {
    const char *test_cases[] = {"android_tv", "apple_watch", "google_pixel"};
    for (int i = 0; i < 3; ++i) {
        char *camel_str = snake_to_camel(test_cases[i]);
        if (camel_str) {
            printf("%s\n", camel_str);
            free(camel_str);
        } else {
            fprintf(stderr, "Failed to convert the string.\n");
        }
    }
    return 0;
}