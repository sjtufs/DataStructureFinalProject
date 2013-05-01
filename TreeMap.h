/* @file */
#ifndef __TREEMAP_H
#define __TREEMAP_H

#include "Utility.h"
#include<stdlib.h>
#include<time.h>

/*
 * A map is a sequence of (key,value) entries that provides fast retrieval
 * based on the key. At most one value is held for each key.
 *
 * TreeMap is the balanced-tree implementation of map. The iterators must
 * iterate through the map in the natural order (operator<) of the key.
 */
template<class K,class V>
class TreeMap
    {
    private:
    static const int mod=1000000000;
        struct Node
            {
            Node *left,*right,*father;
            Entry<K,V> data;
            int nowSize,aux;
            Node():data(K(),V())
                {
                nowSize=0;
                srand(time(NULL));
                aux=rand()%mod;
                }
            Node(const Entry<K,V>& data):data(data)
                {
                nowSize=0;
                srand(time(NULL));
                aux=rand()%mod;
                }
            };

        Node *root,*emptyNode;

        void update(Node *n)
            {
            if(n==emptyNode) n->nowSize=0;
            else n->nowSize=n->left->nowSize+n->right->nowSize+1;
            }

        Node* leftrotate(Node *n)
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
            update(n);
            update(tmp);
            return tmp;
            }

        Node* rightrotate(Node *n)
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
            update(n);
            update(tmp);
            return tmp;
            }

        Node* insert(Node *n,Entry<K,V> &e)
            {
            if(n==emptyNode) {
                n=new Node(e);
                n->left=n->right=n->father=emptyNode;
                n->nowSize=1;
                n->aux=rand()%mod;
                e.value=V();
            }
            else if(e.key<n->data.key)
                {
                n->left=insert(n->left,e);
                n->left->father=n;
				if(n->left->left->aux>n->aux) n=rightrotate(n);
                }
            else if(e.key>n->data.key)
                {
                n->right=insert(n->right,e);
                n->right->father=n;
				if(n->right->right->aux>n->aux) n=leftrotate(n);
                }
            else if(e.key==n->data.key)
                {
                V tmp=e.value;
                e.value=n->data.value;
                n->data.value=tmp;
                }
		update(n);
		return n;
        }

        Node* erase(Node *n,const K &key,V &value)
            {
            if(n==emptyNode) return emptyNode;
            if(key<n->data.key)
                n->left=erase(n->left,key,value);
            else if(key>n->data.key)
                n->right=erase(n->right,key,value);
            else if(n->left==emptyNode&&n->right==emptyNode)
                {
                value=n->data.value;
                delete n;
                n=emptyNode;
                }
            else
                {
                if(n->left->aux<n->right->aux) n=leftrotate(n);
                else n=rightrotate(n);
                n=erase(n,key,value);
                }
            update(n);
            return n;
            }

        Node* removeAll(Node *n)
            {
            if(n==emptyNode) return emptyNode;
            n->left=removeAll(n->left);
            n->right=removeAll(n->right);
            delete n;
            return emptyNode;
            }

        Node* findKey(const K &key) const
            {
            Node *n=root;
            while (n!=emptyNode)
                {
                if(n->data.key==key) return n;
                else if(key<n->data.key) n=n->left;
                else n=n->right;
                }
            return n;
            }

	bool findValue(Node *n,const V &value) const
        {
		if(n==emptyNode) return false;
		if(n->data.value==value) return true;
		if(findValue(n->left,value)) return true;
		if(findValue(n->right,value)) return true;
		return false;
        }

    public:
        class constIterator
            {
            private:
                Node *pos,*emptyNode;
                bool visited;

            public:
                /*
                * Returns true ifthe iteration has more elements..
                */
                bool hasNext()
                    {
                    if(pos==emptyNode||pos==NULL) return false;
                    if(pos->right!=emptyNode||!visited) return true;
                    Node *q=pos,*f=q->father;
                    while (f!=emptyNode)
                        {
                        if(f->left==q) return true;
                        else q=f,f=q->father;
                        }
                    return false;
                    }

                /*
                 * Returns a const reference to the next element in the iteration.
                 * @throw ElementNotExist
                 */
                const Entry<K,V>& next()
                    {
                    if(pos==emptyNode||pos==NULL) throw ElementNotExist();
                    if(!visited)
                        {
                        visited=true;
                        return pos->data;
                    }
                    if(pos->right!=emptyNode)
                        {
                        pos=pos->right;
                        while (pos->left!=emptyNode) pos=pos->left;
                        return pos->data;
                        }
                    Node *q=pos,*f=q->father;
                    while (f!=emptyNode)
                        {
                        if(f->left==q) return (pos=f)->data;
                        else q=f,f=q->father;
                    }
                    throw ElementNotExist();
                    }

                constIterator(Node *pos=NULL,Node *emptyNode=NULL)
                    :pos(pos),emptyNode(emptyNode) {visited=false;}
            };

        class Iterator
            {
            private:
                Node *pos,*emptyNode;
                bool visited;
                TreeMap<K,V> *t;

            public:
                /*
                 * Returns true ifthe iteration has more elements.
                 */
                bool hasNext() {
                    if(pos==emptyNode||pos==NULL) return false;
                    if(pos->right!=emptyNode||!visited) return true;
                    Node *q=pos,*f=q->father;
                    while (f!=emptyNode) {
                        if(f->left==q) return true;
                        else q=f,f=q->father;
                    }
                    return false;
                }

                /*
                 * Returns a reference to the next element in the iteration.
                 * @throw ElementNotExist
                 */
                Entry<K,V>& next() {
                    if(pos==emptyNode||pos==NULL) throw ElementNotExist();
                    if(!visited) {
                        visited=true;
                        return pos->data;
                    }
                    if(pos->right!=emptyNode) {
                        pos=pos->right;
                        while (pos->left!=emptyNode) pos=pos->left;
                        return pos->data;
                    }
                    Node *q=pos,*f=q->father;
                    while (f!=emptyNode) {
                        if(f->left==q) return (pos=f)->data;
                        else q=f,f=q->father;
                    }
                    throw ElementNotExist();
                }

                /*
                 * Removes from the underlying collection the last element
                 * returned by the iterator
                 * @throw ElementNotExist
                 */
                void remove() {
                    if(pos==emptyNode||pos==NULL) throw ElementNotExist();
                    if(!t->containsKey(pos->data->key)) throw ElementNotExist();
                    t->remove(pos->key);
                    pos=emptyNode;
                }

                Iterator(Node *pos=NULL,Node *emptyNode=NULL,TreeMap<K,V> *t=NULL)
                    : pos(pos),emptyNode(emptyNode),t(t) {visited=false;}
            };

        /*
         * Constructs an empty map
         */
        TreeMap()
            {
            emptyNode=new Node();
            emptyNode->father=emptyNode->left=emptyNode->right=emptyNode;
            root=emptyNode;
            }

        /*
         * Copy constructor
         */
        TreeMap(const TreeMap &x)
            {
            emptyNode=new Node();
            emptyNode->father=emptyNode->left=emptyNode->right=emptyNode;
            root=emptyNode;
            typename TreeMap<K,V>::constIterator it=x.ConstIterator();
            while (it->hasNext())
                {
                Entry<K,V> tmp=it->next();
                put(tmp.key,tmp.value);
                }
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
            typename TreeMap<K,V>::constIterator it=x.ConstIterator();
            while (it->hasNext())
                {
                Entry<K,V> tmp=it->next();
                put(tmp.key,tmp.value);
                }
            }

        /*
         * Constructs a new tree map containing the same mappings as the
         * given map
         */
        template <class T2> TreeMap(const T2 &x)
            {
            emptyNode=new Node();
            emptyNode->father=emptyNode->left=emptyNode->right=emptyNode;
            root=emptyNode;
            typename T2::constIterator it=x.ConstIterator();
            while (it->hasNext())
                {
                Entry<K,V> tmp=it->next();
                put(tmp.key,tmp.value);
                }
            }

        /*
         * Returns an iterator over the elements in this map.
         * O(1).
         */
        Iterator iterator()
            {
            Node *pos=root;
            while (pos->left!=emptyNode) pos=pos->left;
            return Iterator(pos,emptyNode,this);
            }

        /*
         * Returns an const iterator over the elements in this map.
         * O(1).
         */
        constIterator ConstIterator() const
            {
            Node *pos=root;
            while (pos->left!=emptyNode) pos=pos->left;
            return constIterator(pos,emptyNode);
            }

        /*
         * Removes all of the mappings from this map.
         * O(n).
         */
        void clear()
            {
            root=removeAll(root);
            }

        /*
         * Returns true ifthis map contains a mapping for the specified key.
         * O(logn).
         */
        bool containsKey(const K &key) const
            {
            return findKey(key)!=emptyNode;
            }

        /*
         * Returns true ifthis map contains a mapping for the specified value.
         * O(n).
         */
        bool containsValue(const V &value) const
            {
            return findValue(root,value);
            }

        /*
         * Returns a key-value mapping associated with the least key in
         * this map.
         * O(logn).
         * @throw ElementNotExist
         */
        const Entry<K,V>& firstEntry() const
            {
            if(root==emptyNode) throw ElementNotExist();
            Node *n=root;
            while (n->left!=emptyNode) n=n->left;
            return n->data;
            }

        /*
         * Returns the first (lowest) key nrently in this map.
         * O(logn).
         * @throw ElementNotExist
         */
        const K& firstKey() const
            {
            return firstEntry().key;
            }

        /*
         * Returns a reference to the value which the specified key is mapped
         * O(logn).
         * @throw ElementNotExist
         */
        V& get(const K &key)
            {
            Node *n=findKey(key);
            if(n==emptyNode) throw ElementNotExist();
            return n->data.value;
            }

        /*
         * Returns a reference to the value which the specified key is mapped
         * O(logn).
         * @throw ElementNotExist
         */
        const V& get(const K &key) const
            {
            Node *n=findKey(key);
            if(n==emptyNode) throw ElementNotExist();
            return n->data.value;
            }

        /*
         * Returns a key-value mapping associated with the greatest key
         * in this map.
         * O(logn).
         * @throw ElementNotExist
         */
        const Entry<K,V>& lastEntry() const
            {
            Node *n=root;
            while (n->right!=emptyNode) n=n->right;
            return n->data;
            }

        /*
         * Returns the last (highest) key nrently in this map.
         * O(logn).
         * @throw ElementNotExist
         */
        const K& lastKey() const
            {
            return lastEntry().key;
            }

        /*
         * Associates the specified value with the specified key in this map.
         * Returns the previous value,ifnot exist,a value returned by the
         * default-constructor.
         * O(logn).
         */
        V put(const K& key,const V &value)
            {
            Entry<K,V> p(key,value);
            root=insert(root,p);
            return p.value;
            }

        /*
         * Removes the mapping for this key from this TreeMap ifpresent.
         * O(logn).
         * @throw ElementNotExist
         */
        V remove(const K &key)
            {
            V ret;
            int pre=root->nowSize;
            root=erase(root,key,ret);
            if(pre==root->nowSize) throw ElementNotExist();
            return ret;
            }

        /*
         * Returns the number of key-value mappings in this map.
         * O(logn).
         */
        int size() const {return root->nowSize;}

        bool isEmpty() const {return root==emptyNode;}
    };

#endif

