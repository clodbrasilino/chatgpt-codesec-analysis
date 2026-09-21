#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* convertDate(const char* date) {
    regex_t regex;
    regmatch_t matches[4];
    if (regcomp(&regex, "^([0-9]{4})-([0-9]{2})-([0-9]{2})$", REG_EXTENDED) != 0) {
        return NULL;
    }

    if (regexec(&regex, date, 4, matches, 0) != 0) {
        regfree(&regex);
        return NULL;
    }
    
    int len1 = matches[3].rm_eo - matches[3].rm_so;
    int len2 = matches[2].rm_eo - matches[2].rm_so;
    int len3 = matches[1].rm_eo - matches[1].rm_so;

    char* result = (char*)malloc(len1 + len2 + len3 + 4);
    if (!result) {
        regfree(&regex);
        return NULL;
    }

    snprintf(result, len1 + 2, "%.*s-", len1, date + matches[3].rm_so);
    snprintf(result + len1 + 1, len2 + 2, "%.*s-", len2, date + matches[2].rm_so);
    snprintf(result + len1 + 1 + len2 + 1, len3 + 1, "%.*s", len3, date + matches[1].rm_so);

    regfree(&regex);
    return result;
}

int main() {
    const char* input_date = "2023-10-05";
    char* output_date = convertDate(input_date);

    if (output_date) {
        printf("%s\n", output_date);
        free(output_date);
    } else {
        printf("Date conversion failed.\n");
    }

    return 0;
}