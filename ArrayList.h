#ifndef __ARRAYLIST_H
#define __ARRAYLIST_H
using namespace std;

#include "ElementNotExist.h"
#include "IndexOutOfBound.h"

template <class T>
class ArrayList
{
    T *_data;
    int _size, _capacity;
	
	public:
    class Iterator 
	{
        int _position;
        ArrayList<T> *_host;
    
		public:
        Iterator(ArrayList *x,int _p=-1):_host(x),_position(_p) {} 
        
		bool hasNext()
		{
            return (_position<_host->size()-1);
        }

        T& next()
		{
            if(!hasNext()) throw ElementNotExist();
			return _host->get(++_position);
        }

        void remove()
		{
			if(_position==-1) throw ElementNotExist();
            _host->removeIndex(_position);
            --_position;
        }
	};

    ArrayList()
	{
        _capacity=10;
        _size=0;
		_data=new T[_capacity];
    }

    ~ArrayList()
	{
        _capacity=0;
        _size=0;
        delete []_data;
    }

    ArrayList& operator=(const ArrayList &x)
	{
		clear();
        for(int i=0;i<x.size();i++) add(x.get(i));
        return *this;
    }

    ArrayList(const ArrayList<T> &x)
	{
		_capacity=x.size()*2;
        _size=0;
		_data=new T[_capacity];
        for(int i=0;i<x.size();i++) add(x.get(i));
    }

    Iterator iterator()
	{
        return Iterator(this,-1);
    }

    bool add(const T &e)
	{
        if (_size==_capacity) ensureCapacity(_capacity*2);
        _data[_size++]=e;
        return true;
    }

    void add(int _index,const T &e)
	{
		if(_index<0||_index>_size) throw IndexOutOfBound();
        if (_size==_capacity) ensureCapacity(_capacity*2);
        for(int i=_size;i>_index;i--) _data[i]=_data[i-1];
        _data[_index]=e;
        _size++;
    }
    
	void clear()
	{
        delete []_data;
        _data=new T[_capacity];
        _size=0;
    }

    bool contains(const T &e) const
	{
        for(int i=0;i<_size;i++)
            if (_data[i]==e) return true;
        return false;
    }

    void ensureCapacity(int _new_capacity) 
	{
		if(_capacity>_new_capacity) return;
        T _tmp[_size];
        for(int i=0;i<_size;i++) _tmp[i]=_data[i];
        delete []_data;
        _capacity=_new_capacity;
		_data=new T[_new_capacity];
        for(int i=0;i<_size;i++) _data[i]=_tmp[i];
    }
	
    T& get(int _index)
	{
		if(_index<0||_index>=_size) throw IndexOutOfBound();
        return _data[_index];
    }
    
	const T& get(int _index) const
	{
		if(_index<0||_index>=_size) throw IndexOutOfBound();
        return _data[_index];
    }

    int indexOf(const T &e) const
	{
        for (int i=0;i<_size;i++) if (_data[i]==e) return i;
        return -1;
    }

    bool isTmpty() const 
	{ 
		return (_size==0);
	}

	void removeIndex(int _index)
	{
		if(_index<0||_index>=_size) throw IndexOutOfBound();
        for(int i=_index;i<_size-1;i++) _data[i]=_data[i+1];
        _size--;
    }
	
    bool remove(const T &e)
	{
        for (int i=0;i<_size;i++)
            if (_data[i]==e) 
			{
                removeIndex(i);
                return true;
            }
    return false;
    }

	void set(int _index,const T &e)
	{
		if(_index<0||_index>=_size) throw IndexOutOfBound();
        _data[_index]=e;
    }

    int size() const
	{
        return _size;
    }

	bool isEmpty() const
	{
		return _size==0;
	}
};
#endif
