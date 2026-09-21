#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

typedef struct {
    char *word;
    int position;
} Adverb;

int find_adverbs(const char *sentence, Adverb **adverbs, int *count) {
    regex_t regex;
    regmatch_t pmatch[1];
    const char *pattern = "\\b[a-zA-Z]+ly\\b";
    int reti;
    int max_matches = 10;
    int match_count = 0;
    int offset = 0;
    const char *cursor = sentence;
    Adverb *result = NULL;
    size_t sentence_len;

    if (!sentence || !adverbs || !count) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    sentence_len = strlen(sentence);

    reti = regcomp(&regex, pattern, REG_EXTENDED | REG_ICASE);
    if (reti) {
        return -1;
    }

    result = (Adverb *)malloc((size_t)max_matches * sizeof(Adverb));
    if (!result) {
        regfree(&regex);
        return -1;
    }

    while (regexec(&regex, cursor, 1, pmatch, 0) == 0) {
        int start = pmatch[0].rm_so;
        int end = pmatch[0].rm_eo;
        size_t length;
        size_t remaining_len;

        if (start < 0 || end < 0 || end <= start) {
            break;
        }

        length = (size_t)(end - start);
        remaining_len = sentence_len - (size_t)offset;

        if ((size_t)start >= remaining_len || length > remaining_len - (size_t)start) {
            break;
        }

        if (match_count >= max_matches) {
            size_t new_max = (size_t)max_matches * 2;
            Adverb *temp;

            if (new_max > SIZE_MAX / sizeof(Adverb)) {
                for (int i = 0; i < match_count; i++) {
                    free(result[i].word);
                }
                free(result);
                regfree(&regex);
                return -1;
            }

            temp = (Adverb *)realloc(result, new_max * sizeof(Adverb));
            if (!temp) {
                for (int i = 0; i < match_count; i++) {
                    free(result[i].word);
                }
                free(result);
                regfree(&regex);
                return -1;
            }
            result = temp;
            max_matches = (int)new_max;
        }

        result[match_count].word = (char *)malloc(length + 1);
        if (!result[match_count].word) {
            for (int i = 0; i < match_count; i++) {
                free(result[i].word);
            }
            free(result);
            regfree(&regex);
            return -1;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result[match_count].word, cursor + start, length);
        result[match_count].word[length] = '\0';
        result[match_count].position = offset + start;
        match_count++;

        cursor += end;
        offset += end;
    }

    regfree(&regex);
    *adverbs = result;
    *count = match_count;
    return 0;
}

int main(void) {
    const char *sentence = "She quickly ran very smoothly and happily across the field.";
    Adverb *adverbs = NULL;
    int count = 0;
    int ret;

    ret = find_adverbs(sentence, &adverbs, &count);
    if (ret != 0) {
        fprintf(stderr, "Error processing sentence\n");
        return 1;
    }

    printf("Found %d adverb(s):\n", count);
    for (int i = 0; i < count; i++) {
        printf("Position %d: %s\n", adverbs[i].position, adverbs[i].word);
        free(adverbs[i].word);
    }
    free(adverbs);

    return 0;
}