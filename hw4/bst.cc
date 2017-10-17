#include "bst.h"
#include <iostream>

template <typename K, typename V>
Bst<K,V>::Bst(TreeNode<K,V> * aNode){
	this->root = aNode;
}

template <typename K, typename V>
Bst<K,V>::~Bst() {
	delete this->root;
}

template <typename K, typename V>
TreeNode<K,V>* Bst<K,V>::getRoot(){
	return root;
}

template <typename K, typename V>
bool Bst<K,V>::isEmpty(){
	return this->root->isNull();
}

template <typename K, typename V>
int Bst<K,V>::height(){
	return root->height();
}

template <typename K, typename V>
void Bst<K,V>::preOrder(pfnv<K,V> visitor){
	root->preOrder(visitor);
}

template <typename K, typename V>
void Bst<K,V>::inOrder(pfnv<K,V> visitor){
	root->inOrder(visitor);
}

template <typename K, typename V>
void Bst<K,V>::postOrder(pfnv<K,V> visitor){
	root->postOrder(visitor);
}

template <typename K, typename V>
void Bst<K,V>::bstAdd(K aKey, V aValue){
	TreeNode<K,V>* foundNode = root->lookup(aKey);
	if( !foundNode->isNull() ){
		foundNode->value = aValue;
		return;
	}
	TreeNode<K,V>* newNode = new TreeNode<K,V>(aKey, aValue, foundNode->parent);
	if(foundNode->isRootNode()){
		delete root;
		root = newNode;
		return;
	}
	if(foundNode->parent->left == foundNode)
		foundNode->parent->left = newNode;
	else
		foundNode->parent->right = newNode;
	delete foundNode;
}

template <typename K, typename V>
void Bst<K,V>::add(K aKey, V aValue){
	bstAdd(aKey, aValue);
	TreeNode<K,V> *newRoot = root->lookup(aKey)->rebalanceAdd();
	if(newRoot != nullptr)
		root = newRoot;
}

template <typename K, typename V>
bool Bst<K,V>::includes(K aKey){
	return !root->lookup(aKey)->isNull();
}

template <typename K, typename V>
V Bst<K,V>::retrieve(K aKey){
	return root->lookup(aKey)->getValue();
}

template <typename K, typename V>
void Bst<K,V>::bstRemove(K aKey){
	TreeNode<K,V>* foundNode = root->lookup(aKey);
	TreeNode<K,V>* newRoot = foundNode->bstRemove();
	if(newRoot != nullptr)
		root = newRoot;
}

#include "bstConfig.h"
