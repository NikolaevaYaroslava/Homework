#include <stdio.h>

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

void quicksort(int* A, int lo, int hi) {

    if (hi - lo <= 1) {
        if (A[hi] < A[lo]) {
            swap(&A[hi], &A[lo]);
        }
        return;
    }

    if (lo < hi) {
        int p = partition(A, lo, hi);
        if (p == hi) {
            p--;
        }
        quicksort(A, lo, p);
        quicksort(A, p + 1, hi);
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

    if (arrSize > ARR_SIZE) {
        printf("arrSize > %d", ARR_SIZE);
        return 1;
    }

	for (int i = 0; i < arrSize; i++) {
        scanf("%d", ARR + i);
	}

    quicksort(ARR, 0, arrSize - 1);

	for (int i = 0; i < arrSize; i++) {
        printf("%d\n", ARR[i]);
	}

    printf("\n");

	return 0;


}

