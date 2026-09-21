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
    /* Possible weaknesses found:
     *  Using argument day
     *  Using argument month
     *  Using argument year
     *  Using argument month that points at uninitialized variable month [ctuuninitvar]
     *  Using argument year that points at uninitialized variable year [ctuuninitvar]
     *  Using argument day that points at uninitialized variable day [ctuuninitvar]
     */
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

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(buffer, url + matches[i].rm_so, len);
        buffer[len] = '\0';

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
    int year, month, day;

    /* Possible weaknesses found:
     *  Calling function extract_date_from_url, 4th argument is uninitialized
     *  Calling function extract_date_from_url, 2nd argument is uninitialized
     *  Calling function extract_date_from_url, 3rd argument is uninitialized
     */
    int result = extract_date_from_url(url, &year, &month, &day);

    if (result == 0) {
        printf("Year: %d, Month: %d, Day: %d\n", year, month, day);
    } else {
        printf("Failed to extract date.\n");
    }

    return 0;
}