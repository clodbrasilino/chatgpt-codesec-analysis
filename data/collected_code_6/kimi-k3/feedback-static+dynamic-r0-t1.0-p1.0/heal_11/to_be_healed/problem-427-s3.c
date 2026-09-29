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
    size_t year_len, month_len, day_len;
    size_t required_size;
    
    if (input_date == NULL || output_date == NULL || output_size < DATE_OUTPUT_SIZE) {
        return -1;
    }
    
    if (input_len > MAX_INPUT_LENGTH) {
        return -1;
    }
    
    if (input_len == 0 || memchr(input_date, '\0', input_len) != NULL) {
        return -1;
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
    
    year_len = (size_t)(matches[1].rm_eo - matches[1].rm_so);
    month_len = (size_t)(matches[2].rm_eo - matches[2].rm_so);
    day_len = (size_t)(matches[3].rm_eo - matches[3].rm_so);
    
    if (year_len != 4 || month_len != 2 || day_len != 2) {
        regfree(&regex);
        return -1;
    }
    
    required_size = year_len + month_len + day_len + 3;
    if (required_size > output_size || required_size > DATE_OUTPUT_SIZE) {
        regfree(&regex);
        return -1;
    }
    
    ret = snprintf(output_date, output_size, "%.*s-%.*s-%.*s",
                   (int)day_len,
                   input_date + matches[3].rm_so,
                   (int)month_len,
                   input_date + matches[2].rm_so,
                   (int)year_len,
                   input_date + matches[1].rm_so);
    
    regfree(&regex);
    
    if (ret < 0 || (size_t)ret >= output_size || (size_t)ret >= DATE_OUTPUT_SIZE) {
        return -1;
    }
    
    return 0;
}

int main(void) {
    const char input[] = "2024-01-15";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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