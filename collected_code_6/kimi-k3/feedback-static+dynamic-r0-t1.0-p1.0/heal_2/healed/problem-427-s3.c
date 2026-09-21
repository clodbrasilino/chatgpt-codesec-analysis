#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <limits.h>

#define DATE_OUTPUT_SIZE 12
#define DATE_PATTERN "^([0-9]{4})-([0-9]{2})-([0-9]{2})$"
#define DATE_MATCH_COUNT 4
#define MAX_INPUT_LENGTH 10

int convert_date_format(const char *input_date, size_t input_len, char *output_date, size_t output_size) {
    regex_t regex;
    regmatch_t matches[DATE_MATCH_COUNT];
    int ret;
    int year_len, month_len, day_len;
    
    if (input_date == NULL || output_date == NULL || output_size < DATE_OUTPUT_SIZE) {
        return -1;
    }
    
    if (input_len > MAX_INPUT_LENGTH) {
        return -1;
    }
    
    if (memchr(input_date, '\0', input_len) == NULL && input_len == MAX_INPUT_LENGTH) {
        if (input_date[MAX_INPUT_LENGTH - 1] != '\0') {
            return -1;
        }
    }
    
    ret = regcomp(&regex, DATE_PATTERN, REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }
    
    ret = regexec(&regex, input_date, DATE_MATCH_COUNT, matches, 0);
    if (ret != 0) {
        regfree(&regex);
        return -1;
    }
    
    year_len = (int)(matches[1].rm_eo - matches[1].rm_so);
    month_len = (int)(matches[2].rm_eo - matches[2].rm_so);
    day_len = (int)(matches[3].rm_eo - matches[3].rm_so);
    
    if (year_len != 4 || month_len != 2 || day_len != 2) {
        regfree(&regex);
        return -1;
    }
    
    if ((size_t)(year_len + month_len + day_len + 3) > output_size) {
        regfree(&regex);
        return -1;
    }
    
    ret = snprintf(output_date, output_size, "%.*s-%.*s-%.*s",
                   day_len,
                   input_date + matches[3].rm_so,
                   month_len,
                   input_date + matches[2].rm_so,
                   year_len,
                   input_date + matches[1].rm_so);
    
    regfree(&regex);
    
    if (ret < 0 || (size_t)ret >= output_size) {
        return -1;
    }
    
    return 0;
}

int main(void) {
    const char input[] = "2024-01-15";
    char output[DATE_OUTPUT_SIZE];
    
    memset(output, 0, sizeof(output));
    
    if (convert_date_format(input, sizeof(input) - 1, output, sizeof(output)) == 0) {
        printf("Original: %s\n", input);
        printf("Converted: %s\n", output);
    } else {
        fprintf(stderr, "Invalid date format\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}