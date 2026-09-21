#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

char *camel_to_snake(const char *input) {
    regex_t regex;
    regmatch_t matches[2];
    size_t input_len = strlen(input);
    char *output = (char *)malloc(input_len * 2 + 1);
    if (output == NULL) {
        return NULL;
    }
    strcpy(output, input);

    if (regcomp(&regex, "([a-z0-9])([A-Z])", REG_EXTENDED) != 0) {
        free(output);
        return NULL;
    }

    int offset = 0;
    for (int i = 0; i < input_len; i++) {
        if (regexec(&regex, output + i, 2, matches, 0) == 0) {
            memmove(output + i + 1 + offset, output + i + 1, input_len - (i + 1 - offset) + 1);
            output[i + offset] = '_';
            output[i + offset + 1] = tolower((unsigned char)output[i + offset + 1]);
            offset++;
        }
    }

    regfree(&regex);
    return output;
}

int main() {
    const char *inputs[] = {"ThisIsCamelCase", "google_assistant", "chrome_cast", "quad_core"};
    for (size_t i = 0; i < 4; ++i) {
        char *result = camel_to_snake(inputs[i]);
        if (result) {
            printf("%s -> %s\n", inputs[i], result);
            free(result);
        } else {
            printf("Error converting string '%s'.\n", inputs[i]);
        }
    }
    return 0;
}