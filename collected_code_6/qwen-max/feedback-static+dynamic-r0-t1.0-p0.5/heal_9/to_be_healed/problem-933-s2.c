#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'chrome_cast', got <no output>
  *  test case 2 failed: expected 'quad_core', got <no output>
  *  test case 0 failed: expected 'google_assistant', got <no output>
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

    int offset = 0;
    for (int i = 0; i + offset < len; i++) {
        if (regexec(&regex, output + i + offset, 2, matches, 0) == 0) {
            memmove(output + i + 1 + offset + 1, output + i + 1 + offset + matches[1].rm_so, len - (i + 1 + offset + matches[1].rm_so) + 1);
            output[i + offset] = '_';
            output[i + 1 + offset] = tolower(output[i + 1 + offset]);
            offset++;
            i--;
        }
    }

    regfree(&regex);
    char *temp = realloc(output, len + offset + 1);
    if (temp == NULL) {
        free(output);
        return NULL;
    }
    output = temp;
    output[len + offset] = '\0';
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