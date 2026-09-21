#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct Tuple {
    int initial;
    char *data;
    struct Tuple *next;
} Tuple;

void free_tuple_list(Tuple *head) {
    Tuple *current = head;
    while (current != NULL) {
        Tuple *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
}

static size_t safe_strlen(const char *str, size_t max_len) {
    if (str == NULL) {
        return 0;
    }
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

static char *safe_strdup(const char *src, size_t len) {
    if (len == 0) {
        char *result = malloc(1);
        if (result != NULL) {
            result[0] = '\0';
        }
        return result;
    }
    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }
    memcpy(result, src, len);
    result[len] = '\0';
    return result;
}

static char *safe_concat(const char *s1, size_t len1, const char *s2, size_t len2) {
    size_t total_len = len1 + len2;
    if (total_len < len1 || total_len < len2) {
        return NULL;
    }
    if (total_len > SIZE_MAX - 1) {
        return NULL;
    }
    char *result = malloc(total_len + 1);
    if (result == NULL) {
        return NULL;
    }
    if (len1 > 0) {
        memcpy(result, s1, len1);
    }
    if (len2 > 0) {
        memcpy(result + len1, s2, len2);
    }
    result[total_len] = '\0';
    return result;
}

Tuple *join_tuples(Tuple *head) {
    if (head == NULL) {
        return NULL;
    }
    Tuple *result = NULL;
    Tuple *result_tail = NULL;
    Tuple *current = head;
    while (current != NULL) {
        if (current->data == NULL) {
            free_tuple_list(result);
            return NULL;
        }
        size_t current_len = strlen(current->data);
        if (current_len >= SIZE_MAX) {
            free_tuple_list(result);
            return NULL;
        }
        Tuple *existing = result;
        while (existing != NULL) {
            if (existing->initial == current->initial) {
                size_t existing_len = strlen(existing->data);
                if (existing_len > SIZE_MAX - current_len) {
                    free_tuple_list(result);
                    return NULL;
                }
                char *new_data = safe_concat(existing->data, existing_len,
                                             current->data, current_len);
                if (new_data == NULL) {
                    free_tuple_list(result);
                    return NULL;
                }
                free(existing->data);
                existing->data = new_data;
                break;
            }
            existing = existing->next;
        }
        if (existing == NULL) {
            Tuple *new_tuple = malloc(sizeof(Tuple));
            if (new_tuple == NULL) {
                free_tuple_list(result);
                return NULL;
            }
            new_tuple->initial = current->initial;
            new_tuple->data = safe_strdup(current->data, current_len);
            if (new_tuple->data == NULL) {
                free(new_tuple);
                free_tuple_list(result);
                return NULL;
            }
            new_tuple->next = NULL;
            if (result == NULL) {
                result = new_tuple;
                result_tail = new_tuple;
            } else {
                result_tail->next = new_tuple;
                result_tail = new_tuple;
            }
        }
        current = current->next;
    }
    return result;
}

int main(void) {
    Tuple *head = NULL;
    Tuple *tail = NULL;
    int initials[] = {1, 2, 1, 3, 2};
    const char *datas[] = {"a", "b", "c", "d", "e"};
    size_t count = sizeof(initials) / sizeof(initials[0]);
    for (size_t i = 0; i < count; i++) {
        Tuple *new_tuple = malloc(sizeof(Tuple));
        if (new_tuple == NULL) {
            free_tuple_list(head);
            return 1;
        }
        new_tuple->initial = initials[i];
        const char *src = datas[i];
        size_t data_len = 0;
        if (src != NULL) {
            const char *ptr = src;
            while (*ptr != '\0') {
                ptr++;
                data_len++;
            }
        }
        new_tuple->data = safe_strdup(src, data_len);
        if (new_tuple->data == NULL) {
            free(new_tuple);
            free_tuple_list(head);
            return 1;
        }
        new_tuple->next = NULL;
        if (head == NULL) {
            head = new_tuple;
            tail = new_tuple;
        } else {
            tail->next = new_tuple;
            tail = new_tuple;
        }
    }
    Tuple *joined = join_tuples(head);
    if (joined == NULL && head != NULL) {
        free_tuple_list(head);
        return 1;
    }
    Tuple *current = joined;
    while (current != NULL) {
        printf("%d: %s\n", current->initial, current->data);
        current = current->next;
    }
    free_tuple_list(head);
    free_tuple_list(joined);
    return 0;
}