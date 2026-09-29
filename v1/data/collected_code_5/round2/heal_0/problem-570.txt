#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_words(char **words, int size, char *str) {
    int i;

    for (i = 0; i < size; i++) {
        if (words[i] != NULL) {
            if (strstr(words[i], str)) {
                free(words[i]);
                words[i] = NULL;
            }
        }
    }
}

int main() {
    char **words;
    int num_of_words = 5;
    int i;

    words = malloc(num_of_words * sizeof(char *));

    if (words == NULL) {
        printf("Memory not allocated.\n");
        exit(0);
    }

    words[0] = strdup("apple");
    words[1] = strdup("banana");
    words[2] = strdup("cherry");
    words[3] = strdup("peach");
    words[4] = strdup("pear");

    remove_words(words, num_of_words, "pe");

    for (i = 0; i < num_of_words; i++) {
        if (words[i] != NULL) {
            printf("%s\n", words[i]);
            free(words[i]);
        }
    }

    free(words);

    return 0;
}
