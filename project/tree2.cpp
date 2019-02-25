//
//
//  Created by Danial on 2/18/19.
//  Copyright © 2019 Danial. All rights reserved.
//

#include <iostream>
#include <fstream>

using namespace std;

typedef struct Node {
    Node* left;
    Node* right;
    
    string name;
    string price;
}Node;

Node *root = NULL;

Node* CreateTree(const string& name,const string& price) {
    Node* root = new Node;
    root->name = name;
    root->price = price;
    root->left = root->right = NULL;
    
    return root;
}

Node* RightRotate(Node* root)
{
    Node* tmp = root->left;
    root->left = tmp->right;
    tmp->right = root;
    return tmp;
}

Node* LeftRotate(Node* root)
{
    Node* tmp = root->right;
    root->right = tmp->left;
    tmp->left = root;
    return tmp;
}

Node* Splay(string key, Node* root)
{
    if (!root)
        return NULL;
    Node header;
    header.left = header.right = NULL;
    Node* LeftTreeMax = &header;
    Node* RightTreeMin = &header;
    while (1)
    {
        if (key < root->price)
        {
            if (!root->left)
                break;
            if (key < root->left->price)
            {
                root = RightRotate(root);
                if (!root->left)
                    break;
            }
            RightTreeMin->left = root;
            RightTreeMin = RightTreeMin->left;
            root = root->left;
            RightTreeMin->left = NULL;
        }
        else if (key > root->price)
        {
            if (!root->right)
                break;
            if (key > root->right->price)
            {
                root = LeftRotate(root);
                if (!root->right)
                    break;
            }
            LeftTreeMax->right = root;
            LeftTreeMax = LeftTreeMax->right;
            root = root->right;
            LeftTreeMax->right = NULL;
        }
        else
            break;
    }
    
    LeftTreeMax->right = root->left;
    RightTreeMin->left = root->right;
    root->left = header.right;
    //cout << "(header.right)->price " <<(header.right)->price <<endl;
    root->right = header.left;
    //cout << "(header.left)->price " <<(header.left)->price <<endl;
    return root;
}

void AddToTree(Node* &root, const string& name, const string& price) {
    if (!root) {
        root = new Node;
        root->price = price;
        root->name = name;
        root->left = root->right = NULL;
        //root->parent = parent;
        return;
    }
    //root = Splay(price, root);
    if (price > root->price) {
        //parent = root;
        AddToTree(root->right, name, price);
    }
    else if (price < root->price){
        //parent = root;
        AddToTree(root->left, name, price);
    }
    else
        cout << "Number is exist\n";
    
}



void ShowTree(Node* root, int p = -1) {
    if (root == NULL){
        return;
    }else {
        ShowTree(root->right,++p);
        //        if (!root->right)
        //        {
        //            for (int i = 0; i < p; i++){
        //                cout << " - ";
        //            }
        //            cout << " - NIL " <<endl;
        //        }
        for (int i = 0; i < p; i++){
            cout << " - ";
        }
        
        //cout << root->name << " = " << root->price <<endl;
        cout << root->price <<endl;
        
        //        if (!root->left)
        //        {
        //            for (int i = 0; i < p; i++){
        //                cout << " - ";
        //            }
        //            cout << " - NIL" <<endl;
        //        }
        p--;
    }
    ShowTree(root->left, ++p);
    
}

Node* Find (string price, Node* root){
    return Splay(price, root);
}

void main_func(Node* &root){
    ifstream file("/Users/danial/Desktop/2 курс/Алгоритмы/alg_3/list.txt");
    if (!file) {
        cout << "Wrong filename :(" << endl;
        exit(1);
    }
    
    string Name;
    string Price;
    file >> Name >> Price;
    
    root = CreateTree(Name,Price);
    //Node* parent = root;
    //cout << "{ " << root->price << " }" <<endl;
    ShowTree(root);
    cout << "------------------------" <<endl;
    
    while (file >> Name) {
        file >> Price;
        AddToTree(root, Name, Price);
        root = Splay(Price, root);
        //Node* parent = root;
        cout << "{ " << root->price << " }" <<endl;
        ShowTree(root);
        cout << "------------------------" <<endl;
    }
    cout << "-------- RESULT --------" <<endl;
    ShowTree(root);
}

int main() {
    main_func(root);
    string tmp;
    cout << "price: ";
    cin >> tmp;
    root = Find(tmp,root);
    ShowTree(root);
    return 0;
}
