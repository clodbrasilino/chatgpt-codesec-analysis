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

    size_t day_len = matches[3].rm_eo - matches[3].rm_so;
    size_t month_len = matches[2].rm_eo - matches[2].rm_so;
    size_t year_len = matches[1].rm_eo - matches[1].rm_so;

    /* Possible weaknesses found:
     *  Assuming that condition 'month_len!=2' is not redundant
     *  Assuming that condition 'day_len!=2' is not redundant
     *  Assuming that condition 'year_len!=4' is not redundant
     */
    if (day_len != 2 || month_len != 2 || year_len != 4) {
        return NULL;
    }

    /* Possible weaknesses found:
     *  Assignment 'result_size=11', assigned value is 11
     */
    size_t result_size = 11;
    char* result = (char*)malloc(result_size);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (result == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     *  Condition 'day_len>result_size-1' is always false [knownConditionTrueFalse]
     *  Condition 'result_size<3' is always false [knownConditionTrueFalse]
     *  Condition 'result_size<3' is always false
     *  Condition 'day_len>result_size-1' is always false
     */
    if (result_size < 3 || day_len > result_size - 1) {
        free(result);
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, yyyy_mm_dd + matches[3].rm_so, day_len);

    result[2] = '-';

    /* Possible weaknesses found:
     *  Condition 'result_size<6' is always false
     *  Condition 'month_len>result_size-4' is always false
     *  Condition 'month_len>result_size-4' is always false [knownConditionTrueFalse]
     *  Condition 'result_size<6' is always false [knownConditionTrueFalse]
     */
    if (result_size < 6 || month_len > result_size - 4) {
        free(result);
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result + 3, yyyy_mm_dd + matches[2].rm_so, month_len);

    result[5] = '-';

    /* Possible weaknesses found:
     *  Condition 'result_size<11' is always false [knownConditionTrueFalse]
     *  Condition 'result_size<11' is always false
     *  Condition 'year_len>result_size-7' is always false
     *  Condition 'year_len>result_size-7' is always false [knownConditionTrueFalse]
     */
    if (result_size < 11 || year_len > result_size - 7) {
        free(result);
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result + 6, yyyy_mm_dd + matches[1].rm_so, year_len);

    result[10] = '\0';

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
     *  Calling function 'convert_date_format' returns 0
     *  Assignment 'converted3=convert_date_format(NULL)', assigned value is 0
     */
    char* converted3 = convert_date_format(NULL);
    /* Possible weaknesses found:
     *  Condition 'converted3!=NULL' is always false [knownConditionTrueFalse]
     *  Condition 'converted3!=NULL' is always false
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