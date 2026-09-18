#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool matchZNotAtStartOrEnd(const char* word) {
    int len = strlen(word);

    for (int i = 1; i < len - 1; i++) {
        if (word[i] == 'z') {
            return true;
        }
    }
    return false;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Invalid input. Please provide a single word as an argument.\n");
        return 1;
    }

    if (matchZNotAtStartOrEnd(argv[1])) {
        printf("The word '%s' contains 'z' and not at the start or end of the word.\n", argv[1]);
    } else {
        printf("The word '%s' either does not contain 'z' or it is at the start or end.\n", argv[1]);
    }

    return 0;
}