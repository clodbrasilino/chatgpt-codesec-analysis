#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_PATTERN_LEN 128
#define MAX_ERRBUF_LEN 512
#define MAX_WORD_LEN 1024

void find_words(const char *str, int min_len, int max_len) {
    regex_t regex;
    regmatch_t match[1];
    const char *p = str;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char pattern[MAX_PATTERN_LEN];
    int ret;
    int written;
    size_t str_len;

    if (str == NULL) {
        fprintf(stderr, "NULL string pointer\n");
        return;
    }

    if (min_len < 0 || max_len < 0 || min_len > max_len || max_len > 99) {
        fprintf(stderr, "invalid length parameters\n");
        return;
    }

    str_len = strnlen(str, MAX_WORD_LEN * 2);
    if (str_len > MAX_WORD_LEN * 2) {
        str_len = MAX_WORD_LEN * 2;
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
        char errbuf[MAX_ERRBUF_LEN];
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        errbuf[sizeof(errbuf) - 1] = '\0';
        fprintf(stderr, "regex compilation failed: %s\n", errbuf);
        return;
    }

    while (regexec(&regex, p, 1, match, 0) == 0) {
        if (match[0].rm_so < 0 || match[0].rm_eo < 0) {
            break;
        }
        if (match[0].rm_eo <= match[0].rm_so) {
            break;
        }
        if (match[0].rm_eo - match[0].rm_so > MAX_WORD_LEN) {
            break;
        }

        int len = match[0].rm_eo - match[0].rm_so;
        if (len <= 0 || len > MAX_WORD_LEN) {
            break;
        }

        if ((size_t)(p - str) + (size_t)match[0].rm_eo > str_len) {
            break;
        }

        size_t copy_len = (size_t)len;
        if (copy_len > MAX_WORD_LEN) {
            copy_len = MAX_WORD_LEN;
        }

        if (copy_len + (size_t)(p - str) + match[0].rm_so > str_len) {
            copy_len = str_len - (size_t)(p - str) - (size_t)match[0].rm_so;
        }

        char *word = malloc(copy_len + 1);
        if (!word) {
            regfree(&regex);
            return;
        }

        if (copy_len > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(word, p + match[0].rm_so, copy_len);
        }
        word[copy_len] = '\0';
        printf("%s\n", word);
        free(word);

        p += match[0].rm_eo;
        if ((size_t)(p - str) >= str_len) {
            break;
        }
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