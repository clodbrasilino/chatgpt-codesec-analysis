#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int convert_date_format(const char *input, char *output, size_t output_size) {
    regex_t regex;
    regmatch_t matches[4];
    const char *pattern = "^([0-9]{4})-([0-9]{2})-([0-9]{2})$";
    
    if (input == NULL || output == NULL) {
        return -1;
    }
    
    if (output_size < 11) {
        return -1;
    }
    
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
    
    size_t year_len = matches[1].rm_eo - matches[1].rm_so;
    size_t month_len = matches[2].rm_eo - matches[2].rm_so;
    size_t day_len = matches[3].rm_eo - matches[3].rm_so;
    
    if (year_len != 4 || month_len != 2 || day_len != 2) {
        regfree(&regex);
        return -1;
    }
    
    const char *year_start = input + matches[1].rm_so;
    const char *month_start = input + matches[2].rm_so;
    const char *day_start = input + matches[3].rm_so;
    
    int written = snprintf(output, output_size, "%.2s-%.2s-%.4s", day_start, month_start, year_start);
    
    regfree(&regex);
    
    if (written < 0 || (size_t)written >= output_size || written != 10) {
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