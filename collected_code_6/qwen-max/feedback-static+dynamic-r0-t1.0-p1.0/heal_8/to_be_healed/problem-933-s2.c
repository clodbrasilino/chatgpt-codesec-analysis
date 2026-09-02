#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'google_assistant', got _oogl_assistant
  *  test case 1 failed: expected 'chrome_cast', got _hrom_cast
  *  test case 2 failed: expected 'quad_core', got _ua_core
  */

char *camel_to_snake(const char *str) {
    const int buffer_size = 256;
    char *snake_case = (char *)malloc(buffer_size * sizeof(char));
    if (!snake_case) {
        return NULL;
    }
    memset(snake_case, 0, buffer_size);

    regex_t regex;
    regmatch_t matches[4];
    if (regcomp(&regex, "([a-z0-9])([A-Z])|([A-Z][a-z])", REG_EXTENDED)) {
        free(snake_case);
        return NULL;
    }

    int pos = 0;
    int match_pos = 0;
    while (regexec(&regex, str + pos, 4, matches, 0) == 0) {
        int match_start = matches[0].rm_so;
        int match_end = matches[0].rm_eo;
        strncpy(snake_case + match_pos, str + pos, match_start);
        match_pos += match_start;

        if (matches[1].rm_so != -1) {
            snake_case[match_pos++] = '_';
            snake_case[match_pos++] = tolower(str[pos + match_start + 1]);
        } else if (matches[3].rm_so != -1) {
            snake_case[match_pos++] = '_';
            snake_case[match_pos++] = tolower(str[pos + match_start + 1]);
        }

        pos += match_end;
    }

    strcpy(snake_case + match_pos, str + pos);
    regfree(&regex);

    return snake_case;
}

int main() {
    const char *test_cases[] = {"chromeCast", "quadCore", "googleAssistant"};
    const char *expected[] = {"chrome_cast", "quad_core", "google_assistant"};

    for (int i = 0; i < 3; i++) {
        char *result = camel_to_snake(test_cases[i]);
        if (result) {
            printf("Expected: %s, Got: %s\n", expected[i], result);
            free(result);
        } else {
            printf("Conversion failed for: %s\n", test_cases[i]);
        }
    }

    return 0;
}