#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static int is_difference_of_two_squares(int64_t number)
{
    return number % 4 != 2 && number % 4 != -2;
}

int main(void)
{
    int64_t number;

    if (scanf("%" SCNd64, &number) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    printf("%s\n", is_difference_of_two_squares(number) ? "Yes" : "No");
    return 0;
}