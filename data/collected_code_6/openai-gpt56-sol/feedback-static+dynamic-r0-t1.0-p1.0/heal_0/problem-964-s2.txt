#include <stdio.h>
#include <string.h>

static int has_even_length(const char *word)
{
    return word != NULL && strlen(word) % 2U == 0U;
}

int main(void)
{
    char word[256];

    if (fgets(word, sizeof word, stdin) == NULL) {
        return 1;
    }

    word[strcspn(word, "\r\n")] = '\0';

    if (has_even_length(word)) {
        puts("Even");
    } else {
        puts("Odd");
    }

    return 0;
}