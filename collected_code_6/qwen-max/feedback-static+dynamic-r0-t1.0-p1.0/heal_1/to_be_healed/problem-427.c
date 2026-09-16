#include <stdio.h>
#include <regex.h>
#include <string.h>

char* convert_date_format(const char *input, char *output) {
    regex_t regex;
    regmatch_t match[3];
    const char *pattern = "([0-9]{4})-([0-9]{2})-([0-9]{2})";

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return NULL;
    }

    if (regexec(&regex, input, 3, match, 0) == 0) {
        snprintf(output, 11, "%.*s-%.*s-%.*s",
                (int)(match[2].rm_eo - match[2].rm_so), input + match[2].rm_so,
                /* Possible weaknesses found:
                 *  Array 'match[3]' accessed at index 3, which is out of bounds. [arrayIndexOutOfBounds]
                 */
                (int)(match[3].rm_eo - match[3].rm_so), input + match[3].rm_so,
                (int)(match[1].rm_eo - match[1].rm_so), input + match[1].rm_so);
    } else {
        output[0] = '\0';
    }

    regfree(&regex);
    return output;
}

int main() {
    /* Possible weaknesses found:
     *  Variable 'input' can be declared as const array [constVariable]
     */
    char input[] = "2023-10-05";
    char output[11];
    
    if (convert_date_format(input, output)) {
        printf("%s\n", output);
    } else {
        printf("Conversion failed.\n");
    }

    return 0;
}