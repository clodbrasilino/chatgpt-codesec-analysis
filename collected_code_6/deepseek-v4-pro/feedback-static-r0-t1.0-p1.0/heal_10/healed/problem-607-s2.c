#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

#define ERR_BUF_SIZE 256
#define MAX_STRING_SIZE 65536

static int validate_input(const char *string, const char *pattern, char **matched_text, int *start_pos, int *end_pos) {
    if (!string || !pattern || !matched_text || !start_pos || !end_pos) {
        return -1;
    }
    return 0;
}

static size_t safe_string_length(const char *string) {
    size_t len = 0;
    while (len < MAX_STRING_SIZE && string[len] != '\0') {
        len++;
    }
    return len;
}

static int compile_regex(regex_t *regex, const char *pattern) {
    char errbuf[ERR_BUF_SIZE];
    int ret;
    
    memset(errbuf, 0, sizeof(errbuf));
    
    ret = regcomp(regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        regerror(ret, regex, errbuf, sizeof(errbuf) - 1);
        fprintf(stderr, "Regex compilation failed: %s\n", errbuf);
        return -1;
    }
    return 0;
}

static int execute_regex(const regex_t *regex, const char *string, regmatch_t *pmatch) {
    char errbuf[ERR_BUF_SIZE];
    int ret;
    
    memset(errbuf, 0, sizeof(errbuf));
    memset(pmatch, 0, sizeof(regmatch_t));
    
    ret = regexec(regex, string, 1, pmatch, 0);
    if (ret == REG_NOMATCH) {
        return REG_NOMATCH;
    }
    if (ret != 0) {
        regerror(ret, regex, errbuf, sizeof(errbuf) - 1);
        fprintf(stderr, "Regex match failed: %s\n", errbuf);
        return -1;
    }
    return 0;
}

static int validate_match_bounds(const regmatch_t *pmatch, size_t string_len) {
    if (pmatch[0].rm_so == -1 || pmatch[0].rm_eo == -1) {
        return -1;
    }
    if (pmatch[0].rm_eo <= pmatch[0].rm_so) {
        return -2;
    }
    if (pmatch[0].rm_so < 0 || (size_t)pmatch[0].rm_eo > string_len) {
        return -2;
    }
    return 0;
}

static char *extract_matched_text(const char *string, const regmatch_t *pmatch, size_t string_len) {
    size_t match_len;
    char *matched_text;
    
    match_len = (size_t)(pmatch[0].rm_eo - pmatch[0].rm_so);
    
    if (match_len > string_len) {
        return NULL;
    }
    if (match_len >= MAX_STRING_SIZE) {
        return NULL;
    }
    if (match_len > SIZE_MAX - 1) {
        return NULL;
    }
    if ((size_t)(pmatch[0].rm_so) >= string_len) {
        return NULL;
    }
    if ((size_t)(pmatch[0].rm_so) + match_len > string_len) {
        return NULL;
    }
    
    matched_text = (char *)malloc(match_len + 1);
    if (!matched_text) {
        return NULL;
    }
    
    memcpy(matched_text, string + pmatch[0].rm_so, match_len);
    matched_text[match_len] = '\0';
    
    return matched_text;
}

int search_pattern(const char *string, const char *pattern, char **matched_text, int *start_pos, int *end_pos) {
    regex_t regex;
    regmatch_t pmatch;
    size_t string_len;
    int ret;
    
    ret = validate_input(string, pattern, matched_text, start_pos, end_pos);
    if (ret != 0) {
        return -1;
    }
    
    string_len = safe_string_length(string);
    if (string_len >= MAX_STRING_SIZE - 1) {
        fprintf(stderr, "Input string exceeds maximum allowed size\n");
        return -1;
    }
    
    ret = compile_regex(&regex, pattern);
    if (ret != 0) {
        return -1;
    }
    
    ret = execute_regex(&regex, string, &pmatch);
    if (ret == REG_NOMATCH) {
        regfree(&regex);
        *matched_text = NULL;
        *start_pos = -1;
        *end_pos = -1;
        return 0;
    }
    if (ret != 0) {
        regfree(&regex);
        return -1;
    }
    
    ret = validate_match_bounds(&pmatch, string_len);
    if (ret != 0) {
        regfree(&regex);
        return -1;
    }
    
    *matched_text = extract_matched_text(string, &pmatch, string_len);
    if (!*matched_text) {
        regfree(&regex);
        return -2;
    }
    
    *start_pos = pmatch.rm_so;
    *end_pos = pmatch.rm_eo - 1;
    
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