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
    int written;

    written = snprintf(pattern, sizeof(pattern), "\\b[a-zA-Z]{%d,%d}\\b", min_len, max_len);
    if (written < 0 || (size_t)written >= sizeof(pattern)) {
        fprintf(stderr, "pattern too long\n");
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
        if (len <= 0) {
            break;
        }
        char *word = malloc(len + 1);
        if (!word) {
            regfree(&regex);
            return;
        }
        memcpy(word, p + match[0].rm_so, len);
        word[len] = '\0';
        printf("%s\n", word);
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