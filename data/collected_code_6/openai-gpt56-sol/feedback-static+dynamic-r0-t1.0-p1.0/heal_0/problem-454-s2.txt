#include <stdio.h>
#include <string.h>

static int contains_z(const char *word)
{
    return word != NULL && strchr(word, 'z') != NULL;
}

int main(void)
{
    char word[256];

    if (fgets(word, sizeof(word), stdin) == NULL) {
        if (ferror(stdin)) {
            return 1;
        }
        return 0;
    }

    word[strcspn(word, "\r\n")] = '\0';

    if (contains_z(word)) {
        puts("match");
    } else {
        puts("no match");
    }

    return 0;
}