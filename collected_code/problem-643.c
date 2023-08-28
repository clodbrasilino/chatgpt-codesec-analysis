#include <stdio.h>
#include <string.h>

int containsZ(char *word) {
    int length = strlen(word);
    if (length < 3) {
        return 0;
    }
    for (int i = 1; i < length - 1; i++) {
        if (word[i] == 'z') {
            return 1;
        }
    }
    return 0;
}

int main() {
    char word1[] = "zebra";
    char word2[] = "aztec";
    char word3[] = "blizzard";
    
    printf("%s: %s\n", word1, containsZ(word1) ? "Match" : "No match");
    printf("%s: %s\n", word2, containsZ(word2) ? "Match" : "No match");
    printf("%s: %s\n", word3, containsZ(word3) ? "Match" : "No match");
    
    return 0;
}