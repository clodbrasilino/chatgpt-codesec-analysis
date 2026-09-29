#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_LEN 11
#define MAX_OUTPUT_LEN 11

int convert_date_format(const char *input, char *output, size_t output_size) {
    regex_t regex;
    regmatch_t matches[4];
    const char *pattern = "^([0-9]{4})-([0-9]{2})-([0-9]{2})$";
    int ret;
    int result = -1;

    if (input == NULL || output == NULL || output_size < MAX_OUTPUT_LEN) {
        return -1;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }

    ret = regexec(&regex, input, 4, matches, 0);
    if (ret == 0) {
        size_t year_len = (size_t)(matches[1].rm_eo - matches[1].rm_so);
        size_t month_len = (size_t)(matches[2].rm_eo - matches[2].rm_so);
        size_t day_len = (size_t)(matches[3].rm_eo - matches[3].rm_so);

        if (year_len == 4 && month_len == 2 && day_len == 2) {
            char year[5];
            char month[3];
            char day[3];

            memcpy(year, input + matches[1].rm_so, year_len);
            year[4] = '\0';
            memcpy(month, input + matches[2].rm_so, month_len);
            month[2] = '\0';
            memcpy(day, input + matches[3].rm_so, day_len);
            day[2] = '\0';

            ret = snprintf(output, output_size, "%s-%s-%s", day, month, year);
            if (ret > 0 && (size_t)ret < output_size) {
                result = 0;
            }
        }
    }

    regfree(&regex);
    return result;
}

int main(void) {
    char input[MAX_INPUT_LEN];
    char output[MAX_OUTPUT_LEN];

    printf("Enter date (yyyy-mm-dd): ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    if (convert_date_format(input, output, sizeof(output)) == 0) {
        printf("Converted date: %s\n", output);
    } else {
        fprintf(stderr, "Invalid date format\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}