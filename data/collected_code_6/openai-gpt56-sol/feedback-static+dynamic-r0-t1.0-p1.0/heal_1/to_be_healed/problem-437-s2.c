#include <stdio.h>
#include <string.h>

static void remove_odd_characters(char *string)
{
    size_t read_index;
    size_t write_index = 0U;

    if (string == NULL) {
        return;
    }

    for (read_index = 0U; string[read_index] != '\0'; read_index += 2U) {
        string[write_index] = string[read_index];
        ++write_index;
    }

    string[write_index] = '\0';
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char string[1024];

    if (fgets(string, sizeof string, stdin) == NULL) {
        if (ferror(stdin) != 0) {
            return 1;
        }
        return 0;
    }

    string[strcspn(string, "\n")] = '\0';
    remove_odd_characters(string);

    if (puts(string) == EOF) {
        return 1;
    }

    return 0;
}