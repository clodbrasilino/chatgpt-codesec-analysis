#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected True, got <no output>
  *  test case 0 failed: expected True, got <no output>
  *  test case 1 failed: expected False, got <no output>
  */

int check_even_parity(unsigned int num) {
    int count = 0;
    while (num) {
        count += num & 1;
        num >>= 1;
    }
    return (count % 2) == 0;
}

int main(int argc, char const * const argv[]) {
    if (argc != 2) {
        printf("False\n");
        return EXIT_FAILURE;
    }

    char *endptr;
    unsigned long val = strtoul(argv[1], &endptr, 10);

    if (*endptr != '\0' || val > 4294967295UL) {
        printf("False\n");
        return EXIT_FAILURE;
    }

    unsigned int num = (unsigned int)val;
    int result = check_even_parity(num);

    printf("%s\n", result ? "True" : "False");
    
    fflush(stdout);

    return EXIT_SUCCESS;
}