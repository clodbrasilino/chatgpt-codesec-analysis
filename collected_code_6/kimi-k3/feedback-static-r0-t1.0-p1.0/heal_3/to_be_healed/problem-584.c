#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <limits.h>

#define MAX_MATCHES 100
#define MAX_SENTENCE_LENGTH 1024

typedef struct {
    int start;
    int end;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char adverb[256];
} AdverbMatch;

int find_adverbs(const char *sentence, AdverbMatch *matches, int max_matches) {
    regex_t regex;
    regmatch_t match[1];
    const char *pattern = "\\b[a-zA-Z]+ly\\b";
    int ret;
    int count = 0;
    const char *cursor = sentence;
    long offset = 0;

    if (sentence == NULL || matches == NULL || max_matches <= 0) {
        return -1;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED | REG_ICASE);
    if (ret != 0) {
        return -1;
    }

    while (count < max_matches) {
        ret = regexec(&regex, cursor, 1, match, 0);
        if (ret != 0) {
            break;
        }

        if (match[0].rm_so == -1) {
            break;
        }

        long start = (long)match[0].rm_so + offset;
        long end = (long)match[0].rm_eo + offset;
        size_t length = (size_t)(match[0].rm_eo - match[0].rm_so);

        if (start > INT_MAX || end > INT_MAX) {
            break;
        }

        if (length >= sizeof(matches[count].adverb)) {
            break;
        }

        matches[count].start = (int)start;
        matches[count].end = (int)end;
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(matches[count].adverb, cursor + match[0].rm_so, length);
        matches[count].adverb[length] = '\0';
        count++;

        cursor += match[0].rm_eo;
        offset += match[0].rm_eo;

        if (match[0].rm_eo == 0) {
            if (*cursor == '\0') {
                break;
            }
            cursor++;
            offset++;
        }
    }

    regfree(&regex);
    return count;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char sentence[MAX_SENTENCE_LENGTH];
    AdverbMatch matches[MAX_MATCHES];
    int num_matches;
    int i;

    printf("Enter a sentence: ");
    if (fgets(sentence, sizeof(sentence), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    size_t len = strnlen(sentence, sizeof(sentence));
    if (len == sizeof(sentence)) {
        fprintf(stderr, "Input too long\n");
        return 1;
    }
    if (len > 0 && sentence[len - 1] == '\n') {
        sentence[len - 1] = '\0';
    }

    num_matches = find_adverbs(sentence, matches, MAX_MATCHES);

    if (num_matches < 0) {
        fprintf(stderr, "Error processing regex\n");
        return 1;
    }

    printf("Found %d adverb(s):\n", num_matches);
    for (i = 0; i < num_matches; i++) {
        printf("Adverb: \"%s\" at position [%d, %d)\n",
               matches[i].adverb, matches[i].start, matches[i].end);
    }

    return 0;
}