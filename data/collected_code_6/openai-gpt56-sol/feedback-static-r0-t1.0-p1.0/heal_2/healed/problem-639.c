#include <ctype.h>
#include <stdint.h>
#include <stdio.h>

#define MAX_NAME_LENGTH 1024U

size_t sum_filtered_name_lengths(
    const char *const names[],
    const size_t lengths[],
    size_t count)
{
    size_t total = 0U;

    if (names == NULL || lengths == NULL) {
        return 0U;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (names[i] == NULL || lengths[i] == 0U) {
            continue;
        }

        const unsigned char first = (unsigned char)names[i][0];

        if (first == '\0' || islower(first) != 0) {
            continue;
        }

        size_t length = 0U;

        while (length < lengths[i] &&
               length < MAX_NAME_LENGTH &&
               names[i][length] != '\0') {
            ++length;
        }

        if (length == lengths[i] ||
            length == MAX_NAME_LENGTH ||
            length > SIZE_MAX - total) {
            return SIZE_MAX;
        }

        total += length;
    }

    return total;
}

int main(void)
{
    static const char alice[] = "Alice";
    static const char bob[] = "bob";
    static const char charlie[] = "Charlie";
    static const char diana[] = "diana";
    static const char eve[] = "Eve";

    const char *const names[] = {
        alice,
        bob,
        charlie,
        diana,
        eve
    };

    const size_t lengths[] = {
        sizeof(alice),
        sizeof(bob),
        sizeof(charlie),
        sizeof(diana),
        sizeof(eve)
    };

    const size_t count = sizeof(names) / sizeof(names[0]);
    const size_t total = sum_filtered_name_lengths(names, lengths, count);

    if (total == SIZE_MAX) {
        fputs("Invalid name data or length sum overflowed.\n", stderr);
        return 1;
    }

    if (printf("%zu\n", total) < 0) {
        return 1;
    }

    return 0;
}