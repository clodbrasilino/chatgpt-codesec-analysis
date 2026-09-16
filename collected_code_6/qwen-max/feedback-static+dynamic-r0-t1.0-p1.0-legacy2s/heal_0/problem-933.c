#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

char* camel_to_snake(const char *input) {
    regex_t regex;
    regmatch_t match[2];
    size_t output_len = 0;
    char *output, *result;
    int rc;

    if (regcomp(&regex, "([a-z0-9])([A-Z])", REG_EXTENDED)) {
        return NULL;
    }

    result = strdup(input);
    if (!result) {
        return NULL;
    }

    while (1) {
        rc = regexec(&regex, result, 2, match, 0);
        if (rc != 0) break;
        memmove(result + match[0].rm_eo + 1, result + match[0].rm_eo, strlen(result + match[0].rm_eo) + 1);
        *(result + match[0].rm_so + 1) = '_';
        *(result + match[0].rm_so + 2) = tolower(*(result + match[0].rm_eo));
    }

    regfree(&regex);
    return result;
}

int main() {
    const char *input = "ThisIsCamelCaseString";
    char *output = camel_to_snake(input);
    if (output) {
        printf("%s\n", output);
        free(output);
    } else {
        printf("Conversion failed.\n");
    }
    return 0;
}