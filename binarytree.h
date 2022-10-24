#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
#include <string>
#include <fstream>

struct treenode
{
    std::string data;
    struct treenode* left;
    struct treenode* right;
      
    treenode(std::string val)
    {
        data = val;
        left = NULL;
        right = NULL;
    }
};

//this is the function that calls the the survey and builds the tree
void survey();
//this is the function that allows the us to read in the user's input
std::string getUserMessage();
//this is the function that pushed the user's message into the tetx file
void recordUserMessage(std::string userMessage);
//this is the function that deallocates the tree
void deleteTree(treenode* root);
#endif