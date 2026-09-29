#include <stdio.h>
#include <string.h>
#define MAX 2

typedef enum {INT, STRING, FLOAT} Type;

typedef struct{
    Type type;
    union {
        int intValue;
        float floatValue;
        char str[20];
    } value;
} Data;

typedef struct{
    char key[20];
    Data data;
} Dict;

typedef struct{
    Dict tuple[MAX];
} Tuple;

void addDictToTuple(Tuple* tuple, Dict* dict, int pos){
    tuple->tuple[pos] = *dict;
}

int main(){
    Data data;
    data.type = STRING;
    strcpy(data.value.str, "This is a string");

    Dict dict;
    strcpy(dict.key, "Key1");
    dict.data = data;

    Tuple tuple;

    addDictToTuple(&tuple, &dict, 0);

    if(tuple.tuple[0].data.type == STRING){
        printf("\n[Key: %s, Value: %s]", tuple.tuple[0].key, tuple.tuple[0].data.value.str);
    } else {
        printf("\nInvalid Type");
    }

    return 0;
}