#include <stdio.h>
#include <stdlib.h>

char *extract_rear_elements(const char *const strings[],
                            const size_t lengths[],
                            size_t count)
{
    char *result;
    size_t i;

    if (count == SIZE_MAX) {
        return NULL;
    }

    if (count != 0 && (strings == NULL || lengths == NULL)) {
        return NULL;
    }

    result = malloc(count + 1);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < count; ++i) {
        if (strings[i] == NULL || lengths[i] == 0) {
            free(result);
            return NULL;
        }

        result[i] = strings[i][lengths[i] - 1];
    }

    result[count] = '\0';
    return result;
}

int main(void)
{
    static const char apple[] = "apple";
    static const char banana[] = "banana";
    static const char cherry[] = "cherry";
    static const char date[] = "date";

    const char *strings[] = {apple, banana, cherry, date};
    const size_t lengths[] = {
        sizeof(apple) - 1,
        sizeof(banana) - 1,
        sizeof(cherry) - 1,
        sizeof(date) - 1
    };
    const size_t count = sizeof(strings) / sizeof(strings[0]);
    char *rear_elements = extract_rear_elements(strings, lengths, count);

    if (rear_elements == NULL) {
        fputs("Failed to extract rear elements.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(rear_elements);
    free(rear_elements);

    return EXIT_SUCCESS;
}