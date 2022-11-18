/// @file "Container.h"
/// @author Thien Nguyen thiennguyen@.csn.edu
/// @date 3/3/22
/// @note I pledge my word of honor that
///       I have abided by the the CSN Academic Integrity Policy
///       while completing this assignment.
///
/// @brief This assignment using template and putting definitions
///         as well as the prototypes of Container in here
/// @note People who helped: TA Miguel, TA Chris
/// @note This is but one possible solution to the assignment.
///       Programming techniques and commands in this solution
///       are aligned with the current and previous chapters,
///       labs, and lectures, which may result in a trade-off
///       between efficient coding and what student are
///       currently able to understand.

// define CONTAINER_H when computer don't know it yet
#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <iostream>
#include <ostream>
#include <utility>
#include <algorithm>
#include <initializer_list>
#include <stdexcept>
#include <stdlib.h>

/// A Container stores a set of values The storage of the
/// Container is handled automatically, being expanded as needed.

template <class T>
class Container {
public:
    /// Member types.
    // value type is what kind of type store , value at the position
    // size type is positional
    using value_type = T;
    using size_type = std::size_t;
    using pointer = value_type*;
    using const_pointer = const value_type*;

    // default/ parameterized constructor
    Container(size_type count = 0)
    : capacity(count), data(new T[count]{}) {}

    /// Copy ctor.
    Container(const Container &other);

    /// Move ctor
    Container(Container &&other)
    : capacity(std::exchange(other.capacity, 0)),
          used(std::exchange(other.used, 0)),
          data(std::exchange(other.data, nullptr)) {}

    /// Initializer List ctor
    /// allow pass in all the value into characteristic when we declared it
    /// unless default (created empty), fill the value into the array
    /// c = {1 , 2 , 3, 4}, give the value to init
    Container(const std::initializer_list<value_type> &init);

    /// Destructor.
    ~Container();

    /// Checks if the container has no elements, e.g begin() == end()
    /// @returns true if the container is empty, false otherwise.
    bool empty() const { return begin() == end(); }

    /// Returns the number of elements in the container.
    size_type size() const { return used; };

    /// Returns a pointer to the first element.
    pointer begin() { return data; }
    const_pointer begin() const { return data; }

    /// Returns a pointer to the end (the element following the last element).
    pointer end() { return begin() + size(); }
    const_pointer end() const { return begin() + size(); }

    /// Adds an element to the end.
    void push_back(const value_type &value);

    /// Removes a single item from the container.
    void erase(pointer pos);

    /// After this call, size() returns zero. The capacity remains unchanged.
    void clear() { used = 0; };

    /// Exchanges the contents of the container with those of other.
    void swap(Container &other);

    /// Finds the first element equal to the given target.
    /// Search begins at pos.
    /// @returns pointer to the element if found, or end() if not found.
    pointer find(const value_type &target, pointer pos = nullptr);

    const_pointer find(const value_type &target, pointer pos = nullptr) const;

    /// const and non-const version of at function
    /// @returns a constant reference
          T& at(size_type pos);
    const T& at(size_type pos) const;

    /// overloading oerator [], with no bound checking
    /// @returns a constant reference
          T& operator[](size_type pos)       { return *(begin() + pos); } 
    const T& operator[](size_type pos) const { return *(begin() + pos); }

    // ----------------------------------------------------------
    /// @paragraph /include within pa13/ /include within pa13b/
    // ----------------------------------------------------------

    /// Replaces the contents of the container with a copy of the contents of rhs.
    Container &operator=(const Container &rhs);

    /// Move assignment
    Container &operator=(Container &&rhs);

    /// Returns other appended to this.
    /// @returns this
    Container &operator+=(const Container &other);

private:
    size_type capacity{}; ///< Physical capacity of container.
    size_type used{};     ///< Number of items in container.
    pointer data{};       ///< Array of items.
};

// ==========================================================================
/// @paragraph Prototypes overloading function non-member of class Container
// ==========================================================================

/// Equality comparison operator.
/// @returns true if lhs compares equal to rhs, otherwise false
template <class T>
bool operator==(const Container<T>& lhs, const Container<T>& rhs);

/// Inequality comparison operator.
/// @returns true if lhs does not compare equal to rhs, otherwise false
template <class T>
bool operator!=(const Container<T>& lhs, const Container<T>& rhs);

/// Returns the concatenation of lhs and rhs.
template <class T>
Container<T> operator+(const Container<T>& lhs, const Container<T>& rhs);

/// Writes a formatted representation of rhs to output.
/// @returns output
template <class T>
std::ostream& operator<<(std::ostream& output, const Container<T>& oset);

            /// ===================================================
            /// @paragraph OUT-OF-LINE member function definitions
            /// ===================================================

/// Copy constructor
template <class T>
Container<T>::Container(const Container<T>& other)
: Container<T>(other.size()) {
    std::copy(other.begin(), other.end(), begin());  // copy all the element
    used = other.size();
}

/// Initializer List constructor
template <class T>
Container<T>::Container(const std::initializer_list<value_type>& init)
    : Container<T>(init.size()) {
    // copy all the elements from init.begin() to init.end() to data
    std::copy(init.begin(), init.end(), begin());
    used = init.size();
}

/// Destructor.
template <class T>
Container<T>::~Container() {
    // Dynamically delete the memory we allocated earlier
    delete[] data;
    data = nullptr;
    used = 0;
    capacity = 0;
}

/// Adds an element to the end.
template <class T>
void Container<T>::push_back(const value_type& value) {
    // variable declaration(s)
    // pointer data_2 = nullptr;
    // if the array is at its maximum capacity
    if (used == capacity) {
        // make a new dynamic array of sufficient size (capacity +8)
        pointer data_2 = new value_type[capacity += 8];

        // copy elements from data to new temp array
        std::copy(begin(), end(), data_2);

        // delete the old data array
        delete[] data;

        // reassign data pointer to the temp array
        data = data_2;
    }

    // // increment used to take everything back
    *(data + used) = value;
    ++used;

    // a different version of increment used to take everything back
    // *(data + used++) = value;
}

/// Removes a single item from the container.
template <class T>
void Container<T>::erase(pointer pos) {
    // if pos is not empty
    if (pos != nullptr) {
        // replace assert function with throw exception
        if (pos < begin() || pos >= end())
        { throw std::out_of_range("This position is out of bound_erase"); }
        // overwrite the useless element to the end - 1
        std::copy(pos + 1, end(), pos);
        --used;
    }
}

/// Exchanges the contents of the container with those of other.
/// @param other
template <class T>
void Container<T>::swap(Container<T>& other) {
    // take two parameter of type T, no matter what T might be
    std::swap(capacity, other.capacity);
    std::swap(used,     other.used    );
    std::swap(data,     other.data    );
}

/// Finds the first element equal to the given target.
/// Search begins at pos.
/// @returns pointer to the element if found, or end() if not found.
template <class T>
typename Container<T>::pointer Container<T>::find(const value_type& 
                                                  target, pointer pos) 
    // start the pos at begin() if it's nullptr
    { return std::find(pos == nullptr ? begin() : pos, end(), target); }

/// definition of non const at function
template <class T>
T& Container<T>::at(size_type pos) {
    // if position is greater or equal to that 1 passed element
    // throw an exception
    if (pos >= used) {throw std::out_of_range("Position is out of bound_at");}

    // return the value of that index
    return data[pos];
}

/// definition of const at function
template <class T>
const T& Container<T>::at(size_type pos) const {
    // if position is greater or equal to that 1 passed element
    // throw an exception, it's an unsigned type so no worrie about negative
    if (pos >= used) {throw std::out_of_range("Position is out of bound_at");}

    // return the value of that index
    return data[pos];
}

// /// definition of non-const overloading operator[]
// template <class T>
// T& Container<T>::operator[](size_type pos) { return data[pos]; }

// /// definition of const overloading operator[]
// template <class T>
// const T& Container<T>::operator[](size_type pos) const { return data[pos]; }

        // -------------------------------------------------------
        /// @paragraph Overloading operator definitions (MEMBERS)
        // -------------------------------------------------------

template <class T>
Container<T>& Container<T>::operator=(const Container<T>& rhs) {
    // guard against self-assignment
    if (this != &rhs) {
        // use the copy constructor to have
        // a copy of the rhs
        Container<T> temp(rhs);

        // since temp is going to be destroy or go out of scope
        // this get its members and then return *this
        this->swap(temp);
        // NOTE: the copy constructor life-time only
        // last till the end of the if {} statement
    }

    // return *this
    return *this;
}

template <class T>
Container<T>& Container<T>::operator=(Container<T>&& rhs) {
    // self guard assignment
    if (this != &rhs) {
        capacity = std::exchange(rhs.capacity, 0);
        used     = std::exchange(rhs.used, 0);
        data     = std::exchange(rhs.data, data);
    }
    // since rhs is passed by reference
    // it get destroy at the end of if {}, after
    // destructor being called.
    return *this;
}

/// Returns other appended to this.
/// @returns this
template <class T>
Container<T>& Container<T>::operator+=(const Container<T>& other) {
    // allocate the memory
    auto copy_data = new value_type[size() + other.size()];

    // copy the array to the new data
    std::copy(begin(), end(), copy_data);

    // delete old data
    // assigning ownership of data to the copydata new chunk of memory
    delete[] data;

    // assign it to the new copy
    data = copy_data;

    // update the capacity
    capacity = size() + other.size();

    std::copy(other.begin(), other.end(), end());

    // update the capacity
    used = capacity;

    // 2. return *this
    return *this;
}

    // ------------------------------------------------------------
    /// @paragraph Overloading operator definitions (NON-MEMBERS)
    // ------------------------------------------------------------

/// Equality comparison operator.
/// @returns true if lhs compares equal to rhs, otherwise false
template <class T>
bool operator==(const Container<T>& lhs, const Container<T>& rhs) {
    // using equal function we wrote down below
    return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

/// Inequality comparison operator.
/// @returns true if lhs does not compare equal to rhs, otherwise false
template <class T>
bool operator!=(const Container<T>& lhs, const Container<T>& rhs) {
    // opposite of equal is !equal
    // return !::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    return !(lhs == rhs);
}

/// Returns the concatenation of lhs and rhs.
template <class T>
Container<T> operator+(const Container<T>& lhs, const Container<T>& rhs) 
                { return Container<T>(lhs) += rhs; }    
    //----------------------------------------------------------//
    // this is an annonymus type                                //
    // Container(lhs) is a left value due                       //
    // right value is unassignable (left side) in the           //
    // assignment ope to its being a soon be delete temp array  //
    //----------------------------------------------------------//

/// Writes a formatted representation of rhs to output.
/// @returns output
template <class T>
std::ostream& operator<<(std::ostream& output, const Container<T>& oset) {
    // seperator do be reset after each loop
    char sep[2] = "";
    output << '{';

    // print the content of the container
    for (auto& i : oset) {
        output << sep << i;
        *sep = ',';
    }
    // end the array
    return output << '}';
}



#endif /* CONTAINER_HPP */
