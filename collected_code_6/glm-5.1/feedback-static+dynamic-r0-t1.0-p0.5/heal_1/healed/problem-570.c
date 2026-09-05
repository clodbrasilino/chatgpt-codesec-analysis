#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_words(char **list, size_t size, const char *substr, char ch) {
    if (list == NULL || size == 0) {
        return;
    }

    size_t count = 0;
    for (size_t i = 0; i < size; i++) {
        if (list[i] != NULL) {
            int match = 0;
            if (substr != NULL && *substr != '\0') {
                if (strstr(list[i], substr) != NULL) match = 1;
            } else if (ch != '\0') {
                if (strchr(list[i], ch) != NULL) match = 1;
            }
            if (!match) {
                list[count] = list[i];
                count++;
            }
        }
    }

    for (size_t i = count; i < size; i++) {
        list[i] = NULL;
    }
}

void print_list(char **list, size_t size) {
    printf("[");
    for (size_t i = 0; i < size; i++) {
        if (list[i] == NULL) {
            break;
        }
        printf("'%s'", list[i]);
        if (i + 1 < size && list[i+1] != NULL) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(void) {
    char *list0[] = {"Red", "", "Green", "Orange", "White"};
    size_t size0 = sizeof(list0) / sizeof(list0[0]);
    remove_words(list0, size0, "an", '\0');
    print_list(list0, size0);

    char *list1[] = {"Red", "", "Green", "Orange", "White"};
    size_t size1 = sizeof(list1) / sizeof(list1[0]);
    remove_words(list1, size1, NULL, '\0');
    print_list(list1, size1);

    char *list2[] = {"Red &", "Orange+", "Green", "Orange", "White"};
    size_t size2 = sizeof(list2) / sizeof(list2[0]);
    remove_words(list2, size2, NULL, '+');
    print_list(list2, size2);

    char *words[] = {"apple", "banana", "cherry", "date", "elderberry"};
    size_t size = sizeof(words) / sizeof(words[0]);
    remove_words(words, size, "an", '\0');
    print_list(words, size);

    return 0;
}