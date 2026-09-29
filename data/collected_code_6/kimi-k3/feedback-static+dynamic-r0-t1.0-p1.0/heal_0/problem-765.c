#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int is_polite(unsigned int num)
{
    return (num & (num - 1)) != 0;
}

int find_nth_polite(unsigned int n, unsigned int *result)
{
    unsigned int count;
    unsigned int num;

    if (result == NULL) {
        return -1;
    }

    if (n == 0) {
        return -1;
    }

    count = 0;
    num = 1;

    while (count < n) {
        if (is_polite(num)) {
            count++;
            if (count == n) {
                *result = num;
                return 0;
            }
        }
        if (num == UINT_MAX) {
            return -1;
        }
        num++;
    }

    return -1;
}

int main(void)
{
    unsigned int n;
    unsigned int result;
    int status;

    printf("Enter n: ");
    
    if (scanf("%u", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    status = find_nth_polite(n, &result);

    if (status != 0) {
        fprintf(stderr, "Error: Unable to find %uth polite number\n", n);
        return EXIT_FAILURE;
    }

    printf("The %uth polite number is: %u\n", n, result);

    return EXIT_SUCCESS;
}