#include <iostream>
#include <stdlib.h>
int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    int *p = new int[10];
    for (short i = 0; i < 10; i++) {
        p[i] = i + 1;
    }
    for (short i = 0; i < 10; i++) {
        printf("%d\t", p[i]);
    }
    return 0;
}   