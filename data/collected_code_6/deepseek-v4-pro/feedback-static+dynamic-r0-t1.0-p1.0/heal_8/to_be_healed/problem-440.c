#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ADVERBS 100
#define MAX_WORD_LEN 50
#define MAX_POSITIONS 100
#define MAX_SENTENCE_LEN 4096

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[MAX_WORD_LEN];
    int positions[MAX_POSITIONS];
    int position_count;
} AdverbInfo;

static int is_adverb(const char *word) {
    if (word == NULL) {
        return 0;
    }
    
    size_t len = strnlen(word, MAX_WORD_LEN);
    if (len >= MAX_WORD_LEN || len == 0) {
        return 0;
    }
    
    if (len >= 2) {
        const char *suffix = word + len - 2;
        if (suffix[0] == 'l' && suffix[1] == 'y') {
            return 1;
        }
    }
    
    static const char *exceptions[] = {
        "well", "fast", "hard", "high", "late",
        "early", "daily", "weekly", "monthly", "yearly"
    };
    size_t num_exceptions = sizeof(exceptions) / sizeof(exceptions[0]);
    
    for (size_t i = 0; i < num_exceptions; i++) {
        if (strcmp(word, exceptions[i]) == 0) {
            return 1;
        }
    }
    
    return 0;
}

static int find_adverbs(const char *sentence, AdverbInfo *adverbs, int max_adverbs) {
    if (sentence == NULL || adverbs == NULL || max_adverbs <= 0) {
        return 0;
    }

    int adverb_count = 0;
    int position = 0;
    
    size_t len = strnlen(sentence, MAX_SENTENCE_LEN);
    if (len == 0 || len >= MAX_SENTENCE_LEN) {
        return 0;
    }

    char *temp = malloc(len + 1);
    if (temp == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(temp, sentence, len);
    temp[len] = '\0';

    for (size_t idx = 0; idx < len; idx++) {
        temp[idx] = (char)tolower((unsigned char)temp[idx]);
    }

    char *saveptr;
    char *token = strtok_r(temp, " ,.!?;:()\t\n\"'", &saveptr);
    
    while (token != NULL && adverb_count < max_adverbs) {
        size_t token_len = strnlen(token, MAX_WORD_LEN);
        if (token_len >= MAX_WORD_LEN) {
            position++;
            token = strtok_r(NULL, " ,.!?;:()\t\n\"'", &saveptr);
            continue;
        }
        
        if (is_adverb(token)) {
            int found = -1;
            for (int idx2 = 0; idx2 < adverb_count; idx2++) {
                if (strcmp(token, adverbs[idx2].word) == 0) {
                    found = idx2;
                    break;
                }
            }
            
            if (found == -1) {
                size_t copy_len = token_len < (size_t)(MAX_WORD_LEN - 1) 
                                  ? token_len : (size_t)(MAX_WORD_LEN - 1);
                
                /* Possible weaknesses found:
                 * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                 */
                strncpy(adverbs[adverb_count].word, token, copy_len);
                adverbs[adverb_count].word[copy_len] = '\0';
                adverbs[adverb_count].positions[0] = position;
                adverbs[adverb_count].position_count = 1;
                adverb_count++;
            } else {
                if (adverbs[found].position_count < MAX_POSITIONS) {
                    adverbs[found].positions[adverbs[found].position_count] = position;
                    adverbs[found].position_count++;
                }
            }
        }
        position++;
        token = strtok_r(NULL, " ,.!?;:()\t\n\"'", &saveptr);
    }

    free(temp);
    return adverb_count;
}

int main(void) {
    char sentence[] = "He quickly ran fast and worked very hardly early daily well.";
    AdverbInfo adverbs[MAX_ADVERBS];
    int count = find_adverbs(sentence, adverbs, MAX_ADVERBS);

    printf("Sentence: %s\n", sentence);
    printf("Found %d adverb(s):\n", count);
    for (int i = 0; i < count; i++) {
        printf("  '%s' at position(s): ", adverbs[i].word);
        for (int j = 0; j < adverbs[i].position_count; j++) {
            printf("%d", adverbs[i].positions[j]);
            if (j < adverbs[i].position_count - 1) {
                printf(", ");
            }
        }
        printf("\n");
    }

    return 0;
}