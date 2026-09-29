#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool is_concatenation(const char *string)
{
    size_t length;

    if (string == NULL) {
        return false;
    }

    length = strlen(string);
    if (length < 2U) {
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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    printf("%s\n", is_concatenation(argv[1]) ? "true" : "false");
    return 0;
}