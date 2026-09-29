#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

#define MAX_ERR_LEN 256
#define MAX_SENTENCE_LEN 4096

static int is_word_boundary(const char *sentence, size_t len, size_t end)
{
    if (end >= len) {
        return 1;
    }
    return !isalpha((unsigned char)sentence[end]);
}

static void report_regex_error(int code, const regex_t *regex, const char *context)
{
    char errbuf[MAX_ERR_LEN] = {0};

    (void)regerror(code, regex, errbuf, sizeof(errbuf));
    errbuf[sizeof(errbuf) - 1] = '\0';
    fprintf(stderr, "%s: %s\n", context, errbuf);
}

static int extract_and_print_word(const char *sentence, size_t start, size_t word_len, size_t end)
{
    char *word;

    word = calloc(word_len + 1, sizeof(char));
    if (word == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return -1;
    }

    memcpy(word, sentence + start, word_len);
    word[word_len] = '\0';

    printf("Adverb: %-15s Position: %zu-%zu\n", word, start, end - 1);

    free(word);
    return 0;
}

int find_adverbs(const char *sentence)
{
    regex_t regex;
    regmatch_t match;
    const char *pattern = "[A-Za-z]+ly";
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
        report_regex_error(ret, &regex, "Regex compilation failed");
        return -1;
    }

    while (offset < len) {
        ret = regexec(&regex, sentence + offset, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            break;
        }
        if (ret != 0) {
            report_regex_error(ret, &regex, "Regex execution failed");
            regfree(&regex);
            return -1;
        }

        if (match.rm_so < 0 || match.rm_eo < match.rm_so) {
            fprintf(stderr, "Error: invalid match offsets\n");
            regfree(&regex);
            return -1;
        }

        size_t start = offset + (size_t)match.rm_so;
        size_t end = offset + (size_t)match.rm_eo;

        if (start > len || end > len || end < start) {
            fprintf(stderr, "Error: match offsets out of bounds\n");
            regfree(&regex);
            return -1;
        }

        size_t word_len = end - start;

        if (word_len > 0 && start < len &&
            is_word_boundary(sentence, len, end)) {
            if (extract_and_print_word(sentence, start, word_len, end) != 0) {
                regfree(&regex);
                return -1;
            }
            count++;
        }

        if (match.rm_eo == match.rm_so) {
            if (offset + 1 >= len) {
                break;
            }
            offset += 1;
        } else {
            offset = end;
        }
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