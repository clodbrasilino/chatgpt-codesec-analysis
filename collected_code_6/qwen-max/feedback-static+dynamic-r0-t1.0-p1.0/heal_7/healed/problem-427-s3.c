#include <stdio.h>
#include <regex.h>
#include <string.h>

int convert_date_format(const char *input, char *output, size_t output_size) {
    regex_t regex;
    regmatch_t matches[4];
    const char *pattern = "^([0-9]{4})-([0-9]{2})-([0-9]{2})$";

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return -1;
    }

    if (regexec(&regex, input, 4, matches, 0) != 0) {
        regfree(&regex);
        return -1;
    }

    size_t year_len = matches[1].rm_eo - matches[1].rm_so;
    size_t month_len = matches[2].rm_eo - matches[2].rm_so;
    size_t day_len = matches[3].rm_eo - matches[3].rm_so;

    if (year_len + month_len + day_len + 2 > output_size) {
        regfree(&regex);
        return -1;
    }

    snprintf(output, output_size, "%.*s/%.*s/%.*s",
             (int)day_len, &input[matches[3].rm_so],
             (int)month_len, &input[matches[2].rm_so],
             (int)year_len, &input[matches[1].rm_so]);
    
    regfree(&regex);
    return 0;
}

int main() {
    const char *input = "2023-10-05";
    char output[11];

    if (convert_date_format(input, output, sizeof(output)) == 0) {
        printf("%s\n", output);
    } else {
        fprintf(stderr, "Failed to convert the date format.\n");
        return 1;
    }
    return 0;
}