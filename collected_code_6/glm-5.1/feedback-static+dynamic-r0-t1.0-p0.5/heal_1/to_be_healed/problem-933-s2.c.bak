#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'google_assistant', got Google_assistant
  *  test case 2 failed: expected 'quad_core', got Quad_core
  *  test case 1 failed: expected 'chrome_cast', got Chrome_cast
  */

char *camel_to_snake(const char *camel_str) {
    if (camel_str == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "([a-z0-9])([A-Z])", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t max_len = strlen(camel_str) * 2 + 1;
    char *temp1 = malloc(max_len);
    char *temp2 = malloc(max_len);
    if (temp1 == NULL || temp2 == NULL) {
        free(temp1);
        free(temp2);
        regfree(&regex);
        return NULL;
    }

    strncpy(temp1, camel_str, max_len - 1);
    temp1[max_len - 1] = '\0';

    regmatch_t matches[3];
    while (regexec(&regex, temp1, 3, matches, 0) == 0) {
        /* Possible weaknesses found:
         *  Value stored to 'prefix_len' during its initialization is never read [deadcode.DeadStores]
         *  Variable 'prefix_len' is assigned a value that is never used. [unreadVariable]
         */
        size_t prefix_len = matches[2].rm_so;
        size_t match1_start = matches[1].rm_so;
        size_t match1_end = matches[1].rm_eo;
        size_t match2_start = matches[2].rm_so;
        size_t match2_end = matches[2].rm_eo;

        memcpy(temp2, temp1, match1_start);
        temp2[match1_start] = temp1[match1_start];
        temp2[match1_end] = '_';
        temp2[match1_end + 1] = temp1[match2_start] + 32;
        
        size_t remaining_len = strlen(temp1 + match2_end);
        memcpy(temp2 + match1_end + 2, temp1 + match2_end, remaining_len);
        temp2[match1_end + 2 + remaining_len] = '\0';

        char *swap = temp1;
        temp1 = temp2;
        temp2 = swap;
    }

    regfree(&regex);
    free(temp2);

    char *result = malloc(strlen(temp1) + 1);
    if (result == NULL) {
        free(temp1);
        return NULL;
    }
    strcpy(result, temp1);
    free(temp1);

    return result;
}

int main(void) {
    const char *inputs[] = {
        "camelCase",
        "thisIsATest",
        "convertCamelCaseToSnakeCase",
        "already_snake",
        "simple",
        "aB",
        NULL
    };

    for (int i = 0; inputs[i] != NULL; i++) {
        char *snake = camel_to_snake(inputs[i]);
        if (snake != NULL) {
            printf("%s -> %s\n", inputs[i], snake);
            free(snake);
        } else {
            printf("%s -> (conversion failed)\n", inputs[i]);
        }
    }

    return 0;
}