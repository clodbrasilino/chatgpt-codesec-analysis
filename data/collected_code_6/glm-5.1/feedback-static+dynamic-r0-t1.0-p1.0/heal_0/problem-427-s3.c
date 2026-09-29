#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int convert_date(const char *src, char *dst, size_t dst_size) {
    regex_t regex;
    regmatch_t matches[4];
    int ret;

    if (src == NULL || dst == NULL || dst_size < 11) {
        return -1;
    }

    ret = regcomp(&regex, "^([0-9]{4})-([0-9]{2})-([0-9]{2})$", REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }

    ret = regexec(&regex, src, 4, matches, 0);
    if (ret != 0) {
        regfree(&regex);
        return -1;
    }

    size_t m1_len = matches[3].rm_eo - matches[3].rm_so;
    size_t m2_len = matches[2].rm_eo - matches[2].rm_so;
    size_t m3_len = matches[1].rm_eo - matches[1].rm_so;
    size_t total_len = m1_len + m2_len + m3_len + 2;

    if (total_len >= dst_size) {
        regfree(&regex);
        return -1;
    }

    snprintf(dst, dst_size, "%.*s-%.*s-%.*s",
             (int)m1_len, src + matches[3].rm_so,
             (int)m2_len, src + matches[2].rm_so,
             (int)m3_len, src + matches[1].rm_so);

    regfree(&regex);
    return 0;
}

int main(void) {
    const char *input = "2023-10-25";
    char output[11];

    if (convert_date(input, output, sizeof(output)) == 0) {
        printf("%s\n", output);
    } else {
        printf("Conversion failed\n");
    }

    return 0;
}