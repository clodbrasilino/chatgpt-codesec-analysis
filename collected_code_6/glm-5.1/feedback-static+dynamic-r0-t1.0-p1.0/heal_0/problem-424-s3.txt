#include <stdio.h>
#include <stdlib.h>

char *extract_rear_chars(char **strings, size_t count) {
    if (strings == NULL || count == 0) {
        return NULL;
    }

    char *result = malloc(count * sizeof(char));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < count; i++) {
        if (strings[i] != NULL) {
            size_t len = 0;
            while (strings[i][len] != '\0') {
                len++;
            }
            if (len > 0) {
                result[i] = strings[i][len - 1];
            } else {
                result[i] = '\0';
            }
        } else {
            result[i] = '\0';
        }
    }

    return result;
}

int main(void) {
    char *arr[] = {"hello", "world", "C", "programming", ""};
    size_t count = sizeof(arr) / sizeof(arr[0]);

    char *rear_chars = extract_rear_chars(arr, count);
    if (rear_chars == NULL) {
        return 1;
    }

    for (size_t i = 0; i < count; i++) {
        if (rear_chars[i] != '\0') {
            printf("%c\n", rear_chars[i]);
        } else {
            printf("(empty)\n");
        }
    }

    free(rear_chars);
    rear_chars = NULL;

    return 0;
}