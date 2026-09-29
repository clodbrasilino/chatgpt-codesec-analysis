#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <errno.h>
#include <limits.h>

int extract_date_from_url(const char *url, int *year, int *month, int *day) {
    regex_t regex;
    regmatch_t matches[4];
    int ret = regcomp(&regex, "([0-9]{4})/([0-9]{2})/([0-9]{2})", REG_EXTENDED);
    if (ret != 0) {
        return ret;
    }

    ret = regexec(&regex, url, 4, matches, 0);
    if (ret != 0) {
        regfree(&regex);
        return ret;
    }

    for (int i = 1; i <= 3; i++) {
        if (matches[i].rm_so == -1) {
            regfree(&regex);
            return -1;
        }
    }

    char buffer[16];
    char *endptr;
    int *dest[3] = {year, month, day};

    for (int i = 0; i < 3; i++) {
        size_t len = matches[i + 1].rm_eo - matches[i + 1].rm_so;
        if (len == 0) {
            regfree(&regex);
            return -1;
        }
        
        int written = snprintf(buffer, sizeof(buffer), "%.*s", (int)len, url + matches[i + 1].rm_so);
        if (written < 0 || (size_t)written >= sizeof(buffer)) {
            regfree(&regex);
            return -1;
        }
        
        errno = 0;
        long val = strtol(buffer, &endptr, 10);
        if (*endptr != '\0' || errno != 0 || val < INT_MIN || val > INT_MAX) {
            regfree(&regex);
            return -1;
        }
        
        *dest[i] = (int)val;
    }

    regfree(&regex);
    return 0;
}

int main(void) {
    const char *url = "https://example.com/archive/2023/10/25/article.html";
    int year, month, day;

    int result = extract_date_from_url(url, &year, &month, &day);

    if (result == 0) {
        printf("Year: %d, Month: %d, Day: %d\n", year, month, day);
    } else {
        printf("Failed to extract date.\n");
    }

    return 0;
}