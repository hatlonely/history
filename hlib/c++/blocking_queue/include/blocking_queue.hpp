// @file blocking_queue.hpp
// @desc 如果BlockingQueue是空的，从BlockingQueue取东西的操作
//  将会被阻断进入等待状态，直到BlockingQueue进了东西才会被唤醒
//  同样,如果BlockingQueue是满的，任何试图往里存东西的操作
//  也会被阻断进入等待状态，直到BlockingQueue里有空间才会被唤醒继续操作
// @auth hatlonely(hatlonely@gmail.com)
// @vers 1.0
// @date 2015-05-12

#include <list>
#include <boost/thread.hpp>

namespace hl {

template <typename Element>
class BlockingQueue {
public:
    explicit BlockingQueue(const size_t max_queue_size = S_DEFAULT_MAX_QUEUE_SIZE) :
        _max_queue_size(max_queue_size) {
        // nothing to do
    }

    virtual ~BlockingQueue() {
        // nothing to do
    }

    bool offer(const Element& element, uint64_t timeout_us) {
        boost::mutex::scoped_lock op_lock(_op_mutex);
        // 如果队列已满先释放_op_mutex，以便take和poll从队列中取走元素
        // 阻塞等待timeout_us时间，直到队列不满，或者超时返回false
        while (_list.size() == _max_queue_size) {
            op_lock.unlock();
            boost::mutex::scoped_lock add_lock(_add_mutex);
            if (!_not_full.timed_wait(add_lock, boost::get_system_time() + boost::posix_time::microseconds(timeout_us))) {
                return false;
            }
            op_lock.lock();
        }

        // 在从_not_full被唤醒 到 拿到_op_mutex锁之间的时间内队列可能又已经满了
        // 此时直接返回false
        if (_list.size() == _max_queue_size) {
            return false;
        }
        _list.push_back(element);
        _not_empty.notify_one();
        op_lock.unlock();

        return true;
    }

    bool poll(Element& element, uint64_t timeout_us) {
        boost::mutex::scoped_lock op_lock(_op_mutex);
        // 如果队列为空先释放_op_mutex，以便put和offer给队列中插入元素
        // 阻塞等待timeout_us时间，直到队列非空，或者超时返回false
        if (_list.empty()) {
            op_lock.unlock();
            boost::mutex::scoped_lock del_lock(_del_mutex);
            if (!_not_empty.timed_wait(del_lock, boost::get_system_time() + boost::posix_time::microseconds(timeout_us))) {
                return false;
            }
            op_lock.lock();
        }

        // 在从_not_empty被唤醒 到 拿到_op_mutex锁之间的时间内队列可能又空了
        // 此时直接返回false
        if (_list.empty()) {
            return false;
        }
        element = _list.front();
        _list.pop_front();
        _not_full.notify_one();
        op_lock.unlock();

        return true;
    }

    void put(const Element& element) {
        boost::mutex::scoped_lock op_lock(_op_mutex);
        while (_list.size() == _max_queue_size) {
            op_lock.unlock();
            boost::mutex::scoped_lock add_lock(_add_mutex);
            _not_full.wait(add_lock);
            op_lock.lock();
        }
        _list.push_back(element);
        _not_empty.notify_one();
        op_lock.unlock();
    }

    void take(Element& element) {
        boost::mutex::scoped_lock op_lock(_op_mutex);
        while (_list.empty()) {
            op_lock.unlock();
            boost::mutex::scoped_lock del_lock(_del_mutex);
            _not_empty.wait(del_lock);
            op_lock.lock();
        }
        element = _list.front();
        _list.pop_front();
        _not_full.notify_one();
        op_lock.unlock();
    }

    inline bool full() {
        return _list.size() == _max_queue_size;
    }

    inline bool empty() {
        return _list.empty();
    }

    inline size_t size() {
        return _list.size();
    }

private:
    static const size_t S_DEFAULT_MAX_QUEUE_SIZE = 60000;

    size_t _max_queue_size;
    std::list<Element> _list;
    boost::mutex _add_mutex;    // 非空条件锁
    boost::mutex _del_mutex;    // 不满条件锁
    boost::mutex _op_mutex;     // 所有对队列的操作都需要获得该锁
    boost::condition_variable _not_empty;   // 队列非空条件
    boost::condition_variable _not_full;    // 队列不满条件
};

} // namespace hl
