//Miniprojekti 3

//Taso 1

#include <iostream>
#include <algorithm>
#include <ctime>


bool is_straight(int hand[]) {
    // Järjestä kortit
    std::sort(hand, hand + 5);

    if (hand[0] == 2 && hand[1] == 3 && hand[2] == 4 && hand[3] == 5 && hand[4] == 14) {
        return true;
    }
    
    for (int i = 0; i < 4; i++) {
        if (hand[i + 1] - hand[i] != 1) {
            return false;
        }
    }

    return true;
}

// Testiohjelma
int main() {  
    int hand1[] = {5, 8, 7, 6, 4}; // Suora
    int hand2[] = {5, 8, 7, 6, 2}; // Ei suoraa

    clock_t start, end;
    double cpu_time_used;

    start = clock();
    
    if (is_straight(hand1)) {
        std::cout << "Käsi 1: Suora" << std::endl;
    } else {
        std::cout << "Käsi 1: Ei suoraa" << std::endl;
    }

    if (is_straight(hand2)) {
        std::cout << "Käsi 2: Suora" << std::endl;
    } else {
        std::cout << "Käsi 2: Ei suoraa" << std::endl;
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    std::cout << "Suoritusaika: " << cpu_time_used << " sekuntia" << std::endl;

    return 0;
	// Suoritusaika 0.003sekuntia
}

// Taso 2

#include <iostream>
#include <ctime>
#include <bitset>
#include <algorithm>


bool is_straight(int hand[]) {
    std::bitset<15> straight_check;
    for (int i = 0; i < 5; ++i) {
        straight_check.set(hand[i]);
    }

    for (int i = 2; i <= 10; ++i) {
        if (straight_check[i] && straight_check[i+1] && straight_check[i+2] && straight_check[i+3] && straight_check[i+4]) {
            return true;
        }
    }
   
    if (straight_check[2] && straight_check[3] && straight_check[4] && straight_check[5] && straight_check[14]) {
        return true;
    }

    return false;
}

// Testiohjelma
int main() {
    
    int hand1[] = {5, 8, 7, 6, 4}; // Suora
    int hand2[] = {5, 8, 7, 6, 2}; // Ei suoraa

    clock_t start, end;
    double cpu_time_used;

    start = clock();
    
    if (is_straight(hand1)) {
        std::cout << "Käsi 1: Suora" << std::endl;
    } else {
        std::cout << "Käsi 1: Ei suoraa" << std::endl;
    }

    
    if (is_straight(hand2)) {
        std::cout << "Käsi 2: Suora" << std::endl;
    } else {
        std::cout << "Käsi 2: Ei suoraa" << std::endl;
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    std::cout << "Suoritusaika: " << cpu_time_used << " sekuntia" << std::endl;

    return 0;
	//Suoritusaika 0.001 sekuntia
}

//Taso3

#include <iostream>
#include <ctime>
#include <bitset>
#include <algorithm>


bool is_quadsorfullhouse(int hand[]) {

    std::bitset<15> count_check;

    for (int i = 0; i < 5; ++i) {
        count_check.set(hand[i]);
    }

    if (count_check.count() == 2 && (count_check.count() - 1 == 4 || count_check.count() - 1 == 1)) {
        return true;
    }

    if (count_check.count() == 2 && (count_check.count() - 1 == 3 || count_check.count() - 1 == 2)) {
        return true;
    }

    return false;
}

// Testiohjelma
int main() {
    int hand1[] = {2, 2, 2, 2, 5}; // Neloset
    int hand2[] = {2, 2, 2, 5, 5}; // Täyskäsi
    int hand3[] = {2, 3, 4, 5, 6}; // Ei nelosia/täyskäsiä

    clock_t start, end;
    double cpu_time_used;

    start = clock();
    if (is_quadsorfullhouse(hand1)) {
        std::cout << "Käsi 1: Neloset tai täyskäsi" << std::endl;
    } else {
        std::cout << "Käsi 1: Ei nelosia/täyskäsiä" << std::endl;
    }
    if (is_quadsorfullhouse(hand2)) {
        std::cout << "Käsi 2: Neloset tai täyskäsi" << std::endl;
    } else {
        std::cout << "Käsi 2: Ei nelosia/täyskäsiä" << std::endl;
    }

    if (is_quadsorfullhouse(hand3)) {
        std::cout << "Käsi 3: Neloset tai täyskäsi" << std::endl;
    } else {
        std::cout << "Käsi 3: Ei nelosia/täyskäsiä" << std::endl;
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    std::cout << "Suoritusaika: " << cpu_time_used << " sekuntia" << std::endl;

    return 0;
}