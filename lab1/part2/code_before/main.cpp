//
//  main.cpp
//  code_before
//
//  Created by Danial on 3/19/19.
//  Copyright © 2019 Danial. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

typedef enum { BLACK, RED } nodeColor;

vector<pair<string, string>> testDataForCreate = {
    {"apple", "24"},
    {"cucumber", "12"},
    {"cherry", "45"},
    {"watermelon", "55"},
    
};

struct Node {
    
    Node* left;
    Node* right;
    Node* parent;
    
    nodeColor color;
    
    int size;
    
    string name;
    string price;
};

/////////////////////////////////////////=== TREE ===/////////////////////////////////////////

class Tree{
public:
    Node *root = NULL;
    Node *test1 = NULL;
    Node *test2 = NULL;
    Node *test3 = NULL;
    Node *test4 = NULL;
public:
    
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
            //cout << root->price;
            cout << root->name << " = " << root->price; // <<" ["<< root->size << "] ";
            //cout << root->price <<" ["<< root->size << "] ";
            if (root->color == RED){
                cout << " {RED} " <<endl;
            }else{
                cout << " {BLACK} " <<endl;
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
    
    void LoadFromFile(Tree &user, string NameOfFile){
        ifstream file(NameOfFile);
        if (!file) {
            cout << "Wrong filename :(" << endl;
            exit(1);
        }
        
        string Name;
        string Price;
        file >> Name >> Price;
        
        user.root = user.CreateTree(Name,Price);
        //    Node* parent = root;
        
        while (file >> Name) {
            file >> Price;
            Node* parent = user.root;
            user.AddToTree(user.root, parent, Name, Price, false);
        }
    }
    
    void select(Node* root, string& tmp, int size){
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
    
    void AddToTree(Node* &root, Node* &parent, const string& name, const string& price,bool test) {
        if (!root) {
            root = new Node;
            root->price = price;
            root->name = name;
            root->size = 1;
            
            root->left = root->right = NULL;
            root->color = RED;
            root->parent = parent;
            SetColor(root,test);
            return;
        }
        
        if (price > root->price) {
            root->size++;
            parent = root;
            AddToTree(root->right,parent, name, price,test);
        }
        else if (price < root->price){
            root->size++;
            parent = root;
            AddToTree(root->left, parent, name, price, test);
        }
        else
            cout << "Number is exist\n";
    }
    
protected:
    
    void SetColor(Node* node, bool test) {
        
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
        if (test == 0) root->color = BLACK;
        else{
            test1->color = BLACK;
            test2->color = BLACK;
            test3->color = BLACK;
            test4->color = BLACK;
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
};
/////////////////////////////////////////=== TESTING ===/////////////////////////////////////////

class Testing: public Tree{
public:
    
    void Test(){
        cout << "\n----------------------------" <<endl;
        cout << "---------- TESTS -----------" <<endl;
        cout << "----------------------------\n" <<endl;
        
        test1 = CreateTree("apple", "24");
        test2 = CreateTree("cucumber", "12");
        test3 = CreateTree("cherry", "45");
        test4 = CreateTree("watermelon", "55");
        
        Node* parent1 = test1;
        Node* parent2 = test2;
        Node* parent3 = test3;
        Node* parent4 = test4;
        
        vector<Node*> vec_node_create;
        
        vec_node_create.push_back(test1);
        vec_node_create.push_back(test2);
        vec_node_create.push_back(test3);
        vec_node_create.push_back(test4);
        
        TestCreateTree(vec_node_create);
        cout << "----------------------------\n" <<endl;
        
        AddToTree(test1, parent1, "a", "23", true);
        AddToTree(test1, parent1, "a", "25", 1);
        AddToTree(test2, parent2, "b", "11", 1);
        AddToTree(test2, parent2, "b", "13", 1);
        AddToTree(test3, parent3, "c", "44", 1);
        AddToTree(test3, parent3, "c", "46", 1);
        AddToTree(test4, parent4, "d", "54", 1);
        AddToTree(test4, parent4, "d", "58", 1);
        
        TestAddToTree(vec_node_create);
        cout << "----------------------------\n" <<endl;
    }
    
private:
    bool isValid_Create(Node* &node, const string& expectedName, const string& expectedPrice) {
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
        
        for (int i = 0; i < testDataForCreate.size(); i++) {
            if (!isValid_Create(vec_node[i],testDataForCreate[i].first,testDataForCreate[i].second)){
                allTestPassed = false;
                cout << "TestCreateTree["<< i+1 << "]" << " was failed\n" << endl;
            }else{
                cout << "TestCreateTree["<< i+1 << "]" << " was passed\n" << endl;
            }
        }
        
        if (allTestPassed) {
            cout << "All in all TestCreateTree was passed\n" << endl;
        }else{
            cout << "All in all TestCreateTree was failed\n" << endl;
        }
    }
    
    bool isValid_Add(Node* &node) {
        //static data
        if (node->right == NULL || node->left == NULL) {
            return false;
        }
        if (node->size == 1) {
            return false;
        }
        
        if (node->color == RED && (node->left->color != BLACK || node->right->color != BLACK)){
            return false;
        }
        
        //dynamic data
        if (node->price < node->left->price || node->price > node->right->price) {
            return false;
        }
        
        return true;
    }
    
    void TestAddToTree(vector<Node*>& vec_node){
        bool allTestPassed = true;
        
        for (int i = 0; i < vec_node.size(); i++) {
            if (!isValid_Add(vec_node[i])){
                allTestPassed = false;
                cout << "TestAddToTree["<< i+1 << "]" << " was failed\n" << endl;
            }else{
                cout << "TestAddToTree["<< i+1 << "]" << " was passed\n" << endl;
            }
        }
        
        if (allTestPassed) {
            cout << "All in all TestAddToTree was passed\n" << endl;
        }else{
            cout << "All in all TestAddToTree was failed\n" << endl;
        }
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    Testing test;
    test.Test();
    
    Tree user;
    user.LoadFromFile(user,"list.txt");
    user.ShowTree(user.root);
    
    cout << "\nInput rank and max or min for searching: ";
    int size;
    string tmp;
    cin >> size >> tmp;
    
    user.select(user.root,tmp, size);
    
    return 0;
}
