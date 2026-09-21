#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *extract_rear_elements(const char *const strings[],
                            const size_t lengths[],
                            size_t count)
{
    char *result;
    size_t i;

    if (count > 0U && (strings == NULL || lengths == NULL)) {
        return NULL;
    }

    if (count == SIZE_MAX) {
        return NULL;
    }

    result = malloc(count + 1U);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0U; i < count; ++i) {
        if (strings[i] == NULL || lengths[i] == 0U) {
            free(result);
            return NULL;
        }

        result[i] = strings[i][lengths[i] - 1U];
    }

    result[count] = '\0';
    return result;
}

int main(void)
{
    const char *strings[] = {"apple", "banana", "cherry", "date"};
    const size_t lengths[] = {
        sizeof("apple") - 1U,
        sizeof("banana") - 1U,
        sizeof("cherry") - 1U,
        sizeof("date") - 1U
    };
    const size_t count = sizeof(strings) / sizeof(strings[0]);
    char *rear_elements = extract_rear_elements(strings, lengths, count);

    if (rear_elements == NULL) {
        fputs("Failed to extract rear elements.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%s\n", rear_elements);
    free(rear_elements);

    return EXIT_SUCCESS;
}