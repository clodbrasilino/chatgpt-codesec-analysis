#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'quad_core', got Qua_dCoe
  *  test case 0 failed: expected 'google_assistant', got Googl_eAsistant
  *  test case 1 failed: expected 'chrome_cast', got Chrom_eCat
  */

char* camel_to_snake(const char *camel) {
    regex_t regex;
    regmatch_t matches[2];
    char *snake, *p, *result;

    if (regcomp(&regex, "([a-z0-9])([A-Z])", REG_EXTENDED | REG_NEWLINE) != 0) {
        return NULL;
    }

    int len = strlen(camel);
    snake = malloc((len * 2 + 1) * sizeof(char));
    if (snake == NULL) {
        regfree(&regex);
        return NULL;
    }
    strcpy(snake, camel);

    p = snake;
    while (regexec(&regex, p, 2, matches, 0) == 0) {
        int match_len = matches[0].rm_eo - matches[0].rm_so;
        memmove(p + matches[0].rm_so + 1, p + matches[0].rm_so, match_len + 1);
        p[matches[0].rm_so] = '_';
        p += matches[0].rm_so + 2;
    }

    result = realloc(snake, strlen(snake) + 1);
    if (result == NULL) {
        free(snake);
        regfree(&regex);
        return NULL;
    }

    regfree(&regex);
    return result;
}

int main() {
    const char *test_cases[] = {"ThisIsCamelCase", "googleAssistant", "chromeCast", "quadCore"};
    const char *expected_results[] = {"this_is_camel_case", "google_assistant", "chrome_cast", "quad_core"};
    for (int i = 0; i < 4; i++) {
        char *snake = camel_to_snake(test_cases[i]);
        if (snake != NULL) {
            printf("%s\n", snake);
            free(snake);
        } else {
            printf("Error converting to snake case.\n");
        }
    }
    return 0;
}