#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct {
    char* adverb;
    int start_pos;
    int end_pos;
} AdverbInfo;

int count_adverbs(const char* sentence) {
    int count = 0;
    const char* word_start = NULL;
    size_t length = 0;
    while (*sentence) {
        if (isalnum((unsigned char)*sentence) || *sentence == '\'') {
            if (!word_start) {
                word_start = sentence;
                length = 0;
            }
            length++;
        } else if (word_start) {
            if (length >= 3 && (*(sentence - 1) == 'y' || *(sentence - 1) == 'l') && (*(sentence - 2) == 'l' || *(sentence - 2) == 'r')) {
                count++;
            }
            word_start = NULL;
        }
        sentence++;
    }
    if (word_start && length >= 3 && (*(sentence - 1) == 'y' || *(sentence - 1) == 'l') && (*(sentence - 2) == 'l' || *(sentence - 2) == 'r')) {
        count++;
    }
    return count;
}

AdverbInfo* find_adverbs(const char* sentence, int* out_count) {
    int n = count_adverbs(sentence);
    *out_count = n;
    if (n == 0) return NULL;

    AdverbInfo* result = (AdverbInfo*)malloc(n * sizeof(AdverbInfo));
    if (!result) {
        *out_count = 0;
        return NULL;
    }

    int index = 0;
    const char* word_start = NULL;
    size_t length = 0;
    int pos = 0;
    while (*sentence) {
        if (isalnum((unsigned char)*sentence) || *sentence == '\'') {
            if (!word_start) {
                word_start = sentence;
                length = 0;
            }
            length++;
        } else if (word_start) {
            if (length >= 3 && (*(sentence - 1) == 'y' || *(sentence - 1) == 'l') && (*(sentence - 2) == 'l' || *(sentence - 2) == 'r')) {
                result[index].adverb = (char*)malloc((length + 1) * sizeof(char));
                if (result[index].adverb) {
                    /* Possible weaknesses found:
                     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                     */
                    strncpy(result[index].adverb, word_start, length);
                    result[index].adverb[length] = '\0';
                    result[index].start_pos = word_start - sentence;
                    result[index].end_pos = sentence - 1 - word_start;
                    index++;
                }
            }
            word_start = NULL;
        }
        sentence++;
        pos++;
    }
    if (word_start && length >= 3 && (*(sentence - 1) == 'y' || *(sentence - 1) == 'l') && (*(sentence - 2) == 'l' || *(sentence - 2) == 'r')) {
        result[index].adverb = (char*)malloc((length + 1) * sizeof(char));
        if (result[index].adverb) {
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(result[index].adverb, word_start, length);
            result[index].adverb[length] = '\0';
            result[index].start_pos = word_start - sentence;
            result[index].end_pos = sentence - 1 - word_start;
        }
    }
    return result;
}

void free_adverbs(AdverbInfo* adverbs, int count) {
    for (int i = 0; i < count; i++) {
        free(adverbs[i].adverb);
    }
    free(adverbs);
}

int main() {
    const char* sentence = "She carefully placed the book quietly on the table.";
    int adverb_count;
    AdverbInfo* adverbs = find_adverbs(sentence, &adverb_count);

    for (int i = 0; i < adverb_count; i++) {
        printf("Adverb: %s, Start: %d, End: %d\n", adverbs[i].adverb, adverbs[i].start_pos, adverbs[i].end_pos);
    }

    free_adverbs(adverbs, adverb_count);
    return 0;
}