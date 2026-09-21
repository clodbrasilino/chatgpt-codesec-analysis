#include <stdio.h>
#include <regex.h>

int extract_date_from_url(const char *url, int *year, int *month, int *day) {
    regex_t regex;
    regmatch_t matches[4];
    int ret;

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
    }

    *year = 0;
    for (int j = 0; j < 4; j++) {
        *year = *year * 10 + (url[matches[1].rm_so + j] - '0');
    }

    *month = 0;
    for (int j = 0; j < 2; j++) {
        *month = *month * 10 + (url[matches[2].rm_so + j] - '0');
    }

    *day = 0;
    for (int j = 0; j < 2; j++) {
        *day = *day * 10 + (url[matches[3].rm_so + j] - '0');
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