#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>
#include <atomic>

class TaskQueue {
public:
    TaskQueue(int nof_threads) : num_threads(nof_threads), stop(false) {
        for (int i = 0; i < num_threads; ++i) {
            threads.emplace_back(std::thread(&TaskQueue::worker, this));
        }
    }

    ~TaskQueue() {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            stop = true;
        }
        condition.notify_all();
        for (std::thread& thread : threads) {
            if (thread.joinable()) {
                thread.join();
            }
        }
    }

    void addJob(std::function<void()> task) {
        std::unique_lock<std::mutex> lock(queue_mutex);
        tasks.push(task);
        condition.notify_one();
    }

private:
    std::queue<std::function<void()>> tasks;
    std::vector<std::thread> threads;
    std::mutex queue_mutex;
    std::condition_variable condition;
    std::atomic<bool> stop;
    int num_threads;

    void worker() {
        while (true) {
            std::function<void()> task;
            {
                std::unique_lock<std::mutex> lock(queue_mutex);
                condition.wait(lock, [this] { return !tasks.empty() || stop; });
                if (stop && tasks.empty()) {
                    return;
                }
                task = tasks.front();
                tasks.pop();
            }
            task();
        }
    }
};


int main() {
    TaskQueue taskQueue(4); 

    for (int i = 0; i < 10; ++i) {
        taskQueue.addJob([i] {
            std::cout << "Job " << i << " processed by thread " << std::this_thread::get_id() << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            });
    }

    std::this_thread::sleep_for(std::chrono::seconds(5)); 
    return 0;
}