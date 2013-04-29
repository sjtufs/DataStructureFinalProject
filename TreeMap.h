#ifndef __TREEMAP_H
#define __TREEMAP_H

#include "Utility.h"

/*
 * TreeMap is the balanced-tree implementation of map.
 * The iterators must iterate the map in the natural order(operator<) of the key
 */

template<class K,class V>
class TreeMap
	{
	private:
		struct Node
			{
			Node *left,*right,*father;
			Entry<K,V> data;
			int nowSize,nowHeight;

			Node():data(K(),V()) {nowSize=nowHeight=0;}
			Node(const Entry<K,V> &data):data(data) {nowSize=nowHeight=0;}
			
			/*
			 * Update the size and height of the subtree
			 */
			void update(Node *t)
				{
				if(t==emptyNode) t->nowSize=t->nowHeight=0;
				else t->nowSize=t->left->nowSize+t->right->nowSize+1,
					 t->nowHeight=max(t->left->nowHeight,t->right->nowHeight)+1;
				}
			
			/*
			 * left-rotate for avl-tree / rb-tree / splay
			 */
			Node* leftRotate(Node *t)
				{
				Node *f=t->father;
				Node *tmp=t->right;
				if(f!=emptyNode)
					{
					if(t==f->left) f->left=tmp;
					else f->right=tmp;
					}
				tmp->father=f;
				t->right=tmp->left;
				if(t->right!=emptyNode) t->right->father=t;
				tmp->left=t;
				t->father=tmp;
				update(t);
				update(tmp);
				}

			/*
			 * right-rotate for avl-tree / rb-tree / splay
			 */
			Node* righRotate(Node *t)
				{
				Node *f=t->father;
				Node *tmp=t->left;
				if(f!=emptyNode)
					{
					if(t==f->left) f->left=tmp;
					else f->right=tmp;
					}
				tmp->father=f;
				t->left=tmp->right;
				if(t->left!=emptyNode) t->left->father=t;
				tmp->right=t;
				t->father=tmp;
				update(t);
				update(tmp);
				}
			
			/*
			 * Returns the pointer of the Node with specified key.
			 */
			Node* findKey(const K &key) const
				{
				Node *t=root;
				while(t!=emptyNode)
					{
					if(t->data.key==key) return t;
					if(key<t->data.key) t=t->left;
					if(key>t->data.key) t=t->right;
					}
				}

			/*
			 * Returns the pointer of ther Node with spcified value.
			 */
			Node* findValue(Node *t,const V &value) const
				{
				if(t==emptyNode) return false;
				if(value==t->data.value) return true;
				if(findValue(t->left,value)) return true;
				if(findValue(t->right,value)) return true;
				return false;
				}
			
			/*
			 * Deletes the Node with a specified key.
			 */
			Node* erase(Node *t,const K &key)
				{
				}

			/*
			 * Deletes all Nodes in the subtree
			 */
			Node* removeAll(Node *t)
				{
				if(t==emptyNode) return emptyNode;
				t->left=removeAll(t->left);
				t->right=removeAll(t->right);
				delete t;
				return emptyNode;
				}
			};

		Node *root,*emptyNode;

	public:
		class Iterator
			{
			private:
				TreeMap<K,V> *t;
				Node *pos,*emptyNode;
				bool visited;
			
			public:
				Iterator(Node *pos=NULL,Node *emptyNode=NULL,TreeMap<K,V> *t=NULL)
					:pos(pos),emptyNode(emptyNode),t(t) {visited=false;}
				/*
				 * Returns true if the iteration has more elements.
				 */
				bool hasNext()
					{
					if(pos==NULL||pos==emptyNode) return false;
					if(pos->right!=emptyNode||visited==false) return true;
					else
						{
						Node *tmp=pos,*f=pos->father;
						while(f!=emptyNode)
							{
							if(tmp==f->left) return true;
							else tmp=f,f=f->father;
							}
						}
					return false;
					}

				/*
				 * Returns the next element in the iteration.
				 * Exceptions : ElementNotExist	exception when hasNext() == false
				 */
				const Entry<K,V>& next()
					{
					if(pos==NULL||pos==emptyNode) throw ElementNotExist();
					if(visited==false)
						{
						visited=true;
						return pos->data;
						}
					if(pos->right!=emptyNode)
						{
						pos=pos->right;
						while(pos->right!=emptyNode) pos=pos->left;
						return pos->data;
						}
					else
						{
						Node *tmp=pos,*f=pos->father;
						while(f!=emptyNode)
							{
							if(tmp==f->left)
								{
								pos=f;
								return pos->data;
								}
							else tmp=f,f=f->father;
							}
						}
					throw ElementNotExist();
					}
			};

		class constIterator
			{
			private:
				Node *pos,*emptyNode;
				bool visited;
			
			public:
				constIterator(Node *pos=NULL,Node *emptyNode=NULL)
					:pos(pos),emptyNode(emptyNode) {visited=false;}
				/*
				 * Returns true if the iteration has more elements.
				 */
				bool hasNext()
					{
					if(pos==NULL||pos==emptyNode) return false;
					if(pos->right!=emptyNode||visited==false) return true;
					else
						{
						Node *tmp=pos,*f=pos->father;
						while(f!=emptyNode)
							{
							if(tmp==f->left) return true;
							else tmp=f,f=f->father;
							}
						}
					return false;
					}

				/*
				 * Returns the next element in the iteration.
				 * Exceptions : ElementNotExist	exception when hasNext() == false
				 */
				const Entry<K,V>& next()
					{
					if(pos==NULL||pos==emptyNode) throw ElementNotExist();
					if(visited==false)
						{
						visited=true;
						return pos->data;
						}
					if(pos->right!=emptyNode)
						{
						pos=pos->right;
						while(pos->right!=emptyNode) pos=pos->left;
						return pos->data;
						}
					else
						{
						Node *tmp=pos,*f=pos->father;
						while(f!=emptyNode)
							{
							if(tmp==f->left)
								{
								pos=f;
								return pos->data;
								}
							else tmp=f,f=f->father;
							}
						}
					throw ElementNotExist();
					}
			};
		/*
		 * Constructs an empty map
		 */
		TreeMap()
			{
			emptyNode=new Node();
			root=emptyNode->father=emptyNode->left=emptyNode->right=emptyNode;
			}
		
		/*
		 * Destructor
		 */
		~TreeMap()
			{
			clear();
			delete emptyNode;
			}

		/*
		 * Assignment operator
		 */
		TreeMap& operator=(const TreeMap &x)
			{
			clear();
			typename TreeMap<K,V>::constIterator tmp=x.constIterator();
			while(tmp->hasNext())
				{
				Entry<K,V> element=tmp.next();
				put(element.key,element.value);
				}
			}
		
		/*
		 * Copy-constructor
		 */
		TreeMap(const TreeMap &x)
			{
			emptyNode=new Node();
			root=emptyNode->father=emptyNode->left=emptyNode->right=emptyNode;
			typename TreeMap<K,V>::constIterator tmp=x.ConstIterator();
			while(tmp->hasNext())
				{
				Entry<K,V> element=tmp->next();
				put(element.key,element.value);
				}
			}
			
		/*
		 * Returns an iterator over the elements in this map. 
		 */
		Iterator iterator() const
			{
			Node *tmp=root;
			while(tmp->left!=emptyNode) tmp=tmp->left;
			return Iterator(tmp,emptyNode,this);
			}
		
		/*
		 * Returns a const iterator over the elements in this map. 
		 */
		constIterator ConstIterator() const
			{
			Node *tmp=root;
			while(tmp->left!=emptyNode) tmp=tmp->left;
			return constIterator(tmp,emptyNode);
			}
		
		/*
		 * Removes all of the mappings from this map. 
		 */
		void clear()
			{
			root=removeAll(root);
			delete emptyNode;
			}
		
		/*
		 * Returns true if this map contains a mapping for the specified key. 
		 */
		bool containsKey(const K &key) const
			{
			return findKey(key)!=emptyNode;
			}

		/*
		 * Returns true if this map maps one or more keys to the specified value. 
		 */
		bool containsValue(const V &value) const
			{
			return findValue(value);
			}
		
		/*
		 * Returns a const reference to the value to which the specified key is mapped. 
		 * If the key is not present in this map, this function should throw ElementNotExist exception.
		 * Exceptions : ElementNotExist	
		 */
		const V &get(const K &key) const
			{
			Node *tmp=findKey(key);
			if(tmp==emptyNode) throw ElementNotExist();
			return tmp->data.value;
			}
		
		/*
		 * Returns true if this map contains no key-value mappings. 
		 */
		bool isEmpty() const
			{
			return root==emptyNode;
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
		 *Exceptions : ElementNotExist	
		 */
		void remove(const K &key)
			{
			int oldSize=root->nowSize;
			root=erase(root,key);
			if(root->nowSize==oldSize) throw ElementNotExist();
			}

		/*
		 * Returns the number of key-value mappings in this map. 
		 */
		int size() const
			{
			return root->nowSize;
			}
	};

#endif
