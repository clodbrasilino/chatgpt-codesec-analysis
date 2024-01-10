#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#define MAX_MATCHES 10
#define MAX_YEAR_LENGTH 4
#define MAX_MONTH_LENGTH 2
#define MAX_DATE_LENGTH 2

int is_pointer_valid(const char* ptr) {
    return ptr != NULL;
}

int extract_date_from_url(const char *url, size_t url_length, char *year, char *month, char *date) {
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
        size_t year_length = (size_t) (match[1].rm_eo - match[1].rm_so);
        size_t month_length = (size_t) (match[2].rm_eo - match[2].rm_so);
        size_t date_length = (size_t) (match[3].rm_eo - match[3].rm_so);

        if (year_length > MAX_YEAR_LENGTH || month_length > MAX_MONTH_LENGTH || date_length > MAX_DATE_LENGTH) {
            printf("Invalid date format\n");
            return -1;
        }

        memcpy(year, url + match[1].rm_so, year_length);
        year[year_length] = '\0';
        memcpy(month, url + match[2].rm_so, month_length);
        month[month_length] = '\0';
        memcpy(date, url + match[3].rm_so, date_length);
        date[date_length] = '\0';

    } else if (status == REG_NOMATCH) {
        printf("No date found in URL\n");
        return -1;
    } else 
    {
        printf("Regex match failed\n");
        return -1;
    }

    regfree(&regex);
    return 0;
}

int main() {
    const char *url = "https://example.com/2022/03/15/some-page.html";
    size_t url_length = strlen(url);

    char year[MAX_YEAR_LENGTH + 1] = {0};
    char month[MAX_MONTH_LENGTH + 1] = {0};
    char date[MAX_DATE_LENGTH + 1] = {0};
    
    int result = extract_date_from_url(url, url_length, year, month, date);
    
    if (result == 0) {
        printf("Year: %s\n", year);
        printf("Month: %s\n", month);
        printf("Date: %s\n", date);
    }
    
    return 0;
}