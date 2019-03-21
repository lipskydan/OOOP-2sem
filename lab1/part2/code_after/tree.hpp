//
//  tree.hpp
//  code_after
//
//  Created by Danial on 3/19/19.
//  Copyright © 2019 Danial. All rights reserved.
//

#ifndef tree_hpp
#define tree_hpp

#include <stdio.h>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <vector>
#include <fstream>

using namespace std;

typedef enum { BLACK, RED } nodeColor;

vector<pair<string, int>> testDataForCreate = {
    {"a", 24},
    {"b", 12},
    {"c", 45},
    {"d", 55},
};

vector<pair<string, int>> testDataForAdd = {
    {"a", 23},
    {"a", 25},
    {"b", 11},
    {"b", 13},
    {"c", 44},
    {"c", 46},
    {"d", 54},
    {"d", 58},
};

struct Node {
    Node* left;
    Node* right;
    nodeColor color;
    Node* parent;
    int size;
    string name;
    int price;
};

///////////////////////////////////////////////////////////////////////////////////////////////

class Tree {
public:
    Tree();
    void CreateTree(const string& name,const int& price /*const int& data*/);
    void AddToTree(Node* &root, const string name, const int price /*const int& data*/);
    void ShowTree(Node* root, int counter = -1);
    void Load(string nameOfFile);
    void Select(Node* root);

    int GetPrice(){
        return root->price;
    }

    Node*& getRoot(){
        return root;
    }
    
private:
    void RotateLeft(Node *x);
    void RotateRight(Node *x);
    void SetColor(Node* node);
    
    Node* select_max(Node* root, int size);
    Node* select_min(Node* root, int size);
    

private:
    Node *root;
    Node *parent;
};

///////////////////////////////////////////////////////////////////////////////////////////////

class Testing: public Tree{
public:
    void Creating();

private:
    void TestCreateTree(vector<Tree>& vec_node);
    void TestAddToTree(vector<Tree>& vec_node);

    bool isValid_Create(Node* &node, const string& expectedName, const int& expectedPrice);
    bool isValid_Add(Node* &node);
    
public:
    int quantityOfTesting = 0;
};




#endif /* tree_hpp */
