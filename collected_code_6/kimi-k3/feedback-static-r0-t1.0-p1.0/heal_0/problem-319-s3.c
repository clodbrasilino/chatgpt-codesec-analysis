#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int find_five_char_words(const char *str) {
    regex_t regex;
    regmatch_t match[1];
    const char *pattern = "\\b[a-zA-Z]{5}\\b";
    int ret;
    int found = 0;

    if (str == NULL) {
        fprintf(stderr, "Error: Input string is NULL\n");
        return -1;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        char error_buffer[256];
        regerror(ret, &regex, error_buffer, sizeof(error_buffer));
        fprintf(stderr, "Error: Could not compile regex: %s\n", error_buffer);
        return -1;
    }

    const char *cursor = str;
    while ((ret = regexec(&regex, cursor, 1, match, 0)) == 0) {
        int start = match[0].rm_so;
        int end = match[0].rm_eo;
        int length = end - start;

        if (length > 0) {
            printf("Found: %.*s\n", length, cursor + start);
            found = 1;
        }

        cursor += end;
        if (match[0].rm_eo == 0) {
            cursor++;
        }
    }

    if (ret != REG_NOMATCH) {
        char error_buffer[256];
        regerror(ret, &regex, error_buffer, sizeof(error_buffer));
        fprintf(stderr, "Error: Regex match failed: %s\n", error_buffer);
        regfree(&regex);
        return -1;
    }

    regfree(&regex);

    if (!found) {
        printf("No five-character words found.\n");
    }

    return 0;
}

int main(void) {
    const char *test_string = "Hello world this is a test string with five letter words like apple and mango";
    
    printf("Searching for five-character words in: \"%s\"\n", test_string);
    
    if (find_five_char_words(test_string) != 0) {
        fprintf(stderr, "Error: Failed to process string\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}