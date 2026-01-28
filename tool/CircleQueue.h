#pragma once

#include <memory>
#include <mutex>
#include <condition_variable>

template <typename T>
class CircleQueue {
public:
    CircleQueue() = default;

    void setCapacity(size_t Capacity_)
    {
        Capacity = Capacity_ + 1;
        data = allocator.allocate(Capacity);
        head = 0;
        tail = 0;
    }

    CircleQueue(const CircleQueue&) = delete;
    CircleQueue& operator=(const CircleQueue&) = delete;
    //CircleQueue& operator=(const CircleQueue&) volatile = delete;

    ~CircleQueue()
    {
        std::lock_guard<std::mutex> lock(mutex);
        while(head != tail)
        {
            (data + head)->~T(); 
            head = (head + 1) % Capacity;
        }

        allocator.deallocate(data, Capacity);
    }

    template<typename... Args>
    bool emplace(Args&&... args)
    {
        std::lock_guard<std::mutex> lock(mutex);

        if(head == (tail + 1) % Capacity) return false;

        new (data + tail) T(std::forward<Args>(args)...);  
        tail = (tail + 1) % Capacity;
        return true;
    }

    template<typename U>
    void push(U&& value)
    {
        if(emplace(std::forward<U>(value)))
        {
            cond_var_.notify_one();
        }
    }

    bool pop(T& value)
    {
        std::unique_lock<std::mutex> lock(mutex);

        cond_var_.wait(lock, [this] {
            return !this->empty() || is_shutdown_;
        });

        if (is_shutdown_ && this->empty()) {
            return false;
        }

        value = std::move(*(data + head));
        (data + head)->~T();

        head = (head + 1) % Capacity;

        return true;
    }

    bool empty()
    {
        if(head == tail)
        {
            return true;
        }
        return false;
    }

    void shutdown()
    {
        std::lock_guard<std::mutex> lock(mutex);
        is_shutdown_ = true;
        cond_var_.notify_all();
    }

private:
    std::allocator<T> allocator;
    T* data = nullptr;  
    size_t Capacity;    
    size_t head;      
    size_t tail;      
    std::mutex mutex;
    std::condition_variable cond_var_;
    bool is_shutdown_ = false;
};



