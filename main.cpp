//
//  main.cpp
//  HuffmanTree
//
//  Created by Rogelio Camargo on 3/20/17.
//  Copyright © 2017 Rogelio Camargo. All rights reserved.
//
//
//
//  Quynh Nguyen and Rogelio Camargo's Projects
//  Together we completed this project.
//

#include "HuffmanTree.h"
#include "LinkedList.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

void readFile(string, string &);
void printCharCode(LinkedList<HuffmanTree> &);
void decodeWord(HuffmanTree &);
void displayMenu();
//void encodeWord(HuffmanNode *leafs[], int size);
void encodeWord(LinkedList<HuffmanTree> &);
void encodeTextFile(LinkedList<HuffmanTree> &, HuffmanTree &, HuffmanNode *[], bool &);
void decodeTextFile(HuffmanTree &);
HuffmanTree huffmanEncode(string, vector<bool> &, LinkedList<HuffmanTree> &, HuffmanNode * []);

int main()
{
    vector<bool> encoded;
    
    LinkedList<HuffmanTree> trees;

    // When the tree is created, the huffman tree is will be stored here
    HuffmanTree huffmanTree;

    HuffmanNode *temp[256];
    int count = 0;
    
    for (int i = 0; i < 256; i++)
    {
        if (temp[i] == 0)
            count++;
    }
    
    HuffmanNode *leafNodes[count];
    
    // this is becomes true when the tree has been built successfully
    bool isBuilt = false;
    
    //string decoded = tree.decode(encoded);
    
    cout << "\t\t~~~~Huffman Coding Algorithm~~~~\n\n";
    char choice;
    do
    {
        displayMenu();
        cout << "Please Enter A Valid Option: ";
        cin >> choice;
        cout << endl;
        switch (toupper(choice))
        {
            case 'A':
                if (isBuilt)
                    trees.displayList(); // DONE
                else
                    cout << "\nYOU NEED TO BUILT THE TREE FIRST.\n\n";
                break;
            case 'B':
                if (isBuilt)
                    huffmanTree.indentTree(); // DONE
                else
                    cout << "\nYOU NEED TO BUILT THE TREE FIRST.\n\n";
                break;
            case 'C':
                if (isBuilt)
                    huffmanTree.printAllCharacters(); // DONE
                else
                    cout << "\nYOU NEED TO BUILT THE TREE FIRST.\n\n";
                break;
            case 'D':
                if (isBuilt)
                    printCharCode(trees);  // DONE
                else
                    cout << "\nYOU NEED TO BUILT THE TREE FIRST.\n\n";
                break;
            case 'E':
                if (isBuilt)
                    encodeWord(trees);
                else
                    cout << "\nYOU NEED TO BUILT THE TREE FIRST.\n\n";
                break;
            case 'F':
                if (isBuilt)
                    decodeWord(huffmanTree); // DONE
                else
                    cout << "\nYOU NEED TO BUILT THE TREE FIRST.\n\n";
                break;
            case 'G':
                encodeTextFile(trees, huffmanTree, leafNodes, isBuilt);  // DONE
                break;
            case 'H':
                if (isBuilt)
                    decodeTextFile(huffmanTree); // DONE
                else
                    cout << "\nYOU NEED TO BUILT THE TREE FIRST.\n\n";
                break;
            case 'I':
                displayMenu();  // DONE
                break;
            case 'Q':
                break;
            default:
                cout << "Please Enter A Valid Option.\n\n";
        }
            
        cout << endl;
        cin.clear();
    } while (choice != 'q');
	
	return 0;
}

//************************************************************************************
// The displayMenu() function displays the available options(the menu) to the user.
// Input: None
// Return: None
//************************************************************************************
void displayMenu()
{
    cout << "A - Print The Character Weights\n"
    << "B - Print Indented Tree(Right-Root-Left)\n"
    << "C - Print the Huffman Codes For All Characters In The List\n"
    << "D - Enter A Character / Print Its Huffman Code\n"
    << "E - Enter A Word / Print Its ASCII Binary Representation And Its Huffman Code\n"
    << "F - Enter An Encoded Word / Print The Decoded Word\n"
    << "G - Enter The Name Of A Text File / It Will Be Encoded And Saved Into Another File\n"
    << "H - Enter The Name Of A Encoded File / It Will Be Decoded And Saved Into Another File\n"
    << "I - Help / Menu Will Be Displayed\n"
    << "Q - Quit\n";
    
    cout << endl;
}

void readFile(string filename, string &str)
{
    ifstream inputFile(filename);
    if (!inputFile)
    {
        cout << "COULD NOT OPEN FILE\n\n";
        exit (1);
    }
    
    // this reads a whole file and onto a string
    str.assign((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
}


HuffmanTree huffmanEncode(string str, vector<bool> &out, LinkedList<HuffmanTree> &huffmanTrees, HuffmanNode *allLeafs[])
{
    LinkedList<HuffmanTree> trees;

    int frequencies[256] = { 0 };
    int numLeafs = 0;

    for (int i = 0; i < str.size(); ++i)
    {
        if (frequencies[(int)str[i]] == 0) numLeafs++;
        frequencies[(int)str[i]]++;
    }
    
    // a collection of huffmanNodes
    HuffmanNode *leafs[numLeafs];

    for (int i = 0, j = 0; i < 256; i++)
    {
        if (frequencies[i] != 0)
        {
            // assigns the character and frequency to each node who's frequency is not 0
            leafs[j] = new HuffmanNode(frequencies[i], i);
            // insert a the tree on the list
            huffmanTrees.insertNode(HuffmanTree(leafs[j]));
            trees.insertNode(HuffmanTree(leafs[j]));
            j++;
        }
    }

    while (trees.getCount() >= 2)
    {
        // delete the first two nodes from the list
        HuffmanTree a, b;
        a = trees.getItem();
        trees.deleteNode();
        b = trees.getItem();
        trees.deleteNode();
        
        // join the two nodes that were just deleted
        huffmanTrees.insertNode(HuffmanTree(a, b));
        trees.insertNode(HuffmanTree(a, b));
    }

    vector<bool> codes[256];
    for (int i = 0; i < numLeafs; i++)
    {
        leafs[i]->getCode(codes[(int)leafs[i]->getChar()]);
        allLeafs[i] = leafs[i];
    }
    
    //cout << str.size() << endl << endl;
    for (int i = 0; i < str.size(); ++i)
    {
        vector<bool> &code = codes[(int)str[i]];
        out.insert(out.end(), code.rbegin(), code.rend());
    }
    
    return trees.getItem();
}

//*********************************************************
// After the Huffman tree has been built, the user can
// enter a character and its huffman code will be printed.
//
//*********************************************************
void printCharCode(LinkedList<HuffmanTree> &tree)
{
    char c;
    cout << "\nPlease enter a character to be encoded: ";
    cin >> c;
    
    cout << "\nThe huffman code: ";
    tree.searchCharacterAndEncode(c);
    
    cout << endl;
}

//*********************************************************
// After the Huffman tree has been built, the user can
// enter a word and its huffman code will be printed.
//
//*********************************************************
void encodeWord(LinkedList<HuffmanTree> &tree)
{
    string word;
    cout << "\nPlease enter a word to be encoded: ";
    cin >> word;
    
    cout << "\nThe huffman code: ";
    for (int i = 0; i < word.size(); i++)
        tree.searchCharacterAndEncode(word[i]);
    
    
    cout << endl;
}


//*********************************************************
// The user is asked to enter an encoded word so it could
// be decoded.
//
//*********************************************************
void decodeWord(HuffmanTree &htree)
{
    vector<bool> encoded;
    string enWord;

    cout << "\nPlease enter an encoded word to be decoded: ";
    cin >> enWord;
    
    for (int i = 0; i < enWord.size(); i++)
    {
        if (enWord[i] == '0')
            encoded.push_back(0);
        if (enWord[i] == '1')
            encoded.push_back(1);
    }
    
    cout << "DECODED: " <<  htree.decode(encoded) << endl;
}

//*********************************************************
// The user is asked to enter a file name. After,
// a tree will be built and the text will be encoded
// and saved onto another file.
//
//*********************************************************
void encodeTextFile(LinkedList<HuffmanTree> &huffmanTrees, HuffmanTree &huffmanTree, HuffmanNode *leafs[], bool &isBuilt)
{
    string filename;
    string str;
    
    cout << "Please enter a valid file name to be encoded: ";
    cin >> filename;
    cout << endl;
    
    readFile(filename, str);
    
    vector<bool> encoded;
    
    huffmanTree = huffmanEncode(str, encoded, huffmanTrees, leafs);
    
    ofstream outputFile("in_encoded.txt");
    for (int i = 0; i < encoded.size(); i++)
        outputFile << encoded[i];
    
    isBuilt = true;
    
    outputFile.close();
    
}


//*********************************************************
// The user is asked to enter a file name which
// contains an encoded text.
// The text will be decoded and displayed to another file.
//
//*********************************************************
void decodeTextFile(HuffmanTree &htree)
{
    string filename;
    string str;
    string decoded;
    
    cout << "Please enter a valid file name to decode: ";
    cin >> filename;
    cout << endl;
    
    readFile(filename, str);
    
    vector<bool> encoded;
    
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == '0')
            encoded.push_back(0);
        if (str[i] == '1')
            encoded.push_back(1);
    }
    
    decoded = htree.decode(encoded);
    
    ofstream outputFile("in_decoded.txt");
    outputFile << decoded;
    
    cout << decoded << endl;
    outputFile.close();
}


/**********

 
***/
