#ifndef __TREEMAP_H
#define __TREEMAP_H

#include "Utility.h"

/**
 * A map is a sequence of (key,value) entries that provides fast retrieval
 * based on the key. At most one value is held foreach key.
 *
 * TreeMap is the balanced-tree implementation of map. The iterators must
 * iterate through the map in the natural order (operator<) of the key.
 */
template<class K,class V>
class TreeMap
    {
    private:
        struct Node
            {
            Node *left,*right,*father;
            Entry<K,V> data;
            int nowSize;
            Node ():data(K(),V()) {nowSize=0;}
            Node(const Entry<K,V>& data):data(data) {nowSize=0;}
            };

        Node *root,*emptyNode;

        void updateNode(Node *n)
            {
            if(n==emptyNode) n->nowSize=0;
            else n->nowSize=n->left->nowSize + n->right->nowSize + 1;
            }

        Node* leftRotate(Node *n)
            {
            Node *father=n->father;
            Node *tmp=n->right;
            if(father!=emptyNode)
                {
                if(father->left==n) father->left=tmp;
                else father->right=tmp;
                }
            tmp->father=father;
            n->right=tmp->left;
            if(n->right!=emptyNode) n->right->father=n;
            tmp->left=n;
            n->father=tmp;
            updateNode(n);
            updateNode(tmp);
            return tmp;
            }

        Node* rightRotate(Node *n)
            {
            Node *father=n->father;
            Node *tmp=n->left;
            if(father!=emptyNode)
                {
                if(father->left==n) father->left=tmp;
                else father->right=tmp;
                }
            tmp->father=father;
            n->left=tmp->right;
            if(n->left!=emptyNode) n->left->father=n;
            tmp->right=n;
            n->father=tmp;
            updateNode(n);updateNode(tmp);
            return tmp;
            }

        Node* insert(Node *n,Entry<K,V> &data)
            {
            if(n==emptyNode)
                {
                n=new Node(data);
                n->left=n->right=n->father=emptyNode;
                n->nowSize=1;
                }
            else if(data.key < n->data.key)
                {
                n->left=insert(n->left,data);
                n->left->father=n;
                if(n->left->left->nowSize>n->right->nowSize) n=rightRotate(n);
                }
            else if(data.key>n->data.key)
                {
                n->right=insert(n->right,data);
                n->right->father=n;
                if(n->right->right->nowSize>n->left->nowSize) n=leftRotate(n);
                }
            else if(data.key==n->data.key)
                {
                V tmp=data.value;
                data.value=n->data.value;
                n->data.value=tmp;
                }
            updateNode(n);
            return n;
            }

        Node* erase(Node *n,const K &key,V &value)
            {
            if(n==emptyNode) return emptyNode;
            if(key < n->data.key) n->left=erase(n->left,key,value);
            else if(key>n->data.key) n->right=erase(n->right,key,value);
            else if(n->left==emptyNode && n->right==emptyNode)
                {
                value=n->data.value;
                delete n;
                n=emptyNode;
                }
            else
                {
                if(n->left->nowSize < n->right->nowSize) n=leftRotate(n);
                else n=rightRotate(n);
                n=erase(n,key,value);
                }
            updateNode(n);
            return n;
            }

        Node* eraseAll(Node *n)
            {
            if(n==emptyNode) return emptyNode;
            n->left=eraseAll(n->left);
            n->right=eraseAll(n->right);
            delete n;
            return emptyNode;
            }

        Node* find(const K &key) const
            {
            Node *n=root;
            while (n!=emptyNode)
                {
                if(n->data.key==key) return n;
                else if(key < n->data.key) n=n->left;
                else n=n->right;
                }
            return n;
            }

        bool findvalue(Node *n,const V &value) const
            {
            if(n==emptyNode) return false;
            if(n->data.value==value) return true;
            if(findvalue(n->left,value)) return true;
            if(findvalue(n->right,value)) return true;
            return false;
            }

    public:
        class ConstIterator
            {
            private:
                Node *p,*emptyNode;
                bool visited;
            public:
                /**
                 * Returns true if the iteration has more elements.
                 * Amortized O(1).
                 */
                bool hasNext()
                    {
                    if(p==emptyNode||p==NULL) return false;
                    if(p->right!=emptyNode||visited==false) return true;
                    Node *q=p,*x=q->father;
                    while (x!=emptyNode)
                        {
                        if(x->left==q) return true;
                        else q=x,x=q->father;
                        }
                    return false;
                    }

                /**
                 * Returns a const reference to the next element in the iteration.
                 * Amortized O(1).
                 * @throw ElementNotExist
                 */
                const Entry<K,V>& next()
                    {
                    if(p==NULL||p==emptyNode) throw ElementNotExist();
                    if(visited==false)
                        {
                        visited=true;
                        return p->data;
                        }
                    if(p->right!=emptyNode)
                        {
                        p=p->right;
                        while (p->left!=emptyNode) p=p->left;
                        return p->data;
                        }
                    Node *q=p,*x=q->father;
                    while (x!=emptyNode)
                        {
                        if(x->left==q) return (p=x)->data;
                        else q=x,x=q->father;
                        }
                    throw ElementNotExist();
                    }

                ConstIterator(Node *p=NULL,Node *emptyNode=NULL)
                    : p(p),emptyNode(emptyNode) {visited=false;}
            };

        class Iterator
            {
            private:
                Node *p,*emptyNode;
                bool visited;
                TreeMap<K,V> *s;
            public:
                /**
                 * Returns true if the iteration has more elements.
                 */
                bool hasNext()
                    {
                    if(p==emptyNode||p==NULL) return false;
                    if(p->right!=emptyNode||visited==false) return true;
                    Node *q=p,*x=q->father;
                    while (x!=emptyNode)
                        {
                        if(x->left==q) return true;
                        else q=x,x=q->father;
                        }
                    return false;
                    }

                /**
                 * Returns the next element in the iteration.
                 * @throw ElementNotExist exception when hasNext()==false
                 */
                const Entry<K,V>& next()
                    {
                    if(p==emptyNode||p==NULL) throw ElementNotExist();
                    if(visited==false)
                        {
                        visited=true;
                        return p->data;
                        }
                    if(p->right!=emptyNode)
                        {
                        p=p->right;
                        while (p->left!=emptyNode) p=p->left;
                        return p->data;
                        }
                    Node *q=p,*x=q->father;
                    while (x!=emptyNode)
                        {
                        if(x->left==q) return (p=x)->data;
                        else q=x,x=q->father;
                        }
                    throw ElementNotExist();
                }

                /**
                 * Removes from the underlying collection the last element returned by the iterator
                 * @throw ElementNotExist
                 */
                void remove()
                    {
                    if(p==emptyNode||p==NULL) throw ElementNotExist();
                    if(!s->containsKey(p->data->key)) throw ElementNotExist();
                    s->remove(p->key);
                    p=emptyNode;
                    }

                Iterator(Node *p=NULL,Node *emptyNode=NULL,TreeMap<K,V> *s=NULL)
                    : p(p),emptyNode(emptyNode),s(s) {visited=false;}
            };

        /**
         * Constructs an empty map
         */
        TreeMap()
            {
            emptyNode=new Node();
            emptyNode->father=emptyNode->left=emptyNode->right=emptyNode;
            root=emptyNode;
            }

		/**
         * Destructor
         */
        ~TreeMap()
            {
            clear();
            delete emptyNode;
            }

		/**
         * Assignment operator
         */
        TreeMap& operator=(const TreeMap &m)
            {
            clear();
            typename TreeMap<K,V>::ConstIterator it=m.constIterator();
            while (it->hasNext())
                {
                Entry<K,V> tmp=it->next();
                put(tmp.key,tmp.value);
                }
            }

		/**
         * Copy-constructor
         */
        TreeMap(const TreeMap &c)
            {
            emptyNode=new Node();
            emptyNode->father=emptyNode->left=emptyNode->right=emptyNode;
            root=emptyNode;
            typename TreeMap<K,V>::ConstIterator it=c.constIterator();
            while (it->hasNext())
                {
                Entry<K,V> d=it->next();
                put(d.key,d.value);
                }
            }

		/**
         * Returns an iterator over the elements in this map.
         */
        Iterator iterator() const
            {
            Node *n=root;
            while (n->left!=emptyNode) n=n->left;
            return Iterator(n,emptyNode,this);
            }

		/**
         * Removes all of the mappings from this map.
         */
        void clear()
            {
            root=eraseAll(root);
            }

		/**
         * Returns true if this map contains a mapping forthe specified key.
         */
        bool containsKey(const K &key) const
            {
            return find(key)!=emptyNode;
            }

        /**
         * Returns true if this map contains a mapping forthe specified value.
         */
        bool containsValue(const V &value) const
            {
            return findvalue(root,value);
            }

		/**
		 * TODO Returns a const reference to the value to which the specified key is mapped.
		 * If the key is not present in this map, this function should throw ElementNotExist exception.
		 * @throw ElementNotExist
		 */
        const V& get(const K &key) const
            {
            Node *n=find(key);
            if(n==emptyNode) throw ElementNotExist();
            return n->data.value;
            }

		/**
		 * Returns true if this map contains no key-value mappings.
		 */
		bool isEmpty() const {return root==emptyNode;}

		/**
         * Associates the specified value with the specified key in this map.
         */
        void put(const K &key,const V &value)
            {
            Entry<K,V> tmp(key,value);
            root=insert(root,tmp);
            }

		/**
		 * Removes the mapping forthe specified key from this map ifpresent.
		 * If there is no mapping forthe specified key, throws ElementNotExist exception.
		 * @throw ElementNotExist
		 */
        void remove(const K &key)
            {
            V r;
            int pre=root->nowSize;
            root=erase(root,key,r);
            if(pre==root->nowSize) throw ElementNotExist();
            }

		/**
         * Returns the number of key-value mappings in this map.
         */
        int size() const {return root->nowSize;}
    };

#endif

