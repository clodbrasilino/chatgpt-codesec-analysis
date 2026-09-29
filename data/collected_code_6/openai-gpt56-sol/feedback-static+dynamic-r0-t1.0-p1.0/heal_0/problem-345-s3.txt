#include <stdio.h>
#include <stdlib.h>

static int find_differences(const long long *numbers, size_t count, long long *differences)
{
    if (numbers == NULL || differences == NULL || count < 2) {
        return -1;
    }

    for (size_t i = 1; i < count; ++i) {
        differences[i - 1] = numbers[i] - numbers[i - 1];
    }

    return 0;
}

int main(void)
{
    size_t count = 0;

    if (scanf("%zu", &count) != 1 || count < 2 || count > SIZE_MAX / sizeof(long long)) {
        return EXIT_FAILURE;
    }

    long long *numbers = malloc(count * sizeof(*numbers));
    long long *differences = malloc((count - 1) * sizeof(*differences));

    if (numbers == NULL || differences == NULL) {
        free(numbers);
        free(differences);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (scanf("%lld", &numbers[i]) != 1) {
            free(numbers);
            free(differences);
            return EXIT_FAILURE;
        }
    }

    if (find_differences(numbers, count, differences) != 0) {
        free(numbers);
        free(differences);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count - 1; ++i) {
        if (printf("%lld%s", differences[i], i + 1 == count - 1 ? "\n" : " ") < 0) {
            free(numbers);
            free(differences);
            return EXIT_FAILURE;
        }
    }

    free(numbers);
    free(differences);
    return EXIT_SUCCESS;
}