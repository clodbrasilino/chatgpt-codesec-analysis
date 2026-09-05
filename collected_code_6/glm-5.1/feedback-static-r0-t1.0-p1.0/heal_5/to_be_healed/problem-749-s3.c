#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_numeric(const void *a, const void *b) {
    long long num_a = strtoll(*(const char *const *)a, NULL, 10);
    long long num_b = strtoll(*(const char *const *)b, NULL, 10);
    if (num_a < num_b) return -1;
    if (num_a > num_b) return 1;
    return 0;
}

void sort_strings_numerically(char **strings, size_t count) {
    if (strings == NULL || count == 0) {
        return;
    }
    qsort(strings, count, sizeof(char *), compare_numeric);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[const]) {
    if (argc < 2) {
        return EXIT_FAILURE;
    }

    size_t count = (size_t)(argc - 1);
    char **list = malloc(count * sizeof(char *));
    if (list == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; i++) {
        size_t len = strlen(argv[i + 1]);
        list[i] = malloc(len + 1);
        if (list[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(list[j]);
            }
            free(list);
            return EXIT_FAILURE;
        }
        strcpy(list[i], argv[i + 1]);
    }

    sort_strings_numerically(list, count);

    for (size_t i = 0; i < count; i++) {
        printf("%s\n", list[i]);
    }

    for (size_t i = 0; i < count; i++) {
        free(list[i]);
    }
    free(list);

    return EXIT_SUCCESS;
}