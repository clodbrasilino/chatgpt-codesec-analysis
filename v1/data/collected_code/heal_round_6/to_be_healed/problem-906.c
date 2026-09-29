#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#define MAX_MATCHES 10
#define MAX_YEAR_LENGTH 5 // added 1 more for NULL terminator
#define MAX_MONTH_LENGTH 3 // added 1 more for NULL terminator
#define MAX_DATE_LENGTH 3 // added 1 more for NULL terminator

int is_pointer_valid(const char* ptr) {
    return ptr != NULL;
}

int extract_date_from_url(const char *url, char *year, char *month, char *date) {
    if (!is_pointer_valid(url) || !is_pointer_valid(year) || !is_pointer_valid(month) || !is_pointer_valid(date)){
        printf("Invalid pointers provided\n");
        return -1;
    }

    regex_t regex;
    regmatch_t match[MAX_MATCHES];

    int status = regcomp(&regex, "/([0-9]{4})/([0-9]{2})/([0-9]{2})/", REG_EXTENDED);

    if (status != 0) {
        printf("Failed to compile regex\n");
        return -1;
    }

    status = regexec(&regex, url, MAX_MATCHES, match, 0);

    if (status == 0) {
        /* Possible weaknesses found:
         *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
         */
        strncpy(year, url + match[1].rm_so, MAX_YEAR_LENGTH - 1); // subtract 1 from length of amount to capture
        year[MAX_YEAR_LENGTH - 1] = '\0';

        /* Possible weaknesses found:
         *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
         */
        strncpy(month, url + match[2].rm_so, MAX_MONTH_LENGTH - 1); // subtract 1 from length of amount to capture
        month[MAX_MONTH_LENGTH - 1] = '\0';

        /* Possible weaknesses found:
         *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
         */
        strncpy(date, url + match[3].rm_so, MAX_DATE_LENGTH - 1); // subtract 1 from length of amount to capture
        date[MAX_DATE_LENGTH - 1] = '\0';
    } else if (status == REG_NOMATCH) {
        printf("No date found in URL\n");
        return -1;
    } else {
        printf("Regex match failed\n");
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
    
    int result = extract_date_from_url(url, year, month, date);
    
    if (result == 0) {
        printf("Year: %s\n", year);
        printf("Month: %s\n", month);
        printf("Date: %s\n", date);
    }
    
    return 0;
}