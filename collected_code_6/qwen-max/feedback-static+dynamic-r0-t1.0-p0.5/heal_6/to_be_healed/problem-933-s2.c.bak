#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'google_assistant', got G_assistant
  *  test case 2 failed: expected 'quad_core', got Q_core
  *  test case 1 failed: expected 'chrome_cast', got C_cast
  */

char *camel_to_snake(const char *input) {
    regex_t regex;
    regmatch_t matches[2];
    char *output = strdup(input);
    int len = strlen(output);

    if (regcomp(&regex, "([a-z0-9])([A-Z])", REG_EXTENDED) != 0) {
        free(output);
        return NULL;
    }

    int new_len = len;
    for (int i = 0; i < len; i++) {
        if (regexec(&regex, output + i, 2, matches, 0) == 0) {
            memmove(output + i + 2, output + i + matches[1].rm_so + 1, len - (i + matches[1].rm_so + 1) + 1);
            output[i + 1] = '_';
            output[i + 2] = tolower(output[i + 2]);
            new_len++;
        } else {
            continue;
        }
        i += matches[1].rm_so;
    }

    regfree(&regex);
    char *temp = realloc(output, new_len + 1);
    if (temp == NULL) {
        free(output);
        return NULL;
    }
    output = temp;
    output[new_len] = '\0';
    return output;
}

int main() {
    const char *inputs[] = {"ThisIsCamelCase", "chrome_cast", "quad_core", "google_assistant"};
    for (size_t i = 0; i < 4; i++) {
        char *result = camel_to_snake(inputs[i]);
        if (result) {
            printf("%s\n", result);
            free(result);
        } else {
            printf("Error converting string.\n");
        }
    }
    return 0;
}