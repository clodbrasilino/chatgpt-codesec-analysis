#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Defining the structure for a dictionary item
typedef struct {
    char *key;
    char *value;
} dictionary;

// Defining the structure for received keys
typedef struct {
    char **keys;
    int count;
} keylist;

void get_keys(dictionary *dic, int n, keylist *kl) {
    kl->keys = (char **)malloc(sizeof(char *) * n);
    kl->count = n;
    for (int i = 0; i < n; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL '*kl.keys' [CWE-690] [-Wanalyzer-possible-null-dereference]
         *  dereference of possibly-NULL 'kl.keys' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        kl->keys[i] = (char *)malloc(strlen(dic[i].key) + 1);
        strcpy(kl->keys[i], dic[i].key);
    }
}

void free_keylist(keylist *kl) {
    for (int i = 0; i < kl->count; i++) {
        free(kl->keys[i]);
    }
    free(kl->keys);
}

int main() {
    // Create a dictionary with 2 items
    dictionary dic[2] = {
        { "key1", "value1" },
        { "key2", "value2" }
    };
    
    keylist kl;
    
    get_keys(dic, 2, &kl);
    
    for (int i = 0; i < kl.count; i++) {
        printf("%s\n", kl.keys[i]);
    }
    
    // freeing the allocated memory for keys
    free_keylist(&kl);
    
    return 0;
}