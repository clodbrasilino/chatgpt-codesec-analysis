#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int convert_date_format(const char *input, char *output, size_t output_size) {
    regex_t regex;
    regmatch_t matches[4];
    const char *pattern = "^([0-9]{4})-([0-9]{2})-([0-9]{2})$";
    int result = -1;
    
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return -1;
    }
    
    if (regexec(&regex, input, 4, matches, 0) != 0) {
        regfree(&regex);
        return -1;
    }
    
    if (matches[1].rm_so == -1 || matches[2].rm_so == -1 || matches[3].rm_so == -1) {
        regfree(&regex);
        return -1;
    }
    
    size_t year_len = (size_t)(matches[1].rm_eo - matches[1].rm_so);
    size_t month_len = (size_t)(matches[2].rm_eo - matches[2].rm_so);
    size_t day_len = (size_t)(matches[3].rm_eo - matches[3].rm_so);
    
    if (year_len != 4 || month_len != 2 || day_len != 2) {
        regfree(&regex);
        return -1;
    }
    
    if (output_size < 11) {
        regfree(&regex);
        return -1;
    }
    
    char year[5] = {0};
    char month[3] = {0};
    char day[3] = {0};
    
    if (year_len >= sizeof(year) || month_len >= sizeof(month) || day_len >= sizeof(day)) {
        regfree(&regex);
        return -1;
    }
    
    memcpy(year, input + matches[1].rm_so, year_len);
    memcpy(month, input + matches[2].rm_so, month_len);
    memcpy(day, input + matches[3].rm_so, day_len);
    
    year[year_len] = '\0';
    month[month_len] = '\0';
    day[day_len] = '\0';
    
    int written = snprintf(output, output_size, "%s-%s-%s", day, month, year);
    
    regfree(&regex);
    
    if (written < 0 || (size_t)written >= output_size) {
        return -1;
    }
    
    return 0;
}

int main(void) {
    const char *input_date = "2024-03-15";
    char output_date[11] = {0};
    
    if (convert_date_format(input_date, output_date, sizeof(output_date)) == 0) {
        printf("%s\n", output_date);
    } else {
        fprintf(stderr, "Invalid date format\n");
        return 1;
    }
    
    return 0;
}