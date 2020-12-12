#include <stdio.h>

#define ARR_SIZE 500500


void shellSort (int *array, int size) {
    for (int step = size / 2; step > 0; step /= 2)
        for (int i = step; i < size; i++) 
            for (int j = i - step; j >= 0 && array[j] > array[j + step]; j -= step) {
                int buf = array[j];
                array[j] = array[j + step];
                array[j + step] = buf;
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

    shellSort(ARR, arrSize);

	for (int i = 0; i < arrSize; i++) {
        printf("%d\n", ARR[i]);
	}

    printf("\n");

	return 0;


}


