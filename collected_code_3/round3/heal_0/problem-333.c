#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} sublist;

int compare(const void *s1, const void *s2)
{
    sublist *e1 = (sublist *)s1;
    sublist *e2 = (sublist *)s2;
    return e1->second - e2->second;
}

void sort_sublist(sublist *list, int n)
{
    qsort(list, n, sizeof(sublist), compare);
}

int main()
{
    sublist list[] = {{1, 20}, {2, 5}, {3, 15}, {4, 10}};
    int n = sizeof(list)/sizeof(list[0]);

    sort_sublist(list, n);

    for(int i = 0; i < n; i++)
    {
        printf("%d %d\n", list[i].first, list[i].second);
    }

    return 0;
}