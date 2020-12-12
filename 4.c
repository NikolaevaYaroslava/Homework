#include <stdio.h>
#include <math.h>

#define ARR_SIZE 500500

void swap(int* a, int* b) {
    int c = *a;
    *a = *b;
    *b = c;
}

int partition(int *A, int low, int high) {
    int pivot = (A[low] + A[high])/2;
    int i = low;
    int j = high;
    while (i <= j)  {
        while (A[i] < pivot)
            i++;
        while (A[j] > pivot)
            j--;
        if (i >= j) 
            break;
        swap(&A[i++], &A[j--]);
    }
    return j;
}

void siftUp(int *heap, int child);

int extractMin(int * heap, int * size);

void siftDown(int *heap, int parent, int size);

void swap(int *x, int *y);


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

int HEAP[ARR_SIZE];

void heapSort(int* A, int lo, int hi) {
    int heapSize = 0;

    for (int i = lo; i <= hi; i++) {
        HEAP[heapSize++] = A[i];
        siftUp(HEAP, heapSize - 1);
    }

    for (int i = lo; i <= hi; i++) {
        A[i] = extractMin(HEAP, &heapSize);
    }

}

void introsort(int *A, int lo, int hi, int maxdepth) {
    int n = hi - lo + 1;
    if (n <= 2) {
        if (A[hi] < A[lo]) {
            swap(&A[hi], &A[lo]);
        }
        return;
    }
    else if (maxdepth = 0) {
        heapSort(A, lo, hi);
    }
    else {
        int p = partition(A, lo, hi);
        if (p == hi) {
            p--;
        }
        introsort(A, lo, p, maxdepth - 1);
        introsort(A, p+1, hi, maxdepth - 1);
    }
}

int ARR[ARR_SIZE];

int main(int argc, char* argv[]) {

    if (argc < 3) {
        printf("provide 2 file names\n");
        return 1;
    }


	int arrSize;

	freopen(argv[1], "r", stdin);
	freopen(argv[2], "w", stdout);

    scanf("%d", &arrSize);

    int maxdepth = (int)(log(arrSize)) * 2;

    if (arrSize > ARR_SIZE) {
        printf("arrSize > %d", ARR_SIZE);
        return 1;
    }

	for (int i = 0; i < arrSize; i++) {
        scanf("%d", ARR + i);
	}

    introsort(ARR, 0, arrSize - 1, maxdepth);

	for (int i = 0; i < arrSize; i++) {
        printf("%d\n", ARR[i]);
	}

    printf("\n");

	return 0;


}

