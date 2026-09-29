#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STR_LEN 4096

static size_t safe_strnlen(const char *s, size_t maxlen) {
    const char *end = memchr(s, '\0', maxlen);
    return end ? (size_t)(end - s) : maxlen;
}

struct Node {
    char *data;
    struct Node *next;
};

char *concatenate_list(struct Node *head) {
    size_t total_len = 1;
    struct Node *curr = head;
    
    while (curr != NULL) {
        if (curr->data != NULL) {
            size_t len = safe_strnlen(curr->data, MAX_STR_LEN);
            if (len > SIZE_MAX - total_len) {
                return NULL;
            }
            total_len += len;
        }
        curr = curr->next;
    }
    
    char *result = malloc(total_len);
    if (result == NULL) {
        return NULL;
    }
    
    size_t pos = 0;
    curr = head;
    while (curr != NULL) {
        if (curr->data != NULL) {
            size_t remaining = total_len - pos;
            size_t len = safe_strnlen(curr->data, MAX_STR_LEN);
            int written = snprintf(result + pos, remaining, "%.*s", (int)len, curr->data);
            if (written > 0) {
                pos += (size_t)written;
                if (pos >= total_len) {
                    pos = total_len - 1;
                    break;
                }
            }
        }
        curr = curr->next;
    }
    
    result[pos] = '\0';
    return result;
}

int main(void) {
    struct Node n3 = {"!", NULL};
    struct Node n2 = {"world", &n3};
    struct Node n1 = {"Hello, ", &n2};
    
    char *result = concatenate_list(&n1);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }
    
    return 0;
}