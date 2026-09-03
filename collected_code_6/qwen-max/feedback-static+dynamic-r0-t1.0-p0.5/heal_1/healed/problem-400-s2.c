#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int a;
    int b;
} Tuple;

typedef struct {
    Tuple *tuples;
    int count;
} TupleList;

int tuple_compare(const void *a, const void *b) {
    const Tuple *ta = (const Tuple *)a;
    const Tuple *tb = (const Tuple *)b;
    if (ta->a != tb->a) return ta->a - tb->a;
    return ta->b - tb->b;
}

void count_unique_tuples(TupleList *list) {
    qsort(list->tuples, list->count, sizeof(Tuple), tuple_compare);
    int unique_count = 1;
    for (int i = 1; i < list->count; i++) {
        if (list->tuples[i].a != list->tuples[i-1].a || list->tuples[i].b != list->tuples[i-1].b) {
            unique_count++;
        }
    }
    printf("Unique tuples: %d\n", unique_count);
}

int main() {
    TupleList list = { .tuples = NULL, .count = 0 };
    int n;
    scanf("%d", &n);
    list.tuples = (Tuple *)malloc(n * sizeof(Tuple));
    if (list.tuples == NULL) {
        return 1;
    }
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &list.tuples[i].a, &list.tuples[i].b);
    }
    list.count = n;
    count_unique_tuples(&list);
    free(list.tuples);
    return 0;
}