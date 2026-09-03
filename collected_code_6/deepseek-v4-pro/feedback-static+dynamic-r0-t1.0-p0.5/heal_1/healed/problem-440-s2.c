#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 100
#define MAX_WORD_LEN 50
#define MAX_ADVERBS 50

typedef struct {
    char word[MAX_WORD_LEN];
    int position;
} AdverbInfo;

int is_adverb(const char *word) {
    size_t len = strlen(word);
    
    if (len < 2) return 0;
    
    if (strcmp(word + len - 2, "ly") == 0) {
        if (len >= 3) return 1;
    }
    
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

int find_adverbs(const char *sentence, AdverbInfo *adverbs, int max_adverbs) {
    if (sentence == NULL || adverbs == NULL || max_adverbs <= 0) return 0;
    
    int count = 0;
    int pos = 0;
    char word[MAX_WORD_LEN];
    int word_len = 0;
    size_t len = strlen(sentence);
    
    for (size_t i = 0; i <= len; i++) {
        if (isalpha((unsigned char)sentence[i])) {
            if (word_len < MAX_WORD_LEN - 1) {
                word[word_len++] = tolower((unsigned char)sentence[i]);
            }
        } else {
            if (word_len > 0) {
                word[word_len] = '\0';
                if (is_adverb(word) && count < max_adverbs) {
                    strcpy(adverbs[count].word, word);
                    adverbs[count].position = pos;
                    count++;
                }
                word_len = 0;
            }
            if (sentence[i] == ' ' || sentence[i] == '\t' || sentence[i] == '\n') {
                pos = i + 1;
            }
        }
    }
    
    return count;
}

int main(void) {
    char sentence[1000];
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