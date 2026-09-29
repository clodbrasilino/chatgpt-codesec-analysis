#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int convert_date_format(const char *input, char *output, size_t output_size) {
    regex_t regex;
    regmatch_t matches[4];
    const char *pattern = "^([0-9]{4})-([0-9]{2})-([0-9]{2})$";
    
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
    
    char year[5], month[3], day[3];
    
    snprintf(year, sizeof(year), "%.*s", 
             (int)(matches[1].rm_eo - matches[1].rm_so), input + matches[1].rm_so);
    snprintf(month, sizeof(month), "%.*s", 
             (int)(matches[2].rm_eo - matches[2].rm_so), input + matches[2].rm_so);
    snprintf(day, sizeof(day), "%.*s", 
             (int)(matches[3].rm_eo - matches[3].rm_so), input + matches[3].rm_so);
    
    int written = snprintf(output, output_size, "%s-%s-%s", day, month, year);
    
    regfree(&regex);
    
    if (written < 0 || (size_t)written >= output_size) {
        return -1;
    }
    
    return 0;
}

int main(void) {
    const char *input_date = "2024-03-15";
    char output_date[11];
    
    if (convert_date_format(input_date, output_date, sizeof(output_date)) == 0) {
        printf("%s\n", output_date);
    } else {
        fprintf(stderr, "Invalid date format\n");
        return 1;
    }
    
    return 0;
}