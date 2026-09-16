#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 1, got <no output>
  *  test case 2 failed: expected 2, got <no output>
  *  test case 1 failed: expected 1, got <no output>
  */

int count_set_bits(unsigned int num)
{
    int count = 0;
    while (num != 0) {
        count += num & 1;
        num >>= 1;
    }
    return count;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    unsigned int number;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    number = (unsigned int)strtoul(argv[1], NULL, 10);
    printf("%d\n", count_set_bits(number));

    return EXIT_SUCCESS;
}