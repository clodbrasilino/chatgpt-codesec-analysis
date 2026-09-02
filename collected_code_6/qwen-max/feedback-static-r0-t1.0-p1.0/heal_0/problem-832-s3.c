#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int extract_max_numeric_value(const char *input, long *result) {
    regex_t regex;
    regmatch_t matches[2];
    int match_count = 0, reti;
    long max_value = 0;

    if (regcomp(&regex, "(-?\\d+)", REG_EXTENDED | REG_NEWLINE) != 0) {
        return -1;
    }

    while ((reti = regexec(&regex, input + match_count, 2, matches, 0)) == 0) {
        char *number_str = &input[matches[1].rm_so + match_count];
        long number = atol(number_str);
        if (number > max_value) {
            max_value = number;
        }
        match_count += matches[0].rm_eo;
    }

    if (reti != REG_NOMATCH) {
        regfree(&regex);
        return -1;
    }

    *result = max_value;
    regfree(&regex);
    return 0;
}

int main() {
    const char *test_string = "abc-123 def 456 ghi 789 jkl";
    long max_value = 0;

    if (extract_max_numeric_value(test_string, &max_value) == 0) {
        printf("Max value: %ld\n", max_value);
    } else {
        printf("Failed to extract max value\n");
    }

    return 0;
}