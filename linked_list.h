//This is the header file for the linked list class

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

//node class
template<typename TYPE>
class node
{
    public:
    TYPE* data; //points to entry in hash table
    node* next; //points to next node in list
};

//linked list class
template <typename TYPE>
class LinkedList
{
    private:
        int listLength;   //keeps track of list length
        node<TYPE>* head; //points to first node in list
        node<TYPE>* tail; //points to last node in list
        TYPE* blank;      //used in get() to return no results

    public:
        LinkedList();
        ~LinkedList();
        void append(TYPE*); //adds new entry address to list
        void erase(int);    //removes a node from the list
        TYPE* get(int);     //return address of an entry in hash table
        void clear();       //deletes all the nodes in the list
        int length();       //returns list length
};

template <typename TYPE>
LinkedList<TYPE>::LinkedList()
{
    listLength = 0;
    blank = new TYPE;
}

template <typename TYPE>
LinkedList<TYPE>::~LinkedList()
{
    this->clear();
    delete blank;
}

//adds new entry address to list
template <typename TYPE>
void LinkedList<TYPE>::append(TYPE* entry)
{
    node<TYPE>* n = new node<TYPE>; //make new node
    n->data = entry;   //point to entry

    if (listLength == 0) //if list is empty, set head and tail to first node
    {
        head = n;
        tail = n;
    }
    else   //append node to the end
    {
        tail -> next = n;
        tail = n;
    }

    listLength++;
}

//removes a node from the list
template <typename TYPE>
void LinkedList<TYPE>::erase(int index)
{
    node<TYPE>* iterate = head;  //keeps track of current node
    node<TYPE>* previous = head; //keeps track of previous node
    node<TYPE>* temp;            //placeholder node when deleting

    if (index < listLength && index >= 0) //if in range
        for (int i=0; i < listLength; i++)   //search through list
        {
            if (i > 0)   //if not first node, advance iterate
                iterate = iterate->next;

            if (i == index)   //found node to delete
            {
                //delete current node and reroute
                temp = iterate;
                if (index == 0)     //if first entry
                    head = head->next;
                else if (i == listLength - 1)   //if last entry
                    tail = previous;
                else   //its in the middle
                {
                    iterate = iterate->next;
                    previous->next = iterate;
                }
                delete temp;
                listLength--;

                break; //done, EXIT
            }
            else if (i > 0)   //if not first node, advance previous
                previous = previous->next;
        }
}

//return address of an entry in hash table
template <typename TYPE>
TYPE* LinkedList<TYPE>::get(int index)
{
    node<TYPE>* iterate = head; //keeps track of current node

    if (index < listLength && index >= 0) //if in range
        for (int i=0; i < listLength; i++) //search through list
            if (i == index)
                return iterate->data;   //found
            else
                iterate = iterate->next; //advance iterate

    return blank; //couldn't find
}

//clears list by deleting all the nodes
template <typename TYPE>
void LinkedList<TYPE>::clear()
{
    node<TYPE>* iterate = head; //keeps track of current node
    node<TYPE>* temp = head;    //placeholder node when deleting

    for (int i=0; i < listLength; i++) //go through list
    {
        iterate = iterate->next; //advance iterate
        delete temp;   //delete node
        temp = iterate;   //advance temp
    }
    
    listLength = 0; //list is now empty
}

//returns list length
template <typename TYPE>
int LinkedList<TYPE>::length()
{
    return listLength;
}

#endif