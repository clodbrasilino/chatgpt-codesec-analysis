#include <ctype.h>
#include <stdio.h>

void remove_non_alphanumeric(char *string)
{
    unsigned char *source;
    char *destination;

    if (string == NULL) {
        return;
    }

    source = (unsigned char *)string;
    destination = string;

    while (*source != '\0') {
        if (isalnum(*source) != 0) {
            *destination++ = (char)*source;
        }
        ++source;
    }

    *destination = '\0';
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin) != 0) {
            return 1;
        }
        return 0;
    }

    remove_non_alphanumeric(input);

    if (printf("%s\n", input) < 0) {
        return 1;
    }

    return 0;
}