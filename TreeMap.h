#ifndef __TREEMAP_H
#define __TREEMAP_H

#include "ElementNotExist.h"

template<class K,class V>
class TreeMap
{
public:
	class Entry;

private:
    struct node;

	node *_root,*_null;

	void _update(node *_X)
	{
		if(_X==_null) _X->_size=0;
		else _X->_size=_X->_L->_size+_X->_R->_size+1;
	}

    void _left_rotate(node *&_X)
	{
		node *__F=_X->_F;
		node *_Y=_X->_R;
		if(__F!=_null)
		{
			if(__F->_L==_X) __F->_L=_Y;
			else __F->_R=_Y;
		}
		_Y->_F=__F;
		_X->_R=_Y->_L;
		if(_X->_R!=_null) _X->_R->_F=_X;
		_Y->_L=_X;
		_X->_F=_Y;
		_update(_X);
		_update(_Y);
		_X=_Y;
	}

	void _right_rotate(node *&_X)
    {
		node *__F=_X->_F;
		node *_Y=_X->_L;
		if(__F!=_null)
		{
			if(__F->_L==_X) __F->_L=_Y;
			else __F->_R=_Y;
		}
		_Y->_F=__F;
		_X->_L=_Y->_R;
		if(_X->_L!=_null) _X->_L->_F=_X;
		_Y->_R=_X;
		_X->_F=_Y;
		_update(_X);
		_update(_Y);
		_X=_Y;
	}

	node *insert(node *_X,Entry &_data)
	{
		if(_X==_null)
		{
			_X=new node(_data);
			_X->_L=_X->_R=_X->_F=_null;
			_X->_size=1;
		}
		else if(_data.key<_X->_data.key)
		{
			_X->_L=insert(_X->_L,_data);
			_X->_L->_F=_X;
            if(_X->_L->_L->_size>_X->_R->_size)
                _right_rotate(_X);
		}
		else if(_data.key>_X->_data.key)
		{
			_X->_R=insert(_X->_R,_data);
			_X->_R->_F=_X;
            if(_X->_R->_R->_size>_X->_L->_size)
                _left_rotate(_X);
		}
		else if(_data.key==_X->_data.key)
		{
			_X->_data.value=_data.value;
		}
		_update(_X);
		return _X;
	}

	node *erase(node *_X,const K &key)
	{
		if(_X==_null) return _null;
		if(key<_X->_data.key)
			_X->_L=erase(_X->_L,key);
		else if(key>_X->_data.key)
			_X->_R=erase(_X->_R,key);
		else if(_X->_L==_null && _X->_R==_null)
		{
			delete _X;
			_X=_null;
		}
		else
		{
			if(_X->_L->_size<_X->_R->_size) _left_rotate(_X);
			else _right_rotate(_X);
			_X=erase(_X,key);
		}
		_update(_X);
		return _X;
	}

	node *eraseall(node *_X)
    {
		if(_X==_null) return _null;
		_X->_L=eraseall(_X->_L);
		_X->_R=eraseall(_X->_R);
		delete _X;
		return _null;
	}

	node *findkey(const K &key) const
	{
		node *_X=_root;
		while(_X!=_null)
		{
			if(_X->_data.key==key) return _X;
			else if(key<_X->_data.key) _X=_X->_L;
			else _X=_X->_R;
		}
		return _X;
	}

	bool findvalue(node *_X,const V &value) const
    {
		if(_X==_null) return false;
		if(_X->_data.value==value) return true;
		if(findvalue(_X->_L,value)) return true;
		if(findvalue(_X->_R,value)) return true;
		return false;
	}

public:
    class Iterator;

    TreeMap()
    {
		_null=new node();
		_null->_F=_null->_L=_null->_R=_null;
		_root=_null;
	}

    TreeMap(const TreeMap &_X)
    {
		_null=new node();
		_null->_F=_null->_L=_null->_R=_null;
		_root=_null;
		typename TreeMap<K,V>::Iterator it=_X.iterator();
		while(it.hasNext())
		{
			Entry d=it.next();
			put(d.key,d.value);
		}
	}

    ~TreeMap()
     {
		clear();
		delete _null;
	}

    TreeMap& operator=(const TreeMap &_X)
    {
        if(this==&_X) return *this;
		clear();
		typename TreeMap<K,V>::Iterator it=_X.iterator();
		while(it.hasNext())
        {
			Entry d=it.next();
			put(d.key,d.value);
		}
		return *this;
	}

    Iterator iterator() const
    {
		node *_pos=_root;
		while(_pos->_L!=_null) _pos=_pos->_L;
		return Iterator(_pos,_null);
	}

    void clear()
    {
		_root=eraseall(_root);
	}

    bool containsKey(const K& key) const
    {
		return findkey(key)!=_null;
	}

    bool containsValue(const V& value) const
    {
		return findvalue(_root,value);
	}

    const V& get(const K& key) const
    {
		node *_X=findkey(key);
		if(_X==_null) throw ElementNotExist();
		return _X->_data.value;
	}

    void put(const K& key,const V& value)
    {
		Entry _pos(key,value);
		_root=insert(_root,_pos);
	}

    void remove(const K& key)
    {
		int pre=_root->_size;
		_root=erase(_root,key);
		if(pre==_root->_size) throw ElementNotExist();
	}

    int size() const
    {
        return _root->_size;
    }

	bool isEmpty() const
	{
		return _root==_null;
	}
};

template<class K,class V>
class TreeMap<K,V>::Entry
{
public:
	K key;
	V value;
	Entry(K k,V v):key(k),value(v) {}
	K getKey() const { return key; }
	V getValue() const { return value; }
};

template<class K,class V>
struct TreeMap<K,V>::node
{
	node *_L,*_R,*_F;
	Entry _data;
	int _size;
	node ():_data(K(),V()),_size(0) {}
	node(const Entry &dat):_data(dat),_size(0) {}
};

template<class K,class V>
class TreeMap<K,V>::Iterator
{
private:
	node *_pos,*_null;
	bool _flag;

public:
	bool hasNext()
    {
		if(_pos==_null||_pos==NULL) return false;
		if(_pos->_R!=_null||!_flag) return true;
		node *_Q=_pos,*_X=_Q->_F;
		while(_X!=_null)
		{
			if(_X->_L==_Q) return true;
			else _Q=_X,_X=_Q->_F;
		}
		return false;
	}

	const Entry& next()
    {
		if(_pos==NULL||_pos==_null) throw ElementNotExist();
		if(!_flag)
		{
			_flag=true;
			return _pos->_data;
		}
		if(_pos->_R!=_null)
		{
			_pos=_pos->_R;
			while(_pos->_L!=_null) _pos=_pos->_L;
			return _pos->_data;
		}
		node *_Q=_pos,*_X=_Q->_F;
		while(_X!=_null)
		{
			if(_X->_L==_Q) return (_pos=_X)->_data;
			else _Q=_X,_X=_Q->_F;
		}
		throw ElementNotExist();
	}

	Iterator(node *_pos=NULL,node *_null=NULL):_pos(_pos),_null(_null),_flag(false) {}
    };

#endif

