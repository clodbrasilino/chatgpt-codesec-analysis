#include <stdio.h>
#include <string.h>

int contains_z(const char *word)
{
    return word != NULL && strchr(word, 'z') != NULL;
}

int main(void)
{
    char word[256];

    if (fgets(word, sizeof word, stdin) == NULL) {
        if (ferror(stdin)) {
            return 1;
        }
        return 0;
    }

    word[strcspn(word, "\r\n")] = '\0';

    if (contains_z(word)) {
        puts("Match");
    } else {
        puts("No match");
    }

    return 0;
}