#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
} Person;

void rearrangeTuples(Person **arr, const int *order, int n) {
    Person **temp = malloc(n * sizeof(Person *));
    for (int i = 0; i < n; i++) {
        if (order[i] >= 0 && order[i] < n) {
            temp[order[i]] = arr[i];
        }
    }
    for (int i = 0; i < n; i++) {
        arr[i] = temp[i];
    }
    free(temp);
}

int main() {
    int n = 3;
    Person *persons[n];
    persons[0] = malloc(sizeof(Person));
    persons[1] = malloc(sizeof(Person));
    persons[2] = malloc(sizeof(Person));

    persons[0]->id = 1;
    strcpy(persons[0]->name, "Alice");
    persons[1]->id = 2;
    strcpy(persons[1]->name, "Bob");
    persons[2]->id = 3;
    strcpy(persons[2]->name, "Charlie");

    const int order[] = {2, 0, 1};

    rearrangeTuples(persons, order, n);

    for (int i = 0; i < n; i++) {
        printf("ID: %d, Name: %s\n", persons[i]->id, persons[i]->name);
    }

    for (int i = 0; i < n; i++) {
        free(persons[i]);
    }
    return 0;
}