#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

char *snake_to_camel(const char *snake_str) {
    regex_t regex;
    if (regcomp(&regex, "_([a-z])", REG_EXTENDED | REG_NEWLINE) != 0) {
        return NULL;
    }

    int len = strlen(snake_str);
    char *camel_str = malloc(len + 1);
    if (!camel_str) {
        regfree(&regex);
        return NULL;
    }
    strcpy(camel_str, snake_str);

    int offset = 0;
    regmatch_t matches[2];
    while (regexec(&regex, camel_str + offset, 2, matches, 0) == 0) {
        int match_pos = matches[1].rm_so + offset;
        camel_str[match_pos] = toupper((unsigned char)camel_str[match_pos]);
        memmove(camel_str + match_pos, camel_str + match_pos + 1, strlen(camel_str + match_pos));
        offset = match_pos;
    }

    camel_str[0] = toupper((unsigned char)camel_str[0]);

    regfree(&regex);
    return camel_str;
}

int main() {
    const char *test_strings[] = {"android_tv", "google_pixel", "apple_watch"};
    for (size_t i = 0; i < 3; ++i) {
        char *camel_str = snake_to_camel(test_strings[i]);
        if (camel_str) {
            printf("%s\n", camel_str);
            free(camel_str);
        }
    }
    return 0;
}