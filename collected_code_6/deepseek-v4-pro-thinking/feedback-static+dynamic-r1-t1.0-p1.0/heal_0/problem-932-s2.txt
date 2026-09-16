#include <stdio.h>
#include <string.h>

int remove_duplicate_words(char **words, int count) {
    int unique_count = 0;
    int i;
    int j;

    if (words == NULL || count <= 0) {
        return 0;
    }

    for (i = 0; i < count; ++i) {
        int duplicate = 0;

        for (j = 0; j < unique_count; ++j) {
            if (strcmp(words[j], words[i]) == 0) {
                duplicate = 1;
                break;
            }
        }

        if (!duplicate) {
            words[unique_count] = words[i];
            ++unique_count;
        }
    }

    return unique_count;
}

int main(void) {
    char *words[] = {"one", "two", "one", "three", "two", "four"};
    int count = (int)(sizeof(words) / sizeof(words[0]));
    int unique_count;
    int i;

    unique_count = remove_duplicate_words(words, count);

    for (i = 0; i < unique_count; ++i) {
        printf("%s\n", words[i]);
    }

    return 0;
}