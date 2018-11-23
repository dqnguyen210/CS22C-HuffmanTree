#ifndef _HUFFMAN_TREE
#define _HUFFMAN_TREE

#include "HuffmanNode.h"
#include "LinkedList.h"
#include <string>
using namespace std;

class HuffmanTree
{
private:
	HuffmanNode *root;

    void _destroy(HuffmanNode *);
    void _indentTree(HuffmanNode*);
    void _printAllCharacters(HuffmanNode*);

public:
    // Constructors
	HuffmanTree() {}
	HuffmanTree(HuffmanNode *root) { this->root = root; }
    HuffmanTree(HuffmanTree &a, HuffmanTree &b);
    
    // accessors
	int getFrequency() { return root->getFreq(); }
    char getCharacter() { return root->getChar(); }
    void getHuffCode() { root->getHuffmanCode(); }
    
    string decode(vector<bool> &encoded);
    void indentTree() { _indentTree(root); }
    void printAllCharacters() { _printAllCharacters(root); }
    void destroy() { _destroy(root); }
    
};

//*****************************************************************
// Constructor builds a new tree by combining two existing
// trees and setting the pointers accordingly
//
//*****************************************************************
HuffmanTree::HuffmanTree(HuffmanTree &a, HuffmanTree &b)
{
    int total = a.getFrequency() + b.getFrequency();
    root = new HuffmanNode(total);
    root->setLeft(a.root);
    root->setRight(b.root);
    a.root->setParent(root);
    a.root->setIsRight(false);
    b.root->setParent(root);
    b.root->setIsRight(true);
}

string HuffmanTree::decode(vector<bool> &encoded)
{
    string out;
    
    int i = 0;
    HuffmanNode *node = root;
    while (i != encoded.size())
    {
        bool b = encoded[i++];
        if (b)
            node = node->getRight();
        else
            node = node->getLeft();
        if (node->getChar() != 0)
        {
            out += node->getChar();
            node = root;
        }
    }
    
    return out;
}

void HuffmanTree::_destroy(HuffmanNode *ptr)
{
    if (ptr)
    {
        _destroy(ptr->getLeft());
        _destroy(ptr->getRight());
        delete ptr;
    }
}

void HuffmanTree::_indentTree(HuffmanNode* tree)
{
    static int indent = 0; //used to indent the tree by levels
    if(tree == NULL)
    {
        return;
    }
    
    if(tree != NULL)
    {
        indent++;
        
        _indentTree(tree->getRight());
        
        cout << setw(indent * 5) << indent << ") Frequency: " << tree->getFreq() << endl;
        
        _indentTree(tree->getLeft());
        
        indent--;
    }
}


void HuffmanTree::_printAllCharacters(HuffmanNode* tree)
{
    if(tree == NULL)
    {
        return;
    }
    
    if(tree != NULL)
    {
        
        _printAllCharacters(tree->getRight());
        
        if (tree->getChar() != 0)
        {
            if ((int)tree->getChar() == 32)
            {
                cout << "Character: \' \' " << " Huffman Code: ";
                tree->getHuffmanCode();
                cout << endl;
            }
            else if((int)tree->getChar() == 10)
            {
                cout << "Character: \'\\n\' " << " Huffman Code: ";
                tree->getHuffmanCode();
                cout << endl;
            }
            else
            {
                cout << "Character: " << tree->getChar() << " Huffman Code: ";
                tree->getHuffmanCode();
                cout << endl;
            }
        }
        
        _printAllCharacters(tree->getLeft());
        
    }
}



/*
 
 */


#endif
