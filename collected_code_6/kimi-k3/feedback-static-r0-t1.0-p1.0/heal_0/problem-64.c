#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int first;
    int second;
    char *third;
} Tuple;

typedef int (*Comparator)(const void *, const void *);

int compare_tuples(const void *a, const void *b)
{
    const Tuple *ta = (const Tuple *)a;
    const Tuple *tb = (const Tuple *)b;
    
    if (ta->first != tb->first)
        return (ta->first > tb->first) - (ta->first < tb->first);
    if (ta->second != tb->second)
        return (ta->second > tb->second) - (ta->second < tb->second);
    return strcmp(ta->third, tb->third);
}

void sort_tuples(Tuple *arr, size_t count, Comparator cmp)
{
    if (arr == NULL || cmp == NULL || count == 0)
        return;
    qsort(arr, count, sizeof(Tuple), cmp);
}

int main(void)
{
    Tuple tuples[] = {
        {3, 2, "apple"},
        {1, 5, "banana"},
        {3, 1, "cherry"},
        {1, 3, "date"}
    };
    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    
    sort_tuples(tuples, count, compare_tuples);
    
    for (size_t i = 0; i < count; i++) {
        printf("(%d, %d, %s)\n", tuples[i].first, tuples[i].second, tuples[i].third);
    }
    
    return 0;
}