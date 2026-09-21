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

    /* Possible weaknesses found:
     *  Assuming that condition 'len3>total_len' is not redundant
     */
    if (len3 > total_len) {
        free(result);
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, yyyy_mm_dd + matches[3].rm_so, len3);
    /* Possible weaknesses found:
     *  pos is assigned 'len3' here.
     */
    size_t pos = len3;

    /* Possible weaknesses found:
     *  Condition 'pos>=total_len' is always true [knownConditionTrueFalse]
     *  Condition 'pos>=total_len' is always true
     */
    if (pos >= total_len) {
        free(result);
        return NULL;
    }
    result[pos++] = '-';

    if (len2 > total_len - pos) {
        free(result);
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result + pos, yyyy_mm_dd + matches[2].rm_so, len2);
    pos += len2;

    if (pos >= total_len) {
        free(result);
        return NULL;
    }
    result[pos++] = '-';

    if (len1 > total_len - pos) {
        free(result);
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result + pos, yyyy_mm_dd + matches[1].rm_so, len1);
    pos += len1;

    if (pos >= total_len) {
        free(result);
        return NULL;
    }
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

    /* Possible weaknesses found:
     *  Assignment 'converted3=convert_date_format(NULL)', assigned value is 0
     *  Calling function 'convert_date_format' returns 0
     */
    char* converted3 = convert_date_format(NULL);
    /* Possible weaknesses found:
     *  Condition 'converted3!=NULL' is always false
     *  Condition 'converted3!=NULL' is always false [knownConditionTrueFalse]
     */
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