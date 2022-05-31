#include <iostream>
#include <future>
#include <thread>
#include <queue>
#include <vector>
#include <functional>

class ThreadPool{
public:
    using Task = std::function<void ()>;
    bool progress;
    std::vector<std::thread> threads;
    std::vector<std::thread::id> ids;
    std::queue<Task> work_queue;
    std::mutex mutex_;
    std::condition_variable condition;
    size_t size_pool;

    explicit ThreadPool(size_t poolSize){
        size_pool = poolSize;
        progress = true;
        for (size_t i = 0; i < size_pool; ++i) {
            threads.emplace_back([this]() { 
                // std::cout<<std::this_thread::get_id()<<std::endl;
                while (progress) {
                    std::unique_lock<std::mutex> lock(mutex_);
                    if (!work_queue.empty()) {
                        auto task = work_queue.front();
                        ids.emplace_back(std::this_thread::get_id());
                        // std::cout<<std::this_thread::get_id()<<std::endl;
                        work_queue.pop();
                        lock.unlock();
                        task();
                    } else {
                        condition.wait(lock);
                    }
                }
            });
        }
    }

    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>{
        using type_return = decltype(func(args...));
        // std::packaged_task<type_return()>task([func, args...](){return func(args...);});
        auto task = std::make_shared<std::packaged_task<type_return()>>([func, args...]() {return func(args...);});
        std::lock_guard<std::mutex> lock(mutex_);
        work_queue.emplace([task](){ (*task)(); });
        condition.notify_one();
        return task->get_future();
    }

    ~ThreadPool(){
        progress = false;
        condition.notify_all();
        for (size_t i = 0; i < size_pool; ++i){
            threads[i].join();
        }
    }
};