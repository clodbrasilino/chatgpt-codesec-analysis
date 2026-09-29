#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

#define MAX_ERR_LEN 256
#define MAX_SENTENCE_LEN 4096
#define MAX_WORD_LEN 256

int find_adverbs(const char *sentence)
{
    regex_t regex;
    regmatch_t match;
    const char *pattern = "[A-Za-z]+ly";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char errbuf[MAX_ERR_LEN];
    int ret;
    size_t offset = 0;
    size_t len;
    int count = 0;

    if (sentence == NULL) {
        fprintf(stderr, "Error: sentence is NULL\n");
        return -1;
    }

    len = strnlen(sentence, MAX_SENTENCE_LEN);
    if (len >= MAX_SENTENCE_LEN) {
        fprintf(stderr, "Error: sentence too long or not null-terminated\n");
        return -1;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "Regex compilation failed: %s\n", errbuf);
        return -1;
    }

    while (offset < len) {
        ret = regexec(&regex, sentence + offset, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            break;
        }
        if (ret != 0) {
            regerror(ret, &regex, errbuf, sizeof(errbuf));
            fprintf(stderr, "Regex execution failed: %s\n", errbuf);
            regfree(&regex);
            return -1;
        }

        if (match.rm_so < 0 || match.rm_eo < 0 || match.rm_eo < match.rm_so) {
            fprintf(stderr, "Error: invalid match offsets\n");
            regfree(&regex);
            return -1;
        }

        size_t start = offset + (size_t)match.rm_so;
        size_t end = offset + (size_t)match.rm_eo;

        if (start > len || end > len || start > end) {
            fprintf(stderr, "Error: match out of bounds\n");
            regfree(&regex);
            return -1;
        }

        size_t word_len = end - start;

        if (word_len == 0 || word_len >= MAX_WORD_LEN) {
            offset = (end > offset) ? end : offset + 1;
            continue;
        }

        if (end < len && isalpha((unsigned char)sentence[end])) {
            offset = end;
            continue;
        }

        printf("Adverb: %-15.*s Position: %zu-%zu\n",
               (int)word_len, sentence + start, start, end - 1);
        count++;

        offset = end;
    }

    regfree(&regex);
    return count;
}

int main(void)
{
    const char *sentence = "She quickly ran to the store and quietly bought some milk, then happily walked home.";
    int result;

    printf("Sentence: %s\n\n", sentence);

    result = find_adverbs(sentence);
    if (result < 0) {
        fprintf(stderr, "Failed to search for adverbs\n");
        return EXIT_FAILURE;
    }

    if (result == 0) {
        printf("No adverbs found.\n");
    } else {
        printf("\nTotal adverbs found: %d\n", result);
    }

    return EXIT_SUCCESS;
}