#include <stdio.h>
#include <string.h>

static int matches(const char *string)
{
    size_t length;

    if (string == NULL) {
        return 0;
    }

    length = strlen(string);

    return length == 1U ? string[0] == 'a'
                        : length == 2U && string[0] == 'a' && string[1] == 'b';
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    if (argc != 2) {
        if (fprintf(stderr, "Usage: %s <string>\n", argv[0]) < 0) {
            return 2;
        }
        return 1;
    }

    if (printf("%s\n", matches(argv[1]) ? "match" : "no match") < 0) {
        return 2;
    }

    return 0;
}