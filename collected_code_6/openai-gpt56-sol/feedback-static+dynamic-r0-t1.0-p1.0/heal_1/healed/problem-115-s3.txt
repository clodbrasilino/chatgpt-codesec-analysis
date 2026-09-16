#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

typedef struct {
    size_t entry_count;
} Dictionary;

bool all_dictionaries_empty(const Dictionary *dictionaries, size_t count)
{
    if (count == 0U) {
        return true;
    }

    if (dictionaries == NULL) {
        return false;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (dictionaries[i].entry_count != 0U) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    const Dictionary dictionaries[] = {
        {0U},
        {0U},
        {0U}
    };
    const size_t count = sizeof dictionaries / sizeof dictionaries[0];

    const char *message = all_dictionaries_empty(dictionaries, count)
        ? "All dictionaries are empty."
        : "Not all dictionaries are empty.";

    return puts(message) == EOF ? 1 : 0;
}