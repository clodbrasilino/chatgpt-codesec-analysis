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
    char pattern[64];
    int ret;
    size_t str_len;

    if (str == NULL) return;
    if (min_len < 0) min_len = 0;
    if (max_len < 0) max_len = 0;
    if (min_len > max_len) return;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    str_len = strlen(str);

    ret = snprintf(pattern, sizeof(pattern), "\\b[a-zA-Z]{%d,%d}\\b", min_len, max_len);
    if (ret < 0 || (size_t)ret >= sizeof(pattern)) {
        fprintf(stderr, "pattern buffer too small\n");
        return;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char errbuf[256];
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "regex compilation failed: %s\n", errbuf);
        return;
    }

    while (regexec(&regex, p, 1, match, 0) == 0) {
        int len = match[0].rm_eo - match[0].rm_so;
        size_t p_offset;

        if (p < str || p > str + str_len) break;

        p_offset = (size_t)(p - str);

        if (len <= 0 || len > 256) {
            p++;
            continue;
        }

        if ((size_t)match[0].rm_so > str_len - p_offset ||
            (size_t)len > str_len - p_offset - match[0].rm_so) {
            p++;
            continue;
        }

        {
            char *word = malloc((size_t)len + 1);
            if (!word) {
                regfree(&regex);
                return;
            }

            if (len > 0 && p_offset + match[0].rm_so + len <= str_len) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(word, p + match[0].rm_so, (size_t)len);
                word[len] = '\0';
                printf("%s\n", word);
            }
            free(word);
        }

        if (match[0].rm_eo > 0 && p_offset + match[0].rm_eo <= str_len) {
            p += match[0].rm_eo;
        } else {
            p++;
        }

        if (p >= str + str_len) break;
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