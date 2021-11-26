// ExpandableHashMap.h

// Skeleton for the ExpandableHashMap class template.  You must implement the first six
// member functions.

#include <list> // for std::list
#include <utility> // for std::pair

template<typename KeyType, typename ValueType>
class ExpandableHashMap {
public:
	ExpandableHashMap(double maximumLoadFactor = 0.5);
	~ExpandableHashMap();
	void reset();
	int size() const;
	void associate(const KeyType& key, const ValueType& value);
	const ValueType* find(const KeyType& key) const;
	ValueType* find(const KeyType& key) {
		return const_cast<ValueType*>(const_cast<const ExpandableHashMap*>(this)->find(key));
	}
	ExpandableHashMap(const ExpandableHashMap&) = delete;
	ExpandableHashMap& operator=(const ExpandableHashMap&) = delete;

private:
    double m_size; // amnt of data in the map
    double m_maxLoadFactor; // duh
    int m_numBuckets; // num of buckets in the map
    std::list<std::pair<KeyType, ValueType>>* m_buckets; // array of lists, buckets
};

template<typename KeyType, typename ValueType>
ExpandableHashMap<KeyType, ValueType>::ExpandableHashMap(double maximumLoadFactor) : m_size(0), m_maxLoadFactor(maximumLoadFactor), m_numBuckets(8) {
    m_buckets = new std::list<std::pair<KeyType, ValueType>>[m_numBuckets];
}

template<typename KeyType, typename ValueType>
ExpandableHashMap<KeyType, ValueType>::~ExpandableHashMap() {
    delete [] m_buckets;
}

template<typename KeyType, typename ValueType>
void ExpandableHashMap<KeyType, ValueType>::reset() {
    delete m_buckets; // destroy old map
    m_numBuckets = 8; // make initial value
    m_size = 0; // make initial value
    m_buckets = new std::list<std::pair<KeyType, ValueType>>*[m_numBuckets]; // make new empty map
}

template<typename KeyType, typename ValueType>
int ExpandableHashMap<KeyType, ValueType>::size() const {
    return m_size;
}

template<typename KeyType, typename ValueType>
void ExpandableHashMap<KeyType, ValueType>::associate(const KeyType& key, const ValueType& value) {
    unsigned int hasher(const KeyType& k); // prototype
    ValueType* dupeCheck = find(key);
    if (dupeCheck != nullptr) { // if the key is already in the map
        *dupeCheck = value; // change value to new one (no need to check if the value is diff)
        return;
    }
    m_size++; // reflect new addition
    if (m_size / m_numBuckets > m_maxLoadFactor) { // rehash needed
        std::list<std::pair<KeyType, ValueType>>* temp = new std::list<std::pair<KeyType, ValueType>>[m_numBuckets * 2];
        for (int i = 0; i < m_numBuckets; i++) { // effectively O(1)
            for (auto iter = m_buckets[i].begin(); iter != m_buckets[i].end(); iter++) { // O(N)
                unsigned int bucketNum = hasher(std::get<0>(*iter)) % (m_numBuckets * 2); // hash into new map
                temp[bucketNum].push_back(*iter); // insert into correct bucket
            }
        }
        delete [] m_buckets;
        m_buckets = temp; // set m_buckets equal to new map
        m_numBuckets *= 2; // update num of buckets
    }
    unsigned int bucketNum = hasher(key) % m_numBuckets;
    m_buckets[bucketNum].push_back(std::make_pair(key, value)); // add new pair
}

template<typename KeyType, typename ValueType>
const ValueType* ExpandableHashMap<KeyType, ValueType>::find(const KeyType& key) const {
    unsigned int hasher(const KeyType& k); // prototype
    unsigned int bucketNum = hasher(key) % m_numBuckets; // find the bucket it belongs in
    for (auto iter = m_buckets[bucketNum].begin(); iter != m_buckets[bucketNum].end(); iter++) { // run thru the bucket, effectively O(1)
        if (std::get<0>(*iter) == key) // if key found
            return &(std::get<1>(*iter)); // return address of valuetype
    }
    return nullptr; // not found
}

