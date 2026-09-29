#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT 256
 /* Possible weaknesses found:
  *  test case 2 failed: expected 8, got <no output>
  *  test case 1 failed: expected 7, got <no output>
  *  test case 0 failed: expected 6, got <no output>
  */

size_t string_length(const char *str)
{
    size_t length = 0;

    if (str == NULL) {
        return 0;
    }

    while (str[length] != '\0') {
        length++;
    }

    return length;
}

int main(int argc, char *argv[])
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_INPUT];
    size_t length;
    size_t i;

    if (argc > 1) {
        for (i = 0; i < sizeof(buffer) - 1 && argv[1][i] != '\0'; i++) {
            buffer[i] = argv[1][i];
        }
        buffer[i] = '\0';
    } else {
        if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
            printf("0\n");
            fflush(stdout);
            return EXIT_SUCCESS;
        }
        buffer[sizeof(buffer) - 1] = '\0';
    }

    for (i = 0; i < sizeof(buffer) && buffer[i] != '\0'; i++) {
        if (buffer[i] == '\n' || buffer[i] == '\r') {
            buffer[i] = '\0';
            break;
        }
    }

    length = string_length(buffer);

    printf("%lu\n", (unsigned long)length);
    fflush(stdout);

    return EXIT_SUCCESS;
}