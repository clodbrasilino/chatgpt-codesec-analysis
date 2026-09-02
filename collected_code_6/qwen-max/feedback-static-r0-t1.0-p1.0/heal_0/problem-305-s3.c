#include <stdio.h>
#include <string.h>

int match_words(char *list[], int size, char start_letter) {
    for (int i = 0; i < size; i++) {
        if (strlen(list[i]) > 0 && list[i][0] == start_letter) {
            for (int j = i + 1; j < size; j++) {
                if (strlen(list[j]) > 0 && list[j][0] == start_letter) {
                    printf("Match: %s and %s\n", list[i], list[j]);
                    return 1;
                }
            }
        }
    }
    return 0;
}

int main() {
    char *words[] = {"apple", "banana", "peach", "pear", "plum", "orange"};
    int count = sizeof(words) / sizeof(words[0]);

    if (match_words(words, count, 'p')) {
        printf("Words matching the criteria found.\n");
    } else {
        printf("No words matching the criteria found.\n");
    }

    return 0;
}