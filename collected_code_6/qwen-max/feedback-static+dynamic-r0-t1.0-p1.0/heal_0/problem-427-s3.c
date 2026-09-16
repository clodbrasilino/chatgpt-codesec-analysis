#include <stdio.h>
#include <regex.h>
#include <string.h>

int convert_date_format(const char *input, char *output) {
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

    snprintf(output, 11, "%.*s-%.*s-%.*s",
             (int)(matches[3].rm_eo - matches[3].rm_so), &input[matches[3].rm_so],
             (int)(matches[2].rm_eo - matches[2].rm_so), &input[matches[2].rm_so],
             (int)(matches[1].rm_eo - matches[1].rm_so), &input[matches[1].rm_so]);
    
    output[10] = '\0';
    regfree(&regex);
    return 0;
}

int main() {
    const char *input = "2023-10-05";
    char output[11];
    
    if (convert_date_format(input, output) == 0) {
        printf("%s\n", output);
    } else {
        fprintf(stderr, "Failed to convert the date format.\n");
        return 1;
    }
    return 0;
}