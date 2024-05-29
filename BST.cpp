/*
 * Thomas Florio
 * Leighanne Hsu
 * CISC 220, 011
 * 11/2/23
 */

#include "BST.hpp"
#include <iostream>
#include <cstdlib>
using namespace std;

BST::BST() {
	root = nullptr;  // empty BST (no root)
}

BST::BST(string title, string author, int yr, string pub, long long isbn, float rate) {
    root = new BSTNode(title, author, yr, pub, isbn, rate); // single item BST (root)
}

BST::~BST() {
	clearTree();
}

void BST::insert(string title, string author, int yr, string pub, long long isbn, float rate) {
    BSTNode *newNode = new BSTNode(title, author, yr, pub, isbn, rate); // node to be inserted
    BSTNode *current = root;
    if(root == nullptr) { // checks if tree is empty
        root = newNode;
        return;
    }
    while (current != nullptr) {
        if (*(newNode->book) >= *(current->book)) {
            if(current -> right == nullptr) { // if right child is nullptr, assigns node
                current->right = newNode;
                newNode->parent = current;
                setHeight(newNode);
                return;
            }
            else
            {
                current = current -> right; // right child so traverse
            }
        }
        else if(*(newNode->book) < *(current->book))
        {
            if(current -> left == nullptr) { // vice versa for left child
                current->left = newNode;
                newNode->parent = current;
                setHeight(newNode);
                return;
            }
            else
            {
                current = current -> left;
            }
        }
    }
}

BSTNode *BST::find(string title, string author) {
    BSTNode *temp = root;
    if(root == nullptr) // checks for empty BST (nothing to search)
    {
        return nullptr;
    }
    while (temp != nullptr)
    {
        if(author == temp -> book -> author && title == temp -> book -> title) //stop condition to check if books match
        {
            return temp;
        }
        else if (author == temp->book->author) //checks by title
        {
            if (title > temp->book->title)
            {
                temp = temp->right;
            }
            else if (title < temp->book->title)
            {
                temp = temp->left;
            }
        }
        else if (author >= temp->book->author) // traverse based on alphabetical order
        {
            temp = temp->right;
        }
        else if (author < temp->book->author)
        {
            temp = temp->left;
        }
    }
    return nullptr;
}

BSTNode *BST::find(string title, string author, BSTNode *start) {
    BSTNode *temp = start;
    if(root == nullptr) // see find function above except temp starts from a given subtree
    {
        return nullptr;
    }
    while (temp != nullptr)
    {
        if(author == temp -> book -> author && title == temp -> book -> title)
        {
            return temp;
        }
        else if (author == temp->book->author)
        {
            if (title > temp->book->title)
            {
                temp = temp->right;
            }
            else if (title < temp->book->title)
            {
                temp = temp->left;
            }
        }
        else if (author >= temp->book->author)
        {
            temp = temp->right;
        }
        else if (author < temp->book->author)
        {
            temp = temp->left;
        }
    }
    return nullptr;
}

void BST::printTreeIO() {
	if (root == nullptr) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl << "Printing In-Order:" << endl;
		printTreeIO(root);
	}
}

void BST::printTreeIO(BSTNode *node) {
    if (node == nullptr)
    {
        return;
    }
    printTreeIO(node->left);
    node->printNode(false);
    printTreeIO(node->right);
}

void BST::printTreePre() {
	if (root == nullptr) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl << "Printing Pre-Order:" << endl;
		printTreePre(root);
	}
}

void BST::printTreePre(BSTNode *node)
{
    if(node == nullptr)
    {
        return;
    }
    else
    {
        node ->printNode(false);
        printTreePre(node -> left);
        printTreePre(node -> right);
    }
}

void BST::printTreePost() {
	if (root == nullptr) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl<<"Printing Post-Order:" <<endl;
		printTreePost(root);
	}
}

void BST::printTreePost(BSTNode *node)
{
	if(node == nullptr)
    {
        return;
    }
    else
    {
        printTreePost(node -> left);
        printTreePost(node -> right);
        node -> printNode(false);
    }
}

void BST::clearTree() {
	if (root == NULL) {
		cout << "Tree already empty" << endl;
	}
	else {
		cout << endl << "Clearing Tree:" << endl;
		clearTree(root);
		root = NULL;
	}
}

void BST::clearTree(BSTNode *node) {
	if (node == NULL) {
		return;
	}
	else {
		clearTree(node->left);
		node->left = NULL;
		clearTree(node->right);
		node->right = NULL;
		node->printNode(true);
		delete node;
	}
}

bool BST::checkOut(string title, string author) {
    BSTNode *bookTarget = find(title, author);
    while(bookTarget != nullptr && bookTarget -> book -> checked_out)
    {
        bookTarget = find(title, author, bookTarget -> right); // traverses book by book that matches and stops when no more are assigned
    }
    if(bookTarget)
    {
        bookTarget -> book -> checked_out = true; // update flag
        return true;
    }
    return false;
}

bool BST::checkIn(string title, string author) { // opposite of check out
    BSTNode *bookTarget = find(title, author);
    while(bookTarget != nullptr && !bookTarget -> book -> checked_out)
    {
        bookTarget = find(title, author, bookTarget -> right);
    }
    if(bookTarget)
    {
        bookTarget -> book -> checked_out = false; // update flag
        return true;
    }
    return false;
}

void BST::updateRating(string title, string author, float newRating)
{
    BSTNode* targetBook = find(title, author);
    targetBook -> book -> rating = newRating;
    while(targetBook != nullptr)
    {
        targetBook -> book -> rating = newRating; // update rating
        targetBook = find(title, author, targetBook -> right); // traverse all copies
    }
}

BSTNode *BST::removeNoKids(BSTNode *node) {
    if(node == root) // check root
    {
        root = nullptr;
        return node;
    }
    else if(node -> parent -> left == node) // update parent if node with no kids is its left child
    {
        node -> parent -> left = nullptr;
    }
    else
    {
        node -> parent -> right = nullptr; // update parent if node with no kids is its right child
    }
    setHeight(node); //update height
    return node;
}

BSTNode *BST::removeOneKid(BSTNode *node, bool leftFlag)
{
    BSTNode* temp = node;
    if(node == root && leftFlag)
    {
        node -> left -> parent = nullptr;
        root = node -> left;
        node -> left = nullptr;
    }
    else if(node == root && !leftFlag)
    {
        node -> right -> parent = nullptr;
        root = node -> right;
        node -> right = nullptr;
    }
    else if(node -> parent -> left == node)
    {
        if(leftFlag)
        {
            node -> left -> parent = node -> parent; // rearrange pointers
            node -> parent -> left = node -> left;
        }
        else
        {
            node -> right -> parent = node -> parent;
            node -> parent -> left = node -> right;
        }
    }
    else
    {
        if(leftFlag)
        {
            node -> left -> parent = node -> parent; // rearrange pointers
            node -> parent -> right = node -> left;
        }
        else
        {
            node -> right -> parent = node -> parent;
            node -> parent -> right = node -> right;
        }
    }
    setHeight(node -> parent); // update height after removal
    return temp;
}

BSTNode *BST::remove(string title, string author)
{
    BSTNode* targetNode = find(title,author);
    if(targetNode != NULL)
    {
        BSTNode *tempNode = NULL;
        if(targetNode->right && targetNode->left) // two children
        {
            tempNode = targetNode->right;
            while(tempNode->left != NULL)
            {
                tempNode = tempNode->left; // take the next biggest node
            }
            BSTNode *copy = new BSTNode();
            copy->book = targetNode -> book;
            targetNode->book = tempNode->book; // copy contents over
            tempNode->printNode(true);
            if(tempNode->right != nullptr) // remove tempNode after data is copied
            {
                removeOneKid(tempNode, false);
            }
            else
            {
                removeNoKids(tempNode);
            }
            return copy;
        }
        if(targetNode->left) // one child
        {
            return removeOneKid(targetNode, true);
        }
        else if(targetNode->right)
        {
            return removeOneKid(targetNode, false);
        }
        return removeNoKids(targetNode); // no kids
    }
    return NULL;

}

void BST::setHeight(BSTNode *node)
{
    int leftHeight = 0;
    int rightHeight = 0;
    if(node == nullptr)
    {
        return;
    }
    if(node -> left == nullptr)
    {
        leftHeight = 0;
    }
    else
    {
        leftHeight = node -> left -> height; // set left height
    }
    if(node -> right == nullptr)
    {
        rightHeight = 0;
    }
    else
    {
        rightHeight = node -> right -> height; // set right height
    }
    if(rightHeight > leftHeight)
    {
        node -> height = rightHeight + 1; // checks balance
    }
    else
    {
        node -> height = leftHeight + 1; // checks balance
    }
    BST:setHeight(node -> parent);
}