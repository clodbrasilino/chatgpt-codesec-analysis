#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int convert_date(const char *src, char *dst, size_t dst_size) {
    if (src == NULL || dst == NULL || dst_size < 11) {
        return -1;
    }

    regex_t regex;
    regmatch_t matches[4];
    int ret;

    ret = regcomp(&regex, "^([0-9]{4})-([0-9]{2})-([0-9]{2})$", REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }

    ret = regexec(&regex, src, 4, matches, 0);
    if (ret != 0) {
        regfree(&regex);
        return -1;
    }

    size_t day_len = matches[3].rm_eo - matches[3].rm_so;
    size_t month_len = matches[2].rm_eo - matches[2].rm_so;
    size_t year_len = matches[1].rm_eo - matches[1].rm_so;

    if (day_len != 2 || month_len != 2 || year_len != 4) {
        regfree(&regex);
        return -1;
    }

    if (day_len > dst_size - 0) {
        regfree(&regex);
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dst + 0, src + matches[3].rm_so, day_len);
    
    if (1 > dst_size - 3) {
        regfree(&regex);
        return -1;
    }
    dst[2] = '-';
    
    if (month_len > dst_size - 3) {
        regfree(&regex);
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dst + 3, src + matches[2].rm_so, month_len);
    
    if (1 > dst_size - 6) {
        regfree(&regex);
        return -1;
    }
    dst[5] = '-';
    
    if (year_len > dst_size - 6) {
        regfree(&regex);
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dst + 6, src + matches[1].rm_so, year_len);
    
    if (1 > dst_size - 11) {
        regfree(&regex);
        return -1;
    }
    dst[10] = '\0';

    regfree(&regex);
    return 0;
}

int main(void) {
    const char *date1 = "2023-10-25";
    const char *date2 = "2023-5-10";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char result[11];

    if (convert_date(date1, result, sizeof(result)) == 0) {
        printf("%s\n", result);
    } else {
        printf("Conversion failed for %s\n", date1);
    }

    if (convert_date(date2, result, sizeof(result)) == 0) {
        printf("%s\n", result);
    } else {
        printf("Conversion failed for %s\n", date2);
    }

    return 0;
}