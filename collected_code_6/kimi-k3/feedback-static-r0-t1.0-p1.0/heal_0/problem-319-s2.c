#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int find_five_char_words(const char *str)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    int ret;
    int count = 0;

    if (str == NULL) {
        return -1;
    }

    ret = regcomp(&regex, "[[:<:]][[:alnum:]]{5}[[:>:]]", REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }

    cursor = str;
    while (*cursor != '\0') {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            break;
        }
        if (ret != 0) {
            regfree(&regex);
            return -1;
        }
        printf("%.*s\n", (int)(match.rm_eo - match.rm_so), cursor + match.rm_so);
        count++;
        cursor += match.rm_eo;
    }

    regfree(&regex);
    return count;
}

int main(void)
{
    const char *text = "This is a simple string with several words of five chars like apple mango and grape";
    int result;

    result = find_five_char_words(text);
    if (result < 0) {
        fprintf(stderr, "Error processing regex\n");
        return EXIT_FAILURE;
    }

    printf("Found %d five-character words\n", result);
    return EXIT_SUCCESS;
}