#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Sublist;

int compare_by_second(const void *a, const void *b)
{
    const Sublist *sa = (const Sublist *)a;
    const Sublist *sb = (const Sublist *)b;
    
    if (sa->second < sb->second)
        return -1;
    if (sa->second > sb->second)
        return 1;
    return 0;
}

int sort_list_by_second(Sublist *list, size_t size)
{
    if (list == NULL)
        return -1;
    
    if (size <= 1)
        return 0;
    
    qsort(list, size, sizeof(Sublist), compare_by_second);
    return 0;
}

int main(void)
{
    Sublist list[] = {{1, 5}, {2, 3}, {3, 8}, {4, 1}, {5, 2}};
    size_t size = sizeof(list) / sizeof(list[0]);
    size_t i;
    
    if (sort_list_by_second(list, size) != 0) {
        fprintf(stderr, "Error: Failed to sort list\n");
        return EXIT_FAILURE;
    }
    
    for (i = 0; i < size; i++) {
        printf("(%d, %d)\n", list[i].first, list[i].second);
    }
    
    return EXIT_SUCCESS;
}