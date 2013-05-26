#ifndef __ARRAYLIST_H
#define __ARRAYLIST_H

#include "IndexOutOfBound.h"
#include "ElementNotExist.h"

template<class T>
class ArrayList
{
private:
	T *list;
	int _capacity,_size;

	void make_space()
	{
		T *tmp=list;
		_capacity*=2;
		list=new T[_capacity];
		for(int i=0;i<_size;i++)
			list[i]=tmp[i];
		delete []tmp;
	}

public:
	class Iterator
	{
	public:
		int pos;
		bool flag;
		ArrayList *array;

		Iterator(ArrayList *arr=NULL):array(arr),pos(-1),flag(false) {}

		bool hasNext()
		{
			return pos<array->_size-1;
		}
	
		const T& next()
		{
			if(!hasNext()) throw ElementNotExist();
			flag=true;
			return array->get(++pos);
		}
		
		void remove()
		{
			if(flag==false) throw ElementNotExist();
			array->removeIndex(pos--);
			flag=false;
		}
	};

	ArrayList()
	{
		_capacity=100;
		_size=0;
		list=new T[_capacity];
	}

	ArrayList(int initial_capacity)
	{
		_capacity=initial_capacity;
		_size=0;
		list=new T[initial_capacity];
	}

	~ArrayList()
	{
		_capacity=0;
		_size=0;
		delete []list;
	}
	
	ArrayList& operator=(const ArrayList &x)
	{
		clear();
		for(int i=0;i<x._size;i++) add(x.get(i));
		return *this;
	}
	
	ArrayList(const ArrayList &x)
	{
		_capacity=x._size*2;
		_size=0;
		list=new T[_capacity];
		for(int i=0;i<x._size;i++) add(x.get(i));
	}
	
	bool add(const T &e)
	{
		if(_size==_capacity) make_space();
		list[_size++]=e;
		return true;
	}

	void add(int index,const T &e)
	{
		if(index<0||index>_size) throw IndexOutOfBound();
		if(_size==_capacity) make_space();
		for(int i=_size;i>index;i--)
			list[i]=list[i-1];
		list[index]=e;
		_size++;
	}


	void clear()
	{
		delete []list;
		list=new T[_capacity];
		_size=0;
	}

	bool contains(const T &e) const
	{
		for(int i=0;i<_size;i++)
		 if(list[i]==e)
			 return true;
		return false;
	}

	const T& get(int index) const
	{
		if(index<0||index>=_size) throw IndexOutOfBound();
		return list[index];
	}

	bool isEmpty() const
	{
		return _size==0;
	}

	void removeIndex(int index)
	{
		if(index<0||index>=_size) throw IndexOutOfBound();
		for(int i=index;i<_size-1;i++)
			list[i]=list[i+1];
		_size--;
	}

	bool remove(const T &e)
	{
		for(int i=0;i<_size;i++)
			if(list[i]==e)
			{
				removeIndex(i);
				return true;
			}
		return false;
	}

	void set(int index,const T &e)
	{
		if(index<0||index>=_size) throw IndexOutOfBound();
		list[index]=e;
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

#endif
