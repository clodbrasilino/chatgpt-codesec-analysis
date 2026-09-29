#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int element_present(void *list, size_t list_len, size_t elem_size, void *elem, int (*cmp)(const void *, const void *)) {
    if (list == NULL || elem == NULL || cmp == NULL || list_len == 0 || elem_size == 0) {
        return 0;
    }

    unsigned char *bytes = (unsigned char *)list;
    for (size_t i = 0; i < list_len; i++) {
        if (cmp(bytes + i * elem_size, elem) == 0) {
            return 1;
        }
    }

    return 0;
}

typedef struct {
    int id;
    size_t name_len;
    char *name;
} Item;

int item_cmp(const void *a, const void *b) {
    const Item *ia = (const Item *)a;
    const Item *ib = (const Item *)b;
    if (ia->id < ib->id) return -1;
    if (ia->id > ib->id) return 1;
    return 0;
}

int main(void) {
    char name1[] = "Apple";
    char name2[] = "Banana";
    char name3[] = "Cherry";
    
    Item list[] = {
        {1, sizeof(name1), name1},
        {2, sizeof(name2), name2},
        {3, sizeof(name3), name3}
    };
    
    size_t list_len = sizeof(list) / sizeof(list[0]);
    size_t elem_size = sizeof(Item);

    char target_name1[] = "Banana";
    Item target1 = {2, sizeof(target_name1), target_name1};
    
    char target_name2[] = "Date";
    Item target2 = {4, sizeof(target_name2), target_name2};

    int result1 = element_present(list, list_len, elem_size, &target1, item_cmp);
    int result2 = element_present(list, list_len, elem_size, &target2, item_cmp);

    printf("%d\n", result1);
    printf("%d\n", result2);

    return 0;
}