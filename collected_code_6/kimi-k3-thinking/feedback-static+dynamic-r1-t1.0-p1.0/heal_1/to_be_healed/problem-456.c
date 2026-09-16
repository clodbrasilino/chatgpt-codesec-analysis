#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_string(char *str)
{
    size_t len;
    size_t i;
    /* Possible weaknesses found:
     *  The scope of the variable 'temp' can be reduced. [variableScope]
     */
    char temp;

    if (str == NULL) {
        return;
    }

    len = strlen(str);
    for (i = 0; i < len / 2; i++) {
        temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

int reverse_string_list(char **list, size_t count)
{
    size_t i;

    if (list == NULL) {
        return -1;
    }

    for (i = 0; i < count; i++) {
        if (list[i] == NULL) {
            return -1;
        }
    }

    for (i = 0; i < count; i++) {
        reverse_string(list[i]);
    }

    return 0;
}

int main(void)
{
    const char *strings[] = {"hello", "world", "programming", "language", "reverse"};
    size_t count = sizeof(strings) / sizeof(strings[0]);
    size_t i;
    size_t j;
    char **list;
    /* Possible weaknesses found:
     *  The scope of the variable 'len' can be reduced. [variableScope]
     */
    size_t len;

    list = malloc(count * sizeof(*list));
    if (list == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        list[i] = NULL;
    }

    for (i = 0; i < count; i++) {
        len = strlen(strings[i]) + 1;
        list[i] = malloc(len);
        if (list[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            for (j = 0; j < count; j++) {
                free(list[j]);
            }
            free(list);
            return EXIT_FAILURE;
        }
        memcpy(list[i], strings[i], len);
    }

    printf("Original list:\n");
    for (i = 0; i < count; i++) {
        printf("%s\n", list[i]);
    }

    if (reverse_string_list(list, count) != 0) {
        fprintf(stderr, "Failed to reverse string list\n");
        for (i = 0; i < count; i++) {
            free(list[i]);
        }
        free(list);
        return EXIT_FAILURE;
    }

    printf("Reversed list:\n");
    for (i = 0; i < count; i++) {
        printf("%s\n", list[i]);
    }

    for (i = 0; i < count; i++) {
        free(list[i]);
    }
    free(list);

    return EXIT_SUCCESS;
}