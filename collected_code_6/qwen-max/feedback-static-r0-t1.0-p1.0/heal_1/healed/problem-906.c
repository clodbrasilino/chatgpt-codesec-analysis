#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <limits.h>

void extract_date(const char *url, int *year, int *month, int *day) {
    regex_t regex;
    regmatch_t matches[4];
    
    if (regcomp(&regex, "/(\\d{4})/(\\d{2})/(\\d{2})/", REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex.\n");
        exit(EXIT_FAILURE);
    }
    
    if (regexec(&regex, url, 4, matches, 0) == 0) {
        long y, m, d;
        if (sscanf(url + matches[1].rm_so, "%ld", &y) == 1 && y >= 0 && y <= INT_MAX) {
            *year = (int)y;
        } else {
            *year = 0;
        }
        
        if (sscanf(url + matches[2].rm_so, "%ld", &m) == 1 && m >= 1 && m <= 12) {
            *month = (int)m;
        } else {
            *month = 0;
        }
        
        if (sscanf(url + matches[3].rm_so, "%ld", &d) == 1 && d >= 1 && d <= 31) {
            *day = (int)d;
        } else {
            *day = 0;
        }
    } else {
        *year = 0;
        *month = 0;
        *day = 0;
    }
    
    regfree(&regex);
}

int main() {
    const char *url = "https://example.com/2023/08/15/some-article";
    int year, month, day;
    
    extract_date(url, &year, &month, &day);
    
    if (year != 0 && month != 0 && day != 0) {
        printf("Year: %d, Month: %d, Day: %d\n", year, month, day);
    } else {
        printf("Date not found.\n");
    }
    
    return 0;
}