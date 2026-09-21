#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *extract_rear_elements(char *arr[], int size) {
    if (arr == NULL || size <= 0) {
        return NULL;
    }

    char *result = (char *)malloc((size + 1) * sizeof(char));
    if (result == NULL) {
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (arr[i] == NULL || strlen(arr[i]) == 0) {
            free(result);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        result[i] = arr[i][strlen(arr[i]) - 1];
    }
    result[size] = '\0';

    return result;
}

int main(void) {
    char *strings[] = {"apple", "banana", "cherry", "date"};
    int size = sizeof(strings) / sizeof(strings[0]);

    char *rear_elements = extract_rear_elements(strings, size);
    if (rear_elements != NULL) {
        printf("Rear elements: %s\n", rear_elements);
        free(rear_elements);
    } else {
        printf("Failed to extract rear elements.\n");
    }

    return 0;
}