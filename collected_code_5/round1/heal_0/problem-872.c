#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int *array;
	int count;
} NestedList;

int isSubset(NestedList *a, NestedList *b) {
	int i, j, flag;

	for (i = 0; i < a->count; i++) {
		flag = 0;
		for (j = 0; j < b->count; j++) {
			if (a->array[i] == b->array[j])
				flag = 1;
		}
		if (flag == 0)
			return 0;
	}

	return 1;
}

int main() {
	int a[] = {1, 2, 3, 4, 5};
	int b[] = {1, 2, 3};

	NestedList listA;
	listA.array = a;
	listA.count = sizeof(a) / sizeof(a[0]);

	NestedList listB;
	listB.array = b;
	listB.count = sizeof(b) / sizeof(b[0]);

	int result = isSubset(&listB, &listA);

	if (result)
		printf("List B is a subset of List A\n");
	else
		printf("List B is not a subset of List A\n");

	return 0;
}