#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ADVERBS 100
#define MAX_WORD_LEN 50
#define MAX_POSITIONS 100

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
    
    size_t len = 0;
    while (word[len] != '\0') {
        len++;
        if (len >= MAX_WORD_LEN) {
            return 0;
        }
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
        const char *ex = exceptions[i];
        size_t j = 0;
        while (word[j] != '\0' && ex[j] != '\0' && word[j] == ex[j]) {
            j++;
        }
        if (word[j] == '\0' && ex[j] == '\0') {
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
    
    size_t len = 0;
    while (sentence[len] != '\0') {
        len++;
    }
    
    char *temp = malloc(len + 1);
    if (temp == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     *  Shadowed declaration
     */
    size_t i = 0;
    for (i = 0; i < len; i++) {
        temp[i] = sentence[i];
    }
    temp[len] = '\0';

    for (i = 0; i < len; i++) {
        temp[i] = (char)tolower((unsigned char)temp[i]);
    }

    char *saveptr;
    char *token = strtok_r(temp, " ,.!?;:()\t\n\"'", &saveptr);
    
    while (token != NULL && adverb_count < max_adverbs) {
        if (is_adverb(token)) {
            int found = -1;
            /* Possible weaknesses found:
             *  Shadow variable
             *  Local variable 'i' shadows outer variable [shadowVariable]
             */
            for (int i = 0; i < adverb_count; i++) {
                int match = 1;
                int j = 0;
                while (token[j] != '\0' && adverbs[i].word[j] != '\0') {
                    if (token[j] != adverbs[i].word[j]) {
                        match = 0;
                        break;
                    }
                    j++;
                }
                if (match && token[j] == '\0' && adverbs[i].word[j] == '\0') {
                    found = i;
                    break;
                }
            }
            
            if (found == -1) {
                size_t token_len = 0;
                while (token[token_len] != '\0') {
                    token_len++;
                }
                
                size_t copy_len = token_len < (size_t)(MAX_WORD_LEN - 1) 
                                  /* Possible weaknesses found:
                                   *  Assignment 'copy_len=token_len<(unsigned long)(50-1)?token_len:(unsigned long)(50-1)', assigned value is less than 1
                                   */
                                  ? token_len : (size_t)(MAX_WORD_LEN - 1);
                
                /* Possible weaknesses found:
                 *  Condition 'k<copy_len' is always false [knownConditionTrueFalse]
                 *  Condition 'k<copy_len' is always false
                 */
                for (size_t k = 0; k < copy_len; k++) {
                    adverbs[adverb_count].word[k] = token[k];
                }
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