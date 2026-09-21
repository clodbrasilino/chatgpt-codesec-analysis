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

    size_t len = matches[1].rm_eo - matches[1].rm_so;
    if (len >= sizeof(buffer)) {
        regfree(&regex);
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(buffer, url + matches[1].rm_so, len);
    buffer[len] = '\0';
    *year = (int)strtol(buffer, &endptr, 10);
    if (*endptr != '\0') {
        regfree(&regex);
        return -1;
    }

    len = matches[2].rm_eo - matches[2].rm_so;
    if (len >= sizeof(buffer)) {
        regfree(&regex);
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(buffer, url + matches[2].rm_so, len);
    buffer[len] = '\0';
    *month = (int)strtol(buffer, &endptr, 10);
    if (*endptr != '\0') {
        regfree(&regex);
        return -1;
    }

    len = matches[3].rm_eo - matches[3].rm_so;
    if (len >= sizeof(buffer)) {
        regfree(&regex);
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(buffer, url + matches[3].rm_so, len);
    buffer[len] = '\0';
    *day = (int)strtol(buffer, &endptr, 10);
    if (*endptr != '\0') {
        regfree(&regex);
        return -1;
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