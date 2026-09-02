#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct {
    char *adverb;
    int position;
} AdverbInfo;

int is_adverb(const char *word) {
    size_t len = strlen(word);
    if (len > 3 && word[len - 1] == 'y' && word[len - 2] == 'l') {
        return 1;
    }
    return 0;
}

int count_words(const char *sentence) {
    const char *p = sentence;
    int wc = 0;
    while (*p) {
        if (isspace((unsigned char)*p)) {
            p++;
            continue;
        }
        wc++;
        while (*p && !isspace((unsigned char)*p)) {
            p++;
        }
    }
    return wc;
}

AdverbInfo* find_adverbs(const char *sentence, int *count) {
    int num_words = count_words(sentence);
    AdverbInfo *adverbs = (AdverbInfo *)malloc(num_words * sizeof(AdverbInfo));
    if (!adverbs) {
        *count = 0;
        return NULL;
    }

    const char *p = sentence;
    int pos = 0;
    *count = 0;

    while (*p) {
        if (isspace((unsigned char)*p)) {
            p++;
            pos++;
            continue;
        }

        const char *start = p;
        while (*p && !isspace((unsigned char)*p)) {
            p++;
        }

        int len = p - start;
        char *word = (char *)malloc(len + 1);
        if (!word) {
            free(adverbs);
            *count = 0;
            return NULL;
        }
        strncpy(word, start, len);
        word[len] = '\0';

        if (is_adverb(word)) {
            adverbs[*count].adverb = word;
            adverbs[*count].position = pos;
            (*count)++;
        } else {
            free(word);
        }

        pos += len;
    }

    return adverbs;
}

void print_adverbs(AdverbInfo *adverbs, int count) {
    for (int i = 0; i < count; i++) {
        printf("Adverb: %s, Position: %d\n", adverbs[i].adverb, adverbs[i].position);
    }
}

void free_adverbs(AdverbInfo *adverbs, int count) {
    for (int i = 0; i < count; i++) {
        free(adverbs[i].adverb);
    }
    free(adverbs);
}

int main() {
    const char *sentence = "He quickly and quietly walked away";
    int count = 0;
    AdverbInfo *adverbs = find_adverbs(sentence, &count);

    if (adverbs) {
        print_adverbs(adverbs, count);
        free_adverbs(adverbs, count);
    }

    return 0;
}