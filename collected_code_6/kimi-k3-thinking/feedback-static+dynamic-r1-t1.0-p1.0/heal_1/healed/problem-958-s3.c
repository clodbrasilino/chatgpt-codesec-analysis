#include <stdio.h>

#define ROMAN_BUFFER_SIZE 32
#define MIN_ROMAN_VALUE 1
#define MAX_ROMAN_VALUE 3999
#define MAX_ROMAN_LENGTH 15

typedef struct {
    int value;
    const char *symbol;
    size_t symbol_len;
} RomanEntry;

_Static_assert(ROMAN_BUFFER_SIZE > MAX_ROMAN_LENGTH,
               "ROMAN_BUFFER_SIZE must exceed the maximum Roman numeral length");

static int int_to_roman(int number, char *buffer, size_t buffer_size)
{
    static const RomanEntry table[] = {
        {1000, "M",  sizeof("M")  - 1U},
        { 900, "CM", sizeof("CM") - 1U},
        { 500, "D",  sizeof("D")  - 1U},
        { 400, "CD", sizeof("CD") - 1U},
        { 100, "C",  sizeof("C")  - 1U},
        {  90, "XC", sizeof("XC") - 1U},
        {  50, "L",  sizeof("L")  - 1U},
        {  40, "XL", sizeof("XL") - 1U},
        {  10, "X",  sizeof("X")  - 1U},
        {   9, "IX", sizeof("IX") - 1U},
        {   5, "V",  sizeof("V")  - 1U},
        {   4, "IV", sizeof("IV") - 1U},
        {   1, "I",  sizeof("I")  - 1U}
    };
    const size_t entry_count = sizeof(table) / sizeof(table[0]);
    size_t used;
    size_t i;
    size_t j;
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

    if (buffer_size < (MAX_ROMAN_LENGTH + 1U))
    {
        return -1;
    }

    used = 0U;
    remaining = number;

    for (i = 0U; i < entry_count; i++)
    {
        while (remaining >= table[i].value)
        {
            if ((used + table[i].symbol_len) >= buffer_size)
            {
                buffer[0] = '\0';
                return -1;
            }

            for (j = 0U; j < table[i].symbol_len; j++)
            {
                buffer[used] = table[i].symbol[j];
                used++;
            }

            remaining -= table[i].value;
        }
    }

    buffer[used] = '\0';
    return 0;
}

int main(void)
{
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