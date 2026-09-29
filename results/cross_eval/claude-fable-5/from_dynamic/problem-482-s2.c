#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int find_sequences(const char *input)
{
    regex_t regex;
    regmatch_t match;
    const char *pattern = "[A-Z][a-z]+";
    const char *cursor;
    int ret;
    char errbuf[256];

    if (input == NULL) {
        fprintf(stderr, "Error: input string is NULL\n");
        return -1;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "Error: could not compile regex: %s\n", errbuf);
        return -1;
    }

    cursor = input;
    while (1) {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            break;
        }
        if (ret != 0) {
            regerror(ret, &regex, errbuf, sizeof(errbuf));
            fprintf(stderr, "Error: regex match failed: %s\n", errbuf);
            regfree(&regex);
            return -1;
        }

        {
            regoff_t start = match.rm_so;
            regoff_t end = match.rm_eo;
            size_t len = (size_t)(end - start);
            char *found = malloc(len + 1);

            if (found == NULL) {
                fprintf(stderr, "Error: memory allocation failed\n");
                regfree(&regex);
                return -1;
            }

            memcpy(found, cursor + start, len);
            found[len] = '\0';
            printf("Found sequence: %s\n", found);
            free(found);

            cursor += end;
            if (*cursor == '\0') {
                break;
            }
        }
    }

    regfree(&regex);
    return 0;
}

int main(void)
{
    const char *test_string = "Hello world This is a Test String with Sequences";
    int result;

    printf("Input: %s\n", test_string);
    result = find_sequences(test_string);
    if (result != 0) {
        fprintf(stderr, "Error: sequence search failed\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}