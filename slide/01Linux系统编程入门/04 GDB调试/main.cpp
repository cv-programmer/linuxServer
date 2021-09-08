#include <iostream>
#include "sort.h"

using namespace std;

int main() {

    int array[] = {12, 27, 55, 22, 67};
    int len = sizeof(array) / sizeof(int);

    bubbleSort(array, len);
    
    // 遍历
    cout << "冒泡排序之后的数组: ";
    for(int i = 0; i < len; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
    cout << "===================================" << endl;

    int array1[] = {25, 47, 36, 80, 11};
    len = sizeof(array1) / sizeof(int);
    
    selectSort(array1, len);
    
    // 遍历
    cout << "选择排序之后的数组: ";
    for(int i = 0; i < len; i++) {
        cout << array1[i] << " ";
    }
    cout << endl;

    return 0;
}