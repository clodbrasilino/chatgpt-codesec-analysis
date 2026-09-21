#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define PATTERN_SIZE 256

static int build_pattern(char *pattern, size_t pattern_size, int min_len, int max_len) {
    int ret;
    if (min_len < 1 || max_len < min_len || max_len > 99) {
        return 0;
    }
    ret = snprintf(pattern, pattern_size, "\\b[A-Za-z]{%d,%d}\\b", min_len, max_len);
    if (ret < 0 || (size_t)ret >= pattern_size) {
        return 0;
    }
    return 1;
}

static char *extract_word(const char *str, int offset, int len) {
    char *word;
    /* Possible weaknesses found:
     *  Assuming that condition 'len<=0' is not redundant
     */
    if (len <= 0) {
        return NULL;
    }
    word = malloc((size_t)len + 1);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (!word) {
        return NULL;
    }
    /* Possible weaknesses found:
     *  Condition 'len>0' is always true [knownConditionTrueFalse]
     *  Condition 'len>0' is always true
     */
    if (len > 0) {
        size_t copy_len = (size_t)len;
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(word, str + offset, copy_len);
    }
    word[len] = '\0';
    return word;
}

void find_words(const char *str, int min_len, int max_len) {
    regex_t regex;
    regmatch_t match;
    const char *p = str;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char pattern[PATTERN_SIZE];
    int ret;
    int compiled = 0;

    if (!str) {
        return;
    }

    if (!build_pattern(pattern, sizeof(pattern), min_len, max_len)) {
        fprintf(stderr, "Invalid length parameters or pattern too long\n");
        return;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }
    compiled = 1;

    while (p && *p && regexec(&regex, p, 1, &match, 0) == 0) {
        int len = match.rm_eo - match.rm_so;
        if (len <= 0) {
            p++;
            continue;
        }
        char *word = extract_word(p, match.rm_so, len);
        if (!word) {
            regfree(&regex);
            return;
        }
        printf("%s\n", word);
        free(word);
        p += match.rm_eo;
    }

    if (compiled) {
        regfree(&regex);
    }
}

int main(int argc, char *argv[]) {
    char *input = NULL;
    size_t len = 0;

    if (argc > 1) {
        input = argv[1];
    } else {
        ssize_t nread = getline(&input, &len, stdin);
        if (nread == -1) {
            free(input);
            return 1;
        }
        if (nread > 0 && input[nread - 1] == '\n') {
            input[nread - 1] = '\0';
        }
    }

    if (!input) {
        return 1;
    }

    find_words(input, 3, 3);
    find_words(input, 4, 4);
    find_words(input, 5, 5);

    if (argc == 1) {
        free(input);
    }

    return 0;
}