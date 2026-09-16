#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool word_contains_z(const char *word)
{
    return word != NULL &&
           (strchr(word, 'z') != NULL || strchr(word, 'Z') != NULL);
}

int main(int argc, char * const argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <word>\n", argv[0]);
        return 2;
    }

    if (word_contains_z(argv[1])) {
        puts("match");
        return 0;
    }

    puts("no match");
    return 1;
}