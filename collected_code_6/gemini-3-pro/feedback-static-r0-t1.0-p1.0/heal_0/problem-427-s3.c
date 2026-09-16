#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int convert_date_format(const char *input, char *output, size_t out_size) {
    if (input == NULL || output == NULL || out_size < 11) {
        return -1;
    }

    regex_t regex;
    int reg_status = regcomp(&regex, "^([0-9]{4})-([0-9]{2})-([0-9]{2})$", REG_EXTENDED);
    if (reg_status != 0) {
        return -1;
    }

    regmatch_t matches[4];
    reg_status = regexec(&regex, input, 4, matches, 0);
    if (reg_status != 0) {
        regfree(&regex);
        return -1;
    }

    int year_len = matches[1].rm_eo - matches[1].rm_so;
    int month_len = matches[2].rm_eo - matches[2].rm_so;
    int day_len = matches[3].rm_eo - matches[3].rm_so;

    if (year_len != 4 || month_len != 2 || day_len != 2) {
        regfree(&regex);
        return -1;
    }

    int written = snprintf(output, out_size, "%.*s-%.*s-%.*s",
                           day_len, input + matches[3].rm_so,
                           month_len, input + matches[2].rm_so,
                           year_len, input + matches[1].rm_so);

    regfree(&regex);

    if (written < 0 || (size_t)written >= out_size) {
        return -1;
    }

    return 0;
}

int main(void) {
    const char *original_date = "2023-10-25";
    char converted_date[11];

    if (convert_date_format(original_date, converted_date, sizeof(converted_date)) == 0) {
        printf("%s\n", converted_date);
    } else {
        fprintf(stderr, "Date conversion failed.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}