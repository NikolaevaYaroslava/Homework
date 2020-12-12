#include <stdio.h>

#define ARR_SIZE 500500

void siftUp(int *heap, int child);

int extractMin(int * heap, int * size);

void siftDown(int *heap, int parent, int size);

void swap(int *x, int *y);

int heap[ARR_SIZE];

int main(int argc, char* argv[]) {

    if (argc < 3) {
        printf("provide 2 file names\n");
        return 1;
    }

	int arrSize;
	int heapSize = 0;

	freopen(argv[1], "r", stdin);
	freopen(argv[2], "w", stdout);

    scanf("%d", &arrSize);

	for (int i = 0; i < arrSize; i++) {
		int inp;
        scanf("%d", &inp);
		heap[heapSize++] = inp;
		siftUp(heap, heapSize - 1);
	}

	for (int i = 0; i < arrSize; i++) {
		int min = extractMin(heap, &heapSize);
        printf("%d\n", min);
	}

    printf("\n");

	return 0;
}

void siftUp(int * heap, int child) {
	int parent;
	
	if (child == 0)
		return;

	parent = (child - 1) / 2;

	if (heap[child] < heap[parent]) {
		swap(&heap[parent], &heap[child]);
		siftUp(heap, parent);
	}

}

int extractMin(int * heap, int * size) {
	
	int res = heap[0];

	swap(&heap[0], &heap[*size - 1]);
	(*size)--;
	siftDown(heap, 0, *size);

	return res;
}

void siftDown(int * heap, int parent, int size) {
	int child[2] = { parent * 2 + 1, parent * 2 + 2 };

	if (size - 1 < child[0])
		return;

	if (size - 1 == child[0]) {
		if (heap[parent] > heap[child[0]])
			swap(&heap[parent], &heap[child[0]]);
		return;
	}

	int bestChild = heap[child[0]] < heap[child[1]] ? child[0] : child[1];
	
	if (heap[parent] > heap[bestChild]) {
		swap(&heap[parent], &heap[bestChild]);
		siftDown(heap, bestChild, size);
	}

}

void swap(int * x, int * y) {
	int buf = *x;
	*x = *y;
	*y = buf;
}

