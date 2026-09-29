#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int find_parity(uint64_t num)
{
    return (int)(num & 1U);
}

int main(void)
{
    uint64_t num;
    int scan_result;
    int parity;

    printf("Enter a non-negative integer: ");
    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    scan_result = scanf("%" SCNu64, &num);

    if (scan_result != 1)
    {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    parity = find_parity(num);

    if (parity == 0)
    {
        printf("The number is even\n");
    }
    else
    {
        printf("The number is odd\n");
    }

    return 0;
}