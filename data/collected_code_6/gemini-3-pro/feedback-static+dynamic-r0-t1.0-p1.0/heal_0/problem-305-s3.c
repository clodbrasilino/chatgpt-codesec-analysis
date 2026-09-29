#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int match_p_words(char **word_list, int list_size, const char *word1, const char *word2) {
    if (!word_list || !word1 || !word2) {
        return 0;
    }

    if (word1[0] != 'p' && word1[0] != 'P') {
        return 0;
    }
    
    if (word2[0] != 'p' && word2[0] != 'P') {
        return 0;
    }

    int found_word1 = 0;
    int found_word2 = 0;

    for (int i = 0; i < list_size; i++) {
        if (word_list[i] == NULL) {
            continue;
        }
        
        if (!found_word1 && strcmp(word_list[i], word1) == 0) {
            found_word1 = 1;
        }
        if (!found_word2 && strcmp(word_list[i], word2) == 0) {
            found_word2 = 1;
        }

        if (found_word1 && found_word2) {
            return 1;
        }
    }

    return 0;
}

int main(void) {
    char *words[] = {
        "apple",
        "pear",
        "peach",
        "banana",
        "plum",
        "pineapple"
    };
    int num_words = sizeof(words) / sizeof(words[0]);

    const char *target1 = "peach";
    const char *target2 = "plum";

    int result = match_p_words(words, num_words, target1, target2);

    if (result) {
        printf("Both words found.\n");
    } else {
        printf("Words not found or do not start with 'p'.\n");
    }

    return 0;
}