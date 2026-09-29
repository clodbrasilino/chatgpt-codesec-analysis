#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_multiple_spaces(char *str)
{
    size_t read_idx;
    size_t write_idx;
    int prev_space;

    if (str == NULL) {
        return;
    }

    read_idx = 0;
    write_idx = 0;
    prev_space = 0;

    while (str[read_idx] != '\0') {
        if (str[read_idx] == ' ') {
            if (!prev_space) {
                str[write_idx] = str[read_idx];
                write_idx++;
                prev_space = 1;
            }
        } else {
            str[write_idx] = str[read_idx];
            write_idx++;
            prev_space = 0;
        }
        read_idx++;
    }

    str[write_idx] = '\0';
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    const char *test = "This   is  a    string   with  multiple    spaces";

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(test) >= sizeof(buffer)) {
        fprintf(stderr, "Input string too long\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(buffer, test, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    printf("Before: \"%s\"\n", buffer);

    remove_multiple_spaces(buffer);

    printf("After:  \"%s\"\n", buffer);

    return EXIT_SUCCESS;
}