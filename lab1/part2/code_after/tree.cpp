//
//  tree.cpp
//  code_after
//
//  Created by Danial on 3/19/19.
//  Copyright © 2019 Danial. All rights reserved.
//

#include "tree.hpp"

Tree::Tree(){
    root = NULL;
    parent = NULL;
}

void Tree::Load(string nameOfFile){
    ifstream file(nameOfFile);
    if (!file) {
        cout << "Wrong filename :(" << endl;
        exit(1);
    }

    string Name;
    string Price;
    file >> Name >> Price;
    int Price_int = atoi(Price.c_str());

    CreateTree(Name,Price_int);

    while (file >> Name) {
        file >> Price;
        Price_int = atoi(Price.c_str());
        AddToTree(root,Name, Price_int);
    }
}

void Tree::CreateTree(const string& name,const int& price /*const int& data*/) {
    Node* root = new Node;
    root->name = name;
    root->price = price;
    root->left = root->right = NULL;
    root->color = BLACK;
    root->size = 1;
    this->root = root;
    this->parent = root;
}

void Tree::AddToTree(Node* &root, const string name, const int price /*const int& data*/) {
    if (!root) {
        root = new Node;
        root->price = price;
        root->name = name;
        root->size = 1;
        root->left = root->right = NULL;
        root->color = RED;
        root->parent = parent;

        //SetColor(root);
        return;
    }

    if (price > root->price) {
        root->size++;
        parent = root;
        AddToTree(root->right, name, price);
    }
    else if (price < root->price){
        root->size++;
        parent = root;
        AddToTree(root->left, name, price);
    }
    else
        cout << "Number is exist\n";
}

void Tree::RotateLeft(Node *x) {

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

void Tree::RotateRight(Node *x) {
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

void Tree::SetColor(Node* node) {

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

void Tree::ShowTree(Node* root, int counter /*= - 1*/) {
    if (root == NULL){
        return;
    }else {
        ShowTree(root->right,++counter);

        if (!root->right)
        {
            for (int i = 0; i < counter; i++){
                cout << " - ";

            }
            cout << " - NIL {BLACK}" <<endl;

        }

        for (int i = 0; i < counter; i++){
            cout << " - ";
        }

        cout << root->name << " = " << root->price << " ";

        if (root->color == RED){
            cout << "{RED}" <<endl;
        }else{
            cout << "{BLACK}" <<endl;
        }

        if (!root->left)
        {
            for (int i = 0; i < counter; i++){
                cout << " - ";
            }
            cout << " - NIL {BLACK}" <<endl;
        }

        counter--;
    }

    ShowTree(root->left, ++counter);
}

void Tree::Select(Node* root){
    
    cout << "\nInput rank and max or min for searching: ";
    int size;
    string tmp;
    cin >> size >> tmp;
    
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

Node* Tree::select_max(Node* root, int size){
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

Node* Tree::select_min(Node* root, int size){
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

///////////////////////////////////////////////////////////////////////////////////////////////

void Testing::Creating(){
    cout << "\n----------------------------" <<endl;
    cout << "---------- TESTS -----------" <<endl;
    cout << "----------------------------\n" <<endl;
    
    vector<Tree> vec_test;
    Tree a;
    int indexDataForAdd = 0;
    
    for (int i = 0; i < 4; i++) {
        a.CreateTree(testDataForCreate[i].first, testDataForCreate[i].second);
        vec_test.push_back(a);
    }
    
    TestCreateTree(vec_test);
    
    cout << "----------------------------\n" <<endl;
    
    for (int i = 0; i < 4; i++) {
        vec_test[i].AddToTree(vec_test[i].getRoot(), testDataForAdd[indexDataForAdd].first, testDataForAdd[indexDataForAdd].second);
        
        indexDataForAdd++;
        
        vec_test[i].AddToTree(vec_test[i].getRoot(), testDataForAdd[indexDataForAdd].first, testDataForAdd[indexDataForAdd].second);
        
        indexDataForAdd++;
    }
    
    TestAddToTree(vec_test);
    
      cout << "----------------------------\n" <<endl;
}

bool Testing::isValid_Create(Node* &node, const string& expectedName, const int& expectedPrice){
    if (node->right != NULL || node->left != NULL) {
        return false;
    }
    if (node->color != BLACK) {
        return false;
    }
    if (node->size != 1) {
        return false;
    }

    if (node->name != expectedName || node->price != expectedPrice) {
        return false;
    }

    return true;
}

void Testing::TestCreateTree(vector<Tree>& vec_node){
    bool allTestPassed = true;

    for (int i = 0; i < testDataForCreate.size(); i++) {
        if (!isValid_Create(vec_node[i].getRoot(),testDataForCreate[i].first,testDataForCreate[i].second)){
            allTestPassed = false;
            cout << "TestCreateTree["<< i+1 << "]" << " was failed\n" << endl;
        }else{
            cout << "TestCreateTree["<< i+1 << "]" << " was passed\n" << endl;
        }
    }
    cout << "########################################" <<endl;
    if (allTestPassed) {
        cout << "# All in all TestCreateTree was passed #" << endl;
    }else{
        cout << "# All in all TestCreateTree was failed #" << endl;
    }
    cout << "########################################" <<endl;
}

bool Testing::isValid_Add(Node* &node){
    if (node->right == NULL || node->left == NULL) {
        return false;
    }
    if (node->size == 1) {
        return false;
    }

    if (node->color == RED && (node->left->color != BLACK || node->right->color != BLACK)){
        return false;
    }

    if (node->price < node->left->price || node->price > node->right->price) {
        return false;
    }

    return true;
}

void Testing::TestAddToTree(vector<Tree>& vec_node){
    bool allTestPassed = true;

    for (int i = 0; i < vec_node.size(); i++) {
        if (!isValid_Add(vec_node[i].getRoot())){
            allTestPassed = false;
            cout << "TestAddToTree["<< i+1 << "]" << " was failed\n" << endl;
        }else{
            cout << "TestAddToTree["<< i+1 << "]" << " was passed\n" << endl;
        }
    }
    
    cout << "#######################################" <<endl;
    if (allTestPassed) {
        cout << "# All in all TestAddToTree was passed #" << endl;
    }else{
        cout << "# All in all TestAddToTree was failed #" << endl;
    }
     cout << "#######################################" <<endl;
}
