#ifndef __TREEMAP_H
#define __TREEMAP_H

#include "ElementNotExist.h"
#include "Entry.h"

/*
 * TreeMap is the balanced-tree implementation of map. 
 * The iterators must iterate through the map in the natural order (operator<) of the key. 
 */

template <class K,class V>
class TreeMap
	{
	private:
		struct Node
			{
			Node *left,*right,*father;
			Entry<K,V> data;
			int nowSize;
			Node():data(K(),V()) {nowSize=0;}
			Node(const Entry<K,V> &data):data(data) {nowSize=0;}
			};

		Node *root,*none;
		
		Node *leftRotate(Node *n)
			{
			Node *tmp=n->right,*f=n->father;
			if(f!=none)
				{
				if(n==f->left) f->left=tmp;
				else f->right=tmp;
				}
			tmp->father=f;
			n->right=tmp->right;
			if(n->right!=none) n->right->father=n;
			tmp->left=n;
			n->father=tmp;
			if(n==none) n->nowSize=0;
			else n->nowSize=n->left->nowSize+n->right->size+1;
			if(tmp==none) tmp->nowSize=0;
			else tmp->nowSize=tmp->left->nowSize+tmp->right->nowSize+1;
			return tmp;
			}

		Node *rightRotate(Node *n)
			{
			Node *tmp=n->left,*f=n->father;
			if(f!=none)
				{
				if(n==f->left) f->left=tmp;
				else f->right=tmp;
				}
			tmp->father=f;
			n->left=tmp->right;
			if(n->left!=none) n->left->father=n;
			tmp->right=n;
			n->father=tmp;
			if(n==none) n->nowSize=0;
			else n->nowSize=n->left->nowSize+n->right->nowSize+1;
			if(tmp==0) tmp->nowSize=0;
			else tmp->nowSize=tmp->left->nowSize+tmp->right->nowSize+1;
			return tmp;
			}
		
		Node* insert(Node *n,Entry<K,V> &element)
			{
			if(n==none)
				{
				n=new Node(element);
				n->father=n->left=n->right=none;
				n->nowSize=1;
				element.value=V();
				}
			else if(element.key<n->data.key)
				{
				n->left=insert(n->left,element);
				n->left->father=n;
				if(n->left->left->nowSize>n->right->nowSize) n=rightRotate(n);
				}
			else if(element.key>n->data.key)
				{
				n->right=insert(n->right,element);
				n->right->father=n;
				if(n->right->right->nowSize>n->left->nowSize) n=leftRotate(n);
				}
			else if(element.key==n->data->key)
				{
				V tmp=element.value;
				element.value=n->data.value;
				n->data.value=tmp;
				}
			if(n==none) n->nowSize=0;
			else n->nowSIze=n->left->nowSIze+n->right->nowSize+1;
			return n;
			}

		Node *erase(Node *n,const K &key,V &value)
			{
			}

		Node *allErase(Node *n)
			{
			}

		Node *find(const K &key) const
			{
			Node *tmp=root;
			while(tmp!=none)
				{
				if(tmp->data.key==key) return tmp;
				else if(key<tmp->data.key) tmp=tmp->left;
				else if(key>tmp->data.key) tmp=tmp->right;
				}
			return tmp;
			}

		bool findValue(Node *n,const V &value) const
			{
			if(n==none) return false;
			if(n->data.value==value) return true;
			if(findValue(n->left,value)) return true;
			if(findValue(n->right,value)) return true;
			return false;
			}

	public:
		class Iterator
			{
			private:
				Node *pos,*none;
				bool visited;
				TreeMap<K,V> *list;
	
			public:
				Iterator(Node *pos=NULL,Node *none=NULL,TreeMap<K,V> *list=NULL)
					:pos(pos),none(none),list(list) {visited=false;}

				bool hasNext()
					{
					if(pos==none||pos==NULL) return false;
					if(pos->right!=NULL||visited==false) return true;
					Node *tmp=pos,*f=tmp->father;
					while(f!=NULL)
						{
						if(f->left==pos) return true;
						else tmp=f,f=tmp->father;
						}
					}

				Entry<K,V>& next()
					{
					if(pos==none||pos==NULL) throw ElementNotExist();
					if(visited==false)
						{
						visited=true;
						return pos->data;
						}
					if(pos->right!=none)
						{
						while(pos->right!=none) pos=pos->right;
						return pos->data;
						}
					Node *tmp=pos,*f=pos->father;
					while(tmp!=none)
						{
						if(f->left==tmp)
							{
							pos=tmp;
							return pos->data;
							}
						else tmp=f,f=f->father;
						}
					throw ElementNotExist();
					}

				void remove()
					{
					}
			};
		
		/*
		 * Constructs an empty tree map. 
		 */
		TreeMap()
			{
			none=new Node();
			none->father=none->left=none->right=none;
			root=none;
			}
		
		/*
		 * Copy-constructor
		 */
		TreeMap(const TreeMap &t)
			{
			}
		
		/*
		 * Destructor
		 */
		~TreeMap()
			{
			}
		
		/*
		 * Assignment operator 
		 */
		
		/*
		 * Returns an iterator over the elements in this map. 
		 */
		Iterator iterator()
			{
			Node *tmp=root;
			while(tmp->left!=none) tmp=tmp->left;
			return Iterator(tmp,none,this);
			}
		
		/*
		 * Removes all of the mappings from this map. 
		 */
		void clear()
			{
			}
		
		/*
		 * Returns true if this map contains a mapping for the specified key. 
		 */
		bool containsKey(const K &key) const
			{
			return find(key)!=none;
			}
		
		/*
		 * Returns true if this map maps one or more keys to the specified value. 
		 */
		bool containsValue(const V &value) const
			{
			return findValue(root,value);
			}
		
		const Entry<K,V>& firstEntry() const
			{
			if(root==none) throw ElementNotExist();
			Node *tmp=root;
			while(tmp!=none) tmp=tmp->left;
			return tmp->data;
			}

		const K& firstKey() const
			{
			return firstEntry().key;
			}
		
		/*
		 * Returns a const reference to the value to which the specified key is mapped.
		 * If the key is not present in this map, this function should throw ElementNotExist exception. 
		 */
		const V& get(const K &key)
			{
			Node *tmp=find(key);
			if(tmp==none) throw ElementNotExist();
			return tmp->data.value;
			}

		const Entry<K,V>& lastEntry() const
			{
			Node *tmp=root;
			while(tmp->right!=none) tmp=tmp->right;
			return tmp->data;
			}

		const K& lastKey() const
			{
			return lastEntry().key;
			}
		
		/*
		 * Associates the specified value with the specified key in this map. 
		 */
		void put(const K &key,const V &value)
			{
			Entry<K,V> tmp(key,value);
			root=insert(root,tmp);
			}
		
		/*
		 * Removes the mapping for the specified key from this map if present.
		 * If there is no mapping for the specified key, throws ElementNotExist exception. 
		 */
		void remove(const K &key)
			{
			}

		/*
		 * Returns the number of key-value mappings in this map. 
		 */
		int size() const {return root->nowSize;}
		
		/*
		 * Returns true if this map contains no key-value mappings. 
		 */
		bool isEmpty() const {return root==none;}
	};



#endif
