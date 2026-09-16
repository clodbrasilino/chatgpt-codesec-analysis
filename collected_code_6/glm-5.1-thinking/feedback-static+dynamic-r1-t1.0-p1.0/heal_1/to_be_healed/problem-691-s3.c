#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    int key;
    int *values;
    int value_count;
    int value_capacity;
} Group;

typedef struct {
    Group *groups;
    int group_count;
    int group_capacity;
    int error;
} GroupedResult;

GroupedResult group_tuples(const Tuple *tuples, int count) {
    GroupedResult result = {NULL, 0, 0, 0};
    if (tuples == NULL || count <= 0) {
        return result;
    }

    for (int i = 0; i < count; i++) {
        int found = 0;
        for (int j = 0; j < result.group_count; j++) {
            if (result.groups[j].key == tuples[i].second) {
                if (result.groups[j].value_count >= result.groups[j].value_capacity) {
                    int new_cap = result.groups[j].value_capacity == 0 ? 4 : result.groups[j].value_capacity * 2;
                    int *new_values = realloc(result.groups[j].values, new_cap * sizeof(int));
                    if (!new_values) {
                        result.error = 1;
                        return result;
                    }
                    result.groups[j].values = new_values;
                    result.groups[j].value_capacity = new_cap;
                }
                result.groups[j].values[result.groups[j].value_count++] = tuples[i].first;
                found = 1;
                break;
            }
        }

        if (!found) {
            if (result.group_count >= result.group_capacity) {
                int new_cap = result.group_capacity == 0 ? 4 : result.group_capacity * 2;
                Group *new_groups = realloc(result.groups, new_cap * sizeof(Group));
                if (!new_groups) {
                    result.error = 1;
                    return result;
                }
                result.groups = new_groups;
                result.group_capacity = new_cap;
            }

            result.groups[result.group_count].key = tuples[i].second;
            result.groups[result.group_count].value_capacity = 4;
            result.groups[result.group_count].value_count = 0;
            result.groups[result.group_count].values = malloc(result.groups[result.group_count].value_capacity * sizeof(int));

            if (!result.groups[result.group_count].values) {
                result.error = 1;
                return result;
            }

            result.groups[result.group_count].values[result.groups[result.group_count].value_count++] = tuples[i].first;
            result.group_count++;
        }
    }

    return result;
}

void free_grouped_result(GroupedResult *result) {
    if (result == NULL) {
        return;
    }
    if (result->groups != NULL) {
        /* Possible weaknesses found:
         *  'result' is a pointer; did you mean to use '->'?
         *  member reference type 'GroupedResult *' is a pointer; did you mean to use '->'?
         */
        for (int i = 0; i < result.group_count; i++) {
            free(result->groups[i].values);
        }
        free(result->groups);
    }
    result->groups = NULL;
    result->group_count = 0;
    result->group_capacity = 0;
}

int main(void) {
    Tuple data[] = {{1, 10}, {2, 20}, {3, 10}, {4, 30}, {5, 20}, {6, 10}};
    int data_count = sizeof(data) / sizeof(data[0]);

    GroupedResult result = group_tuples(data, data_count);

    if (result.error) {
        fprintf(stderr, "Memory allocation failed\n");
        free_grouped_result(&result);
        return EXIT_FAILURE;
    }

    for (int i = 0; i < result.group_count; i++) {
        printf("Key %d: ", result.groups[i].key);
        for (int j = 0; j < result.groups[i].value_count; j++) {
            printf("%d ", result.groups[i].values[j]);
        }
        printf("\n");
    }

    free_grouped_result(&result);

    return EXIT_SUCCESS;
}