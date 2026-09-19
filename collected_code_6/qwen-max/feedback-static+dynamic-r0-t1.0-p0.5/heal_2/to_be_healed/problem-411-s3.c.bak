#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'AndroidTv', got avvvvvvVvv
  *  test case 1 failed: expected 'GooglePixel', got giiiiiIiixel
  *  test case 2 failed: expected 'AppleWatch', got aaaaaAaatch
  */

char *snake_to_camel(const char *snake_str) {
    regex_t regex;
    regmatch_t matches[2];
    char *camel_str = strdup(snake_str);
    int len = strlen(camel_str);
    int i, j;

    if (regcomp(&regex, "(_[a-z])", REG_EXTENDED | REG_NEWLINE) != 0) {
        free(camel_str);
        return NULL;
    }

    for (i = 0; i < len; ) {
        if (regexec(&regex, camel_str + i, 2, matches, 0) == 0) {
            for (j = matches[0].rm_eo - 1; j > i; --j) {
                camel_str[j] = camel_str[j + 1];
            }
            camel_str[matches[1].rm_so] = toupper(camel_str[matches[1].rm_so]);
            len -= 1;
        } else {
            break;
        }
    }

    regfree(&regex);
    return camel_str;
}

int main() {
    const char *snake_str = "this_is_a_snake_case_string";
    char *camel_str = snake_to_camel(snake_str);

    if (camel_str) {
        printf("%s\n", camel_str);
        free(camel_str);
    } else {
        fprintf(stderr, "Failed to convert the string.\n");
    }

    return 0;
}