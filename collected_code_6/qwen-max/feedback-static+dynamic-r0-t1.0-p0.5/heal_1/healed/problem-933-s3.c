#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

char *camel_to_snake(const char *input) {
    regex_t regex;
    regmatch_t matches[2];
    char *output = strdup(input);
    int offset = 0;

    if (regcomp(&regex, "([a-z])([A-Z])", REG_EXTENDED) != 0) {
        free(output);
        return NULL;
    }

    while (regexec(&regex, output + offset, 2, matches, 0) == 0) {
        memmove(output + matches[0].rm_eo + 1 + offset, output + matches[0].rm_eo + offset, strlen(output + matches[0].rm_eo + offset) + 1);
        output[matches[0].rm_so + offset] = '_';
        output[matches[0].rm_so + 1 + offset] = tolower(output[matches[0].rm_so + 1 + offset]);
        offset += 1;
    }

    regfree(&regex);
    return output;
}

int main() {
    const char *input = "ThisIsCamelCase";
    char *result = camel_to_snake(input);

    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    } else {
        fprintf(stderr, "Error converting string.\n");
    }

    return 0;
}