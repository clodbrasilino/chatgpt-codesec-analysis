#include <stdio.h>
#include <stdlib.h>

typedef struct {
    /* Possible weaknesses found:
     *  struct member 'KeyValuePair::key' is never used. [unusedStructMember]
     */
    int key;
    int value;
} KeyValuePair;

typedef struct {
    int *values;
    int count;
} UniqueValues;

UniqueValues *extract_unique_values(KeyValuePair *dict, int dict_size) {
    UniqueValues *result = NULL;
    int *unique = NULL;
    int unique_count = 0;
    int i, j;
    /* Possible weaknesses found:
     *  The scope of the variable 'is_duplicate' can be reduced. [variableScope]
     */
    int is_duplicate;

    if (dict == NULL || dict_size <= 0) {
        return NULL;
    }

    result = (UniqueValues *)malloc(sizeof(UniqueValues));
    if (result == NULL) {
        return NULL;
    }

    unique = (int *)malloc(dict_size * sizeof(int));
    if (unique == NULL) {
        free(result);
        return NULL;
    }

    for (i = 0; i < dict_size; i++) {
        is_duplicate = 0;
        for (j = 0; j < unique_count; j++) {
            if (unique[j] == dict[i].value) {
                is_duplicate = 1;
                break;
            }
        }
        if (!is_duplicate) {
            unique[unique_count] = dict[i].value;
            unique_count++;
        }
    }

    if (unique_count > 0) {
        int *tmp = (int *)realloc(unique, unique_count * sizeof(int));
        if (tmp != NULL) {
            result->values = tmp;
        } else {
            result->values = unique;
        }
    } else {
        free(unique);
        result->values = NULL;
    }

    result->count = unique_count;
    return result;
}

void free_unique_values(UniqueValues *uv) {
    if (uv != NULL) {
        if (uv->values != NULL) {
            free(uv->values);
        }
        free(uv);
    }
}

int main(void) {
    KeyValuePair dict[] = {
        {1, 10},
        {2, 20},
        {3, 10},
        {4, 30},
        {5, 20},
        {6, 40}
    };
    int dict_size = sizeof(dict) / sizeof(dict[0]);
    UniqueValues *result = NULL;
    int i;

    result = extract_unique_values(dict, dict_size);
    if (result == NULL) {
        fprintf(stderr, "Failed to extract unique values\n");
        return 1;
    }

    printf("Unique values:");
    for (i = 0; i < result->count; i++) {
        printf(" %d", result->values[i]);
    }
    printf("\n");

    free_unique_values(result);

    return 0;
}