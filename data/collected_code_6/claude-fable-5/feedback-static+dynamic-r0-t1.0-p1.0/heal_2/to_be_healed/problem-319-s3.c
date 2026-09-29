#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

#define MAX_ERR_LEN 256U
#define NUM_GROUPS 3U

static int find_five_letter_words(const char *text)
{
    regex_t regex;
    regmatch_t groups[NUM_GROUPS];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char errbuf[MAX_ERR_LEN];
    const char *pattern = "(^|[^[:alnum:]_])([[:alpha:]]{5})([^[:alnum:]_]|$)";
    const char *cursor = text;
    int rc;
    int found = 0;

    if (text == NULL) {
        return -1;
    }

    rc = regcomp(&regex, pattern, REG_EXTENDED);
    if (rc != 0) {
        (void)regerror(rc, &regex, errbuf, sizeof(errbuf));
        errbuf[sizeof(errbuf) - 1U] = '\0';
        (void)fprintf(stderr, "Regex compilation failed: %s\n", errbuf);
        return -1;
    }

    for (;;) {
        rc = regexec(&regex, cursor, (size_t)NUM_GROUPS, groups, 0);
        if (rc == REG_NOMATCH) {
            break;
        }
        if (rc != 0) {
            (void)regerror(rc, &regex, errbuf, sizeof(errbuf));
            errbuf[sizeof(errbuf) - 1U] = '\0';
            (void)fprintf(stderr, "Regex execution failed: %s\n", errbuf);
            regfree(&regex);
            return -1;
        }
        if ((groups[2].rm_so < 0) || (groups[2].rm_eo < groups[2].rm_so)) {
            break;
        }
        if (printf("%.*s\n", (int)(groups[2].rm_eo - groups[2].rm_so),
                   cursor + groups[2].rm_so) < 0) {
            regfree(&regex);
            return -1;
        }
        found++;
        cursor += groups[2].rm_eo;
        if (*cursor == '\0') {
            break;
        }
    }

    regfree(&regex);

    if (found == 0) {
        (void)printf("No five character words found.\n");
    }

    return 0;
}

int main(void)
{
    const char *text = "There might exist words which occur about seven times daily";
    int result;

    result = find_five_letter_words(text);
    if (result != 0) {
        (void)fprintf(stderr, "Failed to process the input string.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}