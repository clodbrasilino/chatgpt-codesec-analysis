#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define NUM_GROUPS 4U
#define WORD_GROUP 2U

static void print_regex_error(int rc, const regex_t *regex)
{
    size_t needed;
    char *errbuf;

    needed = regerror(rc, regex, NULL, 0U);
    if (needed == 0U) {
        (void)fprintf(stderr, "Regex error: unknown\n");
        return;
    }

    errbuf = (char *)calloc(needed, sizeof(char));
    if (errbuf == NULL) {
        (void)fprintf(stderr, "Regex error: allocation failure\n");
        return;
    }

    (void)regerror(rc, regex, errbuf, needed);
    errbuf[needed - 1U] = '\0';
    (void)fprintf(stderr, "Regex error: %s\n", errbuf);
    free(errbuf);
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
        (void)memset(groups, 0, sizeof(groups));
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