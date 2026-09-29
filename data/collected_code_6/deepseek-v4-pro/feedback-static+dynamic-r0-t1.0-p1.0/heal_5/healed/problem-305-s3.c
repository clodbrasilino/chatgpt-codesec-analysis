#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORDS 100
#define MAX_WORD_LEN 50

int match_p_words(const char *word1, const char *word2) {
    if (word1 == NULL || word2 == NULL) {
        return 0;
    }
    if (word1[0] != 'p' && word1[0] != 'P') {
        return 0;
    }
    if (word2[0] != 'p' && word2[0] != 'P') {
        return 0;
    }
    return strcmp(word1, word2) == 0;
}

int main(void) {
    char **words = NULL;
    int word_count = 0;
    char *input = NULL;
    size_t input_size = 0;
    int i;
    int found = 0;
    size_t len;

    words = malloc(MAX_WORDS * sizeof(char *));
    if (words == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (i = 0; i < MAX_WORDS; i++) {
        words[i] = NULL;
    }

    printf("Enter words starting with 'p' (type 'end' to finish):\n");

    while (word_count < MAX_WORDS) {
        ssize_t read = getline(&input, &input_size, stdin);
        if (read == -1) {
            break;
        }

        if (read > 0 && input[read - 1] == '\n') {
            input[read - 1] = '\0';
            read--;
        }

        if (read == 0) {
            continue;
        }

        if (strcmp(input, "end") == 0) {
            break;
        }

        if (input[0] != 'p' && input[0] != 'P') {
            printf("Word must start with 'p'. Try again.\n");
            continue;
        }

        len = (size_t)read;
        if (len > MAX_WORD_LEN) {
            len = MAX_WORD_LEN;
        }

        words[word_count] = malloc(len + 1);
        if (words[word_count] == NULL) {
            printf("Memory allocation failed.\n");
            break;
        }

        if (len <= (size_t)read) {
            memcpy(words[word_count], input, len);
        }
        words[word_count][len] = '\0';
        word_count++;
    }

    free(input);

    if (word_count < 2) {
        printf("Not enough words to compare.\n");
        for (i = 0; i < word_count; i++) {
            free(words[i]);
        }
        free(words);
        return 1;
    }

    printf("\nMatching pairs of words starting with 'p':\n");
    for (i = 0; i < word_count - 1; i++) {
        int j;
        for (j = i + 1; j < word_count; j++) {
            if (match_p_words(words[i], words[j])) {
                printf("%s and %s match\n", words[i], words[j]);
                found = 1;
            }
        }
    }

    if (!found) {
        printf("No matching pairs found.\n");
    }

    for (i = 0; i < word_count; i++) {
        free(words[i]);
    }
    free(words);

    return 0;
}