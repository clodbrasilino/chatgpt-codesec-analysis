#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool is_concatenation(const char *string, size_t length)
{
    if (string == NULL || length < 2U) {
        return false;
    }

    for (size_t unit_length = 1U; unit_length <= length / 2U; ++unit_length) {
        if (length % unit_length != 0U) {
            continue;
        }

        bool matches = true;

        for (size_t i = unit_length; i < length; ++i) {
            if (string[i] != string[i % unit_length]) {
                matches = false;
                break;
            }
        }

        if (matches) {
            return true;
        }
    }

    return false;
}

int main(int argc, char *const argv[])
{
    if (argc != 2) {
        const char *program_name = argc > 0 && argv[0] != NULL ? argv[0] : "program";
        fprintf(stderr, "Usage: %s <string>\n", program_name);
        return 1;
    }

    const char *string = argv[1];
    size_t length = strlen(string);

    printf("%s\n", is_concatenation(string, length) ? "true" : "false");
    return 0;
}