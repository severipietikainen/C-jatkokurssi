#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <sstream>
#include <mutex>

template <typename T>
class Log_Ptr {
public:
    explicit Log_Ptr(T* ptr = nullptr)
        : ptr_(ptr), count_(ptr ? new std::size_t(1) : nullptr), mtx_(ptr ? new std::mutex : nullptr) {
        if (ptr_) {
            log("ownership transferred " + ptrToStr(ptr_));
        }
    }

    // Kopiokonstruktori
    Log_Ptr(const Log_Ptr& other) {
        std::lock_guard<std::mutex> lock(*other.mtx_);
        ptr_ = other.ptr_;
        count_ = other.count_;
        mtx_ = other.mtx_;
        if (ptr_) {
            ++(*count_);
            log("copy constructor " + ptrToStr(ptr_) + " count = " + std::to_string(*count_));
        }
    }

    // Sijoitusoperaattori
    Log_Ptr& operator=(const Log_Ptr& other) {
        if (this != &other) {
            std::lock_guard<std::mutex> lock_this(*mtx_);
            std::lock_guard<std::mutex> lock_other(*other.mtx_);

            // Vapautetaan nykyinen resurssi
            release();

            // Kopioidaan uusi resurssi
            ptr_ = other.ptr_;
            count_ = other.count_;
            mtx_ = other.mtx_;
            if (ptr_) {
                ++(*count_);
                log("assignment operator " + ptrToStr(ptr_) + " count = " + std::to_string(*count_));
            }
        }
        return *this;
    }

    ~Log_Ptr() {
        release();
    }

    T* operator->() const {
        log("operator-> " + ptrToStr(ptr_));
        return ptr_;
    }

    T& operator*() const {
        log("operator* " + ptrToStr(ptr_));
        return *ptr_;
    }

private:
    T* ptr_;
    std::size_t* count_;
    std::mutex* mtx_;

    void release() {
        if (count_ && mtx_) {
            std::lock_guard<std::mutex> lock(*mtx_);
            --(*count_);
            log("release " + ptrToStr(ptr_) + " count = " + std::to_string(*count_));
            if (*count_ == 0) {
                log("object destroyed " + ptrToStr(ptr_));
                delete ptr_;
                delete count_;
                delete mtx_;
            }
        }
    }

    void log(const std::string& message) const {
        std::ofstream logFile("log_ptr.txt", std::ios_base::app);
        if (logFile.is_open()) {
            logFile << currentDateTime() << " " << message << std::endl;
        }
    }

    std::string ptrToStr(void* ptr) const {
        std::ostringstream ss;
        ss << ptr;
        return ss.str();
    }

    std::string currentDateTime() const {
        time_t now = time(0);
        struct tm tstruct;
        char buf[80];
        tstruct = *localtime(&now);
        strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
        return buf;
    }
};

// Testiohjelma
#include <thread>

void threadFunction(Log_Ptr<int> logPtr) {
    std::cout << "Value: " << *logPtr << std::endl;
}

int main() {
    Log_Ptr<int> logPtr1(new int(10));
    
    std::thread t1(threadFunction, logPtr1);
    std::thread t2(threadFunction, logPtr1);
    std::thread t3(threadFunction, logPtr1);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}