#include <stdio.h>
#include <string.h>

#define MAX_SIZE 100

// Define a key-value pair
typedef struct {
    char key[MAX_SIZE];
    int value;
} KeyValuePair;

// Define a dictionary
typedef struct {
    KeyValuePair pairs[MAX_SIZE];
    int size;
} Dictionary;

// Define a tuple
typedef struct {
    int first;
    int second;
    Dictionary dict;
} Tuple;

// Function to add a dictionary to a tuple
void addDictionaryToTuple(Tuple *tuple, Dictionary dict) {
    tuple->dict = dict;
}

int main() {
    // Create a dictionary
    Dictionary dict;
    dict.size = 0;

    // Add a key-value pair to the dictionary
    strcpy(dict.pairs[dict.size].key, "example");
    dict.pairs[dict.size].value = 123;
    dict.size++;

    // Create a tuple
    Tuple tuple;
    tuple.first = 1;
    tuple.second = 2;

    // Add the dictionary to the tuple
    addDictionaryToTuple(&tuple, dict);

    // Print the tuple
    printf("Tuple: (%d, %d, {", tuple.first, tuple.second);
    for (int i = 0; i < tuple.dict.size; i++) {
        printf("(%s: %d)", tuple.dict.pairs[i].key, tuple.dict.pairs[i].value);
        if (i < tuple.dict.size - 1) {
            printf(", ");
        }
    }
    printf("})\n");

    return 0;
}