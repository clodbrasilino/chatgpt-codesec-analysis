#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int remove_multiple_spaces(char **str) {
    if (str == NULL || *str == NULL) {
        return -1;
    }

    regex_t regex;
    int reti;

    reti = regcomp(&regex, "  +", REG_EXTENDED);
    if (reti) {
        return -1;
    }

    regmatch_t pmatch[1];
    char *current = *str;
    size_t new_len = strlen(current);
    char *new_str = malloc(new_len + 1);

    if (new_str == NULL) {
        regfree(&regex);
        return -1;
    }

    new_str[0] = '\0';

    while (regexec(&regex, current, 1, pmatch, 0) == 0) {
        strncat(new_str, current, pmatch[0].rm_so);
        strcat(new_str, " ");
        current += pmatch[0].rm_eo;
    }

    strcat(new_str, current);

    free(*str);
    *str = new_str;

    regfree(&regex);
    return 0;
}

int main(void) {
    char *text = strdup("This   is  a    test string   with multiple     spaces.");
    if (text == NULL) {
        return 1;
    }

    printf("Original: '%s'\n", text);

    if (remove_multiple_spaces(&text) == 0) {
        printf("Modified: '%s'\n", text);
    } else {
        printf("Error processing string.\n");
    }

    free(text);
    return 0;
}