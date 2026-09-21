#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void find_words(const char *str, int min_len, int max_len) {
    regex_t regex;
    regmatch_t match[1];
    const char *p = str;
    char pattern[64];
    int ret;
    size_t str_len;

    if (str == NULL) return;
    if (min_len < 0) min_len = 0;
    if (max_len < 0) max_len = 0;
    if (min_len > max_len) return;

    str_len = strlen(str);

    ret = snprintf(pattern, sizeof(pattern), "\\b[a-zA-Z]{%d,%d}\\b", min_len, max_len);
    if (ret < 0 || (size_t)ret >= sizeof(pattern)) {
        fprintf(stderr, "pattern buffer too small\n");
        return;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        char errbuf[256];
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "regex compilation failed: %s\n", errbuf);
        return;
    }

    while (regexec(&regex, p, 1, match, 0) == 0) {
        int len = match[0].rm_eo - match[0].rm_so;
        size_t p_offset;

        if (p < str || p >= str + str_len) break;

        p_offset = (size_t)(p - str);

        if (len <= 0 || len > 256) {
            p++;
            continue;
        }

        if ((size_t)match[0].rm_so > str_len - p_offset ||
            (size_t)len > str_len - p_offset - (size_t)match[0].rm_so) {
            p++;
            continue;
        }

        {
            size_t alloc_size = (size_t)len + 1;
            char *word = malloc(alloc_size);
            if (!word) {
                regfree(&regex);
                return;
            }

            if (p_offset + (size_t)match[0].rm_so + (size_t)len <= str_len) {
                memcpy(word, p + match[0].rm_so, (size_t)len);
                word[len] = '\0';
                printf("%s\n", word);
            }
            free(word);
        }

        if (match[0].rm_eo > 0 && p_offset + (size_t)match[0].rm_eo <= str_len) {
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