#include <stdio.h>
#include <string.h>

void remove_multiple_spaces(char *str)
{
    char *read_ptr;
    char *write_ptr;
    int previous_was_space = 0;

    if (str == NULL) {
        return;
    }

    read_ptr = str;
    write_ptr = str;

    while (*read_ptr != '\0') {
        if (*read_ptr == ' ') {
            if (!previous_was_space) {
                *write_ptr++ = *read_ptr;
                previous_was_space = 1;
            }
        } else {
            *write_ptr++ = *read_ptr;
            previous_was_space = 0;
        }
        ++read_ptr;
    }

    *write_ptr = '\0';
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];

    if (fgets(input, sizeof(input), stdin) == NULL) {
        if (ferror(stdin)) {
            return 1;
        }
        return 0;
    }

    input[strcspn(input, "\n")] = '\0';
    remove_multiple_spaces(input);

    if (puts(input) == EOF) {
        return 1;
    }

    return 0;
}