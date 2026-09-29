#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h> 

#define DATE_REGEX "\\b(19|20)\\d\\d[- /.](0[1-9]|1[012])[- /.](0[1-9]|[12][0-9]|3[01])\\b"

struct Date {
    int year;
    int month;
    int day;
};

int extract_date_from_url(const char* url, struct Date* date){
    regex_t regex;
    regmatch_t matches[2];

    if(regcomp(&regex, DATE_REGEX, REG_EXTENDED)){
        return -1;
    }

    if(regexec(&regex, url, 2, matches, 0)){
        regfree(&regex);
        return -1;
    }

    char year[5];
    char month[3];
    char day[3];

    strncpy(year, &url[matches[0].rm_so], 4);
    year[4] = '\0';
    date->year = atoi(year);

    strncpy(month, &url[matches[0].rm_so + 5], 2);
    month[2] = '\0';
    date->month = atoi(month);

    strncpy(day, &url[matches[0].rm_so + 8], 2);
    day[2] = '\0';
    date->day = atoi(day);

    regfree(&regex);
    
    return 0;
}

int main() {
    char url[100];
    struct Date date;

    printf("Enter a URL: ");
    fgets(url, 100, stdin);
    url[strcspn(url, "\n")] = 0;

    if(!extract_date_from_url(url, &date)){
        printf("Date found: %d-%d-%d\n", date.year, date.month, date.day);
    } else {
        printf("No date found in the URL!\n");
    }

    return 0;
}