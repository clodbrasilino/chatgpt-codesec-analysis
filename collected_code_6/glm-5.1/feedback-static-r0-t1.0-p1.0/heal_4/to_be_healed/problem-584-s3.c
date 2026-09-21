#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_WORD_LEN 255

typedef struct {
    int start;
    int end;
} Position;

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[MAX_WORD_LEN + 1];
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

        if (current_count >= capacity) {
            capacity *= 2;
            temp = realloc(res_arr, capacity * sizeof(AdverbResult));
            if (temp == NULL) {
                free(res_arr);
                regfree(&regex);
                return REG_ESPACE;
            }
            res_arr = temp;
        }

        size_t word_len = match.rm_eo - match.rm_so;
        if (word_len > MAX_WORD_LEN) {
            word_len = MAX_WORD_LEN;
        }
        
        if (word_len > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(res_arr[current_count].word, cursor + match.rm_so, word_len);
        }
        res_arr[current_count].word[word_len] = '\0';

        res_arr[current_count].pos.start = (int)(cursor - sentence) + match.rm_so;
        res_arr[current_count].pos.end = (int)(cursor - sentence) + match.rm_eo;

        current_count++;

        cursor += match.rm_eo;
        if (match.rm_eo == 0) {
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     *  The scope of the variable 'errbuf' can be reduced. [variableScope]
     */
    char errbuf[1024];

    ret = find_adverbs(sentence, &results, &count);
    if (ret != 0) {
        regerror(ret, NULL, errbuf, sizeof(errbuf));
        fprintf(stderr, "Regex error: %s\n", errbuf);
        return 1;
    }

    for (size_t i = 0; i < count; i++) {
        printf("Adverb: \"%s\" | Position: [%d, %d)\n", results[i].word, results[i].pos.start, results[i].pos.end);
    }

    free(results);

    return 0;
}