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

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNd64, &number) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    printf("%s\n", is_difference_of_two_squares(number) ? "Yes" : "No");
    return 0;
}