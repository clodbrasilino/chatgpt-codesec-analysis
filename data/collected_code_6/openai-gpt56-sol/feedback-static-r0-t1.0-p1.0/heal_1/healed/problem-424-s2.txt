#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *extract_rear_elements(const char *const strings[],
                            const size_t capacities[],
                            size_t count)
{
    char *result;
    size_t i;

    if (count > 0 && (strings == NULL || capacities == NULL)) {
        return NULL;
    }

    if (count == SIZE_MAX) {
        return NULL;
    }

    result = malloc(count + 1);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < count; ++i) {
        const char *terminator;

        if (strings[i] == NULL || capacities[i] == 0) {
            free(result);
            return NULL;
        }

        terminator = memchr(strings[i], '\0', capacities[i]);
        if (terminator == NULL || terminator == strings[i]) {
            free(result);
            return NULL;
        }

        result[i] = terminator[-1];
    }

    result[count] = '\0';
    return result;
}

int main(void)
{
    const char *strings[] = {"apple", "banana", "cherry", "date"};
    const size_t capacities[] = {
        sizeof("apple"),
        sizeof("banana"),
        sizeof("cherry"),
        sizeof("date")
    };
    const size_t count = sizeof(strings) / sizeof(strings[0]);
    char *rear_elements = extract_rear_elements(strings, capacities, count);

    if (rear_elements == NULL) {
        fputs("Failed to extract rear elements.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(rear_elements);
    free(rear_elements);

    return EXIT_SUCCESS;
}