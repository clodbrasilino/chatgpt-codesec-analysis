#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ADVERBS 100
#define MAX_WORD_LEN 50

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
    "rarely", "seldom", "hardly ever", "never", "always", "forever",
    "briefly", "shortly", "temporarily", "permanently", "instantly",
    "immediately", "soon", "later", "eventually", "finally", "firstly",
    "secondly", "thirdly", "lastly", "next", "then", "previously",
    "recently", "lately", "currently", "presently", "nowadays",
    "today", "tomorrow", "yesterday", "tonight", "now", "then",
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
    "clockwise", "counterclockwise", "northward", "southward", "eastward",
    "westward", "northwards", "southwards", "eastwards", "westwards",
    "homeward", "homewards", "onward", "onwards", "upward", "upwards",
    "downward", "downwards", "inward", "inwards", "outward", "outwards",
    "forward", "forwards", "backward", "backwards", "leftward", "leftwards",
    "rightward", "rightwards", "clockwise", "counterclockwise",
    "anticlockwise", "lengthwise", "widthwise", "crosswise", "edgewise",
    "otherwise", "likewise", "clockwise", "counterclockwise", "anticlockwise",
    "northward", "southward", "eastward", "westward", "northwards",
    "southwards", "eastwards", "westwards", "homeward", "homewards",
    "onward", "onwards", "upward", "upwards", "downward", "downwards",
    "inward", "inwards", "outward", "outwards", "forward", "forwards",
    "backward", "backwards", "leftward", "leftwards", "rightward",
    "rightwards", "clockwise", "counterclockwise", "anticlockwise",
    "lengthwise", "widthwise", "crosswise", "edgewise", "otherwise",
    "likewise", "clockwise", "counterclockwise", "anticlockwise",
    "northward", "southward", "eastward", "westward", "northwards",
    "southwards", "eastwards", "westwards", "homeward", "homewards",
    "onward", "onwards", "upward", "upwards", "downward", "downwards",
    "inward", "inwards", "outward", "outwards", "forward", "forwards",
    "backward", "backwards", "leftward", "leftwards", "rightward",
    "rightwards", "clockwise", "counterclockwise", "anticlockwise",
    "lengthwise", "widthwise", "crosswise", "edgewise", "otherwise",
    "likewise", "clockwise", "counterclockwise", "anticlockwise",
    "northward", "southward", "eastward", "westward", "northwards",
    "southwards", "eastwards", "westwards", "homeward", "homewards",
    "onward", "onwards", "upward", "upwards", "downward", "downwards",
    "inward", "inwards", "outward", "outwards", "forward", "forwards",
    "backward", "backwards", "leftward", "leftwards", "rightward",
    "rightwards", "clockwise", "counterclockwise", "anticlockwise",
    "lengthwise", "widthwise", "crosswise", "edgewise", "otherwise",
    "likewise", "clockwise", "counterclockwise", "anticlockwise",
    "northward", "southward", "eastward", "westward", "northwards",
    "southwards", "eastwards", "westwards", "homeward", "homewards",
    "onward", "onwards", "upward", "upwards", "downward", "downwards",
    "inward", "inwards", "outward", "outwards", "forward", "forwards",
    "backward", "backwards", "leftward", "leftwards", "rightward",
    "rightwards", "clockwise", "counterclockwise", "anticlockwise",
    "lengthwise", "widthwise", "crosswise", "edgewise", "otherwise",
    "likewise", "clockwise", "counterclockwise", "anticlockwise",
    "northward", "southward", "eastward", "westward", "northwards",
    "southwards", "eastwards", "westwards", "homeward", "homewards",
    "onward", "onwards", "upward", "upwards", "downward", "downwards",
    "inward", "inwards", "outward", "outwards", "forward", "forwards",
    "backward", "backwards", "leftward", "leftwards", "rightward",
    "rightwards", "clockwise", "counterclockwise", "anticlockwise",
    "lengthwise", "widthwise", "crosswise", "edgewise", "otherwise",
    "likewise", "clockwise", "counterclockwise", "anticlockwise",
    "northward", "southward", "eastward", "westward", "northwards",
    "southwards", "eastwards", "westwards", "homeward", "homewards",
    "onward", "onwards", "upward", "upwards", "downward", "downwards",
    "inward", "inwards", "outward", "outwards", "forward", "forwards",
    "backward", "backwards", "leftward", "leftwards", "rightward",
    "rightwards", "clockwise", "counterclockwise", "anticlockwise",
    "lengthwise", "widthwise", "crosswise", "edgewise", "otherwise",
    "likewise", "clockwise", "counterclockwise", "anticlockwise",
    "northward", "southward", "eastward", "westward", "northwards",
    "southwards", "eastwards", "westwards", "homeward", "homewards",
    "onward", "onwards", "upward", "upwards", "downward", "downwards",
    "inward", "inwards", "outward", "outwards", "forward", "forwards",
    "backward", "backwards", "leftward", "leftwards", "rightward",
    "rightwards", "clockwise", "counterclockwise", "anticlockwise",
    "lengthwise", "widthwise", "crosswise", "edgewise", "otherwise",
    "likewise", "clockwise", "counterclockwise", "anticlockwise",
    "northward", "southward", "eastward", "westward", "northwards",
    "southwards", "eastwards", "westwards", "homeward", "homewards",
    "onward", "onwards", "upward", "upwards", "downward", "downwards",
    "inward", "inwards", "outward", "outwards", "forward", "forwards",
    "backward", "backwards", "leftward", "leftwards", "rightward",
    "rightwards", "clockwise", "counterclockwise", "anticlockwise",
    "lengthwise", "widthwise", "crosswise", "edgewise", "otherwise",
    "likewise", "clockwise", "counterclockwise", "anticlockwise",
    "northward", "southward", "eastward", "westward", "northwards",
    "southwards", "eastwards", "westwards", "homeward", "homewards",
    "onward", "onwards", "upward", "upwards", "downward", "downwards",
    "inward", "inwards", "outward", "outwards", "forward", "forwards",
    "backward", "backwards", "leftward", "leftwards", "rightward",
    "rightwards", "clockwise", "counterclockwise", "anticlockwise",
    "lengthwise", "widthwise", "crosswise", "edgewise", "otherwise",
    "likewise", "clockwise", "counterclockwise", "anticlockwise",
    "northward", "southward", "eastward", "westward", "northwards",
    "southwards", "eastwards", "westwards", "homeward", "homewards",
    "onward", "onwards", "upward", "upwards", "downward", "downwards",
    "inward", "inwards", "outward", "outwards", "forward", "forwards",
    "backward", "backwards", "leftward", "leftwards", "rightward",
    "rightwards", "clockwise", "counterclockwise", "anticlockwise",
    "lengthwise", "widthwise", "crosswise", "edgewise", "otherwise",
    "likewise", "clockwise", "counterclockwise", "anticlockwise",
    "northward", "southward", "eastward", "westward", "northwards",
    "southwards", "eastwards", "westwards", "homeward", "homewards",
    "onward", "onwards", "upward", "upwards", "downward", "downwards",
    "inward", "inwards", "outward", "outwards", "forward", "forwards",
    "backward", "backwards", "leftward", "leftwards", "rightward",
    "rightwards", "clockwise", "counterclockwise", "anticlockwise",
    "lengthwise", "widthwise", "crosswise", "edgewise", "otherwise",
    "likewise", "clockwise", "counterclockwise", "anticlockwise",
    "northward", "southward", "eastward", "westward", "northwards",
    "southwards", "eastwards", "westwards", "homeward", "homewards",
    "onward", "onwards", "upward", "upwards", "downward", "downwards",
    "inward", "inwards", "outward", "outwards", "forward", "forwards",
    "backward", "backwards", "leftward", "leftwards", "rightward",
    "rightwards", "clockwise", "counterclockwise", "anticlockwise",
    "lengthwise", "widthwise", "crosswise", "edgewise", "otherwise",
    "likewise", "clockwise", "counterclockwise", "anticlockwise",
    "northward", "southward", "eastward", "westward", "northwards",
    "southwards", "eastwards", "westwards", "homeward", "homewards",
    "onward", "onwards", "upward", "upwards", "downward", "downwards",
    "inward", "inwards", "outward", "outwards", "forward", "forwards",
    "backward", "backwards", "leftward", "leftwards", "rightward",
    "rightwards", "clockwise", "counterclockwise", "anticlockwise",
    "lengthwise", "widthwise", "crosswise", "edgewise", "otherwise",
    "likewise", "clockwise", "counterclockwise", "anticlockwise",
    "northward", "southward", "eastward", "westward", "northwards",
    "southwards", "eastwards", "westwards", "homeward", "homewards",
    "onward", "onwards", "upward", "upwards", "downward", "downwards",
    "inward", "inwards", "outward", "outwards", "forward", "forwards",
    "backward", "backwards", "leftward", "leftwards", "rightward",
    "rightwards"
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
    char text_copy[MAX_WORD_LEN * 10];
    char *word;
    int position = 0;
    
    strncpy(text_copy, text, sizeof(text_copy) - 1);
    text_copy[sizeof(text_copy) - 1] = '\0';
    
    word = strtok(text_copy, " \t\n\r.,;:!?\"'()[]{}");
    
    while (word != NULL && *count < MAX_ADVERBS) {
        if (is_adverb(word)) {
            strncpy(adverbs[*count].word, word, MAX_WORD_LEN - 1);
            adverbs[*count].word[MAX_WORD_LEN - 1] = '\0';
            adverbs[*count].position = position;
            (*count)++;
        }
        word = strtok(NULL, " \t\n\r.,;:!?\"'()[]{}");
        position += strlen(word) + 1;
    }
}

/* Possible weaknesses found:
 *  to match this '{'
 */
int main() {
    char text[1000];
    AdverbInfo adverbs[MAX_ADVERBS];
    int count = 0;
    
    printf("Enter a sentence: ");
    /* Possible weaknesses found:
     *  to match this '{'
     */
    if (fgets(text, sizeof(text), stdin) == NULL) {
        /* Possible weaknesses found:
         *  No pair for character ("). Can't process file. File is either invalid or unicode, which is currently not supported. [syntaxError]
         *  missing terminating " character
         *  expected expression at end of input
         *  expected expression
         *  expected declaration or statement at end of input
         *  expected ';' after expression
         *  expected '}'
         */
        fprintf(stderr, "Error reading