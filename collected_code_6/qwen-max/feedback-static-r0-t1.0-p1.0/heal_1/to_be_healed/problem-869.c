#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* data;
    size_t length;
} List;

List* create_list(size_t length) {
    List* list = (List*)malloc(sizeof(List));
    if (list == NULL) return NULL;
    list->data = (int*)calloc(length, sizeof(int));
    if (list->data == NULL) {
        free(list);
        return NULL;
    }
    list->length = length;
    return list;
}

void free_list(List* list) {
    if (list != NULL) {
        free(list->data);
        free(list);
    }
}

/* Possible weaknesses found:
 *  Parameter 'lengths' can be declared as pointer to const [constParameterPointer]
 */
List** create_list_of_lists(size_t num_lists, size_t* lengths) {
    List** list_of_lists = (List**)malloc(num_lists * sizeof(List*));
    if (list_of_lists == NULL) return NULL;
    for (size_t i = 0; i < num_lists; ++i) {
        list_of_lists[i] = create_list(lengths[i]);
        if (list_of_lists[i] == NULL) {
            for (size_t j = 0; j < i; ++j) {
                free_list(list_of_lists[j]);
            }
            free(list_of_lists);
            return NULL;
        }
    }
    return list_of_lists;
}

void free_list_of_lists(List** list_of_lists, size_t num_lists) {
    for (size_t i = 0; i < num_lists; ++i) {
        free_list(list_of_lists[i]);
    }
    free(list_of_lists);
}

List** remove_sublists_outside_range(List** list_of_lists, size_t num_lists, int min, int max) {
    List** filtered_list_of_lists = (List**)malloc(num_lists * sizeof(List*));
    if (filtered_list_of_lists == NULL) return NULL;
    size_t new_num_lists = 0;

    for (size_t i = 0; i < num_lists; ++i) {
        int all_in_range = 1;
        for (size_t j = 0; j < list_of_lists[i]->length; ++j) {
            if (list_of_lists[i]->data[j] < min || list_of_lists[i]->data[j] > max) {
                all_in_range = 0;
                break;
            }
        }
        if (all_in_range) {
            filtered_list_of_lists[new_num_lists++] = list_of_lists[i];
        } else {
            free_list(list_of_lists[i]);
        }
    }

    /* Possible weaknesses found:
     *  Common realloc mistake: 'filtered_list_of_lists' nulled but not freed upon failure [memleakOnRealloc]
     */
    filtered_list_of_lists = (List**)realloc(filtered_list_of_lists, new_num_lists * sizeof(List*));
    if (filtered_list_of_lists == NULL) return NULL;

    return filtered_list_of_lists;
}

int main() {
    size_t num_lists = 3;
    size_t lengths[] = {3, 4, 2};
    List** list_of_lists = create_list_of_lists(num_lists, lengths);

    if (list_of_lists == NULL) {
        printf("Failed to create list of lists.\n");
        return 1;
    }

    list_of_lists[0]->data[0] = 1;
    list_of_lists[0]->data[1] = 2;
    list_of_lists[0]->data[2] = 3;
    
    list_of_lists[1]->data[0] = 4;
    list_of_lists[1]->data[1] = 5;
    list_of_lists[1]->data[2] = 6;
    list_of_lists[1]->data[3] = 7;
    
    list_of_lists[2]->data[0] = 8;
    list_of_lists[2]->data[1] = 9;

    int min = 2;
    int max = 6;

    List** filtered_list_of_lists = remove_sublists_outside_range(list_of_lists, num_lists, min, max);
    if (filtered_list_of_lists == NULL) {
        printf("Failed to filter list of lists.\n");
        free_list_of_lists(list_of_lists, num_lists);
        return 1;
    }

    for (size_t i = 0; i < num_lists; ++i) {
        if (filtered_list_of_lists[i] != NULL) {
            for (size_t j = 0; j < filtered_list_of_lists[i]->length; ++j) {
                printf("%d ", filtered_list_of_lists[i]->data[j]);
            }
            printf("\n");
        }
    }

    free_list_of_lists(filtered_list_of_lists, num_lists);
    free_list_of_lists(list_of_lists, num_lists);

    return 0;
}