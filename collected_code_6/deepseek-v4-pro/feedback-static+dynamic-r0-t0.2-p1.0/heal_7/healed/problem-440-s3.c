#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ADVERBS 100
#define MAX_WORD_LEN 50
#define MAX_TEXT_LEN 4096

typedef struct {
    char word[MAX_WORD_LEN];
    int position;
} AdverbInfo;

static const char *adverb_list[] = {
    "quickly", "slowly", "carefully", "badly", "well", "fast", "hard",
    "late", "early", "easily", "happily", "sadly", "loudly", "quietly",
    "gently", "suddenly", "always", "never", "often", "sometimes",
    "usually", "rarely", "very", "too", "quite", "almost", "just",
    "only", "really", "certainly", "probably", "perhaps", "maybe",
    "already", "yet", "still", "even", "ever", "again", "once",
    "twice", "here", "there", "everywhere", "nowhere", "somewhere",
    "inside", "outside", "upstairs", "downstairs", "abroad", "away",
    "back", "down", "up", "in", "out", "on", "off", "over", "under",
    "above", "below", "near", "far", "together", "apart", "alone",
    "indeed", "obviously", "clearly", "apparently", "fortunately",
    "unfortunately", "honestly", "frankly", "seriously", "literally",
    "actually", "basically", "definitely", "absolutely", "completely",
    "totally", "extremely", "highly", "deeply", "fully", "greatly",
    "hardly", "scarcely", "barely", "merely", "simply", "solely",
    "mainly", "mostly", "particularly", "especially", "specifically",
    "generally", "typically", "normally", "usually", "regularly",
    "constantly", "continuously", "frequently", "occasionally",
    "rarely", "seldom", "never", "always", "forever",
    "briefly", "shortly", "temporarily", "permanently", "instantly",
    "immediately", "soon", "later", "eventually", "finally", "firstly",
    "secondly", "thirdly", "lastly", "next", "then", "previously",
    "recently", "lately", "currently", "presently", "nowadays",
    "today", "tomorrow", "yesterday", "tonight", "now",
    "afterwards", "beforehand", "meanwhile", "simultaneously",
    "consequently", "therefore", "thus", "hence", "accordingly",
    "otherwise", "instead", "however", "nevertheless", "nonetheless",
    "regardless", "anyway", "anyhow", "besides", "furthermore",
    "moreover", "additionally", "similarly", "likewise", "equally",
    "comparatively", "relatively", "absolutely", "utterly", "entirely",
    "wholly", "partially", "partly", "somewhat", "rather", "fairly",
    "pretty", "moderately", "slightly", "marginally", "considerably",
    "substantially", "significantly", "dramatically", "sharply",
    "steeply", "gradually", "steadily", "progressively", "increasingly",
    "decreasingly", "rapidly", "swiftly", "promptly", "speedily",
    "hurriedly", "leisurely", "calmly", "peacefully", "patiently",
    "impatiently", "eagerly", "enthusiastically", "reluctantly",
    "willingly", "voluntarily", "involuntarily", "deliberately",
    "intentionally", "accidentally", "unintentionally", "purposely",
    "consciously", "unconsciously", "instinctively", "automatically",
    "mechanically", "manually", "electronically", "digitally",
    "physically", "mentally", "emotionally", "spiritually", "morally",
    "ethically", "legally", "illegally", "politically", "economically",
    "socially", "culturally", "historically", "geographically",
    "locally", "nationally", "internationally", "globally", "universally",
    "individually", "collectively", "jointly", "separately", "independently",
    "dependently", "mutually", "reciprocally", "respectively", "alternatively",
    "conversely", "inversely", "directly", "indirectly", "straight",
    "straightforwardly", "diagonally", "vertically", "horizontally",
    "perpendicularly", "parallel", "clockwise", "counterclockwise",
    "anticlockwise", "forward", "backward", "sideways", "lengthwise",
    "widthwise", "crosswise", "edgewise", "otherwise", "likewise",
    "northward", "southward", "eastward", "westward", "northwards",
    "southwards", "eastwards", "westwards", "homeward", "homewards",
    "onward", "onwards", "upward", "upwards", "downward", "downwards",
    "inward", "inwards", "outward", "outwards", "forwards",
    "backwards", "leftward", "leftwards", "rightward", "rightwards",
    "hardly ever"
};

static int adverb_count = sizeof(adverb_list) / sizeof(adverb_list[0]);

static int is_adverb(const char *word) {
    for (int i = 0; i < adverb_count; i++) {
        if (strcasecmp(word, adverb_list[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

static void find_adverbs(const char *text, AdverbInfo *adverbs, int *count) {
    char *text_copy;
    char *word;
    int position = 0;
    
    text_copy = (char *)malloc(strlen(text) + 1);
    if (text_copy == NULL) {
        return;
    }
    strcpy(text_copy, text);
    
    word = strtok(text_copy, " \t\n\r.,;:!?\"'()[]{}");
    
    while (word != NULL && *count < MAX_ADVERBS) {
        int word_length = strlen(word);
        
        if (is_adverb(word)) {
            strncpy(adverbs[*count].word, word, MAX_WORD_LEN - 1);
            adverbs[*count].word[MAX_WORD_LEN - 1] = '\0';
            adverbs[*count].position = position;
            (*count)++;
        }
        
        word = strtok(NULL, " \t\n\r.,;:!?\"'()[]{}");
        if (word != NULL) {
            position += word_length + 1;
        }
    }
    
    free(text_copy);
}

int main(void) {
    char text[MAX_TEXT_LEN];
    AdverbInfo adverbs[MAX_ADVERBS];
    int count = 0;
    
    printf("Enter a sentence: ");
    
    if (fgets(text, sizeof(text), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }
    
    text[strcspn(text, "\n")] = '\0';
    
    find_adverbs(text, adverbs, &count);
    
    printf("Found %d adverb(s):\n", count);
    for (int i = 0; i < count; i++) {
        printf("  %s (position %d)\n", adverbs[i].word, adverbs[i].position);
    }
    
    return 0;
}