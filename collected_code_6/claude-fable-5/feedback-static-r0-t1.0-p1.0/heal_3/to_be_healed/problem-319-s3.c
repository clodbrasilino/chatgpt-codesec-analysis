#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_ERR_LEN 256U
#define NUM_GROUPS 3U
#define WORD_GROUP 2U

static void print_regex_error(int rc, const regex_t *regex)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char errbuf[MAX_ERR_LEN];
    size_t needed;

    (void)memset(errbuf, 0, sizeof(errbuf));
    needed = regerror(rc, regex, errbuf, sizeof(errbuf));
    errbuf[sizeof(errbuf) - 1U] = '\0';
    if (needed >= sizeof(errbuf)) {
        (void)fprintf(stderr, "Regex error (truncated): %s\n", errbuf);
    } else {
        (void)fprintf(stderr, "Regex error: %s\n", errbuf);
    }
}

static int find_five_letter_words(const char *text)
{
    regex_t regex;
    regmatch_t groups[NUM_GROUPS];
    const char *pattern = "(^|[^[:alnum:]_])([[:alpha:]]{5})([^[:alnum:]_]|$)";
    const char *cursor;
    int rc;
    int found = 0;

    if (text == NULL) {
        return -1;
    }

    cursor = text;

    rc = regcomp(&regex, pattern, REG_EXTENDED);
    if (rc != 0) {
        print_regex_error(rc, &regex);
        return -1;
    }

    for (;;) {
        rc = regexec(&regex, cursor, (size_t)NUM_GROUPS, groups, 0);
        if (rc == REG_NOMATCH) {
            break;
        }
        if (rc != 0) {
            print_regex_error(rc, &regex);
            regfree(&regex);
            return -1;
        }
        if ((groups[WORD_GROUP].rm_so < 0) ||
            (groups[WORD_GROUP].rm_eo <= groups[WORD_GROUP].rm_so)) {
            break;
        }
        if (printf("%.*s\n",
                   (int)(groups[WORD_GROUP].rm_eo - groups[WORD_GROUP].rm_so),
                   cursor + groups[WORD_GROUP].rm_so) < 0) {
            regfree(&regex);
            return -1;
        }
        found++;
        if (groups[WORD_GROUP].rm_eo <= 0) {
            break;
        }
        cursor += groups[WORD_GROUP].rm_eo;
        if (*cursor == '\0') {
            break;
        }
    }

    regfree(&regex);

    if (found == 0) {
        if (printf("No five character words found.\n") < 0) {
            return -1;
        }
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