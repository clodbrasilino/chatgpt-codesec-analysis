#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const void *head;
} Dictionary;

static bool all_dictionaries_empty(const Dictionary *dictionaries, size_t count)
{
    if (count > 0U && dictionaries == NULL) {
        return false;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (dictionaries[i].head != NULL) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    static const Dictionary dictionaries[] = {
        { .head = NULL },
        { .head = NULL },
        { .head = NULL }
    };

    const size_t dictionary_count =
        sizeof dictionaries / sizeof dictionaries[0];

    if (puts(all_dictionaries_empty(dictionaries, dictionary_count)
                 ? "All dictionaries are empty."
                 : "At least one dictionary is not empty.") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}