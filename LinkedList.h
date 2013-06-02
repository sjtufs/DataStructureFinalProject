#ifndef __LINKEDLIST_H
#define __LINKEDLIST_H

#include "IndexOutOfBound.h"
#include "ElementNotExist.h"

template<class T>
class LinkedList
{
private:
	struct node;
	node *_head;
	int _size;

	void _node_clear()
	{
		for(node *_pos=_head->_next,*nex;_pos!=_head;_pos=nex)
		{
			nex=_pos->_next;
			delete _pos;
		}
		_head->_next=_head->_prev=_head;
		_size=0;
	}

	void _node_remove(node *_pos)
	{
		_pos->_next->_prev=_pos->_prev;
		_pos->_prev->_next=_pos->_next;
		delete _pos;
		_size--;
	}

public:
	class Iterator;

	LinkedList()
	{
		_head=new node();
		_head->_next=_head->_prev=_head;
		_size=0;
	}

	LinkedList(const LinkedList &_X)
	{
		_head=new node();
		_head->_next=_head->_prev=_head;
		copy(_X);
	}

	LinkedList& operator=(const LinkedList &_X)
	{
		if(this==&_X) return *this;
		copy(_X);
		return *this;
	}

	void copy(const LinkedList &_X)
	{
		node *_pos=_head,*xpos=_X._head->_next;
		for(;xpos!=_X._head;_pos=_pos->_next,xpos=xpos->_next)
			_pos->_next=new node(_pos,NULL,xpos->_data);
		_pos->_next=_head;
		_pos->_next->_prev=_pos;
		_size=_X._size;
	}

	~LinkedList()
	{
		_node_clear();
		delete _head;
	}

	bool add(const T &_E)
	{
		addLast(_E);
		return true;
	}

	void addFirst(const T &_E)
	{
		node *newnode=new node(_head,_head->_next,_E);
		_head->_next=newnode;
		newnode->_next->_prev=newnode;
		_size++;
	}

	void addLast(const T &_E)
	{
		node *newnode=new node(_head->_prev,_head,_E);
		_head->_prev=newnode;
		newnode->_prev->_next=newnode;
		_size++;
	}

	void add(int _index,const T &_E)
	{
		if(_index<0||_index>_size) throw IndexOutOfBound();
		node *_pos=_head;
		for(int __I=0;__I<_index;__I++) _pos=_pos->_next;
		node *newnode=new node(_pos,_pos->_next,_E);
		_pos->_next=newnode;
		newnode->_next->_prev=newnode;
		_size++;
	}

	void clear()
	{
		_node_clear();
	}

	bool contains(const T &_E) const
	{
		for(node *_pos=_head->_next;_pos!=_head;_pos=_pos->_next)
			if(_E==_pos->_data) return true;
		return false;
	}

	const T& get(int _index) const
	{
		if(_index<0||_index>=_size) throw IndexOutOfBound();
		node *_pos=_head;
		for(int __I=0;__I<=_index;__I++) _pos=_pos->_next;
		return _pos->_data;
	}

	const T& getFirst() const
	{
		if(isEmpty()) throw ElementNotExist();
		return _head->_next->_data;
	}

	const T& getLast() const
	{
		if(isEmpty()) throw ElementNotExist();
		return _head->_prev->_data;
	}

	bool isEmpty() const
	{
		return _head==_head->_prev;
	}

	void removeIndex(int _index)
	{
		if(_index<0||_index>=_size) throw IndexOutOfBound();
		node *_pos=_head;
		for(int __I=0;__I<=_index;__I++) _pos=_pos->_next;
		_node_remove(_pos);
	}

	bool remove(const T &_E)
	{
		for(node *_pos=_head->_next;_pos!=_head;_pos=_pos->_next)
			if(_E==_pos->_data)
			{
				_node_remove(_pos);
				return true;
			}
		return false;
	}

	void removeFirst()
	{
		if(isEmpty()) throw ElementNotExist();
		_node_remove(_head->_next);
	}

	void removeLast()
	{
		if(isEmpty()) throw ElementNotExist();
		_node_remove(_head->_prev);
	}

	void set(int _index,const T &_E)
	{
		if(_index<0||_index>=_size) throw IndexOutOfBound();
		node *_pos=_head;
		for(int __I=0;__I<=_index;__I++) _pos=_pos->_next;
		_pos->_data=_E;
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
struct LinkedList<T>::node
{
	node *_prev,*_next;
	T _data;
	node(node *pre,node *nex,const T &dat)
		:_prev(pre),_next(nex),_data(dat) {}
	node() {}
};

template<class T>
class LinkedList<T>::Iterator
{
private:
	node *_pos;
	LinkedList *_host;
	bool flag;

public:
	Iterator(LinkedList *hos)
		:_host(hos),_pos(hos->_head),flag(false) {}
	Iterator() {}
	bool hasNext()
	{
		return _pos->_next!=_host->_head;
	}

	const T& next()
	{
		if(!hasNext()) throw ElementNotExist();
		if(flag==true) flag=false;
		_pos=_pos->_next;
		return _pos->_data;
	}

	void remove()
	{
		if(flag==true||_pos==_host->_head) throw ElementNotExist();
		flag=true;
		node *pre=_pos->_prev;
		_host->_node_remove(_pos);
		_pos=pre;
	}
};

#endif
