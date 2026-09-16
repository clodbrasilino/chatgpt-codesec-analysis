#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t count;
} StringList;

static int compare_strings(const void *left, const void *right)
{
    const char *const *a = left;
    const char *const *b = right;

    return strcmp(*a, *b);
}

static void sort_sublists(StringList *lists, size_t list_count)
{
    if (lists == NULL) {
        return;
    }

    for (size_t i = 0; i < list_count; ++i) {
        if (lists[i].items != NULL && lists[i].count > 1U) {
            qsort(lists[i].items, lists[i].count,
                  sizeof(lists[i].items[0]), compare_strings);
        }
    }
}

static void print_sublists(const StringList *lists, size_t list_count)
{
    if (lists == NULL) {
        return;
    }

    for (size_t i = 0; i < list_count; ++i) {
        putchar('[');

        for (size_t j = 0; j < lists[i].count; ++j) {
            printf("%s%s", lists[i].items[j],
                   j + 1U < lists[i].count ? ", " : "");
        }

        puts("]");
    }
}

int main(void)
{
    char *first[] = {"pear", "apple", "orange"};
    char *second[] = {"zebra", "ant", "lion", "bear"};
    char *third[] = {"blue", "red", "green"};

    StringList lists[] = {
        {first, sizeof(first) / sizeof(first[0])},
        {second, sizeof(second) / sizeof(second[0])},
        {third, sizeof(third) / sizeof(third[0])}
    };

    const size_t list_count = sizeof(lists) / sizeof(lists[0]);

    sort_sublists(lists, list_count);
    print_sublists(lists, list_count);

    return EXIT_SUCCESS;
}