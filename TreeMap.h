#ifndef __T_REEMAP_H
#define __T_REEMAP_H

#include "ElementNotExist.h"
#include "IndexOutOfBound.h"
#include <cstdlib>

template<class K,class V>
class TreeMap
{
public:
	class Entry
	{
	public:
		K _key;
		V _value;
		Entry(K _k,V _v)
		{
			_key=_k;
			_value=_v;
		}
		K getKey() const { return _key; }
		V getValue() const { return _value; }
	};

	struct node
	{
		Entry _data;
		int _aux;
		node *_L,*_R;

		node (const Entry &_dat):_data(_dat),_L(NULL),_R(NULL)
		{
			_aux=std::rand()<<15+std::rand();
		}

		node():_L(NULL),_R(NULL)
		{
			_aux=std::rand()<<15+std::rand();
		}
		~node() {}
	};
	node *_root;
	int _size;

	class Iterator
	{
	public:
		K _k;
		bool _flag;
		const TreeMap *_treap;

		Iterator(const TreeMap *_tre=NULL):_treap(_tre),_flag(false) {}

		bool hasNext()
		{
			if(_treap->_root==NULL) return false;
			if(_flag==false) return true;
			if(_treap->_get_next(_treap->_root,_k)!=NULL) return true;
			return false;
			//return (!_flag || _treap->get_next(_treap->_root,_k)!=NULL);
		}

		const Entry& next()
		{
			if(hasNext()==false) throw ElementNotExist();
			node *_Y;
			if(!_flag) _Y=_treap->_get_min();
			else _Y=_treap->_get_next(_treap->_root,_k);
			_flag=true;
			_k=_Y->_data._key;
			return _Y->_data;
		}
	};

	void _right_rotate(node *&_X)
	{
		node *_Y=_X->_L;
		_X->_L=_Y->_R;
		_Y->_R=_X;
		_X=_Y;
	}

	void _left_rotate(node *&_X)
	{
		node *_Y=_X->_R;
		_X->_R=_Y->_L;
		_Y->_L=_X;
		_X=_Y;
	}

	void _insert(node *&_X,const Entry &_e)
	{
		if(_X==NULL)
		{
			_X=new node(_e);
			_size++;
			return;
		}
		else if(_e._key<_X->_data._key)
		{
			_insert(_X->_L,_e);
			if(_X->_L->_aux>_X->_aux) _right_rotate(_X);
		}
		else if(_e._key>_X->_data._key)
		{
			_insert(_X->_R,_e);
			if(_X->_R->_aux>_X->_aux) _left_rotate(_X);
		}
		else _X->_data._value=_e._value;
	}

	void _remove(node *&_X,const K &_k)
	{
		if(_X==NULL) throw ElementNotExist();
		if(_X->_data._key==_k)
			if(_X->_L==NULL)
			{
				node *_Y=_X;
				_X=_X->_R;
				delete _Y;
				_size--;
			}
			else if(_X->_R==NULL)
			{
				node *_Y=_X;
				_X=_X->_L;
				delete _Y;
				_size--;
			}
			else if(_X->_L->_aux>_X->_R->_aux)
			{
				_right_rotate(_X);
				_remove(_X->_R,_k);
			}
			else
			{
				_left_rotate(_X);
				_remove(_X->_L,_k);
			}
		else if(_k<_X->_data._key) _remove(_X->_L,_k);
		else _remove(_X->_R,_k);
	}

	void _remove_sub(node *&_X)
	{
		if(_X==NULL) return;
		_remove_sub(_X->_L);
		_remove_sub(_X->_R);
		node *_Y=_X;
		_X=NULL;
		delete _Y;
	}

	node* _get_next(node *_X,const K &_k) const
	{
		if(_X==NULL) return NULL;
		if(_X->_data._key<=_k) return _get_next(_X->_R,_k);
		else
		{
			node *_Y=_get_next(_X->_L,_k);
			if(_Y) return _Y;
			return _X;
		}
	}

	node* _get_min() const
	{
		node *_pos=_root;
		while(_pos->_L!=NULL) _pos=_pos->_L;
		return _pos;
	}

	void _add_all(node *&_X,node *_Y)
	{
		if(_Y==NULL) return;
		_X=new node(_Y->_data);
		_X->_aux=_Y->_aux;
		_add_all(_X->_L,_Y->_L);
		_add_all(_X->_R,_Y->_R);
	}

	bool _has_key(node *_X,const K &_k,V &_v) const
	{
		if(_X==NULL) return false;
		if(_k==_X->_data._key) { _v=_X->_data._value; return true; }
		else if(_k<_X->_data._key) return _has_key(_X->_L,_k,_v);
		else return _has_key(_X->_R,_k,_v);
	}

	bool _has_value(node *_X,const V &_v) const
	{
		if(_X==NULL) return false;
		return _v==_X->_data._value || _has_value(_X->_L,_v) || _has_value(_X->_R,_v);
	}

	TreeMap()
	{
		_root=NULL;
		_size=0;
	}

	~TreeMap()
	{
		clear();
	}

	TreeMap& operator=(const TreeMap &_X)
	{
		_remove_sub(_root);
		_size=_X._size;
		_add_all(_root,_X._root);
	}

	TreeMap(const TreeMap &_X)
	{
		_root=NULL;
		_size=_X._size;
		_add_all(_root,_X._root);
	}

	Iterator iterator() const
	{
		return Iterator(this);
	}

	void clear()
	{
		_size=0;
		_remove_sub(_root);
	}

	bool containsKey(const K &_key) const
	{
		V _v;
		return _has_key(_root,_key,_v);
	}

	bool containsValue(const V &_value) const
	{
		return _has_value(_root,_value);
	}

	const V &get(const K &_key) const
	{
		V _v;
		if(!_has_key(_root,_key,_v)) throw ElementNotExist();
		return _v;
	}

	bool isEmpty() const
	{
		return _size==0;
	}

	void put(const K &_key,const V &_value)
	{
		Entry _data(_key,_value);
		_insert(_root,_data);
	}

	void remove(const K &_key)
	{
		_remove(_root,_key);
	}

	int size() const
	{
		return _size;
	}
};

#endif
