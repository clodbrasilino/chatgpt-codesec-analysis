#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'GooglePixel', got googlePixel
  *  test case 2 failed: expected 'AppleWatch', got appleWatch
  *  test case 0 failed: expected 'AndroidTv', got androidTv
  */

char *snake_to_camel(const char *snake_str) {
    regex_t regex;
    regmatch_t matches[2];
    char *camel_str = strdup(snake_str);
    int offset = 0;

    if (regcomp(&regex, "(_[a-z])", REG_EXTENDED | REG_NEWLINE) != 0) {
        free(camel_str);
        return NULL;
    }

    while (regexec(&regex, camel_str + offset, 2, matches, 0) == 0) {
        int i = matches[1].rm_so + offset;
        camel_str[i] = toupper((unsigned char)camel_str[i + 1]);
        memmove(camel_str + i + 1, camel_str + i + 2, strlen(camel_str + i + 2) + 1);
        offset = i + 1;
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
        printf("Error converting string.\n");
    }

    return 0;
}