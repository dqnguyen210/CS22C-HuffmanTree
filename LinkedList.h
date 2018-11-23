//
//  
//
//
//  Created by: Rogelio Camargo Isidoro
//
//

#ifndef LinkedList_h
#define LinkedList_h

#include "HuffmanTree.h"
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

template<class ItemType>
class LinkedList
{
private:
    // Declare a structure for the list
    struct ListNode
    {
        ItemType item;   // The value in this node
        ListNode *next;     // To point to the next node
    };
    
    int count = 0; // counter to keep tracks of how many nodes.
    
    ListNode *head;        // List head pointer
    
    
public:
    LinkedList();  // Constructor
    ~LinkedList();   // Destructor
    
    // Linked list operations
    void insertNode(ItemType);
    void deleteNode();
    void displayList() const;
    void searchCharacterAndEncode(char) const;
    void encodeWord(string) const;
    
    int getCount()
    { return count; }
    
    ItemType getItem()
    { return head->next->item; }

};


//**************************************************
// Constructor - make senteniel node at beginning
// of linked list
//**************************************************
template<class ItemType>
LinkedList<ItemType>::LinkedList()
{
    head = new ListNode; // head points to the sentinel node
    head->next = NULL;
}

//**************************************************
// The insertNode function inserts a new node in
// a sorted list (it keeps the list sorted)
//
//**************************************************
template<class ItemType>
void LinkedList<ItemType>::insertNode(ItemType dataIn)
{
    ListNode *newNode;  // A new node
    ListNode *pCur;     // To traverse the list
    ListNode *pPre;     // The previous node
    
    count++; // updates the counter; whenever a new node is added, the counter is incremented by 1.
    
    // Allocate a new node and store num there.
    newNode = new ListNode;
    newNode->item = dataIn;
    
    
    // Initialize pointers
    pPre = head;
    pCur = head->next;
    while (pCur != NULL && pCur->item.getFrequency() < dataIn.getFrequency())
        // the latter statement, enables the list
        // to go in ascending order
    {
        // traverses through the list
        pPre = pCur;
        pCur = pCur->next;
    }
    
    // Insert the new node between pPre and pCur
    pPre->next = newNode;
    newNode->next = pCur;
    
}


//**************************************************
// The deleteNode function deletes the
// first node with data everytime(not the sentinel
// node)
//**************************************************
template<class ItemType>
void LinkedList<ItemType>::deleteNode()
{
    ListNode *pCur;       // To traverse the list
    ListNode *pPre;        // To point to the previous node
    //bool deleted = false;
    
    // Initialize pointers
    pPre = head;
    pCur = head->next;
    
    
    pPre->next = pCur->next;
    //deleted = pCur;
    delete pCur;
    count--; // updates counter; when one node/item is deleted, counter is decremented by 1.

    //return deleted;
}

//**************************************************
// The displayList function shows the value
// stored in each node of the linked list
// pointed to by head.
//
//**************************************************
template<class ItemType>
void LinkedList<ItemType>::displayList() const
{
    ListNode *pCur;
    
    // Position pCur: skip the head of the list.
    pCur = head->next;
    // While pCur points to a node, traverse the list.
    while (pCur)
    {
        // Display the elements of a node with BOTH characher and frequency
        if(pCur->item.getCharacter() != 0)
        {
            if((int)pCur->item.getCharacter() == 32)
            {
                cout << "Charactor: \' \'" << endl
                     << "Frequency: " << pCur->item.getFrequency() << endl << endl;
            }
            else if((int)pCur->item.getCharacter() == 10)
            {
                cout << "Charactor: \'\\n\'" << endl
                << "Frequency: " << pCur->item.getFrequency() << endl << endl;
            }
            else
            {
                cout << "Charactor: " << pCur->item.getCharacter() << endl
                << "Frequency: " << pCur->item.getFrequency() << endl << endl;
            }
        }
        
        // Move to the next node.
        pCur = pCur->next;
    }
}

template<class ItemType>
void LinkedList<ItemType>::searchCharacterAndEncode(char c) const
{
    ListNode *pCur;
    bool found = false;
    
    // Position pCur: skip the head of the list.
    pCur = head->next;
    // While pCur points to a node, traverse the list.
    while (pCur && !found)
    {
        if (pCur->item.getCharacter() == c)
        {
            pCur->item.getHuffCode();
            found = true; 
        }
        
        // Move to the next node.
        pCur = pCur->next;
    }
}

//template<class ItemType>
//void LinkedList<ItemType>::encodeCharacter(string word) const
//{
//    ListNode *pCur;
//    
//    // Position pCur: skip the head of the list.
//    pCur = head->next;
//    // While pCur points to a node, traverse the list.
//    while (pCur)
//    {
//        for (int i = 0, i < word.size();i++)
//        if (pCur->item.getCharacter() == word[])
//        {
//            pCur->item.getHuffCode();
//            break;
//        }
//        
//        // Move to the next node.
//        pCur = pCur->next;
//    }
//}

//**************************************************
// Destructor
// This function deletes every node in the list.
// 
//**************************************************
template<class ItemType>
LinkedList<ItemType>::~LinkedList()
{
    ListNode *pCur;   // To traverse the list
    ListNode *pNext;  // To point to the next node
    
    
    pCur = head->next;
    while (pCur != NULL)
    {
        pNext = pCur->next;
        
        // Delete the current node.
        delete pCur;
        
        pCur = pNext;
    }
    
    delete head; // delete the sentinel node
}



#endif
