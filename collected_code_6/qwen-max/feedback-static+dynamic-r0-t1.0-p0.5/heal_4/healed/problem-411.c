#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

char *snake_to_camel(const char *snake_str) {
    regex_t regex;
    regmatch_t matches[2];
    size_t len = strlen(snake_str);
    char *camel_str = (char *)malloc(len + 1);
    if (!camel_str) return NULL;
    strcpy(camel_str, snake_str);

    if (regcomp(&regex, "(_[a-z])", REG_EXTENDED | REG_NEWLINE) != 0) {
        free(camel_str);
        return NULL;
    }

    for (int i = 0; regexec(&regex, camel_str + i, 2, matches, 0) == 0; i += matches[0].rm_eo - 1) {
        int len = matches[0].rm_eo - matches[1].rm_so - 1;
        camel_str[matches[1].rm_so] = toupper((unsigned char)camel_str[matches[1].rm_so + 1]);
        memmove(camel_str + matches[1].rm_so + 1, camel_str + matches[1].rm_so + 2, len + 1);
    }

    regfree(&regex);
    return camel_str;
}

int main() {
    const char *snake_str[] = {"android_tv", "google_pixel", "apple_watch", "this_is_a_snake_case_string"};
    for (int j = 0; j < 4; j++) {
        char *camel_str = snake_to_camel(snake_str[j]);
        if (camel_str) {
            printf("%s\n", camel_str);
            free(camel_str);
        } else {
            printf("Error converting string.\n");
        }
    }
    return 0;
}