
#include <string>

#ifndef __UTILITY_H
#define __UTILITY_H

class IndexOutOfBound
	{
	public:
		IndexOutOfBound(std::string msg="Error: Index out of bound!"):msg(msg) {}
		std::string getMessage() const {return msg;}
	private:
		std::string msg;
	};

class ElementNotExist
	{
	public:
		ElementNotExist(std::string msg="Error: Element not exist!"):msg(msg) {}
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

template<class T1,class T2>
void appendALL(T1 &v1,const T2 &v2)
	{
	typename T2::constIterator tmp=v2.ConstIterator();
	while(tmp.hasNext()) v1.add(tmp.next());
	}
#endif

