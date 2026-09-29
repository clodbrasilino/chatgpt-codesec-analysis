#include <stdio.h>
#include <string.h>

#define ROMAN_BUFFER_SIZE 32
#define MIN_ROMAN_VALUE 1
#define MAX_ROMAN_VALUE 3999

typedef struct {
    int value;
    const char *symbol;
} RomanEntry;

static int int_to_roman(int number, char *buffer, size_t buffer_size)
{
    static const RomanEntry table[] = {
        {1000, "M"},
        {900, "CM"},
        {500, "D"},
        {400, "CD"},
        {100, "C"},
        {90, "XC"},
        {50, "L"},
        {40, "XL"},
        {10, "X"},
        {9, "IX"},
        {5, "V"},
        {4, "IV"},
        {1, "I"}
    };
    const size_t entry_count = sizeof(table) / sizeof(table[0]);
    size_t used;
    size_t i;
    int remaining;

    if (buffer == NULL || buffer_size == 0U)
    {
        return -1;
    }

    buffer[0] = '\0';

    if (number < MIN_ROMAN_VALUE || number > MAX_ROMAN_VALUE)
    {
        return -1;
    }

    used = 0U;
    remaining = number;

    for (i = 0U; i < entry_count; i++)
    {
        while (remaining >= table[i].value)
        {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            const size_t symbol_len = strlen(table[i].symbol);

            if ((used + symbol_len) >= buffer_size)
            {
                buffer[0] = '\0';
                return -1;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(buffer + used, table[i].symbol, symbol_len);
            used += symbol_len;
            remaining -= table[i].value;
        }
    }

    buffer[used] = '\0';
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[ROMAN_BUFFER_SIZE];
    int number;
    int result;

    printf("Enter an integer (1-3999): ");
    result = fflush(stdout);
    if (result != 0)
    {
        fprintf(stderr, "Error: failed to write prompt\n");
        return 1;
    }

    result = scanf("%d", &number);
    if (result != 1)
    {
        fprintf(stderr, "Error: invalid input\n");
        return 1;
    }

    result = int_to_roman(number, buffer, sizeof(buffer));
    if (result != 0)
    {
        fprintf(stderr, "Error: value must be between 1 and 3999\n");
        return 1;
    }

    printf("%d -> %s\n", number, buffer);
    return 0;
}