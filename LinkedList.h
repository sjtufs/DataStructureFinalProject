#ifndef __LINKEDLIST_H
#define __LINKEDLIST_H

#include "Utility.h"
#include <memory.h>

/*
 * A linked list.
 *
 * The iterator iterates in the order of the elements being loaded into this list.
 */
template <class T> class LinkedList
    {
    public:
        struct Node
            {
            Node *prev,*next;
            T *data;
            Node():prev(NULL),next(NULL),data(NULL) {}
            Node(const T &d):prev(NULL),next(NULL) {data=new T(d);}
            void insert(const T &e)
                {
                Node *add=new Node(e);
                add->prev=this;
                add->next=this->next;
                if (add->next) add->next->prev=add;
                this->next=add;
                }
            ~Node()
                {
                delete data;
                }
            };

    private:
        Node *head,*tail;
        int nowSize;

    public:
        class Iterator
            {
            private:
                Node *position;
                LinkedList<T> *host;
            public:
                /*
                 * Returns true if the iteration has more elements.
                 */
                bool hasNext()
                    {
                    if (position==NULL) return false;
                    return position->next!=NULL;
                    }

				/*
			 	 * Returns the next element in the iteration.
				 * @throw ElementNotExist exception when hasNext() == false
				 */
                T& next()
                    {
                    if(!hasNext()) throw ElementNotExist();
                    position=position->next;
                    return *(position->data);
                    }

				/*
				 * TODO Removes from the underlying collection the last element
				 * returned by the iterator
				 * The behavior of an iterator is unspecified if the underlying
				 * collection is modified while the iteration is in progress in
				 * any way other than by calling this method.
				 * @throw ElementNotExist
				 */
                void remove()
                    {
                    if (position==NULL||position->data==NULL) throw ElementNotExist();
                    Node *f=position->prev;
                    if (position==host->tail) host->tail=f;
                    f->next=position->next;
                    if (f->next) f->next->prev=f;
                    delete position;
                    position=NULL;
                    --host->nowSize;
                    }

                void set(const T &e)
                    {
                    if (position==NULL||position->data==NULL) throw ElementNotExist();
                    *position->data=e;
                    }

                Iterator() {position=NULL;}
                Iterator(Node *position,LinkedList <T> *host):position(position),host(host) {}
            };

        /*
         * Constructs an empty list
         */
        LinkedList()
            {
            head=tail=new Node();
            head->prev=head;
            nowSize=0;
            }

        /*
         * Copy constructor
         */
        LinkedList(const LinkedList<T> &x)
            {
            head=tail=new Node();
            head->prev=head;
            nowSize=0;
            addAll(*this,x);
            }

        /*
         * Assignment operator
         */
        LinkedList<T>& operator=(const LinkedList<T> &x)
            {
            this->clear();
            addAll(*this,x);
            return *this;
            }

        /*
         * Desturctor
         */
        ~LinkedList()
            {
            clear();
            delete head;
            }

		/*
         * Appends the specified element to the end of this list.
         * Always returns true;
         */
        bool add(const T &e)
            {
            tail->insert(e);
            while (tail->next) tail=tail->next;
            nowSize++;
            return true;
            }

		/*
         * Inserts the specified element at the beginning of this list.
         */
        void addFirst(const T &e)
            {
            head->insert(e);
            while (tail->next) tail=tail->next;
            nowSize++;
            }

		/*
		 * Insert the specified element to the end of this list.
		 * Equivalent to add.
		 */
		void addLast(const T &e)
			{
			add(e);
			}

		/*
		 * Inserts the specified element to the specified position in this list.
		 * The range of index parameter is [0, size], where index=0 means inserting to the head,
		 * and index=size means appending to the end.
		 * @throw IndexOutOfBound
		 */
        void add(int index,const T &e)
            {
            Node *f=head;
            for(int i=0;i<index;i++)
                f=f->next;
            f->insert(e);
            while (tail->next) tail=tail->next;
            nowSize++;
            }

        /*
         * Removes all of the elements from this list.
         */
        void clear()
            {
            while (head->next)
                {
                Iterator n(head,this);
                n.next();
                n.remove();
                }
            tail=head;
            }

        /*
         * Returns true if this list contains the specified element.
         */
        bool contains(const T &e) const
            {
            Node *n=head;
            while (n->next)
                {
                n=n->next;
                if (*(n->data)==e) return true;
                }
            return false;
            }

		/*
		 * Returns a const reference to the element at the specified position in this list.
		 * The index is zero-based, with range [0, size).
		 * @throw IndexOutOfBound
		 */
        const T& get(int index) const
            {
            Node *n=head;
            for(int i=0;i<=index;i++)
                {
                n=n->next;
                if (!n) throw IndexOutOfBound();
                }
            return *(n->data);
            }

        /*
		 * Returns a const reference to the first element.
		 * @throw ElementNotExist
		 */
        const T& getFirst() const
            {
            if (head->next==NULL) throw ElementNotExist();
            return *(head->next->data);
            }

        /*
         * Returns a const reference to the last element.
         * @throw ElementNotExist
         */
        const T& getLast() const
            {
            if (isEmpty()) throw ElementNotExist();
            return *(tail->data);
            }

		/*
         * Returns true if this list contains no elements.
         */
        bool isEmpty() const
            {
            return (head==tail);
            }

        /*
         * Returns the index of the first ocnrence of the specified element
         * O(1).
         * in this list,or -1 if this list does not contain the element.
         */
        int indexOf(const T &e) const
            {
            Node *n=head;
            int cnt=0;
            while (n->next!=NULL)
                {
                n=n->next;
                if (*(n->data)==e) return cnt;
                ++cnt;
                }
            return -1;
            }

		/*
		 * Removes the element at the specified position in this list.
		 * The index is zero-based, with range [0, size).
		 * @throw IndexOutOfBound
		 */
		void removeIndex(int index)
            {
            if (index >= nowSize||index<0) throw IndexOutOfBound();
            Node *n=head;
            for(int i=0;i<=index;i++) n=n->next;
            Iterator it(n,this);
            it.remove();
            }

		/*
		 * Removes the first ocnrence of the specified element from this list, if it is present.
		 * Returns true if it was present in the list, otherwise false.
		 */
        bool remove(const T &e)
            {
            Node *n=head;
            while (n->next)
                {
                n=n->next;
                if (*(n->data)==e)
                    {
                    Iterator it(n,this);
                    it.remove();
                    return true;
                    }
                }
            return false;
            }

		/*
		 * Removes the first element from  this list.
		 * @throw ElementNotExist
		 */
		void removeFirst()
			{
			if(isEmpty()) throw ElementNotExist();
			Iterator del(head,this);
			T r=del.next();
			del.remove();
			}
		/*
         * Removes the last element from this list.
         * @throw ElementNotExist
         */
        void removeLast()
            {
            if (isEmpty()) throw ElementNotExist();
            Iterator n(tail,this);
            n.remove();
            }

		/*
		 * Replaces the element at the specified position in this list with the specified element.
		 * The index is zero-based, with range [0, size).
		 * @throw IndexOutOfBound
		 */
        void set(int index,const T &e)
            {
            Node *n=head;
            for(int i=0;i<=index;i++)
                {
                n=n->next;
                if (!n) throw IndexOutOfBound();
                }
            *(n->data)=e;
            }

		/*
         * Returns the number of elements in this list.
         */
        int size() const {return nowSize;}

		/*
         * Returns an iterator
         */
        Iterator iterator()
            {
            return Iterator(head,this);
            }
    };
#endif

