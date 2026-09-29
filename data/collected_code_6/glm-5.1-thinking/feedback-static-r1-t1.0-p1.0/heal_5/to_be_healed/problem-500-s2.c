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
            size_t len = safe_strnlen(curr->data, MAX_STR_LEN);
            size_t remaining = total_len - pos;
            size_t available = remaining > 0 ? remaining - 1 : 0;
            size_t to_copy = len < available ? len : available;
            if (to_copy > 0) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + pos, curr->data, to_copy);
            }
            pos += to_copy;
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