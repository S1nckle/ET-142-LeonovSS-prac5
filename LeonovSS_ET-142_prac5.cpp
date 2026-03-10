#include <iostream>
int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    int i = 1000;
    while (i < 32000) {
        printf("%d - 7 = %d\n", i, (i-7));
        i-=7;
    }
    return 0;
}