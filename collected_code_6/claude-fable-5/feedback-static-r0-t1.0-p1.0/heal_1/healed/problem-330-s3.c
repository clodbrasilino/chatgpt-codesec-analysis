#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define ERRBUF_SIZE 256
#define WORD_SIZE 256

static int find_words(const char *text)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    int ret;
    char errbuf[ERRBUF_SIZE];
    char word[WORD_SIZE];
    int found;

    if (text == NULL) {
        return -1;
    }

    ret = regcomp(&regex, "[[:alpha:]]+", REG_EXTENDED);
    if (ret != 0) {
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "regcomp failed: %s\n", errbuf);
        return -1;
    }

    cursor = text;
    found = 0;

    while ((ret = regexec(&regex, cursor, 1, &match, 0)) == 0) {
        if (match.rm_so >= 0 && match.rm_eo >= match.rm_so) {
            const size_t length = (size_t)(match.rm_eo - match.rm_so);
            if (length >= 3 && length <= 5 && length < sizeof(word)) {
                memcpy(word, cursor + match.rm_so, length);
                word[length] = '\0';
                printf("%s\n", word);
                found++;
            }
        }
        if (match.rm_eo == 0) {
            break;
        }
        cursor += match.rm_eo;
    }

    if (ret != 0 && ret != REG_NOMATCH) {
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "regexec failed: %s\n", errbuf);
        regfree(&regex);
        return -1;
    }

    regfree(&regex);
    return found;
}

int main(void)
{
    const char *text = "The quick brown fox jumps over a lazy dog nearby";
    int count;

    count = find_words(text);
    if (count < 0) {
        fprintf(stderr, "Error while searching for words\n");
        return EXIT_FAILURE;
    }

    printf("Total words found: %d\n", count);
    return EXIT_SUCCESS;
}