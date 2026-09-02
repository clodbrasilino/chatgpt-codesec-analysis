#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>
#include <ctype.h>

char* camel_to_snake(const char *input) {
    regex_t regex;
    regmatch_t match[2];
    char *result, *temp;

    if (regcomp(&regex, "([a-z0-9])([A-Z])", REG_EXTENDED)) {
        return NULL;
    }

    result = strdup(input);
    if (!result) {
        return NULL;
    }

    int offset = 0;
    while (1) {
        int rc = regexec(&regex, result + offset, 2, match, 0);
        if (rc != 0) break;

        temp = malloc(strlen(result) + 2);
        if (!temp) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        strncpy(temp, result, match[0].rm_so + offset + 1);
        temp[match[0].rm_so + offset + 1] = '_';
        temp[match[0].rm_so + offset + 2] = tolower(*(result + match[0].rm_so + offset + 1));
        strcat(temp, result + match[0].rm_so + offset + 2);

        free(result);
        result = temp;
        offset += match[0].rm_so + 1;
    }

    regfree(&regex);
    return result;
}

int main() {
    const char *inputs[] = {"ThisIsCamelCaseString", "quadCore", "googleAssistant", "chromeCast"};
    for (size_t i = 0; i < sizeof(inputs) / sizeof(inputs[0]); ++i) {
        char *output = camel_to_snake(inputs[i]);
        if (output) {
            printf("%s\n", output);
            free(output);
        } else {
            printf("Conversion failed.\n");
        }
    }
    return 0;
}