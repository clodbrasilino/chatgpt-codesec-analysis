#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <errno.h>

int find_parity(uint64_t num)
{
    return (int)(num & 1U);
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[32];
    uint64_t num;
    char *endptr;
    int parity;

    printf("Enter a non-negative integer: ");
    
    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    input[strcspn(input, "\n")] = '\0';

    if (input[0] == '\0')
    {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    errno = 0;
    /* Possible weaknesses found:
     *  include the header <stdlib.h> or explicitly provide a declaration for 'strtoull'
     *  call to undeclared library function 'strtoull' with type 'unsigned long long (const char *, char **, int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'strtoull'; did you mean 'strcoll'? [-Wimplicit-function-declaration]
     */
    num = strtoull(input, &endptr, 10);

    if (errno != 0 || *endptr != '\0' || endptr == input)
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