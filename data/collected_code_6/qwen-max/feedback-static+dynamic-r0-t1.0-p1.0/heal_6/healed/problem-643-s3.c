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
    if (fgets(word, sizeof(word), stdin) != NULL) {
        word[strcspn(word, "\n")] = '\0';
        size_t len = strnlen(word, 80);
        if (len > 0 && contains_z_not_at_edges(word, len)) {
            printf("The word contains 'z' not at the start or end.\n");
        } else {
            printf("The word does not contain 'z' not at the start or end.\n");
        }
    } else {
        return 1;
    }

    return 0;
}