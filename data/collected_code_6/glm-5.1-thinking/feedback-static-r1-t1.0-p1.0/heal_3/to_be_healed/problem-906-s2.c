#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int extract_date_from_url(const char *url, int *year, int *month, int *day) {
    regex_t regex;
    regmatch_t matches[4];
    int ret;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[16];
    char *endptr;
    int *results[3] = {year, month, day};

    ret = regcomp(&regex, "([0-9]{4})/([0-9]{2})/([0-9]{2})", REG_EXTENDED);
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

        size_t len = matches[i].rm_eo - matches[i].rm_so;
        if (len >= sizeof(buffer)) {
            regfree(&regex);
            return -1;
        }

        snprintf(buffer, sizeof(buffer), "%.*s", (int)len, url + matches[i].rm_so);

        *results[i - 1] = (int)strtol(buffer, &endptr, 10);
        if (*endptr != '\0') {
            regfree(&regex);
            return -1;
        }
    }

    regfree(&regex);
    return 0;
}

int main(void) {
    const char *url = "https://example.com/archive/2023/10/25/article.html";
    int year = 0;
    int month = 0;
    int day = 0;

    int result = extract_date_from_url(url, &year, &month, &day);

    if (result == 0) {
        printf("Year: %d, Month: %d, Day: %d\n", year, month, day);
    } else {
        printf("Failed to extract date.\n");
    }

    return 0;
}