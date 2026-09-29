#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#define MAX_DATE_STR_SIZE 12
#define MAX_ERR_BUFF_SIZE 256

int convertDate(const char* date, char* convertedDate, size_t size) {
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
        if (match[0].rm_so < 0 || match[0].rm_eo >= size || match[1].rm_so < 0 || match[1].rm_eo >= size ||
             match[2].rm_so < 0 || match[2].rm_eo >= size) {
            printf("Matched group(s) out of bounds\n");
            return -1;
        }

        int day_len = match[2].rm_eo - match[2].rm_so;
        int month_len = match[1].rm_eo - match[1].rm_so;
        int year_len = match[0].rm_eo - match[0].rm_so;

        if (day_len > 2 || month_len > 2 || year_len > 4) {
            printf("Date format is incorrect\n");
            return -1;
        }

        snprintf(convertedDate, size, "%.*s-%.*s-%.*s", day_len, date + match[2].rm_so, 
                month_len, date + match[1].rm_so, 
                year_len, date + match[0].rm_so);
    }
    else if (ret == REG_NOMATCH) {
        printf("No match found\n");
        return -1;
    }
    else {
        char errBuff[MAX_ERR_BUFF_SIZE];
        regerror(ret, &regex, errBuff, sizeof(errBuff));
        printf("Regex match failed: %s\n", errBuff);
        return -1;
    }

    regfree(&regex);
    return 0;
}

int main() {
    const char* date = "2022-10-15";
    char convertedDate[MAX_DATE_STR_SIZE] = {0};

    if (convertDate(date, convertedDate, sizeof(convertedDate)) == 0) {
        printf("Converted date: %s\n", convertedDate);
    }
    return 0;
}