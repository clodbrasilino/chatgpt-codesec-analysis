#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **string_to_list(const char *str, size_t *list_len) {
    if (str == NULL || list_len == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    if (len == 0) {
        *list_len = 0;
        char **empty_list = malloc(sizeof(char *));
        if (empty_list) {
            empty_list[0] = NULL;
        }
        return empty_list;
    }

    char *rest = strdup(str);
    if (rest == NULL) {
        return NULL;
    }

    size_t capacity = 10;
    char **list = malloc(capacity * sizeof(char *));
    if (list == NULL) {
        free(rest);
        return NULL;
    }

    size_t count = 0;
    char *token = strtok(rest, " ");
    while (token != NULL) {
        if (count >= capacity) {
            capacity *= 2;
            char **temp = realloc(list, capacity * sizeof(char *));
            if (temp == NULL) {
                for (size_t i = 0; i < count; i++) free(list[i]);
                free(list);
                free(rest);
                return NULL;
            }
            list = temp;
        }
        list[count] = strdup(token);
        if (list[count] == NULL) {
            for (size_t i = 0; i < count; i++) free(list[i]);
            free(list);
            free(rest);
            return NULL;
        }
        count++;
        token = strtok(NULL, " ");
    }

    free(rest);

    char **final_list = realloc(list, (count + 1) * sizeof(char *));
    if (final_list == NULL) {
        for (size_t i = 0; i < count; i++) free(list[i]);
        free(list);
        return NULL;
    }
    list = final_list;
    list[count] = NULL;
    *list_len = count;

    return list;
}

void free_list(char **list, size_t list_len) {
    if (list == NULL) {
        return;
    }
    for (size_t i = 0; i < list_len; i++) {
        free(list[i]);
    }
    free(list);
}

int main(void) {
    size_t list_len1 = 0;
    char **list1 = string_to_list("python programming", &list_len1);
    if (list1 != NULL) {
        printf("['");
        for (size_t i = 0; i < list_len1; i++) {
            printf("%s", list1[i]);
            if (i < list_len1 - 1) printf("', '");
        }
        printf("']\n");
        free_list(list1, list_len1);
    } else {
        printf("[]\n");
    }

    size_t list_len2 = 0;
    char **list2 = string_to_list("lists tuples strings", &list_len2);
    if (list2 != NULL) {
        printf("['");
        for (size_t i = 0; i < list_len2; i++) {
            printf("%s", list2[i]);
            if (i < list_len2 - 1) printf("', '");
        }
        printf("']\n");
        free_list(list2, list_len2);
    } else {
        printf("[]\n");
    }

    size_t list_len3 = 0;
    char **list3 = string_to_list("write a program", &list_len3);
    if (list3 != NULL) {
        printf("['");
        for (size_t i = 0; i < list_len3; i++) {
            printf("%s", list3[i]);
            if (i < list_len3 - 1) printf("', '");
        }
        printf("']\n");
        free_list(list3, list_len3);
    } else {
        printf("[]\n");
    }

    return 0;
}