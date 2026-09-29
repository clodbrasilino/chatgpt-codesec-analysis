#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LENGTH (1024UL * 1024UL)

static char *duplicate_string(const char *src)
{
    size_t len;
    size_t j;
    char *copy;

    if (src == NULL)
    {
        return NULL;
    }

    len = strnlen(src, MAX_STRING_LENGTH);
    if (len == MAX_STRING_LENGTH)
    {
        return NULL;
    }

    copy = malloc(len + 1);
    if (copy == NULL)
    {
        return NULL;
    }

    for (j = 0; j < len; j++)
    {
        copy[j] = src[j];
    }
    copy[len] = '\0';

    return copy;
}

char **tuple_to_list(const char **tuple, size_t count, const char *str, size_t *out_count)
{
    char **list;
    size_t new_count;
    size_t i;
    size_t k;

    if (str == NULL || out_count == NULL)
    {
        return NULL;
    }

    if (tuple == NULL && count > 0)
    {
        return NULL;
    }

    if (count > SIZE_MAX / 2)
    {
        return NULL;
    }

    new_count = count * 2;

    if (new_count == 0)
    {
        *out_count = 0;
        return NULL;
    }

    if (new_count > SIZE_MAX / sizeof(char *))
    {
        return NULL;
    }

    list = malloc(new_count * sizeof(*list));
    if (list == NULL)
    {
        return NULL;
    }

    for (i = 0; i < count; i++)
    {
        list[i * 2] = duplicate_string(tuple[i]);
        if (list[i * 2] == NULL)
        {
            for (k = 0; k < i * 2; k++)
            {
                free(list[k]);
            }
            free(list);
            return NULL;
        }

        list[i * 2 + 1] = duplicate_string(str);
        if (list[i * 2 + 1] == NULL)
        {
            for (k = 0; k <= i * 2; k++)
            {
                free(list[k]);
            }
            free(list);
            return NULL;
        }
    }

    *out_count = new_count;
    return list;
}

void free_list(char **list, size_t count)
{
    size_t i;

    if (list == NULL)
    {
        return;
    }

    for (i = 0; i < count; i++)
    {
        free(list[i]);
    }

    free(list);
}

int main(void)
{
    const char *tuple[] = {"apple", "banana", "cherry"};
    size_t tuple_count = sizeof(tuple) / sizeof(tuple[0]);
    const char *insert_str = "inserted";
    size_t list_count = 0;
    char **list;
    size_t i;

    list = tuple_to_list(tuple, tuple_count, insert_str, &list_count);
    if (list == NULL)
    {
        fprintf(stderr, "Error: failed to convert tuple to list\n");
        return EXIT_FAILURE;
    }

    printf("[");
    for (i = 0; i < list_count; i++)
    {
        printf("\"%s\"", list[i]);
        if (i + 1 < list_count)
        {
            printf(", ");
        }
    }
    printf("]\n");

    free_list(list, list_count);

    return EXIT_SUCCESS;
}