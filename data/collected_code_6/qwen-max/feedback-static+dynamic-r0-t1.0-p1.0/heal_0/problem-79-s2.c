#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_odd_length(const char *word) {
    size_t length = strlen(word);
    return length % 2 != 0;
}

int main() {
    const char *word = "example";
    if (is_odd_length(word)) {
        printf("The word has an odd length.\n");
    } else {
        printf("The word has an even length.\n");
    }
    return 0;
}