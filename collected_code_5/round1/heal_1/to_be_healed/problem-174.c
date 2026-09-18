#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct kv_kv_pair {
    char *key;
    char *value;
} kv_pair;

typedef struct dict {
    kv_pair **kv_pairs;
    int size;
} dict;

void add_kv_pair(dict *d, kv_pair *pair){
    kv_pair **new_kv_pairs = (kv_pair **)realloc(d->kv_pairs, (d->size + 1) * sizeof(kv_pair *));
    
    if(new_kv_pairs == NULL) {
        printf("Unable to allocate memory.\n");
        return;
    }

    new_kv_pairs[d->size] = pair;
    d->kv_pairs = new_kv_pairs;
    d->size++;
}

dict* initialize_dict() {
    dict *d = (dict *)malloc(sizeof(dict));
    if(d == NULL) {
        printf("Unable to allocate memory.\n");
        return NULL;
    }
    d->kv_pairs = NULL;
    d->size = 0;
    return d;
}

kv_pair* create_kv_pair(char *key, char *value) {
    kv_pair *pair = (kv_pair *)malloc(sizeof(kv_pair));
    if(pair == NULL) {
        printf("Unable to allocate memory.\n");
        return NULL;
    }
    pair->key = key;
    pair->value = value;
    return pair;
}

int main() {
    dict *d = initialize_dict();
    if(d!=NULL){
        char *key = "Key";
        char *value = "Value";
        kv_pair *pair = create_kv_pair(key, value);
        if(pair!=NULL){
            add_kv_pair(d, pair);
            /* Possible weaknesses found:
             *  Array access (via field 'kv_pairs') results in a null pointer dereference [core.NullDereference]
             */
            printf("Added the key-value pair: %s-%s into dictionary.\n", d->kv_pairs[0]->key, d->kv_pairs[0]->value);
            free(pair);
        }
        free(d);
    }
    return 0;
}