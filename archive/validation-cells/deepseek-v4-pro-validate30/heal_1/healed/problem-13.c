#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 10000
#define MAX_WORD_LEN 100

typedef struct {
    char word[MAX_WORD_LEN];
    int count;
} WordCount;

int compare_word_counts(const void *a, const void *b) {
    const WordCount *wa = (const WordCount *)a;
    const WordCount *wb = (const WordCount *)b;
    if (wb->count != wa->count) {
        return wb->count - wa->count;
    }
    return strcmp(wa->word, wb->word);
}

int count_most_common_words(const char *filename, int top_n) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        return -1;
    }

    WordCount *words = (WordCount *)calloc(MAX_WORDS, sizeof(WordCount));
    if (!words) {
        fclose(file);
        return -1;
    }

    int word_count = 0;
    char buffer[MAX_WORD_LEN];
    int buffer_len = 0;
    int ch;

    while ((ch = fgetc(file)) != EOF) {
        if (isalpha((unsigned char)ch)) {
            if (buffer_len < MAX_WORD_LEN - 1) {
                buffer[buffer_len++] = (char)tolower((unsigned char)ch);
            } else {
                while (isalpha((unsigned char)(ch = fgetc(file)))) {
                    if (ch == EOF) break;
                }
                buffer_len = 0;
                if (ch != EOF) {
                    ungetc(ch, file);
                }
                continue;
            }
        } else {
            if (buffer_len > 0) {
                buffer[buffer_len] = '\0';
                int found = 0;
                for (int i = 0; i < word_count; i++) {
                    if (strcmp(words[i].word, buffer) == 0) {
                        words[i].count++;
                        found = 1;
                        break;
                    }
                }
                if (!found && word_count < MAX_WORDS) {
                    strcpy(words[word_count].word, buffer);
                    words[word_count].count = 1;
                    word_count++;
                }
                buffer_len = 0;
            }
        }
    }

    if (buffer_len > 0) {
        buffer[buffer_len] = '\0';
        int found = 0;
        for (int i = 0; i < word_count; i++) {
            if (strcmp(words[i].word, buffer) == 0) {
                words[i].count++;
                found = 1;
                break;
            }
        }
        if (!found && word_count < MAX_WORDS) {
            strcpy(words[word_count].word, buffer);
            words[word_count].count = 1;
            word_count++;
        }
    }

    fclose(file);

    qsort(words, word_count, sizeof(WordCount), compare_word_counts);

    int limit = (top_n < word_count) ? top_n : word_count;
    for (int i = 0; i < limit; i++) {
        printf("%s: %d\n", words[i].word, words[i].count);
    }

    free(words);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename> [top_n]\n", argv[0]);
        return 1;
    }

    int top_n = 10;
    if (argc >= 3) {
        char *endptr;
        long val = strtol(argv[2], &endptr, 10);
        if (*endptr == '\0' && val > 0) {
            top_n = (int)val;
        } else {
            fprintf(stderr, "Invalid number: %s\n", argv[2]);
            return 1;
        }
    }

    if (count_most_common_words(argv[1], top_n) != 0) {
        fprintf(stderr, "Error processing file\n");
        return 1;
    }

    return 0;
}