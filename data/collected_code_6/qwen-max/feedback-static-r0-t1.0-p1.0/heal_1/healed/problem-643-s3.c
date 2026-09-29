#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool contains_z_not_at_edges(const char *word, size_t len) {
    for (size_t i = 1; i < len - 1; ++i) {
        if (word[i] == 'z') {
            return true;
        }
    }
    return false;
}

int main() {
    char word[80];
    printf("Enter a word: ");
    if (scanf("%79s", word) != 1) {
        return 1;
    }

    size_t len = strlen(word);
    if (contains_z_not_at_edges(word, len)) {
        printf("The word contains 'z' not at the start or end.\n");
    } else {
        printf("The word does not contain 'z' not at the start or end.\n");
    }

    return 0;
}