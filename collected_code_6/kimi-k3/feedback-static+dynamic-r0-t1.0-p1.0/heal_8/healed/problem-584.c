#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

#define MAX_MATCHES 100
#define MAX_SENTENCE_LENGTH 1024
#define MAX_ADVERB_LENGTH 256

typedef struct {
    int start;
    int end;
    char adverb[MAX_ADVERB_LENGTH];
} AdverbMatch;

int find_adverbs(const char *sentence, AdverbMatch *matches, int max_matches) {
    regex_t regex;
    regmatch_t match[1];
    const char *pattern = "\\b[a-zA-Z]+ly\\b";
    int ret;
    int count = 0;
    const char *cursor = sentence;
    int offset = 0;

    if (sentence == NULL || matches == NULL || max_matches <= 0) {
        return -1;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED | REG_ICASE);
    if (ret != 0) {
        return -1;
    }

    while (count < max_matches && *cursor != '\0') {
        ret = regexec(&regex, cursor, 1, match, 0);
        if (ret != 0 || match[0].rm_so == -1) {
            break;
        }

        int start = match[0].rm_so + offset;
        int end = match[0].rm_eo + offset;
        int length = match[0].rm_eo - match[0].rm_so;

        if (length > 0 && length < MAX_ADVERB_LENGTH) {
            matches[count].start = start;
            matches[count].end = end;

            size_t copy_len = (size_t)length;
            if (copy_len >= sizeof(matches[count].adverb)) {
                copy_len = sizeof(matches[count].adverb) - 1;
            }

            strncpy(matches[count].adverb, cursor + match[0].rm_so, copy_len);
            matches[count].adverb[copy_len] = '\0';
            count++;
        }

        if (match[0].rm_eo > 0) {
            cursor += match[0].rm_eo;
            offset += match[0].rm_eo;
        } else {
            cursor++;
            offset++;
        }
    }

    regfree(&regex);
    return count;
}

int main(void) {
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