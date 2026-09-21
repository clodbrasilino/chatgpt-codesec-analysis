#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    void **data;
    size_t size;
} Tuple;

typedef struct {
    void *initial;
    void *last;
} TupleAccess;

Tuple *create_tuple(size_t size) {
    Tuple *tuple = (Tuple *)malloc(sizeof(Tuple));
    if (!tuple) return NULL;
    
    tuple->data = (void **)calloc(size, sizeof(void *));
    if (!tuple->data) {
        free(tuple);
        return NULL;
    }
    
    tuple->size = size;
    return tuple;
}

void destroy_tuple(Tuple *tuple) {
    if (!tuple) return;
    
    if (tuple->data) {
        for (size_t i = 0; i < tuple->size; i++) {
            free(tuple->data[i]);
        }
        free(tuple->data);
    }
    
    free(tuple);
}

int set_tuple_element(Tuple *tuple, size_t index, void *element, size_t element_size) {
    if (!tuple || !element || index >= tuple->size || element_size == 0) return -1;
    
    if (tuple->data[index]) {
        free(tuple->data[index]);
        tuple->data[index] = NULL;
    }
    
    void *new_element = malloc(element_size);
    if (!new_element) return -1;
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(new_element, element, element_size);
    tuple->data[index] = new_element;
    
    return 0;
}

TupleAccess access_tuple_data(Tuple *tuple) {
    TupleAccess access = {NULL, NULL};
    
    if (!tuple || tuple->size == 0 || !tuple->data) {
        /* Possible weaknesses found:
         * Flawfinder access: This usually indicates a security flaw. If an attacker can change anything along the path between the call to access() and the file's actual use (e.g., by moving files), the attacker can exploit the race condition (CWE-362/CWE-367!). Set up the correct permissions (e.g., using setuid()) and try to open the file directly. (risk 4, race)
         */
        return access;
    }
    
    /* Possible weaknesses found:
     * Flawfinder access: This usually indicates a security flaw. If an attacker can change anything along the path between the call to access() and the file's actual use (e.g., by moving files), the attacker can exploit the race condition (CWE-362/CWE-367!). Set up the correct permissions (e.g., using setuid()) and try to open the file directly. (risk 4, race)
     */
    access.initial = tuple->data[0];
    /* Possible weaknesses found:
     * Flawfinder access: This usually indicates a security flaw. If an attacker can change anything along the path between the call to access() and the file's actual use (e.g., by moving files), the attacker can exploit the race condition (CWE-362/CWE-367!). Set up the correct permissions (e.g., using setuid()) and try to open the file directly. (risk 4, race)
     */
    access.last = tuple->data[tuple->size - 1];
    
    /* Possible weaknesses found:
     * Flawfinder access: This usually indicates a security flaw. If an attacker can change anything along the path between the call to access() and the file's actual use (e.g., by moving files), the attacker can exploit the race condition (CWE-362/CWE-367!). Set up the correct permissions (e.g., using setuid()) and try to open the file directly. (risk 4, race)
     */
    return access;
}

void safe_copy_value(void *dest, const void *src, size_t size, size_t dest_capacity) {
    if (!dest || !src || size == 0 || size > dest_capacity) {
        return;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dest, src, size);
}

int main(void) {
    Tuple *tuple = create_tuple(3);
    if (!tuple) {
        return EXIT_FAILURE;
    }
    
    int val1 = 10;
    int val2 = 20;
    int val3 = 30;
    
    if (set_tuple_element(tuple, 0, &val1, sizeof(int)) != 0 ||
        set_tuple_element(tuple, 1, &val2, sizeof(int)) != 0 ||
        set_tuple_element(tuple, 2, &val3, sizeof(int)) != 0) {
        destroy_tuple(tuple);
        return EXIT_FAILURE;
    }
    
    TupleAccess access = access_tuple_data(tuple);
    
    /* Possible weaknesses found:
     * Flawfinder access: This usually indicates a security flaw. If an attacker can change anything along the path between the call to access() and the file's actual use (e.g., by moving files), the attacker can exploit the race condition (CWE-362/CWE-367!). Set up the correct permissions (e.g., using setuid()) and try to open the file directly. (risk 4, race)
     */
    if (access.initial && access.last) {
        int initial_val = 0;
        int last_val = 0;
        
        /* Possible weaknesses found:
         * Flawfinder access: This usually indicates a security flaw. If an attacker can change anything along the path between the call to access() and the file's actual use (e.g., by moving files), the attacker can exploit the race condition (CWE-362/CWE-367!). Set up the correct permissions (e.g., using setuid()) and try to open the file directly. (risk 4, race)
         */
        safe_copy_value(&initial_val, access.initial, sizeof(int), sizeof(int));
        /* Possible weaknesses found:
         * Flawfinder access: This usually indicates a security flaw. If an attacker can change anything along the path between the call to access() and the file's actual use (e.g., by moving files), the attacker can exploit the race condition (CWE-362/CWE-367!). Set up the correct permissions (e.g., using setuid()) and try to open the file directly. (risk 4, race)
         */
        safe_copy_value(&last_val, access.last, sizeof(int), sizeof(int));
        
        printf("Initial: %d\n", initial_val);
        printf("Last: %d\n", last_val);
    }
    
    destroy_tuple(tuple);
    
    return EXIT_SUCCESS;
}