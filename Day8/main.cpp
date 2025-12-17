#include <iostream>
#include <numeric>

template<typename T>
class SimpleVector {
private:
    T* data_;
    size_t size_;
    size_t capacity_;

    void reserve(size_t new_capacity) {
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = std::move(data_[i]);
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }
public:
    SimpleVector()
        :data_(nullptr), size_(0), capacity_(0) {
    }

    ~SimpleVector() {
        delete[] data_;
    }

    void push_back(const T& value) {
        if (size_ == capacity_) {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        data_[size_++] = value;
    }

    size_t size() const {return size_;}

    // 重载下标运算符
    T& operator[](size_t index) {return data_[index];}

    const T& operator[](size_t index) const {return data_[index];}


    // // 实现Iterator
    // class iterator {
    // private:
    //     T* ptr_;
    // public:
    //     using value_type = T;
    //     using reference = T&;
    //     using pointer = T*;
    //     using difference_type = std::ptrdiff_t;
    //     using iterator_category = std::forward_iterator_tag;
    //
    //     explicit iterator(T* ptr) : ptr_(ptr) {}
    //
    //     reference operator*() const {return *ptr_;}
    //     pointer operator->() const {return ptr_;}
    //
    //     iterator& operator++() {
    //         ++ptr_;
    //         return *this;
    //     }
    //
    //     iterator operator++(int) {
    //         iterator temp = *this;
    //         ++ptr_;
    //         return temp;
    //     }
    //
    //     bool operator==(const iterator& other) const {return ptr_ == other.ptr_;}
    //     bool operator!=(const iterator& other) const {return ptr_ != other.ptr_;}
    //     iterator operator+(difference_type n) const {return iterator(ptr_ + n);}
    //     difference_type operator-(const iterator& other) const {return ptr_ - other.ptr_;}
    // };


class iterator {
private:
    T* ptr_;
public:
    using value_type = T;
    using reference = T&;
    using pointer = T*;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::random_access_iterator_tag;  // 改为随机访问迭代器

    explicit iterator(T* ptr) : ptr_(ptr) {}

    reference operator*() const {return *ptr_;}
    pointer operator->() const {return ptr_;}

    // 前置递增
    iterator& operator++() {
        ++ptr_;
        return *this;
    }

    // 后置递增
    iterator operator++(int) {
        iterator temp = *this;
        ++ptr_;
        return temp;
    }

    // 前置递减
    iterator& operator--() {
        --ptr_;
        return *this;
    }

    // 后置递减
    iterator operator--(int) {
        iterator temp = *this;
        --ptr_;
        return temp;
    }

    // 算术运算
    iterator operator+(difference_type n) const {return iterator(ptr_ + n);}
    iterator operator-(difference_type n) const {return iterator(ptr_ - n);}
    iterator& operator+=(difference_type n) {
        ptr_ += n;
        return *this;
    }
    iterator& operator-=(difference_type n) {
        ptr_ -= n;
        return *this;
    }

    // 距离计算
    difference_type operator-(const iterator& other) const {return ptr_ - other.ptr_;}

    // 比较运算
    bool operator==(const iterator& other) const {return ptr_ == other.ptr_;}
    bool operator!=(const iterator& other) const {return ptr_ != other.ptr_;}
    bool operator<(const iterator& other) const {return ptr_ < other.ptr_;}
    bool operator>(const iterator& other) const {return ptr_ > other.ptr_;}
    bool operator<=(const iterator& other) const {return ptr_ <= other.ptr_;}
    bool operator>=(const iterator& other) const {return ptr_ >= other.ptr_;}

    // 下标访问
    reference operator[](difference_type n) const {return ptr_[n];}
};


    iterator begin() {return iterator(data_);}
    iterator end() {return iterator(data_ + size_);}
};


int main() {
    int ret = 0;

    SimpleVector<int> vec;
    for (int i = 0; i < 10; ++i) {
        vec.push_back(i);
    }

    auto it = std::find(vec.begin(), vec.end(), 5);
    if (it != vec.end() && *it == 5) {
        std::cout << "Found 5 in SimpleVector." << std::endl;
    } else {
        std::cout << "5 not found in SimpleVector." << std::endl;
        ret = 1;
    }

    // 当前的迭代器不支持随机访问，因此不能使用std::sort
    std::sort(vec.begin(), vec.end());

    int sum = std::accumulate(vec.begin(), vec.end(), 0);

    std::cout << "Sum of elements: " << sum << std::endl;

    return ret;
}