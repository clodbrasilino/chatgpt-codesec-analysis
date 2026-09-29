#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int allBitsSetInRange(unsigned int num, unsigned int left, unsigned int right)
{
    unsigned int mask;
    unsigned int width;

    if (left == 0U || right == 0U) {
        return -1;
    }
    if (left > right) {
        return -1;
    }
    if (right > (unsigned int)(sizeof(unsigned int) * CHAR_BIT)) {
        return -1;
    }

    width = right - left + 1U;
    if (width >= (unsigned int)(sizeof(unsigned int) * CHAR_BIT)) {
        mask = UINT_MAX;
    } else {
        mask = ((1U << width) - 1U) << (left - 1U);
    }

    if ((num & mask) == mask) {
        return 1;
    }
    return 0;
}

int main(void)
{
    unsigned int num;
    unsigned int left;
    unsigned int right;
    int result;

    printf("Enter the number: ");
    if (scanf("%u", &num) != 1) {
        fprintf(stderr, "Invalid input for number\n");
        return EXIT_FAILURE;
    }

    printf("Enter the left bit position (1-based): ");
    if (scanf("%u", &left) != 1) {
        fprintf(stderr, "Invalid input for left position\n");
        return EXIT_FAILURE;
    }

    printf("Enter the right bit position (1-based): ");
    if (scanf("%u", &right) != 1) {
        fprintf(stderr, "Invalid input for right position\n");
        return EXIT_FAILURE;
    }

    result = allBitsSetInRange(num, left, right);
    if (result < 0) {
        fprintf(stderr, "Invalid bit range specified\n");
        return EXIT_FAILURE;
    }

    if (result == 1) {
        printf("All bits in range [%u, %u] are set in %u\n", left, right, num);
    } else {
        printf("Not all bits in range [%u, %u] are set in %u\n", left, right, num);
    }

    return EXIT_SUCCESS;
}