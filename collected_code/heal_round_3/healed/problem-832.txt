#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int extract_max_numeric_value(const char* str) {
    regex_t regex;
    regmatch_t match;
    int status;
    long max_value = 0, current_value;

    status = regcomp(&regex, "[0-9]+", REG_EXTENDED);
    if (status != 0) {
        return INT_MIN;
    }

    const char *curr = str;

    while (regexec(&regex, curr, 1, &match, 0) == 0) {
        size_t length = match.rm_eo - match.rm_so;
        char* numeric_value = (char*)calloc(length + 1, sizeof(char));

        if (numeric_value == NULL) {
            regfree(&regex);
            return INT_MIN;
        }

        memmove(numeric_value, curr + match.rm_so, length);
        numeric_value[length] = '\0';

        current_value = strtol(numeric_value, NULL, 10);
        free(numeric_value);

        if (current_value > max_value) {
            max_value = current_value;
        }

        curr += match.rm_eo;
    }

    regfree(&regex);

    return (int)max_value;
}

int main() {
    const char str[] = "The maximum numeric value is 1000 and the minimum is 10.";
    int max_value = extract_max_numeric_value(str);
    printf("Maximum numeric value: %d\n", max_value);
    return 0;
}