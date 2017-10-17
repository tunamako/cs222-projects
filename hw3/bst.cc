#include "bst.h"
#include <iostream>

template <typename K, typename V>
TreeNode<K,V>::TreeNode(){
}

// Constructor for leaf node.
template <typename K, typename V>
TreeNode<K,V>::TreeNode(K newKey, V newValue, TreeNode<K,V>* parent){
	this->key = newKey;
	this->value = newValue;
	this->left = new NullTreeNode<K,V>(this);
	this->right = new NullTreeNode<K,V>(this);
	this->parent = parent;
	
}

// Constructor for internal node.
template <typename K, typename V>
TreeNode<K,V>::TreeNode(K newKey, 
			V newValue, 
			TreeNode<K,V>* parent, 
			TreeNode<K,V> *leftNode, 
			TreeNode<K,V> *rightNode){
	this->key = newKey;
	this->value = newValue;
	this->parent = parent;
	if(leftNode == nullptr){
		this->left = new NullTreeNode<K,V>(this);
	} else {
		leftNode->parent = this;
		this->left = leftNode;
	}
	if(rightNode == nullptr){
		this->right = new NullTreeNode<K,V>(this);
	} else {
		rightNode->parent = this;
		this->right = rightNode;
	}
}

template <typename K, typename V>
TreeNode<K,V>::~TreeNode(){
	if(this->left != nullptr)
		delete this->left;
	if(this->right != nullptr)
		delete this->right;
}

template <typename K, typename V>
bool TreeNode<K,V>::isNull(){
	return false;
}

template <typename K, typename V>
int TreeNode<K,V>::height(){
	int leftHeight = left->height(); 
	int rightHeight= right->height();
	return leftHeight > rightHeight
		? leftHeight+1
		: rightHeight+1;
}

template <typename K, typename V>
void TreeNode<K,V>::preOrder(pfnv<K,V> visitor){
	visitor(this);
	left->preOrder(visitor);
	right->preOrder(visitor);
}

template <typename K, typename V>
void TreeNode<K,V>::inOrder(pfnv<K,V> visitor){
	left->inOrder(visitor);
	visitor(this);
	right->inOrder(visitor);
}

template <typename K, typename V>
void TreeNode<K,V>::postOrder(pfnv<K,V> visitor){
	left->postOrder(visitor);
	right->postOrder(visitor);
	visitor(this);
}

template <typename K, typename V>
void TreeNode<K,V>::add(K addKey, V addValue){
	this->value = addValue;
}

template <typename K, typename V>
TreeNode<K,V>* TreeNode<K,V>::lookup(K searchKey){
	if(searchKey == this->key)
		return this;
	return searchKey < this->key
		? left->lookup(searchKey)
		: right->lookup(searchKey);
}

template <typename K, typename V>
void TreeNode<K,V>::remove(){
	int children = this->childCount();

	if(children == 0){
		if(this->parent != nullptr){
			if(this->key < parent->key)
				parent->left = new NullTreeNode<K,V>(this);
			else
				parent->right = new NullTreeNode<K,V>(this);
		}
		delete this;
	}
	else if(children == 1){
		TreeNode<K,V> *child;
		if(left->isNull()){
			child = right;
			right = nullptr;
		}
		else{
			child = left;
			left = nullptr;
		}
		child->parent = parent;
		if(this->parent != nullptr){
			if(this->key < parent->key)
				parent->left = child;
			else
				parent->right = child;
		}
		delete this;
	}
	else if(children == 2){
		TreeNode<K,V> *replacement = right->leastOfGreatest();
		key = replacement->key;
		value = replacement->value;
		replacement->remove();
	}
}

template <typename K, typename V>
int TreeNode<K,V>::childCount(){
	int count = 0;
	if(!left->isNull())
		count++;
	if(!right->isNull())
		count++;
	return count;	
}

template <typename K, typename V>
TreeNode<K,V>* TreeNode<K,V>::leastOfGreatest(){
	return left->isNull()
		? this
		: left->leastOfGreatest();
}
  







template <typename K, typename V>
int NullTreeNode<K,V>::height(){
	return 0;
}

template <typename K, typename V>
void NullTreeNode<K,V>::preOrder(pfnv<K,V> visitor){
}

template <typename K, typename V>
void NullTreeNode<K,V>::inOrder(pfnv<K,V> visitor){
}

template <typename K, typename V>
void NullTreeNode<K,V>::postOrder(pfnv<K,V> visitor){
}

template <typename K, typename V>
NullTreeNode<K,V>::NullTreeNode(TreeNode<K,V>* parent){
	this->parent = parent;
	this->left = nullptr;
	this->right = nullptr;
}

template <typename K, typename V>
NullTreeNode<K,V>::~NullTreeNode(){
}

template <typename K, typename V>
bool NullTreeNode<K,V>::isNull(){
	return true;
}

template <typename K, typename V>
void NullTreeNode<K,V>::add(K addKey, V addValue){
	if(addKey < this->parent->key)
		this->parent->left = new TreeNode<K,V>(addKey, addValue, this->parent);
	else
		this->parent->right = new TreeNode<K,V>(addKey, addValue, this->parent);
	delete this;
}

template <typename K, typename V>
void NullTreeNode<K,V>::remove(){
	
}

template <typename K, typename V>
TreeNode<K,V>* NullTreeNode<K,V>::lookup(K key){
	return this;
}








template <typename K, typename V>
Bst<K,V>::Bst(TreeNode<K,V> * aNode){
	this->root = aNode;
}

template <typename K, typename V>
Bst<K,V>::~Bst() {
	delete this->root;
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
void Bst<K,V>::add(K addKey, V addValue){
	if(this->isEmpty()){
		delete root;
		root = new TreeNode<K,V>(addKey, addValue, nullptr);
	}
	else
		root->lookup(addKey)->add(addKey, addValue);
}

template <typename K, typename V>
bool Bst<K,V>::includes(K searchKey){
	return !root->lookup(searchKey)->isNull();
}

template <typename K, typename V>
V Bst<K,V>::retrieve(K searchKey){
	return root->lookup(searchKey)->value;
}

template <typename K, typename V>
void Bst<K,V>::remove(K deleteKey){
	if(this->isEmpty())
		return;
	TreeNode<K,V> *target = root->lookup(deleteKey);
	if(height() == 1){
		delete root;
		root = new NullTreeNode<K,V>(nullptr);
	}
	else if(target == root && root->childCount() == 1){
		TreeNode<K,V> *child;
		if(root->left->isNull()){
			child = root->right;
			root->right = nullptr;
		}
		else{
			child =root->left;
			root->left = nullptr;
		}
		child->parent = nullptr;
		delete root;
		root = child;
	}
	else{
		target->remove();
	}

}

#include "bstConfig.h"