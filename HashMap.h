#ifndef __HASHMAP_H
#define __HASHMAP_H

#include "ElementNotExist.h"

template <class K,class V,class H>
class HashMap
{
private:
    int _capacity,_size;
public:
    class Entry
    {
    public:
        K key;V value;
        Entry(K k,V v):key(k),value(v) {}
        Entry() {}
        K getKey() const { return key; }
        V getValue() const{ return value; }
    };
    struct node
    {
        Entry data;
        node *next;
        node(const Entry &dat):data(dat),next(NULL) {}
        node():next(NULL) {}
    };
    node **storage;

    class Iterator
    {
    private:
        int cur;
        node *pos;
        const HashMap *host;
    public:

        bool hasNext() const
        {
            if(pos->next) return true;
            for(int i=cur+1;i<host->_capacity;i++)
                if(host->storage[i]->next!=NULL)
                    return true;
            return false;
        }

        const Entry &next()
        {
            if(!hasNext()) throw ElementNotExist();
            if(pos->next!=NULL)
            {
                pos=pos->next;
                return pos->data;
            }
            for(int i=cur+1;i<host->_capacity;i++)
                if(host->storage[i]->next!=NULL)
                {
                    pos=host->storage[i]->next;cur=i;
                    return pos->data;
                }
        }

        Iterator(const HashMap *hos=NULL):host(hos) {pos=host->storage[0];cur=0;}
    };

    HashMap()
    {
        _capacity=99971;
        _size=0;
        storage=new node*[_capacity];
        for(int i=0;i<_capacity;i++)
            storage[i]=new node;
    }

    HashMap(int initial_capacity)
    {
        _capacity=initial_capacity;
        _size=0;
        storage=new node*[_capacity];
        for(int i=0;i<_capacity;i++)
            storage[i]=new node;
    }

    ~HashMap()
    {
        clear();
        for(int i=0;i<_capacity;i++)
            delete storage[i];
        delete [] storage;
    }

    HashMap &operator=(const HashMap &x)
    {
        clear();
        for(int i=0;i<_capacity;i++)
            delete storage[i];
        delete [] storage;
        _capacity=x._capacity;
        _size=0;
        storage=new node*[_capacity];
        for(int i=0;i<_capacity;i++)
        {
            storage[i]=new node;
            for(node *pos=x.storage[i]->next;pos!=NULL;pos=pos->next)
                insert(pos->data);
        }
        return *this;
    }

    HashMap(const HashMap &x)
    {
        _capacity=x._capacity;
        _size=0;
        storage=new node*[_capacity];
        for(int i=0;i<_capacity;i++)
        {
            storage[i]=new node;
            for(node *pos=x.storage[i]->next;pos!=NULL;pos=pos->next)
                insert(pos->data);
        }
    }

    Iterator iterator() const
    {
        return Iterator(this);
    }

    void clear()
    {
        for(int i=0;i<_capacity;i++)
        {
            for(node* pos=storage[i]->next,*rem;pos!=NULL;rem=pos,pos=pos->next,delete rem)
                ;
            storage[i]->next=NULL;
        }
        _size=0;
    }

    bool containsKey(const K &key) const
    {
        int p=(H::hashCode(key)%_capacity+_capacity)%_capacity;
        for(node *pos=storage[p]->next;pos!=NULL;pos=pos->next)
            if(pos->data.key==key)
                return true;
        return false;
    }

    bool containsValue(const V &value) const
    {
        for(int i=0;i<_capacity;i++)
            for(node *pos=storage[i]->next;pos!=NULL;pos=pos->next)
                if(pos->data.value==value)
                    return true;
        return false;
    }

    const V &get(const K &key) const
    {
        int p=(H::hashCode(key)%_capacity+_capacity)%_capacity;
        for(node *pos=storage[p]->next;pos!=NULL;pos=pos->next)
            if(pos->data.key==key)
                return pos->data.value;
        throw ElementNotExist();
    }

    bool isEmpty() const
    {
        return !_size;
    }

    void put(const K &key,const V &value)
    {
        int p=(H::hashCode(key)%_capacity+_capacity)%_capacity;
        for(node *pos=storage[p]->next;pos!=NULL;pos=pos->next)
            if(pos->data.key==key)
            {
                pos->data.value=value;
                return;
            }
        insert(Entry(key,value));
    }

    void remove(const K &key)
    {
        int p=(H::hashCode(key)%_capacity+_capacity)%_capacity;
        for(node *pos=storage[p]->next,*rem=storage[p];pos!=NULL;rem=pos,pos=pos->next)
            if(pos->data.key==key)
            {
                rem->next=pos->next;
                delete pos;
                --_size;
                return;
            }
        throw ElementNotExist();
    }

    int size() const
    {
        return _size;
    }

    void insert(const Entry & e)
    {
        int p=(H::hashCode(e.key)%_capacity+_capacity)%_capacity;
        node *data=new node(e);
        data->next=storage[p]->next;
        storage[p]->next=data;
        _size++;
    }

};

#endif
