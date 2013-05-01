#include <string>

#ifndef __UTILITY_H
#define __UTILITY_H

/**
 * Adds all elements of container b into container a
 */
template<class T1,class T2>
inline void addAll(T1 &a,const T2 &b)
    {
    typename T2::ConstIterator it=b.constIterator();
    while (it.hasNext())
        {
        a.add(it.next());
        }
    }

/**
 * Throws when an index is out of range
 */
class IndexOutOfBound {
public:
    IndexOutOfBound() {}
    IndexOutOfBound(std::string msg):msg(msg) {}
    std::string getMessage() const {return msg;}
private:
    std::string msg;
};

/**
 * Throws when an required element does not exist
 */
class ElementNotExist {
public: ElementNotExist() {}
    ElementNotExist(std::string msg):msg(msg) {}
    std::string getMessage() const {return msg;}
private:
    std::string msg;
};

/**
 * Map.Entry,a key-value pair.
 */
template <class K,class V>
class Entry
	{
	public:
		K key;
		V value;

		/**
		 * Constructor
		 */
		Entry(const K& k,const V& v):key(k),value(v) {}

		K getKey() const {return key;}

		V getValue() const {return value;}
};
#endif

