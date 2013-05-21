#ifndef __ARRAYLIST_H
#define __ARRAYLIST_H
using namespace std;
#include "Utility.h"

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
        Iterator(ArrayList *_x,int _p=-1):_host(_x),_position(_p) {} 
        
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
			if(_position==-1/*||_position>=_data->size()*/) throw ElementNotExist();
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

    /**
     * Assignment operator
     */
    ArrayList& operator=(const ArrayList &_x)
	{
        /*
		delete []_data;
        _capacity=_x.size()*2;
		_data=new T[_capacity];
        _size=0;
		*/
		clear();
        for(int i=0;i<_x.size();i++) add(_x.get(i));
        return *this;
    }

    ArrayList(const ArrayList<T> &_x)
	{
		_capacity=_x.size()*2;
        _size=0;
		_data=new T[_capacity];
        for(int i=0;i<_x.size();i++) add(_x.get(i));
    }

    Iterator iterator()
	{
        return Iterator(this,-1);
//		Iterator *_tmp=new Iterator(this);
//        return *_tmp;
    }

    bool add(const T &_e)
	{
        if (_size==_capacity) ensureCapacity(_capacity*2);
        _data[_size++]=_e;
        return true;
    }

    void add(int _index,const T &_e)
	{
		if(_index<0||_index>_size) throw IndexOutOfBound();
        if (_size==_capacity) ensureCapacity(_capacity*2);
        for(int i=_size;i>_index;i--) _data[i]=_data[i-1];
        _data[_index]=_e;
        _size++;
    }

    /**
     * Removes all of the elements from this list.
     */
    void clear()
	{
        delete []_data;
        _data=new T[_capacity];
        _size=0;
    }

    bool contains(const T &_e) const
	{
        for(int i=0;i<_size;i++)
            if (_data[i]==_e) return true;
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

    int indexOf(const T &_e) const
	{
        for (int i=0;i<_size;i++) if (_data[i]==_e) return i;
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
	
	/*
    T removeIndex(int _index)
	{
        T _tmp=_data[_index];
        for(int i=_index;i<_size-1;i++)
            _data[i]=_data[i+1];
        _size--;
        return _tmp;
    }
	*/

    bool remove(const T &_e)
	{
        for (int i=0;i<_size;i++)
            if (_data[i]==_e) 
			{
                removeIndex(i);
                return true;
            }
    return false;
    }

	void set(int _index,const T &_e)
	{
		if(_index<0||_index>=_size) throw IndexOutOfBound();
        _data[_index]=_e;
    }

    /*
	T& set(int _index,const T &_e)
	{
        T _tmp=_data[_index];
        _data[_index]=_e;
        return _tmp;
    }
	*/

    int size() const
	{
        return _size;
    }
};
#endif
