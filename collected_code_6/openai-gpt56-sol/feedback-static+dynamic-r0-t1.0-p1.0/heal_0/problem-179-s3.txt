#include <stdbool.h>
#include <stdio.h>

static bool is_keith_number(unsigned long long number)
{
    unsigned int digits[20];
    size_t count = 0;
    unsigned long long value = number;

    if (number < 10) {
        return false;
    }

    while (value > 0) {
        digits[count++] = (unsigned int)(value % 10);
        value /= 10;
    }

    for (size_t left = 0, right = count - 1; left < right; ++left, --right) {
        unsigned int temp = digits[left];
        digits[left] = digits[right];
        digits[right] = temp;
    }

    size_t index = 0;

    for (;;) {
        unsigned long long sum = 0;

        for (size_t i = 0; i < count; ++i) {
            unsigned long long term = digits[(index + i) % count];

            if (sum > number - term) {
                return false;
            }

            sum += term;
        }

        if (sum == number) {
            return true;
        }

        if (sum > number) {
            return false;
        }

        digits[index] = (unsigned int)sum;
        index = (index + 1) % count;
    }
}

int main(void)
{
    unsigned long long number;
    int result = scanf("%llu", &number);

    if (result != 1) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    printf("%llu is%s a Keith number\n",
           number,
           is_keith_number(number) ? "" : " not");

    return 0;
}