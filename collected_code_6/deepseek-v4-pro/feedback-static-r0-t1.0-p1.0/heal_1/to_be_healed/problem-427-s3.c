#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int convert_date_format(const char *input, char *output, size_t output_size) {
    regex_t regex;
    regmatch_t matches[4];
    const char *pattern = "^([0-9]{4})-([0-9]{2})-([0-9]{2})$";
    int ret;
    size_t len;

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        return -1;
    }

    ret = regexec(&regex, input, 4, matches, 0);
    if (ret == REG_NOMATCH) {
        regfree(&regex);
        return -2;
    }
    if (ret != 0) {
        regfree(&regex);
        return -3;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input);
    if (matches[0].rm_so != 0 || matches[0].rm_eo != (regoff_t)len) {
        regfree(&regex);
        return -4;
    }

    if (output_size < 11) {
        regfree(&regex);
        return -5;
    }

    snprintf(output, output_size, "%.*s-%.*s-%.*s",
             (int)(matches[3].rm_eo - matches[3].rm_so), input + matches[3].rm_so,
             (int)(matches[2].rm_eo - matches[2].rm_so), input + matches[2].rm_so,
             (int)(matches[1].rm_eo - matches[1].rm_so), input + matches[1].rm_so);

    regfree(&regex);
    return 0;
}

int main(void) {
    const char *input_dates[] = {
        "2023-12-25",
        "1999-01-01",
        "invalid-date",
        "2023-13-45",
        "2023-1-01"
    };
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output[16];
    size_t i;

    for (i = 0; i < sizeof(input_dates) / sizeof(input_dates[0]); i++) {
        int result = convert_date_format(input_dates[i], output, sizeof(output));
        if (result == 0) {
            printf("%s -> %s\n", input_dates[i], output);
        } else {
            printf("%s -> conversion failed (code %d)\n", input_dates[i], result);
        }
    }

    return EXIT_SUCCESS;
}