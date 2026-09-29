#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int convert_date_format(const char *input_date, char *output_date, size_t output_size) {
    regex_t regex;
    regmatch_t matches[4];
    const char *pattern = "^([0-9]{4})-([0-9]{2})-([0-9]{2})$";
    int ret;
    int year_len, month_len, day_len;
    size_t required_size;
    
    if (input_date == NULL || output_date == NULL || output_size < 11) {
        return -1;
    }
    
    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }
    
    ret = regexec(&regex, input_date, 4, matches, 0);
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
    
    required_size = (size_t)(day_len + 1 + month_len + 1 + year_len + 1);
    
    if (required_size > output_size) {
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
    const char *input = "2024-01-15";
    char output[16];
    
    memset(output, 0, sizeof(output));
    
    if (convert_date_format(input, output, sizeof(output)) == 0) {
        printf("Original: %s\n", input);
        printf("Converted: %s\n", output);
    } else {
        fprintf(stderr, "Invalid date format\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}