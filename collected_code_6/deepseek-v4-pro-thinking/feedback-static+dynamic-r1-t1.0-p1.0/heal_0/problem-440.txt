#include <stdio.h>
#include <ctype.h>

static int is_adverb_word(const char *word, int length) {
    if (length < 2) {
        return 0;
    }
    return word[length - 2] == 'l' && word[length - 1] == 'y';
}

int find_adverbs(const char *sentence) {
    int i = 0;
    int count = 0;

    if (sentence == NULL) {
        return 0;
    }

    while (sentence[i] != '\0') {
        int start;
        int length;

        while (sentence[i] != '\0' && !isalpha((unsigned char)sentence[i])) {
            i++;
        }

        if (sentence[i] == '\0') {
            break;
        }

        start = i;

        while (sentence[i] != '\0' && isalpha((unsigned char)sentence[i])) {
            i++;
        }

        length = i - start;

        if (is_adverb_word(sentence + start, length)) {
            printf("Adverb: %.*s at position %d\n", length, sentence + start, start);
            count++;
        }
    }

    return count;
}

int main(void) {
    const char *text = "She quickly ran very slowly and happily.";
    int total = find_adverbs(text);
    printf("Total adverbs: %d\n", total);
    return 0;
}