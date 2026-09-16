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

    reti = regcomp(&regex, pattern, REG_EXTENDED | REG_ICASE);
    if (reti) {
        return -1;
    }

    result = (Adverb *)malloc(max_matches * sizeof(Adverb));
    if (!result) {
        regfree(&regex);
        return -1;
    }

    while (regexec(&regex, cursor, 1, pmatch, 0) == 0) {
        int start = pmatch[0].rm_so;
        int end = pmatch[0].rm_eo;
        int length = end - start;

        if (match_count >= max_matches) {
            max_matches *= 2;
            Adverb *temp = (Adverb *)realloc(result, max_matches * sizeof(Adverb));
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

        result[match_count].word = (char *)malloc((length + 1) * sizeof(char));
        if (!result[match_count].word) {
            for (int i = 0; i < match_count; i++) {
                free(result[i].word);
            }
            free(result);
            regfree(&regex);
            return -1;
        }
        strncpy(result[match_count].word, cursor + start, length);
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