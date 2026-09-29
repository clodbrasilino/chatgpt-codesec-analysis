#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#define MAX_MATCHES 10
#define MAX_YEAR_LENGTH 5
#define MAX_MONTH_LENGTH 3
#define MAX_DATE_LENGTH 3

int is_pointer_valid(const char* ptr) {
    return ptr != NULL;
}

int extract_date_from_url(const char *url, char *year, char *month, char *date) {
    if (!is_pointer_valid(url) || !is_pointer_valid(year) || !is_pointer_valid(month) || !is_pointer_valid(date)){
        return -1;
    }

    regex_t regex;
    regmatch_t match[MAX_MATCHES];

    if (regcomp(&regex, "/([0-9]{4})/([0-9]{2})/([0-9]{2})/", REG_EXTENDED) != 0) {
        return -1;
    }

    int status = regexec(&regex, url, MAX_MATCHES, match, 0);

    if (status == 0) {
        snprintf(year, MAX_YEAR_LENGTH, "%.*s", (int)(match[1].rm_eo - match[1].rm_so), url + match[1].rm_so);
        snprintf(month, MAX_MONTH_LENGTH, "%.*s", (int)(match[2].rm_eo - match[2].rm_so), url + match[2].rm_so);
        snprintf(date, MAX_DATE_LENGTH, "%.*s", (int)(match[3].rm_eo - match[3].rm_so), url + match[3].rm_so);
    } else {
        regfree(&regex);
        return -1;
    }

    regfree(&regex);
    return 0;
}

int main() {
    const char *url = "https://example.com/2022/03/15/some-page.html";
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char year[MAX_YEAR_LENGTH] = {0};
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char month[MAX_MONTH_LENGTH] = {0};
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char date[MAX_DATE_LENGTH] = {0};
    
    if (extract_date_from_url(url, year, month, date) == 0) {
        printf("Year: %s\n", year);
        printf("Month: %s\n", month);
        printf("Date: %s\n", date);
    }
    
    return 0;
}