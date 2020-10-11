//
//  linked_list.h
//
//  Created by hatlonely(hatlonely@gmail.com) on 15/3/26.
//  Copyright (c) 2015 hatlonely. All rights reserved.
//

#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <sstream>

namespace hl {

class LinkedListException : public std::exception {
private:
    std::string _message;
public:
    explicit LinkedListException(std::string message) {
        _message = "[LinkedListException] " + message;
    }
    virtual ~LinkedListException() {}
    virtual const char* what() const throw () {
        return _message.c_str();
    }
};

template <
    typename ValueType
> struct node_t {
    ValueType value;
    node_t* prev;
    node_t* next;

    explicit node_t(ValueType value) : value(value), prev(nullptr), next(nullptr) {}
};

template <
    typename ValueType,
    typename Allocator = std::allocator<node_t<ValueType>>
> class LinkedList {

typedef node_t<ValueType> node_t;

public:
    template <
        typename PNode
    > class Iterator : public std::random_access_iterator_tag {
        friend class LinkedList<ValueType, Allocator>;
    public:
        typedef ValueType value_type;
    public:
        explicit Iterator(PNode node) : node(node) {}
        virtual ~Iterator() = default;

        Iterator operator ++(int) {
            PNode temp = node;
            node = node->next;
            return Iterator(temp);
        }

        Iterator operator --(int) {
            PNode temp = node;
            node = node->prev;
            return Iterator(temp);
        }

        Iterator& operator ++() {
            node = node->next;
            return *this;
        }

        Iterator& operator --() {
            node = node->prev;
            return *this;
        }

        Iterator& operator +=(int n) throw (LinkedListException) {
            for (int i = 0; i < n; i++) {
                if (node == nullptr) {
                    throw LinkedListException("iterator out of memery");
                }
                node = node->next;
            }
            return *this;
        }

        Iterator& operator -=(int n) throw (LinkedListException) {
            for (int i = 0; i < n; i++) {
                if (node == nullptr) {
                    throw LinkedListException("iterator out of memery");
                }
                node = node->prev;
            }
            return *this;
        }

        Iterator operator +(int n) throw (LinkedListException) {
            PNode temp = node;
            for (int i = 0; i < n; i++) {
                if (temp == nullptr) {
                    throw LinkedListException("iterator out of memery");
                }
                temp = temp->next;
            }
            return Iterator(temp);
        }

        Iterator operator -(int n) throw (LinkedListException) {
            PNode temp = node;
            for (int i = 0; i < n; i++) {
                if (temp == nullptr) {
                    throw LinkedListException("iterator out of memery");
                }
                temp = temp->prev;
            }
            return Iterator(temp);
        }

        bool operator ==(Iterator it) {
            return node == it.node;
        }

        bool operator !=(Iterator it) {
            return node != it.node;
        }

        ValueType operator *() {
            return node->value;
        }

    private:
        PNode node;
    };

    typedef Iterator<node_t*> iterator;
    typedef Iterator<const node_t*> const_iterator;

public:
    explicit LinkedList() : _head(nullptr), _tail(nullptr), _size(0) {}
    LinkedList(std::initializer_list<ValueType> values) : 
        _head(nullptr), _tail(nullptr), _size(0) {
        for (auto value : values) {
            push_back(value);
        }
    }

    LinkedList(const LinkedList& other) {
        _head = nullptr;
        _tail = nullptr;
        _size = 0;

        node_t* node = other._head;
        while (node != nullptr) {
            push_back(node->value);
            node = node->next;
        }
    }

    LinkedList& operator =(const LinkedList& other) {
        clear();

        node_t* node = other._head;
        while (node != nullptr) {
            push_back(node->value);
            node = node->next;
        }

        return *this;
    }

    LinkedList& operator =(std::initializer_list<ValueType> values) {
        clear();

        for (auto value : values) {
            push_back(value);
        }

        return *this;
    }

    virtual ~LinkedList() {
        clear();
    }

    void clear() {
        node_t* node = _head;
        while (node != nullptr) {
            _head = _head->next;
            _allocator.destroy(node);
            _allocator.deallocate(node, 1);
            node = _head;
        }

        _head = nullptr;
        _tail = nullptr;
        _size = 0;
    }

    void size() {
        return _size;
    }

    bool empty() {
        return _size == 0;
    }

    void push_back(const ValueType& value) {
        node_t* node = _allocator.allocate(1);
        _allocator.construct(node, value);

        if (_tail == nullptr) {
            _head = node;
            _tail = node;
        } else {
            _tail->next = node;
            node->prev = _tail;
            _tail = node;
        }

        _size++;
    }

    void push_front(const ValueType& value) {
        node_t* node = _allocator.allocate(1);
        _allocator.construct(node, value);

        if (_head == nullptr) {
            _head = node;
            _tail = node;
        } else {
            _head->prev = node;
            node->next = _head;
            _head = node;
        }

        _size++;
    }

    void pop_back() {
        if (empty()) {
            return;
        }

        if (_head == _tail) {
            delete _tail;
            _head = nullptr;
            _tail = nullptr;
        } else {
            _tail = _tail->prev;
            _allocator.destroy(_tail->next);
            _allocator.deallocate(_tail->next, 1);
            _tail->next = nullptr;
        }

        _size--;
    }

    void pop_front() {
        if (empty()) {
            return;
        }

        if (_head == _tail) {
            delete _head;
            _head = nullptr;
            _tail = nullptr;
        } else {
            _head = _head->next;
            _allocator.destroy(_head->prev);
            _allocator.deallocate(_head->prev, 1);
            _head->prev = nullptr;
        }

        _size--;
    }

    ValueType at(size_t index) throw (LinkedListException) {
        if (index >= _size) {
            throw LinkedListException("index out of range");
        }

        node_t* node = _head;
        for (size_t i = 0; i < index; i++) {
            node = node->next;
        }

        return node->value;
    }

    ValueType operator [](size_t index) throw (LinkedListException) {
        return at(index);
    }

    iterator begin() {
        return iterator(_head);
    }

    const_iterator begin() const {
        return const_iterator(_head);
    }

    iterator end() {
        return iterator(nullptr);
    }

    const_iterator end() const {
        return const_iterator(nullptr);
    }

    iterator rbegin() {
        return iterator(_tail);
    }

    const_iterator rbegin() const {
        return const_iterator(_tail);
    }

    iterator rend() {
        return iterator(nullptr);
    }

    const_iterator rend() const {
        return const_iterator(nullptr);
    }

    std::string to_string() {
        if (_size == 0) {
            return "[]";
        }

        std::stringstream ss;

        ss << "[";
        node_t* node = _head;
        while (node != _tail) {
            ss << node->value << ", ";
            node = node->next;
        }
        ss << _tail->value << "]";

        return ss.str();
    }
    
    ValueType& front() throw (LinkedListException) {
        if (empty()) {
            throw LinkedListException("empty list");
        }
        return _head->value;
    }

    const ValueType& front() const throw (LinkedListException) {
        if (empty()) {
            throw LinkedListException("empty list");
        }
        return _head->value;
    }
    
    ValueType& back() throw (LinkedListException) {
        if (empty()) {
            throw LinkedListException("empty list");
        }
        return _tail->value;
    }

    const ValueType& back() const throw (LinkedListException) {
        if (empty()) {
            throw LinkedListException("empty list");
        }
        return _tail->value;
    }

    iterator insert(iterator pos, const ValueType& value) {
        if (pos == end()) {
            push_back(value);
            return rbegin();
        }

        if (pos == begin()) {
            push_front(value);
            return begin();
        }

        node_t* node = _allocator.allocate(1);
        _allocator.construct(node, value);
        node->prev = pos.node->prev;
        node->next = pos.node;
        pos.node->prev->next = node;
        pos.node->prev = node;
        _size++;
        return iterator(node);
    }

    const_iterator insert(const_iterator pos, const ValueType& value) {
        if (pos == end()) {
            push_back(value);
            return rbegin();
        }

        if (pos == begin()) {
            push_front(value);
            return begin();
        }

        node_t* node = _allocator.allocate(1);
        _allocator.construct(node, value);
        node->prev = pos.node->prev;
        node->next = pos.node;
        pos.node->prev->next = node;
        pos.node->prev = node;
        _size++;
        return const_iterator(node);
    }

    iterator insert(iterator pos, std::initializer_list<ValueType> ilist) {
        if (pos == end()) {
            *this = ilist;
            return begin();
        }

        node_t* node = pos.node->prev;
        iterator it = pos;
        for (auto i : ilist) {
            it = insert(it, i);
            ++it;
        }

        if (node == nullptr) {
            return begin();
        } else {
            return iterator(node->next);
        }
    }

    iterator erase(iterator pos) {
        if (pos == end()) {
            return end();
        }

        if (pos == begin()) {
            pop_front();
            return begin();
        }

        if (pos == rbegin()) {
            pop_back();
            return end();
        }

        iterator it(pos.node->next);
        node_t* node = pos.node;
        node->prev->next = node->next;
        node->next->prev = node->prev;
        _allocator.destroy(node);
        _allocator.deallocate(node, 1);
        _size--;
        return it;
    }

    const_iterator erase(const_iterator pos) {
        if (pos == end()) {
            return end();
        }

        if (pos == begin()) {
            pop_front();
            return begin();
        }

        if (pos == rbegin()) {
            pop_back();
            return end();
        }

        const_iterator it(pos.node->next);
        node_t* node = pos.node;
        node->prev->next = node->next;
        node->next->prev = node->prev;
        _allocator.destroy(node);
        _allocator.deallocate(node, 1);
        _size--;
        return it;
    }

    template <
        typename InputIterator
    > iterator insert(iterator pos, InputIterator first, InputIterator last) {
        if (pos == end()) {
            for (auto it = first; it != last; ++it) {
                push_back(*it);
            }
            return begin();
        }

        node_t* node = pos.node->prev;
        iterator pos_it = pos;
        for (auto it = first; it != last; ++it) {
            pos_it = insert(pos_it, *it);
            ++pos_it;
        }

        if (node == nullptr) {
            return begin();
        } else {
            return iterator(node->next);
        }
    }

    iterator erase(iterator first, iterator last) {
        for (auto it = first; it != last; ++it) {
            erase(it);
        }

        return last;
    }

    void operator +=(std::initializer_list<ValueType> values) {
        for (auto value : values) {
            push_back(value);
        }
    }

    void merge(LinkedList& other) {
        for (auto value : other) {
            push_back(value);
        }
    }

    /* void sort() { */
        /* std::sort(begin(), end()); */
    /* } */

private:
    void _swap(node_t* node1, node_t* node2) {
        if (node1 == nullptr || node2 == nullptr) {
            return;
        }

        node_t* prev1 = node1->prev;
        node_t* prev2 = node2->prev;
        node_t* next1 = node1->next;
        node_t* next2 = node2->next;
        node1->next = next2;
        node1->prev = prev2;
        node2->next = next1;
        node2->prev = prev1;
    }

private:
    node_t* _head;
    node_t* _tail;
    size_t _size;

    Allocator _allocator;
};

}  // namespace hl

#endif // __LINKED_LIST_H__

