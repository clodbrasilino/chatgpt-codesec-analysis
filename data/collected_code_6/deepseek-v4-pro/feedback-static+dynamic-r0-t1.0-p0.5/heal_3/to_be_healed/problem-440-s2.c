#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 100
#define MAX_WORD_LEN 50
#define MAX_ADVERBS 50
#define MAX_SENTENCE_LEN 1000

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[MAX_WORD_LEN];
    int position;
} AdverbInfo;

static int is_adverb(const char *word) {
    size_t len;
    
    if (word == NULL) return 0;
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(word);
    /* Possible weaknesses found:
     *  Assuming condition 'len<2' is false
     */
    if (len < 2 || len >= MAX_WORD_LEN) return 0;
    
    /* Possible weaknesses found:
     *  Condition 'len>=2' is always true
     *  Condition 'len>=2' is always true [knownConditionTrueFalse]
     */
    if (len >= 2 && strcmp(word + len - 2, "ly") == 0) return 1;
    
    static const char *irregular[] = {
        "well", "fast", "hard", "late", "early", "daily", "weekly",
        "monthly", "yearly", "always", "never", "often", "seldom",
        "sometimes", "usually", "already", "yet", "still", "just",
        "soon", "now", "then", "here", "there", "everywhere",
        "nowhere", "somewhere", "quite", "rather", "very", "too",
        "almost", "enough", "indeed", "perhaps", "maybe", "certainly",
        "definitely", "probably", "possibly", "absolutely", "completely",
        "entirely", "extremely", "fairly", "highly", "really", "slightly",
        "totally", "utterly", "wholly", "badly", "carefully", "easily",
        "happily", "loudly", "quickly", "quietly", "sadly", "slowly",
        "softly", "suddenly", "angrily", "calmly", "gently", "politely",
        "rudely", "seriously", "sharply", "smoothly", "strongly", "weakly",
        NULL
    };
    
    for (int i = 0; irregular[i] != NULL; i++) {
        if (strcmp(word, irregular[i]) == 0) return 1;
    }
    
    return 0;
}

static int find_adverbs(const char *sentence, AdverbInfo *adverbs, int max_adverbs) {
    if (sentence == NULL || adverbs == NULL || max_adverbs <= 0) return 0;
    
    int count = 0;
    int pos = 0;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[MAX_WORD_LEN];
    int word_len = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(sentence);
    
    for (size_t i = 0; i <= len; i++) {
        if (i < len && isalpha((unsigned char)sentence[i])) {
            if (word_len < MAX_WORD_LEN - 1) {
                word[word_len++] = (char)tolower((unsigned char)sentence[i]);
            }
        } else {
            if (word_len > 0) {
                word[word_len] = '\0';
                if (is_adverb(word) && count < max_adverbs) {
                    /* Possible weaknesses found:
                     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                     */
                    strncpy(adverbs[count].word, word, MAX_WORD_LEN - 1);
                    adverbs[count].word[MAX_WORD_LEN - 1] = '\0';
                    adverbs[count].position = pos;
                    count++;
                }
                word_len = 0;
            }
            if (i < len && (sentence[i] == ' ' || sentence[i] == '\t' || sentence[i] == '\n')) {
                pos = (int)(i + 1);
            }
        }
    }
    
    return count;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char sentence[MAX_SENTENCE_LEN];
    AdverbInfo adverbs[MAX_ADVERBS];
    
    printf("Enter a sentence: ");
    if (fgets(sentence, sizeof(sentence), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    sentence[strcspn(sentence, "\n")] = '\0';
    
    int count = find_adverbs(sentence, adverbs, MAX_ADVERBS);
    
    if (count == 0) {
        printf("No adverbs found.\n");
    } else {
        printf("Adverbs found:\n");
        for (int i = 0; i < count; i++) {
            printf("  '%s' at position %d\n", adverbs[i].word, adverbs[i].position);
        }
    }
    
    return 0;
}