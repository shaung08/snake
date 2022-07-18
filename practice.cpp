#include <iostream>

void test(int* v) {
    for (int i = 0; i < 2 ; i++)
        std::cout << *(v+i) << std::endl;
    return;
}

void test01(int* v) {
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 5; j++)
            std::cout << "test01: " << v+i*5+j << std::endl;
    return;
}

int main() {
    int arr[2][5] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    //printf("arr address is: %p\n", *(arr));
    //printf("arr address is: %p\n", &arr);

    int test1[2] = {10, 20};
    //std::cout << *(test1) << std::endl;
    //printf("test1 address is: %d\n", *(test1));
    //printf("test1 address is: %p\n", &(test1));
    int a = 5;
    int c = 100;
    int* b;
    b = &a;
    std::cout << *b << std::endl;
    b = &c;
    std::cout << *b << std::endl;
    test(test1);
    test01(*arr);
    int arr1[2][5];
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 5; j++) {
            arr1[i][j] = *(*(arr+i)+j);
            //printf("arr[%d][%d]address is: %p\n", i, j, *(arr+i)+j);
            //std::cout << arr1[i][j] << std::endl;
        }
    }
    return 0;
}  