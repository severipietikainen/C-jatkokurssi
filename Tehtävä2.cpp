#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;
int accountBalance = 0;

void depositMoney(int amount) {
    for (int i = 0; i < amount; ++i) {
        std::lock_guard<std::mutex> lock(mtx);
        accountBalance += 10; 
    }
}

void withdrawMoney(int amount) {
    for (int i = 0; i < amount; ++i) {
        std::lock_guard<std::mutex> lock(mtx);
        accountBalance -= 5; 
    }
}

int main() {
    std::thread t1(depositMoney, 5000); 
    std::thread t2(withdrawMoney, 9000); 

    t1.join(); 
    t2.join();

   
    std::cout << "Tilin saldo: " << accountBalance << std::endl;

    return 0;
}