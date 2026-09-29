#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    void *data;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
    int length;
} List;

typedef struct ListOfLists {
    List **lists;
    int count;
} ListOfLists;

ListOfLists *find_min_length_lists(ListOfLists *input) {
    if (input == NULL || input->count == 0) {
        return NULL;
    }

    int min_len = input->lists[0]->length;
    for (int i = 1; i < input->count; i++) {
        if (input->lists[i]->length < min_len) {
            min_len = input->lists[i]->length;
        }
    }

    int result_count = 0;
    for (int i = 0; i < input->count; i++) {
        if (input->lists[i]->length == min_len) {
            result_count++;
        }
    }

    ListOfLists *result = (ListOfLists *)malloc(sizeof(ListOfLists));
    if (result == NULL) {
        return NULL;
    }

    result->lists = (List **)malloc(result_count * sizeof(List *));
    if (result->lists == NULL) {
        free(result);
        return NULL;
    }

    result->count = result_count;
    int index = 0;
    for (int i = 0; i < input->count; i++) {
        if (input->lists[i]->length == min_len) {
            result->lists[index++] = input->lists[i];
        }
    }

    return result;
}

void free_list_of_lists(ListOfLists *lol) {
    if (lol == NULL) {
        return;
    }
    if (lol->lists != NULL) {
        for (int i = 0; i < lol->count; i++) {
            List *l = lol->lists[i];
            if (l != NULL) {
                Node *curr = l->head;
                while (curr != NULL) {
                    Node *next = curr->next;
                    free(curr->data);
                    free(curr);
                    curr = next;
                }
                free(l);
            }
        }
        free(lol->lists);
    }
    free(lol);
}

int main() {
    List *l1 = (List *)malloc(sizeof(List));
    l1->length = 3;
    l1->head = NULL;

    List *l2 = (List *)malloc(sizeof(List));
    l2->length = 1;
    l2->head = NULL;

    List *l3 = (List *)malloc(sizeof(List));
    l3->length = 1;
    l3->head = NULL;

    List *l4 = (List *)malloc(sizeof(List));
    l4->length = 5;
    l4->head = NULL;

    ListOfLists *input = (ListOfLists *)malloc(sizeof(ListOfLists));
    input->count = 4;
    input->lists = (List **)malloc(4 * sizeof(List *));
    input->lists[0] = l1;
    input->lists[1] = l2;
    input->lists[2] = l3;
    input->lists[3] = l4;

    ListOfLists *result = find_min_length_lists(input);

    /* Possible weaknesses found:
     *  Assuming that condition 'result!=NULL' is not redundant
     */
    if (result != NULL) {
        printf("Minimum length: %d\n", result->lists[0]->length);
        printf("Number of lists with minimum length: %d\n", result->count);
        for (int i = 0; i < result->count; i++) {
            printf("List index in result: %d, Length: %d\n", i, result->lists[i]->length);
        }
    }

    /* Possible weaknesses found:
     *  Either the condition 'result!=NULL' is redundant or there is possible null pointer dereference: result. [nullPointerRedundantCheck]
     *  Null pointer dereference
     */
    free(result->lists);
    free(result);

    free(input->lists);
    free(input);
    free(l1);
    free(l2);
    free(l3);
    free(l4);

    return 0;
}