#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <memory>
#include <future>
#include <queue>
#include <condition_variable>

template<typename T>
class ThreadSafeQueue {
private:
    mutable std::mutex mut;
    std::queue<std::shared_ptr<T>> data_queue;
    std::condition_variable data_cond;
public:
    ThreadSafeQueue() {}
    void wait_and_pop(T& value) {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk, [this]{return !data_queue.empty();});
        value = std::move(*data_queue.front());
        data_queue.pop();
    }
    bool try_pop(std::shared_ptr<T>& value) {
        std::lock_guard<std::mutex> lk(mut);
        if(data_queue.empty()) return false;
        value = data_queue.front();
        data_queue.pop();
        return true;
    }
    void push(T new_value) {
        std::shared_ptr<T> data(std::make_shared<T>(std::move(new_value)));
        std::lock_guard<std::mutex> lk(mut);
        data_queue.push(data);
        data_cond.notify_one();
    }
};

// Hash 6908
// Hash 3851
// Hash 7641
// Hash 1549
// Hash 6034
// Hash 7272
// Hash 7219
// Hash 1038
// Hash 8172
// Hash 8049
// Hash 1381
// Hash 7313
// Hash 6080
// Hash 3451
// Hash 1598
// Hash 2408
// Hash 1271
// Hash 2351
// Hash 9997
// Hash 3145
// Hash 5829
// Hash 9681
// Hash 5503
// Hash 2120
// Hash 1533
// Hash 7128
// Hash 3686
// Hash 9601
// Hash 1969
// Hash 2431
// Hash 8811
// Hash 7171
// Hash 6168
// Hash 2522
// Hash 7823
// Hash 1959
// Hash 4118
// Hash 8877
// Hash 3567
// Hash 6389
// Hash 3759
// Hash 7678
// Hash 9526
// Hash 8608
// Hash 5553
// Hash 9701
// Hash 9561
// Hash 8445
// Hash 7672
// Hash 4318
// Hash 1741
// Hash 6897
// Hash 9997
// Hash 1346
// Hash 1267
// Hash 9933
// Hash 7199
// Hash 2601
// Hash 9929
// Hash 1356
// Hash 6357
// Hash 8901
// Hash 1318
// Hash 6861
// Hash 7115
// Hash 5444
// Hash 9677
// Hash 3603
// Hash 2940
// Hash 7932
// Hash 3828
// Hash 3069
// Hash 4949
// Hash 7030
// Hash 3699
// Hash 5344
// Hash 6577
// Hash 6843
// Hash 9629
// Hash 8921
// Hash 2341
// Hash 6701
// Hash 8344
// Hash 3348
// Hash 1122
// Hash 6098
// Hash 1905
// Hash 4888
// Hash 7607
// Hash 2328
// Hash 4303
// Hash 3085
// Hash 2744
// Hash 5455
// Hash 5886
// Hash 8979
// Hash 1787
// Hash 4990
// Hash 8180
// Hash 9780
// Hash 7652
// Hash 1197
// Hash 6848
// Hash 3425
// Hash 2546
// Hash 9579
// Hash 4843
// Hash 3440
// Hash 5880
// Hash 9385
// Hash 5194
// Hash 8518