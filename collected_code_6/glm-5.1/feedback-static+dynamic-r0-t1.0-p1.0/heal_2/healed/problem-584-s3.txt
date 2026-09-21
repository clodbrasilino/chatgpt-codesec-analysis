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

    res_arr = (AdverbResult *)malloc(capacity * sizeof(AdverbResult));
    if (res_arr == NULL) {
        regfree(&regex);
        return REG_ESPACE;
    }

    while (1) {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret != 0) {
            break;
        }

        if (current_count >= capacity) {
            capacity *= 2;
            temp = (AdverbResult *)realloc(res_arr, capacity * sizeof(AdverbResult));
            if (temp == NULL) {
                for (size_t i = 0; i < current_count; i++) {
                    free(res_arr[i].word);
                }
                free(res_arr);
                regfree(&regex);
                return REG_ESPACE;
            }
            res_arr = temp;
        }

        size_t word_len = match.rm_eo - match.rm_so;
        res_arr[current_count].word = (char *)malloc(word_len + 1);
        if (res_arr[current_count].word == NULL) {
            for (size_t i = 0; i < current_count; i++) {
                free(res_arr[i].word);
            }
            free(res_arr);
            regfree(&regex);
            return REG_ESPACE;
        }

        memcpy(res_arr[current_count].word, cursor + match.rm_so, word_len);
        res_arr[current_count].word[word_len] = '\0';

        res_arr[current_count].pos.start = (int)(cursor - sentence) + match.rm_so;
        res_arr[current_count].pos.end = (int)(cursor - sentence) + match.rm_eo;

        current_count++;

        if (match.rm_eo == 0) {
            break;
        }
        cursor += match.rm_eo;
    }

    regfree(&regex);

    if (current_count > 0) {
        temp = (AdverbResult *)realloc(res_arr, current_count * sizeof(AdverbResult));
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
    char *errbuf = (char *)malloc(errbuf_size);

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