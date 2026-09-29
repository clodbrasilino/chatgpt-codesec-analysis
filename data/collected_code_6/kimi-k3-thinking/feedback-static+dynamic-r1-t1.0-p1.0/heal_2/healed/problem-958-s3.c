#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#define ROMAN_BUFFER_SIZE 32
#define INPUT_BUFFER_SIZE 64
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
    size_t used = 0U;
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

    if (buffer_size < ((size_t)MAX_ROMAN_LENGTH + 1U))
    {
        return -1;
    }

    remaining = number;

    for (i = 0U; i < entry_count; i++)
    {
        while (remaining >= table[i].value)
        {
            if (table[i].symbol_len > (buffer_size - used - 1U))
            {
                buffer[0] = '\0';
                return -1;
            }

            memcpy(buffer + used, table[i].symbol, table[i].symbol_len);
            used += table[i].symbol_len;
            remaining -= table[i].value;
        }
    }

    buffer[used] = '\0';
    return 0;
}

int main(void)
{
    char buffer[ROMAN_BUFFER_SIZE];
    char input[INPUT_BUFFER_SIZE];
    char *end;
    long number;
    int result;

    printf("Enter an integer (1-3999): ");
    result = fflush(stdout);
    if (result != 0)
    {
        fprintf(stderr, "Error: failed to write prompt\n");
        return 1;
    }

    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        fprintf(stderr, "Error: invalid input\n");
        return 1;
    }

    errno = 0;
    number = strtol(input, &end, 10);
    if (end == input || errno == ERANGE || number > INT_MAX || number < INT_MIN)
    {
        fprintf(stderr, "Error: invalid input\n");
        return 1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r')
    {
        end++;
    }

    if (*end != '\0')
    {
        fprintf(stderr, "Error: invalid input\n");
        return 1;
    }

    result = int_to_roman((int)number, buffer, sizeof(buffer));
    if (result != 0)
    {
        fprintf(stderr, "Error: value must be between 1 and 3999\n");
        return 1;
    }

    printf("%ld -> %s\n", number, buffer);
    return 0;
}