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
			emptyNode->father=emptyNode->left=emptyNode->right=NULL;
			root=emptyNode;
			}


	
	};

#endif
