#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'AndroidTv', got androidTv
  *  test case 2 failed: expected 'AppleWatch', got appleWatch
  *  test case 1 failed: expected 'GooglePixel', got googlePixel
  */

char *snake_to_camel(const char *snake_str) {
    regex_t regex;
    regmatch_t matches[2];
    if (regcomp(&regex, "_([a-z])", REG_EXTENDED) != 0) {
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
    while (regexec(&regex, camel_str + offset, 2, matches, 0) == 0) {
        int match_pos = matches[1].rm_so + offset;
        char *tmp = camel_str + match_pos - 1;
        *tmp = toupper((unsigned char)*(tmp + 1));
        memmove(tmp + 1, tmp + 2, strlen(tmp + 2) + 1);
        offset = match_pos + 1;
    }

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