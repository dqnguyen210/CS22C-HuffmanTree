#ifndef _HUFFMAN_NODE
#define _HUFFMAN_NODE

#include <vector>
#include <iostream>
using namespace std;

class HuffmanNode
{
private:
	int freq;
	char c;
    vector<bool> code;
    
	HuffmanNode *parent;
	bool isRight;
	HuffmanNode *left;
	HuffmanNode *right;

public:
    // constructors
	HuffmanNode() : parent(NULL), left(NULL), right(NULL), c(0) {}
    
    HuffmanNode(char ch) : parent(NULL), left(NULL), right(NULL) { this->c = ch; }
    
    // constructor for a joiner(a node with just a accumulated weight)
	HuffmanNode(int freq) : HuffmanNode() { this->freq = freq; }
    
    // constructor for a leaf
	HuffmanNode(int freq, char c) : HuffmanNode(freq) { this->c = c; }

    // accessors
	int getFreq() { return freq; }
	char getChar() { return c; }
    void getHuffmanCode();
    HuffmanNode *getLeft() { return left; }
    HuffmanNode *getRight() { return right; }
    HuffmanNode *getParent() { return parent;}
    
    // mutators
    void setParent(HuffmanNode *parent) { this->parent = parent; }
	void setIsRight(bool isRight) { this->isRight = isRight; }
	void setLeft(HuffmanNode *left) { this->left = left; }
	void setRight(HuffmanNode *right) { this->right = right; }
    
    void getCode(vector<bool> &in);
    void displayCode(vector<bool> &in);
};


void HuffmanNode::getCode(vector<bool> &in)
{
    HuffmanNode *ptr = this;
    while (ptr->parent)
    {
        if (ptr->isRight)
        {
            code.push_back(1);
            in.push_back(1);
        }
        else
        {
            code.push_back(0); 
            in.push_back(0);
        }
        ptr = ptr->parent;
    }
}

void HuffmanNode::getHuffmanCode()
{
    for (int i = 0; i < code.size(); i++)
        cout << code[i];
}

//void HuffmanNode::displayCode(vector<bool> &in)
//{
//    string code;
//    getCode(in);
//    
//    for (int i = 0; i < in.size(); i++)
//        code += in[i];
//    
//}

#endif
