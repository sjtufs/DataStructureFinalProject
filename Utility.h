
#include <string>

#ifndef __UTILITY_H
#define __UTILITY_H

class IndexOutOfBound 
	{
	public:
		IndexOutOfBound() {}
		IndexOutOfBound(std::string msg):msg(msg) {}
		std::string getMessage() const {return msg;}
	private:
		std::string msg;
	};

class ElementNotExist
	{
	public: 
		ElementNotExist() {}
		ElementNotExist(std::string msg):msg(msg) {}
		std::string getMessage() const {return msg;}
	private:
		std::string msg;
	};

template<class K,class V> 
class Entry
	{
	public:
		const K key;
		V value;

		Entry(const K& key,const V &value):key(key),value(value) {}
	};
#endif

