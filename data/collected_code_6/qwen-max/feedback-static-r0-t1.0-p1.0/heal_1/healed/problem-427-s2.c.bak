#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* convertDate(const char* date) {
    regex_t regex;
    regmatch_t matches[4];
    if (regcomp(&regex, "^([0-9]{4})-([0-9]{2})-([0-9]{2})$", REG_EXTENDED) != 0) {
        return NULL;
    }

    if (regexec(&regex, date, 4, matches, 0) != 0) {
        regfree(&regex);
        return NULL;
    }
    
    char* result = (char*)malloc(11 * sizeof(char));
    if (!result) {
        regfree(&regex);
        return NULL;
    }
    
    int len1 = matches[3].rm_eo - matches[3].rm_so;
    int len2 = matches[2].rm_eo - matches[2].rm_so;
    int len3 = matches[1].rm_eo - matches[1].rm_so;

    strncpy(result, date + matches[3].rm_so, len1);
    result[len1] = '-';
    strncpy(result + len1 + 1, date + matches[2].rm_so, len2);
    result[len1 + 1 + len2] = '-';
    strncpy(result + len1 + 1 + len2 + 1, date + matches[1].rm_so, len3);
    result[len1 + 1 + len2 + 1 + len3] = '\0';

    regfree(&regex);
    return result;
}

int main() {
    const char* input_date = "2023-10-05";
    char* output_date = convertDate(input_date);

    if (output_date) {
        printf("%s\n", output_date);
        free(output_date);
    } else {
        printf("Date conversion failed.\n");
    }

    return 0;
}