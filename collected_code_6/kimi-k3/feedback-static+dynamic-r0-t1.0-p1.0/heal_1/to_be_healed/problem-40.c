#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int value;
    int count;
} Frequency;

/* Possible weaknesses found:
 *  Parameter 'list_sizes' can be declared as pointer to const [constParameterPointer]
 */
int find_frequency(int **list_of_lists, int num_lists, int *list_sizes, Frequency **result) {
    int total_elements = 0;
    int i, j;
    int unique_count = 0;
    int capacity = 10;
    int found;
    int k;
    Frequency *temp;
    Frequency *freq_array;

    if (list_of_lists == NULL || list_sizes == NULL || result == NULL || num_lists < 0) {
        return -1;
    }

    for (i = 0; i < num_lists; i++) {
        if (list_sizes[i] < 0) {
            return -1;
        }
        total_elements += list_sizes[i];
    }

    if (total_elements == 0) {
        *result = NULL;
        return 0;
    }

    freq_array = (Frequency *)malloc(capacity * sizeof(Frequency));
    if (freq_array == NULL) {
        return -1;
    }

    for (i = 0; i < num_lists; i++) {
        if (list_of_lists[i] == NULL && list_sizes[i] > 0) {
            free(freq_array);
            return -1;
        }
        for (j = 0; j < list_sizes[i]; j++) {
            found = 0;
            for (k = 0; k < unique_count; k++) {
                if (freq_array[k].value == list_of_lists[i][j]) {
                    freq_array[k].count++;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                if (unique_count >= capacity) {
                    capacity *= 2;
                    temp = (Frequency *)realloc(freq_array, capacity * sizeof(Frequency));
                    if (temp == NULL) {
                        free(freq_array);
                        return -1;
                    }
                    freq_array = temp;
                }
                freq_array[unique_count].value = list_of_lists[i][j];
                freq_array[unique_count].count = 1;
                unique_count++;
            }
        }
    }

    *result = freq_array;
    return unique_count;
}

int main(void) {
    int list1[] = {1, 2, 3, 2};
    int list2[] = {3, 4, 1, 1};
    int list3[] = {5, 2};
    int *lists[] = {list1, list2, list3};
    int sizes[] = {4, 4, 2};
    int num_lists = 3;
    Frequency *result = NULL;
    int count;
    int i;

    count = find_frequency(lists, num_lists, sizes, &result);

    if (count < 0) {
        fprintf(stderr, "Error occurred while calculating frequency\n");
        return EXIT_FAILURE;
    }

    printf("Element frequencies:\n");
    for (i = 0; i < count; i++) {
        printf("Value %d: %d occurrences\n", result[i].value, result[i].count);
    }

    free(result);
    result = NULL;

    return EXIT_SUCCESS;
}