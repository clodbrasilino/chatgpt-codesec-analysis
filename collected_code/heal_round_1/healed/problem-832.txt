#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>

int extract_max_numeric_value(const char* str) {
    regex_t regex;
    regmatch_t match;
    int status;

    status = regcomp(&regex, "[0-9]+", REG_EXTENDED);
    if (status != 0) {
        return -1;
    }

    status = regexec(&regex, str, 1, &match, 0);
    if (status == 0) {
        size_t length = match.rm_eo - match.rm_so;
        char* numeric_value = malloc((length + 1) * sizeof(char));
        if (numeric_value == NULL) {
            regfree(&regex);
            return -1;
        }
        memcpy(numeric_value, str + match.rm_so, length);
        numeric_value[length] = '\0';

        long max_value = strtol(numeric_value, NULL, 10);
        free(numeric_value);

        while (regexec(&regex, str + match.rm_eo, 1, &match, 0) == 0) {
            length = match.rm_eo - match.rm_so;
            numeric_value = malloc((length + 1) * sizeof(char));
            if (numeric_value == NULL) {
                regfree(&regex);
                return -1;
            }
            memcpy(numeric_value, str + match.rm_so, length);
            numeric_value[length] = '\0';

            long current_value = strtol(numeric_value, NULL, 10);
            free(numeric_value);
            if (current_value > max_value) {
                max_value = current_value;
            }
        }

        regfree(&regex);

        return (int)max_value;
    } else {
        regfree(&regex);
        return -1;
    }
}

int main() {
    const char str[] = "The maximum numeric value is 1000 and the minimum is 10.";
    int max_value = extract_max_numeric_value(str);
    printf("Maximum numeric value: %d\n", max_value);
    return 0;
}