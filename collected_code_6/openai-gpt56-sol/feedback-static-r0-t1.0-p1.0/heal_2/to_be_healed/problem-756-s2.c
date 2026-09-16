#include <stdio.h>
#include <string.h>

static int matches(const char *str)
{
    if (str == NULL) {
        return 0;
    }

    return strcmp(str, "a") == 0 || strcmp(str, "ab") == 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    int result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    result = matches(argv[1]);
    printf("%s\n", result ? "Match" : "No match");

    return result ? 0 : 2;
}