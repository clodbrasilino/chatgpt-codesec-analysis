#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void find_words(const char *str, int min_len, int max_len) {
    regex_t regex;
    regmatch_t match[1];
    const char *p = str;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char pattern[128];
    int ret;
    int written;

    if (min_len < 0 || max_len < 0 || min_len > max_len || max_len > 99) {
        fprintf(stderr, "invalid length parameters\n");
        return;
    }

    written = snprintf(pattern, sizeof(pattern), "\\b[a-zA-Z]{%d,%d}\\b", min_len, max_len);
    if (written < 0 || (size_t)written >= sizeof(pattern)) {
        fprintf(stderr, "pattern too long\n");
        return;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char errbuf[512];
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "regex compilation failed: %s\n", errbuf);
        return;
    }

    while (regexec(&regex, p, 1, match, 0) == 0) {
        if (match[0].rm_so < 0 || match[0].rm_eo < 0) {
            break;
        }
        int len = match[0].rm_eo - match[0].rm_so;
        if (len <= 0 || len > 1024) {
            break;
        }
        char *word = malloc((size_t)len + 1);
        if (!word) {
            regfree(&regex);
            return;
        }
        if ((size_t)len < (size_t)(match[0].rm_eo - match[0].rm_so) + 1) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(word, p + match[0].rm_so, (size_t)len);
            word[len] = '\0';
            printf("%s\n", word);
        }
        free(word);
        p += match[0].rm_eo;
    }

    regfree(&regex);
}

int main(void) {
    const char *text = "This is a sample text with words of different sizes: cat, dogs, horse, apple, banana, tree, house";
    find_words(text, 3, 3);
    find_words(text, 4, 4);
    find_words(text, 5, 5);
    return 0;
}