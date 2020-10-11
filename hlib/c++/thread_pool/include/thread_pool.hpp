// @file thread_pool.h
// @desc 线程池
// @auth hatlonely(hatlonely@gmail.com)
// @vers 1.0
// @date 2015-06-02 16:25:33

#pragma once

#include <iostream>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/thread/mutex.hpp>
#include "blocking_queue.hpp"
#include <sys/syscall.h>

namespace hl {

template <typename Task, typename Callback>
class Runnable {
public:
    Runnable(BlockingQueue<Task>& task_queue, bool& is_running, uint32_t timeout_us) :
        _task_queue(task_queue), _is_running(is_running), _timeout_us(timeout_us) {}

    // 工作线程不断地从任务队列中取出一个任务，通过Callback的对象来执行任务
    // 线程在取任务时调用poll接口，如果队列为空，poll接口会阻塞等待直到有新的任务或者超时退出
    // 当线程池退出时，会执行完当前队列中剩下的任务
    void operator()() {
        Callback callback;
        while (true) {
            Task task;
            if (_task_queue.poll(task, _timeout_us)) {
                callback(task);
            } else if (!_is_running && _task_queue.empty()) {
                break;
            }
        }
    }

private:
    BlockingQueue<Task>& _task_queue;
    bool& _is_running;
    uint32_t _timeout_us;
};

template <typename Task, typename Callback>
class ThreadPool {
public:
    explicit ThreadPool() : _is_running(true) {};
    virtual ~ThreadPool() {};

    int init(uint32_t thread_num, uint32_t timeout_us = 1000000) {
        for (uint32_t i = 0; i < thread_num; i++) {
            if (_workers.create_thread(Runnable<Task, Callback>(_task_queue, _is_running, timeout_us)) == NULL) {
                return -1;
            }
        }

        return 0;
    }

    void add_task(const Task& task) {
        while (_is_running && !_task_queue.offer(task, 1000000));
    }

    void join() {
        _workers.join_all();
    }

    void stop() {
        _is_running = false;
    }

private:
    BlockingQueue<Task> _task_queue;
    boost::thread_group _workers;
    bool _is_running;
};

}  // namespace hl
