#include <iostream>
#include <vector>
#include <algorithm>

// Erillinen funktio vähentämiseen
void decreaseHP(int& hp) {
    hp = (hp > 100) ? hp - 100 : 0;
}

int main() {
    std::vector<int> enemyHPs = {150, 80, 120, 90};

    // a. Erillinen funktio std::for_each:ssa
    std::for_each(enemyHPs.begin(), enemyHPs.end(), decreaseHP);

    // b. Funktio-objekti std::for_each:ssa
    struct DecreaseHP {
        void operator()(int& hp) const {
            hp = (hp > 100) ? hp - 100 : 0;
        }
    };
    std::for_each(enemyHPs.begin(), enemyHPs.end(), DecreaseHP());

    // c. Lambda-funktio std::for_each:ssa
    std::for_each(enemyHPs.begin(), enemyHPs.end(), [](int& hp) {
        hp = (hp > 100) ? hp - 100 : 0;
    });

    // d. Nimetty lambda-funktio std::for_each:ssa
    auto decreaseLambda = [](int& hp) {
        hp = (hp > 100) ? hp - 100 : 0;
    };
    std::for_each(enemyHPs.begin(), enemyHPs.end(), decreaseLambda);

    // Järjestä vektori suurimmasta pienimpään käyttäen std::sort ja lambda-funktiota
    std::sort(enemyHPs.begin(), enemyHPs.end(), [](int a, int b) {
        return a > b; // Laskeva järjestys
    });

    // Tulosta vektori
    for (int hp : enemyHPs) {
        std::cout << hp << " ";
    }
    std::cout << std::endl;

    return 0;
}