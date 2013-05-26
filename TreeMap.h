#ifndef __TREEMAP_H
#define __TREEMAP_H

#include "ElementNotExist.h"

template<class K,class V>
class TreeMap
{
public:
	class Entry
	{
	public:
		K key;
		V value;
		Entry(K k,V v):key(k),value(v) {}
		K getKey() const { return key; }
		V getValue() const { return value; }
	};

private:
    struct node
    {
		node *L,*R,*F;
		Entry data;
		int _size;
		node ():data(K(),V()),_size(0) {}
		node(const Entry &dat):data(dat),_size(0) {}
	};

	node *root,*null;

	void update(node *x)
	{
		if(x==null) x->_size=0;
		else x->_size=x->L->_size+x->R->_size+1;
	}

    void leftrotate(node *&x)
	{
		node *f=x->F;
		node *y=x->R;
		if(f!=null)
		{
			if(f->L==x) f->L=y;
			else f->R=y;
		}
		y->F=f;
		x->R=y->L;
		if(x->R!=null) x->R->F=x;
		y->L=x;
		x->F=y;
		update(x);
		update(y);
		x=y;
	}

	void rightrotate(node *&x)
    {
		node *f=x->F;
		node *y=x->L;
		if(f!=null)
		{
			if(f->L==x) f->L=y;
			else f->R=y;
		}
		y->F=f;
		x->L=y->R;
		if(x->L!=null) x->L->F=x;
		y->R=x;
		x->F=y;
		update(x);
		update(y);
		x=y;
	}

	node *insert(node *x,Entry &data)
	{
		if(x==null)
		{
			x=new node(data);
			x->L=x->R=x->F=null;
			x->_size=1;
		}
		else if(data.key<x->data.key)
		{
			x->L=insert(x->L,data);
			x->L->F=x;
            if(x->L->L->_size>x->R->_size)
                rightrotate(x);
		}
		else if(data.key>x->data.key)
		{
			x->R=insert(x->R,data);
			x->R->F=x;
            if(x->R->R->_size>x->L->_size)
                leftrotate(x);
		}
		else if(data.key==x->data.key)
		{
			//V tmp=data.value;
			//data.value=x->data.value;
			//x->data.value=tmp;
			x->data.value=data.value;
		}
		update(x);
		return x;
	}

	node *erase(node *x,const K &key)
	{
		if(x==null) return null;
		if(key<x->data.key)
			x->L=erase(x->L,key);
		else if(key>x->data.key)
			x->R=erase(x->R,key);
		else if(x->L==null && x->R==null)
		{
			delete x;
			x=null;
		}
		else
		{
			if(x->L->_size<x->R->_size) leftrotate(x);
			else rightrotate(x);
			x=erase(x,key);
		}
		update(x);
		return x;
	}


	node *eraseall(node *x)
    {
		if(x==null) return null;
		x->L=eraseall(x->L);
		x->R=eraseall(x->R);
		delete x;
		return null;
	}

	node *findkey(const K &key) const
	{
		node *x=root;
		while(x!=null)
		{
			if(x->data.key==key) return x;
			else if(key<x->data.key) x=x->L;
			else x=x->R;
		}
		return x;
	}

	bool findvalue(node *x,const V &value) const
    {
		if(x==null) return false;
		if(x->data.value==value) return true;
		if(findvalue(x->L,value)) return true;
		if(findvalue(x->R,value)) return true;
		return false;
	}

public:
    class Iterator
    {
	private:
		node *p,*null;
		bool flag;

    public:
        bool hasNext()
        {
			if(p==null||p==NULL) return false;
			if(p->R!=null||!flag) return true;
			node *q=p,*x=q->F;
			while(x!=null)
			{
				if(x->L==q) return true;
				else q=x,x=q->F;
			}
			return false;
		}

        const Entry& next()
        {
			if(p==NULL||p==null) throw ElementNotExist();
			if(!flag)
			{
				flag=true;
				return p->data;
			}
			if(p->R!=null)
			{
				p=p->R;
				while(p->L!=null) p=p->L;
				return p->data;
			}
			node *q=p,*x=q->F;
			while(x!=null)
			{
				if(x->L==q) return (p=x)->data;
				else q=x,x=q->F;
			}
			throw ElementNotExist();
		}

		Iterator(node *p=NULL,node *null=NULL):p(p),null(null),flag(false) {}
    };


    TreeMap()
    {
		null=new node();
		null->F=null->L=null->R=null;
		root=null;
	}

    TreeMap(const TreeMap &c)
    {
		null=new node();
		null->F=null->L=null->R=null;
		root=null;
		typename TreeMap<K,V>::Iterator it=c.iterator();
		while(it.hasNext())
		{
			Entry d=it.next();
			put(d.key,d.value);
		}
	}

    ~TreeMap()
     {
		clear();
		delete null;
	}

    TreeMap& operator=(const TreeMap &c)
    {
		clear();
		typename TreeMap<K,V>::Iterator it=c.iterator();
		while(it->hasNext())
        {
			Entry d=it->next();
			put(d.key,d.value);
		}
	}

    template <class C> TreeMap(const C& c)
    {
		null=new node();
		null->F=null->L=null->R=null;
		root=null;
		typename C::Iterator it=c.iterator();
		while(it->hasNext())
        {
			Entry d=it->next();
			put(d.key,d.value);
		}
	}

    Iterator iterator() const
    {
		node *p=root;
		while(p->L!=null) p=p->L;
		return Iterator(p,null);
	}

    void clear()
    {
		root=eraseall(root);
	}

    bool containsKey(const K& key) const
    {
		return findkey(key)!=null;
	}

    bool containsValue(const V& value) const
    {
		return findvalue(root,value);
	}

    const V& get(const K& key) const
    {
		node *x=findkey(key);
		if(x==null) throw ElementNotExist();
		return x->data.value;
	}

    void put(const K& key,const V& value)
    {
		Entry p(key,value);
		root=insert(root,p);
	}

    void remove(const K& key)
    {
		int pre=root->_size;
		root=erase(root,key);
		if(pre==root->_size) throw ElementNotExist();
	}

    int size() const
    {
        return root->_size;
    }

	bool isEmpty() const 
	{
		return root==null; 
	}
};

#endif

