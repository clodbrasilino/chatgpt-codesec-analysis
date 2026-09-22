#include <stdio.h>
#include <stdlib.h>

struct List {
    int* elements;
    int length;
};

struct ListOfLists {
    struct List* lists;
    int count;
};

void findMaxLenLists(struct ListOfLists* input, struct ListOfLists* output) {
    if (input == NULL || output == NULL || input->count <= 0) {
        if (output != NULL) {
            output->lists = NULL;
            output->count = 0;
        }
        return;
    }

    int max_len = -1;
    for (int i = 0; i < input->count; i++) {
        if (input->lists[i].length > max_len) {
            max_len = input->lists[i].length;
        }
    }

    int countMax = 0;
    for (int i = 0; i < input->count; i++) {
        if (input->lists[i].length == max_len) {
            countMax++;
        }
    }

    output->lists = (struct List*)malloc(countMax * sizeof(struct List));
    if (output->lists == NULL) {
        output->count = 0;
        return;
    }

    output->count = countMax;
    int index = 0;
    for (int i = 0; i < input->count; i++) {
        if (input->lists[i].length == max_len) {
            output->lists[index].length = max_len;
            if (max_len > 0) {
                output->lists[index].elements = (int*)malloc(max_len * sizeof(int));
                if (output->lists[index].elements != NULL) {
                    for (int j = 0; j < max_len; j++) {
                        output->lists[index].elements[j] = input->lists[i].elements[j];
                    }
                } else {
                    for (int k = 0; k < index; k++) {
                        free(output->lists[k].elements);
                    }
                    free(output->lists);
                    output->lists = NULL;
                    output->count = 0;
                    return;
                }
            } else {
                output->lists[index].elements = NULL;
            }
            index++;
        }
    }
}

void freeListOfLists(struct ListOfLists* lol) {
    if (lol == NULL || lol->lists == NULL) {
        return;
    }
    for (int i = 0; i < lol->count; i++) {
        if (lol->lists[i].elements != NULL) {
            free(lol->lists[i].elements);
            lol->lists[i].elements = NULL;
        }
    }
    free(lol->lists);
    lol->lists = NULL;
    lol->count = 0;
}

int main() {
    struct ListOfLists input;
    input.count = 3;
    input.lists = (struct List*)malloc(input.count * sizeof(struct List));
    
    if (input.lists == NULL) {
        return 1;
    }

    input.lists[0].length = 2;
    input.lists[0].elements = (int*)malloc(2 * sizeof(int));
    if (input.lists[0].elements != NULL) {
        input.lists[0].elements[0] = 1;
        input.lists[0].elements[1] = 2;
    }

    input.lists[1].length = 3;
    input.lists[1].elements = (int*)malloc(3 * sizeof(int));
    if (input.lists[1].elements != NULL) {
        input.lists[1].elements[0] = 3;
        input.lists[1].elements[1] = 4;
        input.lists[1].elements[2] = 5;
    }

    input.lists[2].length = 3;
    input.lists[2].elements = (int*)malloc(3 * sizeof(int));
    if (input.lists[2].elements != NULL) {
        input.lists[2].elements[0] = 6;
        input.lists[2].elements[1] = 7;
        input.lists[2].elements[2] = 8;
    }

    struct ListOfLists result;
    result.lists = NULL;
    result.count = 0;

    findMaxLenLists(&input, &result);

    for (int i = 0; i < result.count; i++) {
        for (int j = 0; j < result.lists[i].length; j++) {
            printf("%d ", result.lists[i].elements[j]);
        }
        printf("\n");
    }

    freeListOfLists(&input);
    freeListOfLists(&result);

    return 0;
}