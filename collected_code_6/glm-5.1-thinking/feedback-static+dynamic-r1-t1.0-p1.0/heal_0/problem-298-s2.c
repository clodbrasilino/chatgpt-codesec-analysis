#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct {
    int *items;
    size_t count;
} List;

typedef struct {
    List *sublists;
    size_t count;
} NestedList;

List find_common_elements(const NestedList *nested, const List *other) {
    List result;
    size_t max_capacity;
    size_t i, j, k;
    int val;
    bool in_other;
    bool in_result;
    int *trimmed;
    const List *sub;

    result.items = NULL;
    result.count = 0;

    if (nested == NULL || other == NULL) {
        return result;
    }

    if (nested->count > 0 && nested->sublists == NULL) {
        return result;
    }

    if (other->count > 0 && other->items == NULL) {
        return result;
    }

    max_capacity = 0;
    for (i = 0; i < nested->count; i++) {
        if (nested->sublists[i].items == NULL && nested->sublists[i].count > 0) {
            continue;
        }
        if (nested->sublists[i].count > SIZE_MAX - max_capacity) {
            return result;
        }
        max_capacity += nested->sublists[i].count;
    }

    if (max_capacity == 0) {
        return result;
    }

    if (max_capacity > SIZE_MAX / sizeof(int)) {
        return result;
    }

    result.items = malloc(max_capacity * sizeof(int));
    if (result.items == NULL) {
        return result;
    }

    for (i = 0; i < nested->count; i++) {
        sub = &nested->sublists[i];
        if (sub->items == NULL) {
            continue;
        }
        for (j = 0; j < sub->count; j++) {
            val = sub->items[j];
            in_other = false;
            for (k = 0; k < other->count; k++) {
                if (val == other->items[k]) {
                    in_other = true;
                    break;
                }
            }
            if (in_other) {
                in_result = false;
                for (k = 0; k < result.count; k++) {
                    if (val == result.items[k]) {
                        in_result = true;
                        break;
                    }
                }
                if (!in_result) {
                    result.items[result.count] = val;
                    result.count++;
                }
            }
        }
    }

    if (result.count == 0) {
        free(result.items);
        result.items = NULL;
    } else {
        trimmed = realloc(result.items, result.count * sizeof(int));
        if (trimmed != NULL) {
            result.items = trimmed;
        }
    }

    return result;
}

int main(void) {
    int data1[] = {1, 2, 3};
    int data2[] = {4, 5, 6};
    int other_data[] = {2, 4, 8};
    List sublist1;
    List sublist2;
    List sublists[2];
    NestedList nested;
    List other;
    List result;
    size_t i;

    sublist1.items = data1;
    sublist1.count = 3;

    sublist2.items = data2;
    sublist2.count = 3;

    sublists[0] = sublist1;
    sublists[1] = sublist2;

    nested.sublists = sublists;
    nested.count = 2;

    other.items = other_data;
    other.count = 3;

    result = find_common_elements(&nested, &other);

    for (i = 0; i < result.count; i++) {
        printf("%d ", result.items[i]);
    }
    printf("\n");

    free(result.items);

    return 0;
}