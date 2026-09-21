#include <stdbool.h>
#include <stdio.h>

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
static bool matches_pattern(const char string[static 1])
{
    const char *end = string;

    while (*end != '\0') {
        ++end;
    }

    return (end - string) >= 2 && string[0] == 'a' && end[-1] == 'b';
}

int main(int argc, char *const argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n",
                (argc > 0 && argv[0] != NULL) ? argv[0] : "program");
        return 1;
    }

    puts(matches_pattern(argv[1]) ? "Match" : "No match");

    return 0;
}