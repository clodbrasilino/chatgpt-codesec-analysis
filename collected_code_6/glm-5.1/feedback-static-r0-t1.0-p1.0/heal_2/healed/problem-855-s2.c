#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int check_even_parity(unsigned int num) {
    int count = 0;
    while (num) {
        count += num & 1;
        num >>= 1;
    }
    return (count % 2) == 0;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    errno = 0;
    unsigned long val = strtoul(argv[1], NULL, 10);

    if (errno != 0 || val > 4294967295UL) {
        return EXIT_FAILURE;
    }

    unsigned int num = (unsigned int)val;
    int result = check_even_parity(num);

    printf("%d\n", result);

    return EXIT_SUCCESS;
}