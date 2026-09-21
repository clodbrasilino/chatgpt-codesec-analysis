#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define ERRBUF_LEN 128

int find_sequences(const char *input);
static void print_regex_error(int code, const regex_t *regex, const char *prefix);

static void print_regex_error(int code, const regex_t *regex, const char *prefix)
{
    char errbuf[ERRBUF_LEN];

    memset(errbuf, 0, sizeof(errbuf));
    regerror(code, regex, errbuf, sizeof(errbuf) - 1);
    errbuf[sizeof(errbuf) - 1] = '\0';
    fprintf(stderr, "Error: %s: %s\n", prefix, errbuf);
}

int find_sequences(const char *input)
{
    regex_t regex;
    regmatch_t match;
    const char *pattern = "[A-Z][a-z]+";
    const char *cursor;
    size_t remaining;
    int ret;
    int found;

    if (input == NULL) {
        fprintf(stderr, "Error: input string is NULL\n");
        return -1;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        print_regex_error(ret, &regex, "failed to compile regex");
        return -1;
    }

    found = 0;
    cursor = input;
    remaining = strlen(input);

    while (*cursor != '\0') {
        size_t length;
        char *buffer;

        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            break;
        }
        if (ret != 0) {
            print_regex_error(ret, &regex, "regex execution failed");
            regfree(&regex);
            return -1;
        }

        if (match.rm_so < 0 || match.rm_eo < match.rm_so) {
            fprintf(stderr, "Error: invalid match offsets\n");
            regfree(&regex);
            return -1;
        }

        if ((size_t)match.rm_eo > remaining) {
            fprintf(stderr, "Error: match offsets exceed input bounds\n");
            regfree(&regex);
            return -1;
        }

        length = (size_t)(match.rm_eo - match.rm_so);

        buffer = malloc(length + 1);
        if (buffer == NULL) {
            fprintf(stderr, "Error: memory allocation failed\n");
            regfree(&regex);
            return -1;
        }

        memcpy(buffer, cursor + match.rm_so, length);
        buffer[length] = '\0';
        printf("Found match: %s\n", buffer);
        free(buffer);
        found++;

        if (match.rm_eo == 0) {
            cursor++;
            remaining--;
        } else {
            cursor += match.rm_eo;
            remaining -= (size_t)match.rm_eo;
        }
    }

    regfree(&regex);

    if (found == 0) {
        printf("No matches found.\n");
    }

    return found;
}

int main(void)
{
    const char *test_string = "HelloWorld this Is a TestString with Mixed caseWords";
    int result;

    printf("Input: %s\n", test_string);

    result = find_sequences(test_string);
    if (result < 0) {
        fprintf(stderr, "Error: sequence search failed\n");
        return EXIT_FAILURE;
    }

    printf("Total matches: %d\n", result);

    return EXIT_SUCCESS;
}