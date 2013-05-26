#ifndef __LINKEDLIST_H
#define __LINKEDLIST_H

#include "IndexOutOfBound.h"
#include "ElementNotExist.h"

template <class T>
class LinkedList
{
    struct node
    {
        T _data;
        node *_prev,*_next;
        node (const T &_dat,node *_pre=NULL,node *_nex=NULL):_data(_dat),_prev(_pre),_next(_nex) {}
		node():_prev(NULL),_next(NULL) {}
        ~node() {};
    };

private:
    node *_head,*_tail;
    int _size;

public:
    class Iterator
    {
        bool _flag;
        node *_position;
        LinkedList *_list;
    public:
        Iterator(LinkedList *_lis=NULL):_list(_lis),_flag(false)
        {
            _position=_list->_head;
        }

		bool hasNext()
        {
            return _position->_next!=_list->_tail;
        }

        const T &next()
        {
            if(!hasNext()) throw ElementNotExist();
            _position=_position->_next;
			_flag=true;
            return _position->_data;
        }

        void remove()
        {
            if(_flag==false) throw ElementNotExist();
            node *_tmp=_position->_prev;
            _tmp->_next=_position->_next;
            _position->_next->_prev=_tmp;
            delete _position;
            _list->_size--;
			_position=_tmp;
			_flag=false;
        }
    };

	node* _get_index(int _index)
    {
        if(_index<0||_index>=_size) throw IndexOutOfBound();
        node *_pos=_head->_next;
        while(_index--) _pos=_pos->_next;
        return _pos;
    }

	LinkedList()
    {
		_size=0;
		_head=new node;
		_tail=new node;
        _head->_next=_tail;
		_tail->_prev=_head;
    }

	void clear()
    {
        node *_last,*_pos=_head->_next;
		while(_pos!=_tail)
		{
			_last=_pos;
			_pos=_pos->_next;
			delete _last;
		}
        _head->_next=_tail;
		_tail->_prev=_head;
		_size=0;
	}

	LinkedList<T>& operator=(const LinkedList<T> &_x)
	{
		clear();
		_size=_x>_size;
		node *_pos=_head,*_x_pos=_x._head->_next,*_newnode;
		while(_x_pos!=_x._tail)
		{
			_newnode=new node(_x_pos->_data,_pos,NULL);
			_pos->_next=_newnode;
			_pos=_pos->_next;
			_x_pos=_x_pos->_next;
		}
		_pos->_next=_tail;
		_tail->_prev=_pos;
	}

	LinkedList(const LinkedList<T> &_x)
	{
		_size=_x._size;
		_head=new node;
		_tail=new node();
		node *_pos=_head,*_x_pos=_x._head->_next,*_newnode;
		while(_x_pos!=_x._tail)
		{
			_newnode=new node(_x_pos->_data,_pos,NULL);
			_pos->_next=_newnode;
			_pos=_pos->_next;
			_x_pos=_x_pos->_next;
		}
		_pos->_next=_tail;
		_tail->_prev=_pos;
	}

    ~LinkedList()
	{
		clear();
	}

    bool add(const T &_E)
    {
        node *_newnode=new node(_E,_tail->_prev,_tail);
        _tail->_prev->_next=_newnode;
        _tail->_prev=_newnode;
        _size++;
        return true;
    }

    void addFirst(const T &_E)
    {
        node *_newnode=new node(_E,_head,_head->_next);
        _head->_next->_prev=_newnode;
        _head->_next=_newnode;
        _size++;
    }

    void addLast(const T &_E)
	{
		add(_E);
	}

    void add(int _index,const T &_E)
    {
        node *_pos=_get_index(_index);
        node *_newnode=new node(_E,_pos->_prev,_pos);
        _pos->_prev->_next=_newnode;
		_pos->_prev=_newnode;
		_size++;
    }

	bool contains(const T &_E) const
	{
		node *_pos=_head->_next;
		while(_pos!=_tail)
			if(_pos->_data==_E) return true;
			else _pos=_pos->_next;
		return false;
	}

	const T& get(int _index) const
    {
        if(_index<0||_index>=_size) throw IndexOutOfBound();
        node *_pos=_head->_next;
		while(_index--) _pos=_pos->_next;
        return _pos->_data;
    }

    const T& getFirst() const
    {
        if(isEmpty()) throw ElementNotExist();
        return get(0);
    }

    const T& getLast() const
    {
        if(isEmpty()) throw ElementNotExist();
        return get(_size-1);
    }

    bool isEmpty() const
    {
        return _size==0;
    }

    void removeIndex(int _index)
    {
        if(_index<0||_index>=_size) throw IndexOutOfBound();
        node *_pos=_get_index(_index);
        _pos->_prev->_next=_pos->_next;
        _pos->_next->_prev=_pos->_prev;
        delete _pos;
		_size--;
    }
    
	bool remove(const T &_E)
    {
        node *_pos=_head->_next;
        for (int __i=0;__i<_size;__i++)
			if(_pos->_data==_E)
			{
				removeIndex(__i);
				return true;
			}
			else _pos=_pos->_next;
        return 0;
    }

	void removeFirst()
    {
        if(isEmpty()) throw ElementNotExist();
        removeIndex(0);
    }

    void removeLast()
    {
        if(isEmpty()) throw ElementNotExist();
        removeIndex(_size-1);
    }
    
	void set(int _index,const T &_E)
    {
        if(_index<0||_index>=_size) throw IndexOutOfBound();
        node *_pos=_get_index(_index);
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
#endif
