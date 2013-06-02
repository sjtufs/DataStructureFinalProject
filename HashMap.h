#ifndef __HASHMAP_H
#define __HASHMAP_H

#include "ElementNotExist.h"

template <class K,class V,class H>
class HashMap
{
private:
    int _capacity,_size;
public:
    class Entry;

    struct node;

    node **_storage;

    class Iterator;

    HashMap()
    {
        _capacity=99971;
        _size=0;
        _storage=new node*[_capacity];
        for(int __I=0;__I<_capacity;__I++)
            _storage[__I]=new node;
    }

    HashMap(int _initial_capacity)
    {
        _capacity=_initial_capacity;
        _size=0;
        _storage=new node*[_capacity];
        for(int __I=0;__I<_capacity;__I++)
            _storage[__I]=new node;
    }

    ~HashMap()
    {
        clear();
        for(int __I=0;__I<_capacity;__I++)
            delete _storage[__I];
        delete [] _storage;
    }

    HashMap &operator=(const HashMap &x)
    {
		if(this==&x) return *this;
        clear();
        for(int __I=0;__I<_capacity;__I++)
            delete _storage[__I];
        delete [] _storage;
        _capacity=x._capacity;
        _size=0;
        _storage=new node*[_capacity];
        for(int __I=0;__I<_capacity;__I++)
        {
            _storage[__I]=new node;
            for(node *_pos=x._storage[__I]->_next;_pos!=NULL;_pos=_pos->_next)
                insert(_pos->_data);
        }
        return *this;
    }

    HashMap(const HashMap &x)
    {
        _capacity=x._capacity;
        _size=0;
        _storage=new node*[_capacity];
        for(int __I=0;__I<_capacity;__I++)
        {
            _storage[__I]=new node;
            for(node *_pos=x._storage[__I]->_next;_pos!=NULL;_pos=_pos->_next)
                insert(_pos->_data);
        }
    }

    Iterator iterator() const
    {
        return Iterator(this);
    }

    void clear()
    {
        for(int __I=0;__I<_capacity;__I++)
        {
            for(node* _pos=_storage[__I]->_next,*_rem;_pos!=NULL;_rem=_pos,_pos=_pos->_next,delete _rem)
                ;
            _storage[__I]->_next=NULL;
        }
        _size=0;
    }

    bool containsKey(const K &key) const
    {
        int _P=(H::hashCode(key)%_capacity+_capacity)%_capacity;
        for(node *_pos=_storage[_P]->_next;_pos!=NULL;_pos=_pos->_next)
            if(_pos->_data.key==key)
                return true;
        return false;
    }

    bool containsValue(const V &value) const
    {
        for(int __I=0;__I<_capacity;__I++)
            for(node *_pos=_storage[__I]->_next;_pos!=NULL;_pos=_pos->_next)
                if(_pos->_data.value==value)
                    return true;
        return false;
    }

    const V &get(const K &key) const
    {
        int _P=(H::hashCode(key)%_capacity+_capacity)%_capacity;
        for(node *_pos=_storage[_P]->_next;_pos!=NULL;_pos=_pos->_next)
            if(_pos->_data.key==key)
                return _pos->_data.value;
        throw ElementNotExist();
    }

    bool isEmpty() const
    {
        return !_size;
    }

    void put(const K &key,const V &value)
    {
        int _P=(H::hashCode(key)%_capacity+_capacity)%_capacity;
        for(node *_pos=_storage[_P]->_next;_pos!=NULL;_pos=_pos->_next)
            if(_pos->_data.key==key)
            {
                _pos->_data.value=value;
                return;
            }
        insert(Entry(key,value));
    }

    void remove(const K &key)
    {
        int _P=(H::hashCode(key)%_capacity+_capacity)%_capacity;
        for(node *_pos=_storage[_P]->_next,*_rem=_storage[_P];_pos!=NULL;_rem=_pos,_pos=_pos->_next)
            if(_pos->_data.key==key)
            {
                _rem->_next=_pos->_next;
                delete _pos;
                --_size;
                return;
            }
        throw ElementNotExist();
    }

    int size() const
    {
        return _size;
    }

    void insert(const Entry & _E)
    {
        int _P=(H::hashCode(_E.key)%_capacity+_capacity)%_capacity;
        node *_data=new node(_E);
        _data->_next=_storage[_P]->_next;
        _storage[_P]->_next=_data;
        _size++;
    }
};

template<class K,class V,class H>
class HashMap<K,V,H>::Entry
{
public:
	K key;V value;
    Entry(K k,V v):key(k),value(v) {}
    Entry() {}
    K getKey() const { return key; }
    V getValue() const{ return value; }
};

template<class K,class V,class H>
struct HashMap<K,V,H>::node
{
    Entry _data;
    node *_next;
    node(const Entry &dat):_data(dat),_next(NULL) {}
    node():_next(NULL) {}
};

template<class K,class V,class H>
class HashMap<K,V,H>::Iterator
{
private:
    int _cur;
    node *_pos;
    const HashMap *_host;
public:
	bool hasNext() const
    {
        if(_pos->_next) return true;
		for(int __I=_cur+1;__I<_host->_capacity;__I++)
	        if(_host->_storage[__I]->_next!=NULL)
                return true;
		return false;
    }

	const Entry &next()
	{
		if(!hasNext()) throw ElementNotExist();
		if(_pos->_next!=NULL)
        {
			_pos=_pos->_next;
			return _pos->_data;
        }
        for(int __I=_cur+1;__I<_host->_capacity;__I++)
            if(_host->_storage[__I]->_next!=NULL)
			{
                _pos=_host->_storage[__I]->_next;_cur=__I;
                return _pos->_data;
            }
	}

    Iterator(const HashMap *hos=NULL):_host(hos) {_pos=_host->_storage[0];_cur=0;}
};
#endif
