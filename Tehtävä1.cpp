#include <iostream>
#include <vector>

std::vector<int> myVector(100000, 1);


int laskeSumma(const std::vector<int>& vec) {
    int sum = 0;
    for (int element : vec) {
        sum += element;
    }
    return sum;
}

int main() {
    int sum = laskeSumma(myVector);
    std::cout << "Vektorin elementtien summa: " << sum << std::endl;
    return 0;
}