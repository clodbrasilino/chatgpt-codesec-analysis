#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* convert_date_format(const char* yyyy_mm_dd) {
    if (yyyy_mm_dd == NULL) {
        return NULL;
    }

    regex_t regex;
    regmatch_t matches[4];
    int ret = regcomp(&regex, "^([0-9]{4})-([0-9]{2})-([0-9]{2})$", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    ret = regexec(&regex, yyyy_mm_dd, 4, matches, 0);
    regfree(&regex);

    if (ret != 0) {
        return NULL;
    }

    size_t len1 = matches[1].rm_eo - matches[1].rm_so;
    size_t len2 = matches[2].rm_eo - matches[2].rm_so;
    size_t len3 = matches[3].rm_eo - matches[3].rm_so;

    size_t total_len = len1 + len2 + len3 + 2 + 1;

    char* result = (char*)malloc(total_len);
    if (result == NULL) {
        return NULL;
    }

    size_t pos = 0;

    memcpy(result + pos, yyyy_mm_dd + matches[3].rm_so, len3);
    pos += len3;

    result[pos++] = '-';

    memcpy(result + pos, yyyy_mm_dd + matches[2].rm_so, len2);
    pos += len2;

    result[pos++] = '-';

    memcpy(result + pos, yyyy_mm_dd + matches[1].rm_so, len1);
    pos += len1;

    result[pos] = '\0';

    return result;
}

int main(void) {
    const char* date1 = "2023-10-25";
    char* converted1 = convert_date_format(date1);
    if (converted1 != NULL) {
        printf("%s\n", converted1);
        free(converted1);
    }

    const char* date2 = "2023-10-25-extra";
    char* converted2 = convert_date_format(date2);
    if (converted2 != NULL) {
        printf("%s\n", converted2);
        free(converted2);
    }

    char* converted3 = convert_date_format(NULL);
    if (converted3 != NULL) {
        printf("%s\n", converted3);
        free(converted3);
    }

    const char* date4 = "2023-10-25";
    char* converted4 = convert_date_format(date4);
    if (converted4 != NULL) {
        printf("%s\n", converted4);
        free(converted4);
    }

    return 0;
}