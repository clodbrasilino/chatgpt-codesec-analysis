#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

typedef struct {
    char *word;
    int position;
} Adverb;

static size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

static void free_adverbs(Adverb *adverbs, int count) {
    if (adverbs) {
        for (int i = 0; i < count; i++) {
            free(adverbs[i].word);
        }
        free(adverbs);
    }
}

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

    sentence_len = safe_strlen(sentence, 65536);
    if (sentence_len == 0 || sentence_len >= 65536) {
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
            size_t new_max;
            Adverb *temp;

            if (max_matches > SIZE_MAX / 2 || (size_t)max_matches > SIZE_MAX / 2 / sizeof(Adverb)) {
                free_adverbs(result, match_count);
                regfree(&regex);
                return -1;
            }

            new_max = (size_t)max_matches * 2;
            if (new_max > SIZE_MAX / sizeof(Adverb)) {
                free_adverbs(result, match_count);
                regfree(&regex);
                return -1;
            }

            temp = (Adverb *)realloc(result, new_max * sizeof(Adverb));
            if (!temp) {
                free_adverbs(result, match_count);
                regfree(&regex);
                return -1;
            }
            result = temp;
            max_matches = (int)new_max;
        }

        if (offset + start < 0 || (size_t)(offset + start) >= sentence_len ||
            (size_t)(offset + end) > sentence_len || length == 0) {
            free_adverbs(result, match_count);
            regfree(&regex);
            return -1;
        }

        if (length > sentence_len - (size_t)(offset + start)) {
            free_adverbs(result, match_count);
            regfree(&regex);
            return -1;
        }

        result[match_count].word = (char *)malloc(length + 1);
        if (!result[match_count].word) {
            free_adverbs(result, match_count);
            regfree(&regex);
            return -1;
        }

        if (length > 0) {
            size_t src_offset = (size_t)(offset + start);
            char *src = (char *)sentence + src_offset;
            char *dst = result[match_count].word;
            size_t dst_size = length + 1;

            if (src_offset + length > sentence_len) {
                free(result[match_count].word);
                free_adverbs(result, match_count);
                regfree(&regex);
                return -1;
            }

            if (length + 1 < length) {
                free(result[match_count].word);
                free_adverbs(result, match_count);
                regfree(&regex);
                return -1;
            }

            for (size_t i = 0; i < length && i < dst_size - 1; i++) {
                dst[i] = src[i];
            }
        }
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