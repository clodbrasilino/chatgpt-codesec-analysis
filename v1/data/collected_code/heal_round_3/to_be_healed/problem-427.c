#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#define DATE_STR_SIZE 12
#define ERR_BUFF_SIZE 256

int convertDate(const char* date, char* convertedDate) {
    regex_t regex;
    regmatch_t match[3];
    char regexPattern[] = "([0-9]{4})-([0-9]{2})-([0-9]{2})";    
    int ret;

    ret = regcomp(&regex, regexPattern, REG_EXTENDED);
    if (ret) {
        printf("Could not compile regex\n");
        return -1;
    }

    ret = regexec(&regex, date, 3, match, 0);
    if (!ret) {
        if (match[0].rm_so < 0 || match[0].rm_eo > DATE_STR_SIZE || match[1].rm_so < 0 || match[1].rm_eo > DATE_STR_SIZE ||
             match[2].rm_so < 0 || match[2].rm_eo > DATE_STR_SIZE) {
            printf("Matched group(s) out of bounds\n");
            return -1;
        }
        snprintf(convertedDate, DATE_STR_SIZE, "%.*s-%.*s-%.*s", match[2].rm_eo - match[2].rm_so, date + match[2].rm_so,
                                                               match[1].rm_eo - match[1].rm_so, date + match[1].rm_so, 
                                                               match[0].rm_eo - match[0].rm_so, date + match[0].rm_so);
    }
    else if (ret == REG_NOMATCH) {
        printf("No match found\n");
        return -1;
    }
    else {
        /* Possible weaknesses found:
         *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
         */
        char errBuff[ERR_BUFF_SIZE];
        regerror(ret, &regex, errBuff, sizeof(errBuff));
        printf("Regex match failed: %s\n", errBuff);
        return -1;
    }

    regfree(&regex);
    return 0;
}

int main() {
    char date[] = "2022-10-15";
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char convertedDate[DATE_STR_SIZE] = {0};

    if (convertDate(date, convertedDate) == 0) {
        printf("Converted date: %s\n", convertedDate);
    }
    return 0;
}