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

void free_adverb_results(AdverbResult *res_arr, size_t current_count) {
    if (res_arr == NULL) {
        return;
    }
    for (size_t i = 0; i < current_count; i++) {
        free(res_arr[i].word);
    }
    free(res_arr);
}

int find_adverbs(const char *sentence, AdverbResult **results, size_t *count) {
    regex_t regex;
    regmatch_t match;
    int ret;
    const char *pattern = "\\b[a-zA-Z]+ly\\b";
    const char *cursor = sentence;
    size_t capacity = 10;
    size_t current_count = 0;
    AdverbResult *res_arr = NULL;
    AdverbResult *temp = NULL;

    if (sentence == NULL || results == NULL || count == NULL) {
        return REG_ESPACE;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return ret;
    }

    res_arr = malloc(capacity * sizeof(AdverbResult));
    if (res_arr == NULL) {
        regfree(&regex);
        return REG_ESPACE;
    }

    while (1) {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret != 0) {
            break;
        }

        if (match.rm_so == -1) {
            break;
        }

        if (current_count >= capacity) {
            capacity *= 2;
            temp = realloc(res_arr, capacity * sizeof(AdverbResult));
            if (temp == NULL) {
                free_adverb_results(res_arr, current_count);
                regfree(&regex);
                return REG_ESPACE;
            }
            res_arr = temp;
        }

        size_t word_len = match.rm_eo - match.rm_so;
        res_arr[current_count].word = malloc(word_len + 1);
        if (res_arr[current_count].word == NULL) {
            free_adverb_results(res_arr, current_count);
            regfree(&regex);
            return REG_ESPACE;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(res_arr[current_count].word, cursor + match.rm_so, word_len);
        res_arr[current_count].word[word_len] = '\0';

        res_arr[current_count].pos.start = (int)(cursor - sentence) + match.rm_so;
        res_arr[current_count].pos.end = (int)(cursor - sentence) + match.rm_eo;

        current_count++;

        cursor += match.rm_eo;
        if (*cursor == '\0') {
            break;
        }
    }

    regfree(&regex);

    if (current_count > 0) {
        temp = realloc(res_arr, current_count * sizeof(AdverbResult));
        if (temp != NULL) {
            res_arr = temp;
        }
    } else {
        free(res_arr);
        res_arr = NULL;
    }

    *results = res_arr;
    *count = current_count;

    return 0;
}

int main() {
    const char *sentence = "He quickly ran and suddenly stopped, then quietly left the beautifully designed room.";
    AdverbResult *results = NULL;
    size_t count = 0;
    int ret;
    size_t errbuf_size = 1024;
    char *errbuf = malloc(errbuf_size);

    if (errbuf == NULL) {
        return 1;
    }

    ret = find_adverbs(sentence, &results, &count);
    if (ret != 0) {
        regerror(ret, NULL, errbuf, errbuf_size);
        fprintf(stderr, "Regex error: %s\n", errbuf);
        free(errbuf);
        return 1;
    }

    for (size_t i = 0; i < count; i++) {
        printf("Adverb: \"%s\" | Position: [%d, %d)\n", results[i].word, results[i].pos.start, results[i].pos.end);
        free(results[i].word);
    }

    free(results);
    free(errbuf);

    return 0;
}