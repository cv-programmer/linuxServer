#include "sort.h"
#include <iostream>

using namespace std;

void selectSort(int *array, int len) {

    for (int j = 0; j < len - 1; j++) {
		for (int i = j + 1; i < len; i++) {
			if (array[j] > array[i]) {
				int temp = array[j];
				array[j] = array[i];
				array[i] = temp;
			}
		}
	}

}