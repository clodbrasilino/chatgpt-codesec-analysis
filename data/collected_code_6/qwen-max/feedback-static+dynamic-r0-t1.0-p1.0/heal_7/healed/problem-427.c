#include <stdio.h>
#include <regex.h>
#include <string.h>

char* convert_date_format(const char *input, char *output, size_t output_size) {
    regex_t regex;
    regmatch_t match[4];
    const char *pattern = "([0-9]{4})-([0-9]{2})-([0-9]{2})";

    if (regcomp(&regex, pattern, REG_EXTENDED)) {
        return NULL;
    }

    if (regexec(&regex, input, 4, match, 0) == 0) {
        int year_len = (int)(match[1].rm_eo - match[1].rm_so);
        int month_len = (int)(match[2].rm_eo - match[2].rm_so);
        int day_len = (int)(match[3].rm_eo - match[3].rm_so);

        size_t len = snprintf(NULL, 0, "%.*s-%.*s-%.*s",
                              year_len, input + match[1].rm_so,
                              month_len, input + match[2].rm_so,
                              day_len, input + match[3].rm_so);

        if (len >= output_size) {
            output[0] = '\0';
            regfree(&regex);
            return NULL;
        }

        snprintf(output, output_size, "%.*s-%.*s-%.*s",
                 year_len, input + match[1].rm_so,
                 month_len, input + match[2].rm_so,
                 day_len, input + match[3].rm_so);
    } else {
        output[0] = '\0';
    }

    regfree(&regex);
    return output;
}

int main() {
    const char input[] = "2023-10-05";
    char output[11];

    if (convert_date_format(input, output, sizeof(output))) {
        printf("%s\n", output);
    } else {
        printf("Conversion failed.\n");
    }

    return 0;
}