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

    char* result = (char*)malloc(11);
    if (result == NULL) {
        return NULL;
    }

    snprintf(result, 11, "%.*s-%.*s-%.*s",
             matches[3].rm_eo - matches[3].rm_so, yyyy_mm_dd + matches[3].rm_so,
             matches[2].rm_eo - matches[2].rm_so, yyyy_mm_dd + matches[2].rm_so,
             matches[1].rm_eo - matches[1].rm_so, yyyy_mm_dd + matches[1].rm_so);

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

    const char* date3 = NULL;
    /* Possible weaknesses found:
     *  Assignment 'converted3=convert_date_format(date3)', assigned value is 0
     *  Variable 'converted3' can be declared as pointer to const [constVariablePointer]
     *  Calling function 'convert_date_format' returns 0
     */
    char* converted3 = convert_date_format(date3);
    /* Possible weaknesses found:
     *  Condition 'converted3==NULL' is always true [knownConditionTrueFalse]
     *  Condition 'converted3==NULL' is always true
     */
    if (converted3 == NULL) {
        printf("Invalid input\n");
    }

    const char* date4 = "2023-10-25";
    char* converted4 = convert_date_format(date4);
    if (converted4 != NULL) {
        printf("%s\n", converted4);
        free(converted4);
    }

    return 0;
}