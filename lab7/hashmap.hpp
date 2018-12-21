// implementation basic hashmap (unordered container)
// Mikhail Nesterenko: adapted from Proc C++
//    edited by Nicholas Stafford
// 4/15/2014

#ifndef MY_HASHMAP_H_
#define MY_HASHMAP_H_

#include <cstddef> 
//#include <stddef.h>
#include <utility>
#include <functional>
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>

using std::vector;
using std::list;
using std::pair;
using std::make_pair;
using std::find_if;
using std::copy;
using std::for_each;
using std::cout;
using std::endl;


//////////////////////////////////////////
// hash function implemented as a class
//////////////////////////////////////////

// any Hash Class must provide 
// two methods: hash() and numBuckets().
template <typename T>
class DefaultHash {
public:
  DefaultHash(size_t numBuckets = defaultNumBuckets);
  size_t hash(const T& key) const;
  size_t numBuckets() const { return numBuckets_; }
  void setNumBuckets(int n) { numBuckets_ = n; }

private:
  static const size_t defaultNumBuckets = 101; // default number of buckets in the hash
  size_t numBuckets_;
};

template <typename T>
DefaultHash<T>::DefaultHash(size_t numBuckets) : numBuckets_(numBuckets) {}


// uses the division method for hashing.
// treats the key as a sequence of bytes, sums the ASCII
// values of the bytes, and mods the total by the number
// of buckets.
template <typename T>
size_t DefaultHash<T>::hash(const T& key) const {
  size_t res = 0;
  for (size_t i = 0; i < sizeof(key); ++i) {
    const unsigned char b = *(reinterpret_cast<const unsigned char *>(&key) + i);
    res += b;
  }
  return res % numBuckets_;
}


////////////////////////////////////////////////
// container class
////////////////////////////////////////////////

template <
  typename Key,
  typename Value,
  typename Compare = std::equal_to<Key>,
  typename Hash = DefaultHash<Key>>
  class hashmap {
  public:
    typedef pair<const Key, Value> Element;

    // constructor
    // invokes constructors for comparison and hash objects
    hashmap(const Compare& comp = Compare(),
      const Hash& hash = Hash());

    Element* find(const Key& x);      // returns pointer to element with key x,
                                      // nullptr if not found

    pair<Value*, bool> insert(const Element& x);    // inserts the key/value pair 

    pair<Element*, bool> erase(const Key& x); // erases element with key x, if exists

    Value& operator[] (const Key& x); // returns reference on value of
                                      // element with key, inserts if does not exist
    void rehash(size_t n);
    void print();
  private:

    // helper function for various searches
    typename list<Element>::iterator // return type
      findElement(const Key& x,
        const size_t bucket);

    size_t size_;   // number of elements in the container
    Compare comp_;  // comparison functor, equal_to by default
    Hash hash_;     // hash functor 

                    // hash contents: vector of buckets
                    // each bucket is a list containing key->value pairs
    vector<list<Element>> elems_;
};


////////////////////////////////////////////////
// container member functions
////////////////////////////////////////////////

// Construct elems_ with the number of buckets.
template <typename Key, typename Value, typename Compare, typename Hash>
hashmap<Key, Value, Compare, Hash>::hashmap(
  const Compare& comp,
  const Hash& hash) : size_(0), comp_(comp), hash_(hash) {
  elems_ = vector<list<Element>>(hash_.numBuckets());
}


// helper function
template <typename Key, typename Value, typename Compare, typename Hash>
typename list<pair<const Key, Value>>::iterator // return type  // whitch to use
hashmap<Key, Value, Compare, Hash>::findElement(const Key& x, size_t bucket) {

  // look for the key in the bucket
  for (auto it = elems_[bucket].begin();
    it != elems_[bucket].end();
    ++it)
    if (comp_(it->first, x)) return it;

  return elems_[bucket].end(); // if element not found, return end()
}


// returns a pointer to the element with key x
// returns nullptr if no element with this key
template <typename Key, typename Value, typename Compare, typename Hash>
typename hashmap<Key, Value, Compare, Hash>::Element* // return type
hashmap<Key, Value, Compare, Hash>::find(const Key& x) {

  size_t bucket = hash_.hash(x);
  auto it = findElement(x, bucket);    // use the findElement() helper   

  if (it != elems_[bucket].end())
    // found the element. Return a pointer to it.
    return &(*it); // dereference the iterator to list 
                   // then take the address of list element

  else // didn't find the element -- return nullptr
    return nullptr;
}

// finds the element with key x, inserts an
// element with that key if none exists yet. Returns a reference to
// the value corresponding to that key.
template <typename Key, typename Value, typename Compare, typename Hash>
pair<Value*, bool>
hashmap<Key, Value, Compare, Hash>::insert(const Element& x) {

  size_t bucket = hash_.hash(x.first);
  auto it = findElement(x.first, bucket);    // try to find the element // returns a list iterator

                                             // if not found, insert a new one.
  if (it == elems_[bucket].end()) {
    ++size_;
    elems_[bucket].push_back(x);
    return make_pair(&(elems_[bucket].back().second), true); // true because insert is successful. 
  }

  return make_pair(&(it->second), false); // false because element already existed
}



// removes the Element with key x, if it exists
template <typename Key, typename Value, typename Compare, typename Hash>
pair<pair<const Key, Value>*, bool>
hashmap<Key, Value, Compare, Hash>::erase(const Key& x) {
  size_t bucket = hash_.hash(x);
  typename list<pair<const Key, Value>>::iterator it = findElement(x, bucket);
  bool erased = false;

  if (it != elems_[bucket].end()) { // the element exists, erase it
    elems_[bucket].erase(it);
    --size_;
    erased = true;
  }
  // find next element in hashmap
  auto nextListIt = find_if(elems_.begin() + bucket, elems_.end(),
    [](list <pair<const Key, Value>> e)
  {return e.size() > 0; });

  // if last element in hashmap was deleted, return nullpointer as element in pair
  if (nextListIt == elems_.end())
    return make_pair(nullptr, erased);

  // if deleted element was not last, return next element as element in pair
  // next elemement is the first element of the list returned from the find_if as an iterator
  pair<const Key, Value> nextElement = *((*nextListIt).begin());
  return make_pair(&nextElement, erased);
}


// returns reference to value of element with key x,
// inserts if does not exist
template <typename Key, typename Value, typename Compare, typename Hash>
Value& hashmap<Key, Value, Compare, Hash>::operator[] (const Key& x) {

  Element* found = find(x);

  if (found == nullptr) { // if key not found, create new element with empty value
    auto inserted = insert(make_pair(x, Value())); // calling default constructor on Value
    return *(inserted.first);
  }
  return found->second;
}

template<typename Key, typename Value, typename Compare, typename Hash>
void hashmap<Key, Value, Compare, Hash>::rehash(size_t n) {

  // sets number of buckets to n 
  hash_.setNumBuckets(n);
  auto temp = std::move(elems_);

  elems_.clear();
  elems_.resize(n);
  size_ = 0;

  for (auto bucket : temp)
    for (auto element : bucket)
      insert(element);


  /*
  hash_.setNumBuckets(n);

  vector<pair<const Key, Value>> temp;

  for_each(elems_.begin(), elems_.end(), [&temp](list<pair<const Key, Value>> bucket) {
  for_each(bucket.begin(), bucket.end(), [&temp](pair<const Key, Value> element) {
  temp.push_back(element);
  });
  });

  elems_.clear();
  elems_.resize(n);
  this->size_ = 0; // reset size to zero so insertion does not double size

  //for_each(temp2.begin(), temp2.end(), [&](pair<const Key, Value> element) {})
  for (pair<const Key, Value> element : temp) {
  this->insert(element);
  }
  */
}

template<typename Key, typename Value, typename Compare, typename Hash>
void hashmap<Key, Value, Compare, Hash>::print() {
  // prints out all elements in hash function
  cout << "------------------------------------------------------------" << endl;
  cout << "Printing all values: \nKEY\tVALUE" << endl;
  for_each(elems_.begin(), elems_.end(), [](list<pair<const Key, Value>> bucket) {
    for_each(bucket.begin(), bucket.end(), [](pair<const Key, Value> element) {
      cout << element.first << "\t" << element.second << "\n";
    });
  });
  cout << "printed all " << this->size_ << " elements." << endl;
  cout << "------------------------------------------------------------" << endl;

}

#endif // MY_HASHMAP_H_




