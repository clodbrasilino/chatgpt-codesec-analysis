#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <limits.h>
#include <stdint.h>

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
    size_t offset = 0;
    const char *cursor = sentence;
    Adverb *result = NULL;
    size_t sentence_len;

    if (!sentence || !adverbs || !count) {
        return -1;
    }

    sentence_len = strnlen(sentence, SIZE_MAX);
    if (sentence_len > (size_t)INT_MAX) {
        return -1;
    }

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

        if (start < 0 || end < 0 || end <= start) {
            break;
        }

        length = (size_t)(end - start);

        if (offset + (size_t)end > sentence_len) {
            break;
        }

        if (match_count >= max_matches) {
            if (max_matches > INT_MAX / 2) {
                for (int i = 0; i < match_count; i++) {
                    free(result[i].word);
                }
                free(result);
                regfree(&regex);
                return -1;
            }
            max_matches *= 2;
            Adverb *temp = (Adverb *)realloc(result, (size_t)max_matches * sizeof(Adverb));
            if (!temp) {
                for (int i = 0; i < match_count; i++) {
                    free(result[i].word);
                }
                free(result);
                regfree(&regex);
                return -1;
            }
            result = temp;
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

        if (length > 0) {
            size_t copy_len = length;
            size_t src_offset = offset + (size_t)start;
            if (src_offset + copy_len > sentence_len) {
                copy_len = sentence_len - src_offset;
            }
            if (copy_len > 0) {
                memcpy(result[match_count].word, sentence + src_offset, copy_len);
            }
            result[match_count].word[copy_len] = '\0';
        } else {
            result[match_count].word[0] = '\0';
        }

        result[match_count].position = (int)(offset + (size_t)start);
        match_count++;

        cursor += end;
        offset += (size_t)end;

        if (offset >= sentence_len || *cursor == '\0') {
            break;
        }
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