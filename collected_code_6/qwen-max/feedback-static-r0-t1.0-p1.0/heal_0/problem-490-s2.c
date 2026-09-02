#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Pair;

typedef struct {
    Pair *pairs;
    size_t count;
} TupleList;

TupleList* create_tuple_list(size_t count) {
    TupleList *list = (TupleList *)malloc(sizeof(TupleList));
    list->pairs = (Pair *)malloc(count * sizeof(Pair));
    list->count = count;
    return list;
}

void free_tuple_list(TupleList *list) {
    free(list->pairs);
    free(list);
}

int is_symmetric(int a, int b) {
    return a == b;
}

TupleList* extract_symmetric_pairs(const TupleList *input) {
    size_t symmetric_count = 0;
    for (size_t i = 0; i < input->count; ++i) {
        if (is_symmetric(input->pairs[i].first, input->pairs[i].second)) {
            ++symmetric_count;
        }
    }

    TupleList *result = create_tuple_list(symmetric_count);
    size_t index = 0;
    for (size_t i = 0; i < input->count; ++i) {
        if (is_symmetric(input->pairs[i].first, input->pairs[i].second)) {
            result->pairs[index++] = input->pairs[i];
        }
    }
    return result;
}

void print_tuple_list(const TupleList *list) {
    for (size_t i = 0; i < list->count; ++i) {
        printf("(%d, %d)\n", list->pairs[i].first, list->pairs[i].second);
    }
}

int main() {
    TupleList *input = create_tuple_list(5);
    input->pairs[0] = (Pair){1, 1};
    input->pairs[1] = (Pair){2, 3};
    input->pairs[2] = (Pair){4, 4};
    input->pairs[3] = (Pair){5, 6};
    input->pairs[4] = (Pair){7, 7};

    TupleList *symmetric_pairs = extract_symmetric_pairs(input);
    print_tuple_list(symmetric_pairs);

    free_tuple_list(input);
    free_tuple_list(symmetric_pairs);
    return 0;
}