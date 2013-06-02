#ifndef __ARRAYLIST_H
#define __ARRAYLIST_H

#include "IndexOutOfBound.h"
#include "ElementNotExist.h"

template<class T>
class ArrayList
{
private:
	T *_list;
	int _capacity,_size;

	void make_space()
	{
		T *__TMP=_list;
		_capacity*=2;
		_list=new T[_capacity];
		for(int __I=0;__I<_size;__I++)
			_list[__I]=__TMP[__I];
		delete []__TMP;
	}

public:
	class Iterator;

	ArrayList()
	{
		_capacity=100;
		_size=0;
		_list=new T[_capacity];
	}

	ArrayList(int _initial_capacity)
	{
		_capacity=_initial_capacity;
		_size=0;
		_list=new T[_initial_capacity];
	}

	~ArrayList()
	{
		_capacity=0;
		_size=0;
		delete []_list;
	}

	ArrayList& operator=(const ArrayList &_X)
	{
		clear();
		for(int __I=0;__I<_X._size;__I++) add(_X.get(__I));
		return *this;
	}

	ArrayList(const ArrayList &_X)
	{
		_capacity=_X._size*2;
		_size=0;
		_list=new T[_capacity];
		for(int __I=0;__I<_X._size;__I++) add(_X.get(__I));
	}

	bool add(const T &_E)
	{
		if(_size==_capacity) make_space();
		_list[_size++]=_E;
		return true;
	}

	void add(int _index,const T &_E)
	{
		if(_index<0||_index>_size) throw IndexOutOfBound();
		if(_size==_capacity) make_space();
		for(int __I=_size;__I>_index;__I--)
			_list[__I]=_list[__I-1];
		_list[_index]=_E;
		_size++;
	}


	void clear()
	{
		delete []_list;
		_list=new T[_capacity];
		_size=0;
	}

	bool contains(const T &_E) const
	{
		for(int __I=0;__I<_size;__I++)
		 if(_list[__I]==_E)
			 return true;
		return false;
	}

	const T& get(int _index) const
	{
		if(_index<0||_index>=_size) throw IndexOutOfBound();
		return _list[_index];
	}

	bool isEmpty() const
	{
		return _size==0;
	}

	void removeIndex(int _index)
	{
		if(_index<0||_index>=_size) throw IndexOutOfBound();
		for(int __I=_index;__I<_size-1;__I++)
			_list[__I]=_list[__I+1];
		_size--;
	}

	bool remove(const T &_E)
	{
		for(int __I=0;__I<_size;__I++)
			if(_list[__I]==_E)
			{
				removeIndex(__I);
				return true;
			}
		return false;
	}

	void set(int _index,const T &_E)
	{
		if(_index<0||_index>=_size) throw IndexOutOfBound();
		_list[_index]=_E;
	}

	int size() const
	{
		return _size;
	}

	Iterator iterator()
	{
		return Iterator(this);
	}
};

template<class T>
class ArrayList<T>::Iterator
{
public:
	int _pos;
	bool _flag;
	ArrayList *_array;

	Iterator(ArrayList *arr=NULL):_array(arr),_pos(-1),_flag(false) {}

	bool hasNext()
	{
		return _pos<_array->_size-1;
	}

	const T& next()
	{
		if(!hasNext()) throw ElementNotExist();
		_flag=true;
		return _array->get(++_pos);
	}

	void remove()
	{
		if(_flag==false) throw ElementNotExist();
		_array->removeIndex(_pos--);
		_flag=false;
	}
};

#endif
