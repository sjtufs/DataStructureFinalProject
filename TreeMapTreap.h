
/** @file */
#ifndef __TREEMAP_H
#define __TREEMAP_H

#include "Utility.h"
#include<stdlib.h>
#include<time.h>

/**
 * A map is a sequence of (key, value) entries that provides fast retrieval
 * based on the key. At most one value is held for each key.
 *
 * TreeMap is the balanced-tree implementation of map. The iterators must
 * iterate through the map in the natural order (operator<) of the key.
 */
template<class K, class V> class TreeMap {
private:
	static const int maxn=1000000000;
	struct Node {
		Node *left,*right;
		Entry<K,V>data;
		int aux;
		Node():data(K(),V())
			{
			srand(time(NULL));
			aux=rand()%maxn;
			left=right=NULL;
			}

		Node(const Entry<K, V>& data):data(data)
			{
			srand(time(NULL));
			aux=rand()%maxn;
			left=right=NULL;
			}

		Node(const K &k,const V &v):data(k,v)
			{
			srand(time(NULL));
			aux=rand()%maxn;
			left=right=NULL;
			}
	};

	Node *root;
	int nowSize;

	void lRotate(Node *&x)
		{
		Node *y=x->right;
		x->right=y->left;
		y->left=x;
		x=y;
		}

	void rRotate(Node *&x)
		{
		Node *y=x->left;
		x->left=y->right;
		y->right=x;
		x=y;
		}
	
	void insert(Node *&n,const Entry<K,V> &e)
		{
		if(n==NULL)
			{
			n=new Node(e);
			nowSize++;
			return;
			}
		if(e.key<n->data.key)
			{
			insert(n->left,e);
			if(n->left->aux<n->aux) rRotate(n);
			}
		else
			{
			insert(n->right,e);
			if(n->right->aux<n->aux) lRotate(n);
			}
		}

	void erase(Node *&n,const K &key)
		{
		if(n==NULL) return;
		if(key<n->data.key) erase(n->left,key);
		else if(key>n->data.key) erase(n->right,key);
		else if(key==n->data.key)
			{
			if(n->left==NULL||n->right==NULL)
				{
				if(n->left==NULL)
					{
					nowSize--;
					Node *tmp=n;
					n=n->right;
					delete tmp;
					}
				else
					{
					nowSize--;
					Node *tmp=n;
					n=n->left;
					delete tmp;
					}
				}
			else
				{
				if(n->left->aux<n->right->aux)
					{
					rRotate(n);
					erase(n->left,key);
					}
				else
					{
					lRotate(n);
					erase(n->right,key);
					}
				}
			}
		}

	void eraseAll(Node *n) 
		{
		if(n==NULL) return;
		eraseAll(n->left);
		eraseAll(n->right);
		delete n;
		}
	
	Node *findKey(const K &key) const
		{
		Node *n=root;
		while(n!=NULL)
			{
			if(n->data.key==key) return n;
			if(n->data.key>key) n=n->left;
			if(n->data.key<key) n=n->right;
			}
		return n;
		}

	bool findValue(Node *n, const V &value) const
		{
		if(n==NULL) return false;
		if(n->data.value==value) return true;
		if(findValue(n->left,value)) return true;
		if(findValue(n->right,value)) return true;
		return false;
		}

public:
    class Iterator
		{
		private:
			const TreeMap<K,V> *host;
			Node *pos;
			bool visited;
	    public:
			Iterator(Node *pos=NULL,TreeMap<K,V> *host=NULL):pos(pos),host(host)
				{
				visited=false;
				}
		    /**
			 * Returns true if the iteration has more elements.
			*/
			
			bool hasNext()
				{
				if(visited==false) return true;
				if(pos->data.key<host->lastKey()) return true;
				return false;
				}

			/**
			* Returns a const reference to the next element in the iteration.
			* @throw ElementNotExist
			*/
		
			const Entry<K,V>& next()
				{
				if(!hasNext()) throw ElementNotExist();
				if(visited==false)
					{
					visited=true;
					return pos->data;
					}
				Node *n=host->getRoot();
				Node *tmp=n;
				while(n->data.key!=pos->data.key)
					{
					tmp=n;
					if(pos->data.key<n->data.key) n=n->left;
					else n=n->right;
					}
				if(n->right!=NULL)
					{
					n=n->right;
					while(n->left!=NULL) n=n->left;
					}
				if(pos->data.key!=n->data.key) tmp=n;
				pos=tmp;
				return tmp->data;
				}

		void remove()
			{
			if(pos==NULL) throw ElementNotExist();
			if(!host->containsKey(pos->data.key)) throw ElementNotExist();
			Node *n=host->getRoot();
			Node *tmp=n;
			while(n->data.key!=pos->data.key)
				{
				tmp=n;
				if(pos->data.key<n->data.key) n=n->left;
				else n=n->right;
				}
			if(n->left!=NULL)
				{
				n=n->left;
				while(n->right!=NULL) n=n->right();
				}
			if(n->data.key<pos->data.key) tmp=n;
			K tmpk=pos->data.key;
			pos=tmp;
			host->remove(tmpk);
			}
		};

	class constIterator
		{
		private:
			const TreeMap<K,V> *host;
			Node *pos;
			bool visited;
	    public:
			constIterator(Node *pos=NULL,TreeMap<K,V> *host=NULL):pos(pos),host(host)
				{
				visited=false;
				}
		    /**
			 * Returns true if the iteration has more elements.
			*/
			
			bool hasNext()
				{
				if(visited==false) return true;
				if(pos->data.key<host->lastKey()) return true;
				return false;
				}

			/**
			* Returns a const reference to the next element in the iteration.
			* @throw ElementNotExist
			*/
		
			const Entry<K,V>& next()
				{
				if(!hasNext()) throw ElementNotExist();
				if(visited==false)
					{
					visited=true;
					return pos->data;
					}
				Node *n=host->getRoot();
				Node *tmp=n;
				while(n->data.key!=pos->data.key)
					{
					tmp=n;
					if(pos->data.key<n->data.key) n=n->left;
					else n=n->right;
					}
				if(n->right!=NULL)
					{
					n=n->right;
					while(n->left!=NULL) n=n->left;
					}
				if(pos->data.key!=n->data.key) tmp=n;
				pos=tmp;
				return tmp->data;
				}
		};
        
    /**
     * Constructs an empty map
     */
    TreeMap()
		{
		root=NULL;
		nowSize=0;
		}

    /**
     * Copy constructor
     */
    TreeMap(const TreeMap &x)
		{
		root=NULL;
		nowSize=0;
		constIterator tmp=x.ConstIterator();
		while(tmp.hasNext()) put(tmp.next());
		}

    /**
     * Destructor
     */
    ~TreeMap()
		{
		clear();
		}

    /**
     * Assignment operator
     */
	
	TreeMap& operator=(const TreeMap &x)
		{
		clear();
		constIterator tmp=x.ConstIterator();
		while(tmp.hasNext()) put(tmp.next());
		return *this;
		}

    /**
     * Constructs a new tree map containing the same mappings as the
     * given map
     */
	template <class C> TreeMap(const C &c)
		{
		typename C::constIterator tmp=c.ConstIterator();
		while(tmp.hasNext()) put(tmp.next());
		}
    /**
     * Returns an iterator over the elements in this map.
     * O(1).
     */

	Iterator iterator()
		{
		Node *n=root;
		while(n->left!=NULL) n=n->left;
		return Iterator(n,this);
		}

    /**
     * Returns an const iterator over the elements in this map.
     * O(1).
     */
    constIterator ConstIterator() const 
		{
		Node *n=root;
		while(n->left!=NULL) n=n->left;
		return constIterator(n,this);
	}

    /**
     * Removes all of the mappings from this map.
     * O(n).
     */
    void clear() 
		{
		eraseAll(root);
		}

    /**
     * Returns true if this map contains a mapping for the specified key.
     * O(logn).
     */
    bool containsKey(const K& key) const 
		{
		return findKey(key)!=NULL;
		}

    /**
     * Returns true if this map contains a mapping for the specified value.
     * O(n).
     */
    bool containsValue(const V& value) const 
		{
			return findvalue(root, value);
		}

    /**
     * Returns a key-value mapping associated with the least key in
     * this map.
     * O(logn).
     * @throw ElementNotExist
     */
	const Entry<K,V>& firstEntry() const
		{
		if(root==NULL) throw ElementNotExist();
		Node *n=root;
		while(n->left!=NULL) n=n->left;
		return n->data;
		}

    /**
     * Returns the first (lowest) key currently in this map.
     * O(logn).
     * @throw ElementNotExist
     */
    const K& firstKey() const 
		{
		return firstEntry().key;
		}

    /**
     * Returns a reference to the value which the specified key is mapped
     * O(logn).
     * @throw ElementNotExist
     */
    V& get(const K &key)
		{
		Node *n=findKey(key);
		if (n==NULL) throw ElementNotExist();
		return n->data.value;
		}

    /**
     * Returns a key-value mapping associated with the greatest key
     * in this map.
     * O(logn).
     * @throw ElementNotExist
     */
	const Entry<K,V>& lastEntry() const
		{
		Node *n=root;
		while(n->right!=NULL) n=n->right;
		return n->data;
		}

    /**
     * Returns the last (highest) key currently in this map.
     * O(logn).
     * @throw ElementNotExist
     */
    const K& lastKey() const 
		{
		return lastEntry().key;
		}

    /**
     * Associates the specified value with the specified key in this map.
     * Returns the previous value, if not exist, a value returned by the
     * default-constructor.
     * O(logn).
     */
    V put(const K& key, const V& value) {
		/*Node *cur = find(key);
		if (cur != null) {
			V ret = cur->data.value;
			cur->data.value = value;
			return ret;
		} else {*/
		Entry<K, V> p(key, value);
		insert(root, p);
		return p.value;
		/*}*/
	}

    /**
     * Removes the mapping for this key from this TreeMap if present.
     * O(logn).
     * @throw ElementNotExist
     */
    V remove(const K& key) {
		V ret;
		int pre = nowSize;
		root = erase(root, key);
		if (pre == nowSize) throw ElementNotExist();
		return ret;
	}

    int size() const {return nowSize;}

	bool isEmpty() const {nowSize==0;}
};

#endif

