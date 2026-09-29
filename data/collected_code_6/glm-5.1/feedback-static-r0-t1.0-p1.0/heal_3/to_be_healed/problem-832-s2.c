#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <limits.h>

long extract_max_numeric_value(const char *str) {
    regex_t regex;
    regmatch_t pmatch[1];
    long max_val = LONG_MIN;
    const char *cursor = str;

    if (regcomp(&regex, "[0-9]+", REG_EXTENDED) != 0) {
        return -1;
    }

    while (regexec(&regex, cursor, 1, pmatch, 0) == 0) {
        if (pmatch[0].rm_so == -1) {
            break;
        }

        long len = pmatch[0].rm_eo - pmatch[0].rm_so;
        char *buffer = malloc(len + 1);
        if (buffer == NULL) {
            regfree(&regex);
            return -1;
        }

        for (long i = 0; i < len; i++) {
            buffer[i] = cursor[pmatch[0].rm_so + i];
        }
        buffer[len] = '\0';

        long current_val = strtol(buffer, NULL, 10);
        free(buffer);

        if (current_val > max_val) {
            max_val = current_val;
        }

        cursor += pmatch[0].rm_eo;
    }

    regfree(&regex);
    return max_val;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    long result = extract_max_numeric_value(argv[1]);
    if (result == LONG_MIN) {
        printf("No numeric values found or error occurred.\n");
    } else {
        printf("Maximum numeric value: %ld\n", result);
    }

    return 0;
}