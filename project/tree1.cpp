//
//  main.cpp

//
//  Created by Danial on 2/6/19.
//  Copyright © 2019 Danial. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <vector>
#include <fstream>

using namespace std;

typedef enum { BLACK, RED } nodeColor;

vector<pair<string, string>> testData = {
    {"apple", "24"},
    {"cucumber", "12"},
    {"cherry", "45"},
    {"watermelon", "55"},
    
};

struct Node {
    Node* left;
    Node* right;
    nodeColor color;
    Node* parent;
    int size;
    //int data;
    string name;
    string price;
};

Node *root = NULL;

Node* CreateTree(const string& name,const string& price) {
    Node* root = new Node;
    root->name = name;
    root->price = price;
    root->left = root->right = NULL;
    root->color = BLACK;
    root->parent = NULL;
    root->size = 1;
    return root;
}

bool isValid(Node* &node, const string& expectedName, const string& expectedPrice) {
    //static data
    if (node->right != NULL || node->left != NULL) {
        return false;
    }
    if (node->color != BLACK) {
        return false;
    }
    if (node->size != 1) {
        return false;
    }
    
    //dynamic data
    if (node->name != expectedName || node->price != expectedPrice) {
        return false;
    }
    
    return true;
}

void TestCreateTree(vector<Node*>& vec_node) {
    bool allTestPassed = true;
    
    for (int i = 0; i < testData.size(); i++) {
        if (!isValid(vec_node[i],testData[i].first,testData[i].second)){
            allTestPassed = false;
        }
    }
    
    if (allTestPassed) {
        cout << "Test passed\n" << endl;
    }else{
        cout << "Test failed\n" << endl;
    }
}

void RotateLeft(Node *x) {
    
    Node *y = x->right;
    
    x->right = y->left;
    if (y->left != NULL) y->left->parent = x;
    
    if (y != NULL) y->parent = x->parent;
    if (x->parent) {
        if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
    } else {
        root = y;
    }
    
    y->left = x;
    if (x != NULL) x->parent = y;
}

void RotateRight(Node *x) {
    
    Node *y = x->left;
    
    x->left = y->right;
    if (y->right != NULL) y->right->parent = x;
    
    if (y != NULL) y->parent = x->parent;
    if (x->parent) {
        if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;
    } else {
        root = y;
    }
    
    y->right = x;
    if (x != NULL) x->parent = y;
}

void SetColor(Node* node) {
    
    while (node != root && node->parent->color == RED) {
        
        if (node->parent == node->parent->parent->left) {
            Node* uncle = node->parent->parent->right;
            if (uncle && uncle->color == RED ) {
                
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                
                if (node == node->parent->right) {
                    node = node->parent;
                    RotateLeft(node);
                }
                
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                RotateRight(node->parent->parent);
            }
        } else {
            
            Node* uncle = node->parent->parent->left;
            if (uncle && uncle->color == RED) {
                
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                
                if (node == node->parent->left) {
                    node = node->parent;
                    RotateRight(node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                RotateLeft(node->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

void AddToTree(Node* &root, Node* &parent, const string name, const string price) {
    if (!root) {
        root = new Node;
        root->price = price;
        root->name = name;
        root->size = 1;
        
        root->left = root->right = NULL;
        root->color = RED;
        root->parent = parent;
        SetColor(root);
        
        return;
    }
    //root->size++;
    if (price > root->price) {
        root->size++;
        parent = root;
        AddToTree(root->right,parent, name, price);
    }
    else if (price < root->price){
        root->size++;
        parent = root;
        AddToTree(root->left, parent, name, price);
    }
    else
        cout << "Number is exist\n";
}

void ShowTree(Node* root, int p = -1) {
    if (root == NULL){
        return;
    }else {
        ShowTree(root->right,++p);
        if (!root->right)
        {
            for (int i = 0; i < p; i++){
                cout << " - ";
            }
            cout << " - NIL {BLACK}" <<endl;
        }
        for (int i = 0; i < p; i++){
            cout << " - ";
        }
        //cout << " NULL {BLACK}" <<endl;
        
        cout << root->name << " = " << root->price <<" ["<< root->size << "] ";
        //cout << root->price <<" ["<< root->size << "] ";
        if (root->color == RED){
            cout << "{RED}" <<endl;
        }else{
            cout << "{BLACK}" <<endl;
        }
        
        if (!root->left)
        {
            for (int i = 0; i < p; i++){
                cout << " - ";
            }
            cout << " - NIL {BLACK}" <<endl;
        }
        
        p--;
    }
    ShowTree(root->left, ++p);
}

Node* select_min(Node* root, int size){
    int r;
    if(root != NULL && root->left)
        r = root->left->size +1;
    else
        r = 1;
    if (size == r) return root;
    else{
        if (size<r) return select_min(root->left,size);
        else return select_min(root->right, size-r);
    }
}

Node* select_max(Node* root, int size){
    int r;
    if(root != NULL && root->right)
        r = root->right->size +1;
    else
        r = 1;
    if (size == r) return root;
    else{
        if (size<r) return select_max(root->right,size);
        else return select_max(root->left, size-r);
    }
}

void select(Node* root, string tmp, int size){
    if (root->size < size){
        cout << "Rank is bad :(" <<endl;
        return;
    }
    
    Node* s = NULL;
    if (tmp == "max"){
        s = select_max(root, size);
        cout << s->name << " - " << s->price <<endl;
    }else{
        s = select_min(root, size);
        cout << s->name << " - " << s->price <<endl;
    }
}

int main() {
    ifstream file("/Users/danial/Desktop/2 курс/Алгоритмы/alg_2/list.txt");
    if (!file) {
        cout << "Wrong filename :(" << endl;
        exit(1);
    }
    
    string Name;
    string Price;
    file >> Name >> Price;
    
    root = CreateTree(Name,Price);
    Node* parent = root;
    
    while (file >> Name) {
        file >> Price;
        AddToTree(root, parent, Name, Price);
        Node* parent = root;
    }
    
    ShowTree(root);
    cout << "----------------------------" <<endl;
    
    //    cout << "Input rank and max or min for searching: ";
    //    int size;
    //    string tmp;
    //    cin >> size >> tmp;
    //
    //    select(root, tmp, size);
    
    cout << "---------- TESTS -----------" <<endl;
    
    Node* test1 = CreateTree("apple", "24");
    Node* test2 = CreateTree("cucumber", "12");
    Node* test3 = CreateTree("cherry", "45");
    Node* test4 = CreateTree("watermelon", "55");
    
    vector<Node*> vec_node;
    
    vec_node.push_back(test1);
    vec_node.push_back(test2);
    vec_node.push_back(test3);
    vec_node.push_back(test4);
    
    TestCreateTree(vec_node);
    return 0;
}
