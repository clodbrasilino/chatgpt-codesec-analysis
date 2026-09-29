#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_string(char *str, size_t size) {
    if (str == NULL || size == 0) {
        return;
    }
    size_t len = strnlen(str, size);
    size_t left = 0;
    size_t right = len > 0 ? len - 1 : 0;
    while (left < right) {
        char temp = str[left];
        str[left] = str[right];
        str[right] = temp;
        left++;
        right--;
    }
}

/* Possible weaknesses found:
 *  Parameter 'sizes' can be declared as pointer to const [constParameterPointer]
 */
void reverse_strings(char **strings, size_t *sizes, size_t count) {
    if (strings == NULL || sizes == NULL) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        reverse_string(strings[i], sizes[i]);
    }
}

int main(void) {
    const char *original_strings[] = {"hello", "world", "C", "programming"};
    size_t count = sizeof(original_strings) / sizeof(original_strings[0]);
    char **strings = malloc(count * sizeof(char *));
    if (strings == NULL) {
        return EXIT_FAILURE;
    }
    size_t *sizes = malloc(count * sizeof(size_t));
    if (sizes == NULL) {
        free(strings);
        return EXIT_FAILURE;
    }
    size_t allocated_count = 0;
    for (size_t i = 0; i < count; i++) {
        int len = snprintf(NULL, 0, "%s", original_strings[i]);
        if (len < 0) {
            for (size_t j = 0; j < allocated_count; j++) {
                free(strings[j]);
            }
            free(strings);
            free(sizes);
            return EXIT_FAILURE;
        }
        sizes[i] = (size_t)len + 1;
        strings[i] = malloc(sizes[i]);
        if (strings[i] == NULL) {
            for (size_t j = 0; j < allocated_count; j++) {
                free(strings[j]);
            }
            free(strings);
            free(sizes);
            return EXIT_FAILURE;
        }
        snprintf(strings[i], sizes[i], "%s", original_strings[i]);
        allocated_count++;
    }
    reverse_strings(strings, sizes, count);
    for (size_t i = 0; i < count; i++) {
        printf("%s\n", strings[i]);
    }
    for (size_t i = 0; i < count; i++) {
        free(strings[i]);
    }
    free(strings);
    free(sizes);
    return EXIT_SUCCESS;
}