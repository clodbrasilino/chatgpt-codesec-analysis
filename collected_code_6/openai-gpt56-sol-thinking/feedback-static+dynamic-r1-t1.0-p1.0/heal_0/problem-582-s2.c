#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t entry_count;
} Dictionary;

bool dictionary_is_empty(const Dictionary *dictionary)
{
    return dictionary != NULL && dictionary->entry_count == 0U;
}

int main(void)
{
    Dictionary dictionary = {0U};

    if (dictionary_is_empty(&dictionary)) {
        puts("Dictionary is empty.");
    } else {
        puts("Dictionary is not empty.");
    }

    return EXIT_SUCCESS;
}