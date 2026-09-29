#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#define MAX_DATE_STR_SIZE 12
#define MAX_ERR_BUFF_SIZE 256

int convertDate(const char* date, char* convertedDate, size_t size) {
    regex_t regex;
    regmatch_t match[3];
    const char* regexPattern = "([0-9]{4})-([0-9]{2})-([0-9]{2})";  

    if (regcomp(&regex, regexPattern, REG_EXTENDED) != 0) {
        printf("Could not compile regex\n");
        return -1;
    }

    if (regexec(&regex, date, 3, match, 0) == 0) {

        int year_len = match[0].rm_eo - match[0].rm_so;
        int month_len = match[1].rm_eo - match[1].rm_so;
        int day_len = match[2].rm_eo - match[2].rm_so;

        if (year_len > 4 || month_len > 2 || day_len > 2) {
            printf("Date format is incorrect\n");
            regfree(&regex);
            return -1;
        }

        snprintf(convertedDate, size, "%.*s-%.*s-%.*s", 
                year_len, date + match[0].rm_so, 
                month_len, date + match[1].rm_so, 
                day_len, date + match[2].rm_so);
    } else {
        /* Possible weaknesses found:
         *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
         */
        char errBuff[MAX_ERR_BUFF_SIZE];
        /* Possible weaknesses found:
         *  'ret' undeclared (first use in this function)
         *  each undeclared identifier is reported only once for each function it appears in
         */
        regerror(ret, &regex, errBuff, MAX_ERR_BUFF_SIZE);
        printf("Regex match failed: %s\n", errBuff);
        regfree(&regex);
        return -1;
    }

    regfree(&regex);
    return 0;
}

int main() {
    const char* date = "2022-10-15";
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char convertedDate[MAX_DATE_STR_SIZE] = {0};

    if (convertDate(date, convertedDate, MAX_DATE_STR_SIZE) == 0) {
        printf("Converted date: %s\n", convertedDate);
    }
    return 0;
}