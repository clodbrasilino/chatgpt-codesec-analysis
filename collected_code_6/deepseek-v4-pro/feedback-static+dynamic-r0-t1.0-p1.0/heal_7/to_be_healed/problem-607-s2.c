#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

int search_pattern(const char *string, const char *pattern, char **matched_text, int *start_pos, int *end_pos) {
    regex_t regex;
    regmatch_t pmatch[1];
    int ret;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char errbuf[256];
    size_t string_len;
    size_t match_len;
    size_t alloc_size;
    size_t rm_so;
    size_t rm_eo;

    if (!string || !pattern || !matched_text || !start_pos || !end_pos) {
        return -2;
    }

    *matched_text = NULL;
    *start_pos = -1;
    *end_pos = -1;

    memset(&regex, 0, sizeof(regex));
    memset(pmatch, 0, sizeof(pmatch));
    memset(errbuf, 0, sizeof(errbuf));

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "Regex compilation failed: %s\n", errbuf);
        return -1;
    }

    ret = regexec(&regex, string, 1, pmatch, 0);
    if (ret == REG_NOMATCH) {
        regfree(&regex);
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
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    string_len = strlen(string);

    rm_so = (size_t)pmatch[0].rm_so;
    rm_eo = (size_t)pmatch[0].rm_eo;

    /* Possible weaknesses found:
     *  Assuming that condition 'rm_eo<=rm_so' is not redundant
     */
    if (rm_so >= string_len || rm_eo > string_len || rm_eo <= rm_so) {
        regfree(&regex);
        return -1;
    }

    /* Possible weaknesses found:
     *  Assignment 'match_len=rm_eo-rm_so', assigned value is greater than 0
     */
    match_len = rm_eo - rm_so;

    /* Possible weaknesses found:
     *  alloc_size is assigned 'match_len+1' here.
     */
    alloc_size = match_len + 1;

    /* Possible weaknesses found:
     *  Condition 'alloc_size<match_len' is always false
     *  Condition 'alloc_size<match_len' is always false [knownConditionTrueFalse]
     */
    if (alloc_size < match_len) {
        regfree(&regex);
        return -2;
    }

    *matched_text = (char *)malloc(alloc_size);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (!*matched_text) {
        regfree(&regex);
        return -2;
    }

    /* Possible weaknesses found:
     *  Condition 'match_len>0' is always true [knownConditionTrueFalse]
     *  Condition 'match_len>0' is always true
     */
    if (match_len > 0) {
        if (rm_so + match_len <= string_len) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(*matched_text, string + rm_so, match_len);
        } else {
            free(*matched_text);
            *matched_text = NULL;
            regfree(&regex);
            return -1;
        }
    }

    (*matched_text)[match_len] = '\0';
    *start_pos = (int)rm_so;
    *end_pos = (int)(rm_eo - 1);

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
    matched = NULL;
    start = 0;
    end = 0;
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
    matched = NULL;
    start = 0;
    end = 0;
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