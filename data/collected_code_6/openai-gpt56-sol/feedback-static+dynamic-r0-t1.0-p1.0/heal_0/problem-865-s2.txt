#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *value;
} ListItem;

typedef int (*MapFunction)(const ListItem *, void *);

static int map_list(const ListItem *items, size_t length, MapFunction function,
                    void *context)
{
    if ((items == NULL && length != 0U) || function == NULL) {
        return EINVAL;
    }

    for (size_t i = 0U; i < length; ++i) {
        int result = function(&items[i], context);

        if (result != 0) {
            return result;
        }
    }

    return 0;
}

static int print_item(const ListItem *item, void *context)
{
    const size_t *repetitions = context;

    if (item == NULL || item->value == NULL || repetitions == NULL) {
        return EINVAL;
    }

    for (size_t i = 0U; i < *repetitions; ++i) {
        if (puts(item->value) == EOF) {
            return EIO;
        }
    }

    return 0;
}

static int print_list_n_times(const ListItem *items, size_t length,
                              size_t repetitions)
{
    return map_list(items, length, print_item, &repetitions);
}

int main(void)
{
    const ListItem items[] = {
        {"apple"},
        {"banana"},
        {"cherry"}
    };
    const size_t item_count = sizeof(items) / sizeof(items[0]);
    int result = print_list_n_times(items, item_count, 3U);

    if (result != 0) {
        errno = result;
        perror("print_list_n_times");
        return EXIT_FAILURE;
    }

    if (fflush(stdout) == EOF) {
        perror("fflush");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}