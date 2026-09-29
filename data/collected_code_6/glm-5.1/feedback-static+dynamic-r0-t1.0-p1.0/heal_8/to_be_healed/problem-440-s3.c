#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN 255

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[MAX_WORD_LEN + 1];
    size_t position;
} Adverb;

Adverb* find_adverbs(const char* sentence, size_t* out_count) {
    if (sentence == NULL || out_count == NULL) {
        return NULL;
    }

    *out_count = 0;
    size_t capacity = 10;
    Adverb* results = malloc(capacity * sizeof(Adverb));
    if (results == NULL) {
        return NULL;
    }

    size_t index = 0;

    while (sentence[index] != '\0') {
        while (sentence[index] != '\0' && isspace((unsigned char)sentence[index])) {
            index++;
        }

        if (sentence[index] == '\0') {
            break;
        }

        size_t start_pos = index;

        while (sentence[index] != '\0' && !isspace((unsigned char)sentence[index])) {
            index++;
        }

        size_t actual_word_len = index - start_pos;

        if (actual_word_len > 2 && sentence[start_pos + actual_word_len - 2] == 'l' && sentence[start_pos + actual_word_len - 1] == 'y') {
            if (*out_count >= capacity) {
                size_t new_capacity = capacity * 2;
                Adverb* temp = realloc(results, new_capacity * sizeof(Adverb));
                if (temp == NULL) {
                    free(results);
                    return NULL;
                }
                results = temp;
                capacity = new_capacity;
            }

            size_t copy_len = actual_word_len < MAX_WORD_LEN ? actual_word_len : MAX_WORD_LEN;
            snprintf(results[*out_count].word, sizeof(results[*out_count].word), "%.*s", (int)copy_len, &sentence[start_pos]);
            results[*out_count].position = start_pos;
            (*out_count)++;
        }
    }

    return results;
}

int main(void) {
    const char* sentence = "He quickly ran to the slowly moving car and happily drove away.";
    size_t count = 0;

    Adverb* adverbs = find_adverbs(sentence, &count);

    if (adverbs != NULL) {
        for (size_t i = 0; i < count; i++) {
            printf("Adverb: '%s' at position %zu\n", adverbs[i].word, adverbs[i].position);
        }
        free(adverbs);
    }

    return 0;
}