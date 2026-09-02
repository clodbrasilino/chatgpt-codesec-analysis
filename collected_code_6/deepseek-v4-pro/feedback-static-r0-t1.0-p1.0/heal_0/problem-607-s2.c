#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int search_pattern(const char *string, const char *pattern, char **matched_text, int *start_pos, int *end_pos) {
    regex_t regex;
    regmatch_t pmatch[1];
    int ret;
    char errbuf[256];

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "Regex compilation failed: %s\n", errbuf);
        return -1;
    }

    ret = regexec(&regex, string, 1, pmatch, 0);
    if (ret == REG_NOMATCH) {
        regfree(&regex);
        *matched_text = NULL;
        *start_pos = -1;
        *end_pos = -1;
        return 0;
    }
    if (ret != 0) {
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "Regex match failed: %s\n", errbuf);
        regfree(&regex);
        return -1;
    }

    if (pmatch[0].rm_so == -1) {
        regfree(&regex);
        *matched_text = NULL;
        *start_pos = -1;
        *end_pos = -1;
        return 0;
    }

    int match_len = pmatch[0].rm_eo - pmatch[0].rm_so;
    *matched_text = (char *)malloc(match_len + 1);
    if (!*matched_text) {
        regfree(&regex);
        return -2;
    }

    strncpy(*matched_text, string + pmatch[0].rm_so, match_len);
    (*matched_text)[match_len] = '\0';
    *start_pos = pmatch[0].rm_so;
    *end_pos = pmatch[0].rm_eo - 1;

    regfree(&regex);
    return 1;
}

int main(void) {
    const char *text = "The quick brown fox jumps over the lazy dog";
    const char *pattern = "quick";
    char *matched = NULL;
    int start = 0;
    int end = 0;
    int result;

    result = search_pattern(text, pattern, &matched, &start, &end);

    if (result == 1) {
        printf("Pattern found: '%s'\n", matched);
        printf("Start position: %d\n", start);
        printf("End position: %d\n", end);
        free(matched);
    } else if (result == 0) {
        printf("Pattern not found\n");
    } else {
        printf("Error occurred during search\n");
    }

    pattern = "fox";
    result = search_pattern(text, pattern, &matched, &start, &end);

    if (result == 1) {
        printf("Pattern found: '%s'\n", matched);
        printf("Start position: %d\n", start);
        printf("End position: %d\n", end);
        free(matched);
    } else if (result == 0) {
        printf("Pattern not found\n");
    } else {
        printf("Error occurred during search\n");
    }

    pattern = "cat";
    result = search_pattern(text, pattern, &matched, &start, &end);

    if (result == 1) {
        printf("Pattern found: '%s'\n", matched);
        printf("Start position: %d\n", start);
        printf("End position: %d\n", end);
        free(matched);
    } else if (result == 0) {
        printf("Pattern not found\n");
    } else {
        printf("Error occurred during search\n");
    }

    return 0;
}