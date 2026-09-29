#include <stdio.h>
#include <stdlib.h>

int count_set_bits(unsigned int num)
{
    int count = 0;
    while (num != 0) {
        count += num & 1;
        num >>= 1;
    }
    return count;
}

int main(int argc, char *const argv[])
{
    unsigned int number;
    char *endptr;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    number = (unsigned int)strtoul(argv[1], &endptr, 10);
    if (*endptr != '\0') {
        fprintf(stderr, "Invalid number: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    printf("%d\n", count_set_bits(number));

    return EXIT_SUCCESS;
}