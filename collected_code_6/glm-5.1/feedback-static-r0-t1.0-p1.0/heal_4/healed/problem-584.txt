#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

typedef struct {
    int start;
    int end;
} Position;

typedef struct {
    char *word;
    Position pos;
} AdverbResult;

AdverbResult* find_adverbs(const char *sentence, size_t *out_count) {
    regex_t regex;
    regmatch_t match;
    int status;
    const char *pattern = "\\b[a-zA-Z]+ly\\b";
    size_t capacity = 10;
    size_t count = 0;
    AdverbResult *results = malloc(capacity * sizeof(AdverbResult));

    if (results == NULL) {
        *out_count = 0;
        return NULL;
    }

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        free(results);
        *out_count = 0;
        return NULL;
    }

    const char *cursor = sentence;
    while (*cursor != '\0') {
        status = regexec(&regex, cursor, 1, &match, 0);
        if (status == REG_NOMATCH) {
            break;
        }
        if (status != 0) {
            regfree(&regex);
            for (size_t i = 0; i < count; i++) {
                free(results[i].word);
            }
            free(results);
            *out_count = 0;
            return NULL;
        }

        if (count >= capacity) {
            capacity *= 2;
            AdverbResult *temp = realloc(results, capacity * sizeof(AdverbResult));
            if (temp == NULL) {
                regfree(&regex);
                for (size_t i = 0; i < count; i++) {
                    free(results[i].word);
                }
                free(results);
                *out_count = 0;
                return NULL;
            }
            results = temp;
        }

        int start_offset = cursor - sentence;
        results[count].pos.start = start_offset + match.rm_so;
        results[count].pos.end = start_offset + match.rm_eo;

        size_t len = match.rm_eo - match.rm_so;
        results[count].word = malloc(len + 1);
        if (results[count].word == NULL) {
            regfree(&regex);
            for (size_t i = 0; i < count; i++) {
                free(results[i].word);
            }
            free(results);
            *out_count = 0;
            return NULL;
        }

        memcpy(results[count].word, cursor + match.rm_so, len);
        results[count].word[len] = '\0';

        count++;
        cursor += match.rm_eo;
        if (match.rm_eo == 0) {
            if (*cursor != '\0') {
                cursor++;
            } else {
                break;
            }
        }
    }

    regfree(&regex);

    if (count == 0) {
        free(results);
        *out_count = 0;
        return NULL;
    }

    AdverbResult *final_results = realloc(results, count * sizeof(AdverbResult));
    if (final_results != NULL) {
        results = final_results;
    }

    *out_count = count;
    return results;
}

void free_adverb_results(AdverbResult *results, size_t count) {
    if (results != NULL) {
        for (size_t i = 0; i < count; i++) {
            free(results[i].word);
        }
        free(results);
    }
}

int main(void) {
    const char *sentence = "He quickly ran and softly spoke while silently observing.";
    size_t count = 0;
    AdverbResult *results = find_adverbs(sentence, &count);

    if (results != NULL) {
        for (size_t i = 0; i < count; i++) {
            printf("Adverb: %s, Position: %d-%d\n", results[i].word, results[i].pos.start, results[i].pos.end);
        }
        free_adverb_results(results, count);
    } else {
        printf("No adverbs found or allocation failed.\n");
    }

    return 0;
}