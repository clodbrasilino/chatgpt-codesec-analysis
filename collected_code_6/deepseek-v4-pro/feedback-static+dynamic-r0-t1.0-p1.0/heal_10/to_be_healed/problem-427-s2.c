#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DATE_BUFFER_SIZE 11
#define MAX_INPUT_SIZE 256

static int safe_copy(const char *input, int start, int len, char *output, size_t output_size, size_t *pos) {
    if (len <= 0) return -1;
    if (start < 0) return -1;
    if (output == NULL || input == NULL) return -1;
    if (*pos + (size_t)len >= output_size) return -1;
    
    memmove(output + *pos, input + start, (size_t)len);
    *pos += (size_t)len;
    return 0;
}

int convert_date_format(const char *input, char *output, size_t output_size) {
    regex_t regex;
    regmatch_t matches[4];
    const char *pattern = "^([0-9]{4})-([0-9]{2})-([0-9]{2})$";
    size_t pos = 0;
    size_t input_len;
    
    if (output == NULL || input == NULL) {
        return -1;
    }
    
    if (output_size < DATE_BUFFER_SIZE) {
        return -1;
    }
    
    input_len = strnlen(input, DATE_BUFFER_SIZE);
    if (input_len >= DATE_BUFFER_SIZE || input_len != 10) {
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
    
    int year_start = (int)matches[1].rm_so;
    int year_end = (int)matches[1].rm_eo;
    int month_start = (int)matches[2].rm_so;
    int month_end = (int)matches[2].rm_eo;
    int day_start = (int)matches[3].rm_so;
    int day_end = (int)matches[3].rm_eo;
    
    if (year_end > (int)input_len || month_end > (int)input_len || day_end > (int)input_len) {
        regfree(&regex);
        return -1;
    }
    
    if (year_end - year_start != 4 || month_end - month_start != 2 || day_end - day_start != 2) {
        regfree(&regex);
        return -1;
    }
    
    if (safe_copy(input, day_start, day_end - day_start, output, output_size, &pos) != 0) {
        regfree(&regex);
        return -1;
    }
    
    if (pos >= output_size) {
        regfree(&regex);
        return -1;
    }
    output[pos++] = '-';
    
    if (safe_copy(input, month_start, month_end - month_start, output, output_size, &pos) != 0) {
        regfree(&regex);
        return -1;
    }
    
    if (pos >= output_size) {
        regfree(&regex);
        return -1;
    }
    output[pos++] = '-';
    
    if (safe_copy(input, year_start, year_end - year_start, output, output_size, &pos) != 0) {
        regfree(&regex);
        return -1;
    }
    
    if (pos >= output_size) {
        regfree(&regex);
        return -1;
    }
    output[pos] = '\0';
    
    regfree(&regex);
    return 0;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input_buffer[MAX_INPUT_SIZE] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input_date[DATE_BUFFER_SIZE] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output_date[DATE_BUFFER_SIZE] = {0};
    size_t input_len;
    
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    input_buffer[strcspn(input_buffer, "\n")] = '\0';
    
    input_len = strnlen(input_buffer, MAX_INPUT_SIZE);
    if (input_len == 0) {
        fprintf(stderr, "Empty input\n");
        return EXIT_FAILURE;
    }
    
    if (input_len >= DATE_BUFFER_SIZE) {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(input_date, input_buffer, DATE_BUFFER_SIZE - 1);
    input_date[DATE_BUFFER_SIZE - 1] = '\0';
    
    if (convert_date_format(input_date, output_date, sizeof(output_date)) == 0) {
        printf("%s\n", output_date);
    } else {
        fprintf(stderr, "Invalid date format\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}