#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *first;
    char *second;
} Tuple;

typedef struct {
    Tuple *tuples;
    int count;
} TupleList;

int compareTuples(const void *a, const void *b) {
    const Tuple *tupleA = (const Tuple *)a;
    const Tuple *tupleB = (const Tuple *)b;
    int cmpFirst = strcmp(tupleA->first, tupleB->first);
    if (cmpFirst != 0) return cmpFirst;
    return strcmp(tupleA->second, tupleB->second);
}

void assignFrequencies(TupleList *list) {
    if (list->count == 0) return;

    qsort(list->tuples, list->count, sizeof(Tuple), compareTuples);

    int frequency = 1;
    for (int i = 1; i < list->count; ++i) {
        if (strcmp(list->tuples[i].first, list->tuples[i - 1].first) == 0 && 
            strcmp(list->tuples[i].second, list->tuples[i - 1].second) == 0) {
            frequency++;
        } else {
            printf("%s, %s: %d\n", list->tuples[i - 1].first, list->tuples[i - 1].second, frequency);
            frequency = 1;
        }
    }
    printf("%s, %s: %d\n", list->tuples[list->count - 1].first, list->tuples[list->count - 1].second, frequency);
}

int main() {
    TupleList list;
    list.count = 5;
    list.tuples = (Tuple *)malloc(list.count * sizeof(Tuple));

    list.tuples[0].first = strdup("apple");
    list.tuples[0].second = strdup("banana");
    list.tuples[1].first = strdup("apple");
    list.tuples[1].second = strdup("banana");
    list.tuples[2].first = strdup("cherry");
    list.tuples[2].second = strdup("date");
    list.tuples[3].first = strdup("apple");
    list.tuples[3].second = strdup("banana");
    list.tuples[4].first = strdup("cherry");
    list.tuples[4].second = strdup("date");

    assignFrequencies(&list);

    for (int i = 0; i < list.count; ++i) {
        free(list.tuples[i].first);
        free(list.tuples[i].second);
    }
    free(list.tuples);

    return 0;
}