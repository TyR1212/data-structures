//Ty Rozell
//This is the header file for the hash table class

#include <string>
#include <vector>

using namespace std;

#ifndef HASHTABLE_H
#define HASHTABLE_H

template<typename TYPE>
class node
{
    public:
        TYPE data;       //holds the actual data of the node
        string key;      //how the node is identified
        bool tombstoned; //has node been deleted or not
        node();
};

template<typename TYPE>
node<TYPE>::node()
{
    key = "";
    tombstoned = false;
}

template<typename TYPE>
class HashTable
{
    public:
        bool add(string, TYPE); //add node to table
        bool remove(string);    //delete node from table
        TYPE get(string);       //return node data from table
        bool set(string, TYPE); //set node data in table
        int count();            //get number of elements in table
        HashTable();

    private:
        int size;                 //number of elements in table
        vector<node<TYPE>> table; //stores all of the nodes
        
        int hash(string);               //multiplicative string hashing function
        int indexOf(string);            //get index of a node in table
        int findAvailableIndex(string); //find the next available index in table based on given key
};

template<typename TYPE>
HashTable<TYPE>::HashTable()
{
    size = 0;
    table.resize(59);
}

//multiplicative string hashing function
template<typename TYPE>
int HashTable<TYPE>::hash(string key)
{
    int index = 0;

    for (int i=0; i < key.length(); i++)
        index = index * 2 + key[i];

    return index % table.size();
}

template<typename TYPE>
int HashTable<TYPE>::indexOf(string key)
{
    int index = hash(key); //hash function

    //search for node
    for (int i=0; i < table.size(); i++)
    {
        if (key == table[index].key)  //found key
        {
            if (!table[index].tombstoned)
                return index;         //success, return the index
            else
                break;                //node has been previously deleted
        }

        if (!table[index].tombstoned) //found an empty index, therefore node is not in the table
            break;

        if (index == table.size()-1)
            index = 0;    //start over, searching at beginning
        else
            index++;
    }

    return -1;   //node is not in table
}

template<typename TYPE>
int HashTable<TYPE>::findAvailableIndex(string key)
{
    int index = hash(key); //hash function

    //search for available index
    for (int i=0; i < table.size(); i++)
    {
        if (table[index].tombstoned || (!table[index].tombstoned && table[index].key == ""))
            return index;   //success

        if (index == table.size()-1)
            index = 0;      //start over, searching at beginning
        else
            index++;
    }

    return -1;   //failed to find available index
}

template<typename TYPE>
bool HashTable<TYPE>::add(string key, TYPE obj)
{
    int index = findAvailableIndex(key);

    //if node is not in table and there is an available index, add it
    if (indexOf(key) == -1 && index != -1)
    {
        table[index].data = obj;   //assign node to table
        table[index].key = key;
        table[index].tombstoned = false;
        size++;
        return true;    //success
    }
    else
        return false;   //failed
}

template<typename TYPE>
bool HashTable<TYPE>::remove(string key)
{
    int index = indexOf(key);

    //if node is in table, remove it
    if (index != -1)
    {
        table[index].tombstoned = true; //mark the node as removed
        size--;
        return true;   //success
    }
    else
        return false;  //failed
}

template<typename TYPE>
TYPE HashTable<TYPE>::get(string key)
{
    int index = indexOf(key);

    //if node is in table, return the node's data
    if (index != -1)
        return table[index].data; //success
    else
        return TYPE();            //failed
}

template<typename TYPE>
bool HashTable<TYPE>::set(string key, TYPE obj)
{
    int index = indexOf(key);

    //if node is in table, update the node's data
    if (index != -1)
    {
        table[index].data = obj;
        return true;   //success
    }
    else
        return false;  //failed

}

template<typename TYPE>
int HashTable<TYPE>::count()
{
    return size;
}

#endif