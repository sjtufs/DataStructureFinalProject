#ifndef __ENTRY_H
#define __ENTRY_H

template<class K,class V>
class Entry
	{
	public:
		K key;
		V value;
		
		Entry(K k,V v):key(k),value(v) {}
		K getKey() {return key;}
		V getValue() {return value;}
	};

#endif
