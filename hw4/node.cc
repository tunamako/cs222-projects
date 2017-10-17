#include "node.h"

// Constructor for leaf node.
template <typename K, typename V>
TreeNode<K,V>::TreeNode(){
}

template <typename K, typename V>
TreeNode<K,V>::TreeNode(K newKey, V newValue, TreeNode<K,V>* parent){
	this->key = newKey;
	this->value = newValue;
	this->left = new NullTreeNode<K,V>(this);
	this->right = new NullTreeNode<K,V>(this);
	this->parent = parent;
	this->black = false;
	
}

// Constructor for internal node.
template <typename K, typename V>
TreeNode<K,V>::TreeNode(K newKey, V newValue, TreeNode<K,V>* parent,TreeNode<K,V> *leftNode, TreeNode<K,V> *rightNode){
	this->key = newKey;
	this->value = newValue;
	this->parent = parent;
	this->black = false;
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
TreeNode<K,V>* TreeNode<K,V>::greatest(){
	if(right->isNull())
		return this;
	return right->greatest();
}












template <typename K, typename V>
TreeNode<K,V>* TreeNode<K,V>::rebalanceAdd(){
	if(isRootNode()){
		setBlack();
		return this;
	}
	else if(parent->isBlack())
		return nullptr;

	TreeNode<K,V> *grampa = parent->parent;
	TreeNode<K,V> *uncle = getUncle();
	if(uncle->isRed()){
		uncle->setBlack();
		parent->setBlack();
		grampa->setRed();
		return grampa->rebalanceAdd();
	}

}

template<typename K, typename V>
TreeNode<K,V>* TreeNode<K,V>::getUncle(){
	TreeNode<K,V> *grampa = parent->parent;
	return grampa->left == parent
		? grampa->right
		: grampa->left;
}


template <typename K, typename V>
TreeNode<K,V>* TreeNode<K,V>::rotateRight(){
	TreeNode<K,V> *grampa = parent->parent;
	if(parent->isRootNode()){
		rightHelper();
		return this;
	}
	else{
		if(parent->isLeftChild())
			grampa->left = this;
		else
			grampa->right = this;
		rightHelper();
		return nullptr;
	}
}

template <typename K, typename V>
void TreeNode<K,V>::rightHelper(){
	TreeNode<K,V> *grampa = parent->parent;
	parent->parent = this;
	parent->left = right;
	right->parent = parent;
	right = parent;
	parent = grampa;
}

template <typename K, typename V>
TreeNode<K,V>* TreeNode<K,V>::rotateLeft(){
	TreeNode<K,V> *grampa = parent->parent;
	if(parent->isRootNode()){
		leftHelper();
		return this;
	}
	else{
		if(parent->isLeftChild())
			grampa->left = this;
		else
			grampa->right = this;
		leftHelper();
		return nullptr;
	}
}

template <typename K, typename V>
void TreeNode<K,V>::leftHelper(){
	TreeNode<K,V> *grampa = parent->parent;
	parent->parent = this;
	parent->right = left;
	left->parent = parent;
	left = parent;
	parent = grampa;
}

template <typename K, typename V>
TreeNode<K,V>* TreeNode<K,V>::rotate(){
	return this->isLeftChild()
		? rotateRight()
		: rotateLeft();
}

template <typename K, typename V>
bool TreeNode<K,V>::isDirectGrandchild(){
       return (isLeftChild() && parent->isLeftChild()) || !(isLeftChild() && parent->isLeftChild());
}
template <typename K, typename V>
bool TreeNode<K,V>::isNull(){
	return false;
}

template <typename K, typename V>
bool TreeNode<K,V>::isLeafNode(){
	return left->isNull() && right->isNull();
}

template <typename K, typename V>
bool TreeNode<K,V>::hasTwoChildren(){
	return !(left->isNull() || right->isNull());
}

template <typename K, typename V>
bool TreeNode<K,V>::isRed(){
	return !this->black;
}

template <typename K, typename V>
bool TreeNode<K,V>::isBlack(){
	return this->black;
}

template <typename K, typename V>
void TreeNode<K,V>::setBlack(){
	black = true;
}

template <typename K, typename V>
void TreeNode<K,V>::setRed(){
	black = false;
}

template <typename K, typename V>
bool TreeNode<K,V>::isRootNode(){
	return parent == nullptr;
}

template <typename K, typename V>
bool TreeNode<K,V>::isLeftChild(){
	return this == parent->left;
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
TreeNode<K,V>* TreeNode<K,V>::lookup(K aKey){
	if(aKey == this->key)
		return this;
	return aKey < this->key
		? left->lookup(aKey)
		: right->lookup(aKey);
}

template <typename K, typename V>
TreeNode<K,V>* TreeNode<K,V>::bstRemove(){
	if(this->hasTwoChildren()){
		TreeNode<K,V>* glbNode = left->greatest();
		key = glbNode->key;
		value = glbNode->value;
		return glbNode->bstRemove();
	}
	if(this->isLeafNode()){
		NullTreeNode<K,V>* newNode = new NullTreeNode<K,V>(this->parent);
		if(this->isRootNode()){
			delete this;
			return newNode;
		}
		if(this == parent->left)
			parent->left = newNode;
		else
			parent->right = newNode;
		delete this;
		return nullptr;
	}
	// this has one child
	TreeNode<K,V>* childNode;
	if(left->isNull()){
		childNode = right;
		right = nullptr;
	}else{
		childNode = left;
		left = nullptr;
	}
	childNode->parent = parent;
	if(this->isRootNode()){
		delete this;
		return childNode;
	}
	if(parent->left == this){
		parent->left = childNode;
	}else{
		parent->right = childNode;
	}
	delete this;
	return nullptr;
}

template <typename K, typename V>
V TreeNode<K,V>::getValue(){
	return this->value;
}

template <typename K, typename V>
int NullTreeNode<K,V>::height(){
	return 0;
}

template <typename K, typename V>
void NullTreeNode<K,V>::preOrder(__attribute__((unused)) pfnv<K,V> visitor){
}

template <typename K, typename V>
void NullTreeNode<K,V>::inOrder(__attribute__((unused)) pfnv<K,V> visitor){
}

template <typename K, typename V>
void NullTreeNode<K,V>::postOrder(__attribute__((unused)) pfnv<K,V> visitor){
}

template <typename K, typename V>
NullTreeNode<K,V>::NullTreeNode(TreeNode<K,V>* parent){
	this->parent = parent;
	this->left = nullptr;
	this->right = nullptr;
	this->black = true;
}

template <typename K, typename V>
NullTreeNode<K,V>::~NullTreeNode(){
}

template <typename K, typename V>
bool NullTreeNode<K,V>::isNull(){
	return true;
}

template <typename K, typename V>
bool NullTreeNode<K,V>::isLeafNode(){
	return false;
}

template <typename K, typename V>
bool NullTreeNode<K,V>::hasTwoChildren(){
	return false;
}

template <typename K, typename V>
bool NullTreeNode<K,V>::isRed(){
	return false;
}

template <typename K, typename V>
bool NullTreeNode<K,V>::isBlack(){
	return true;
}

template <typename K, typename V>
void NullTreeNode<K,V>::setBlack(){
}

template <typename K, typename V>
void NullTreeNode<K,V>::setRed(){
	throw 8;
}

template <typename K, typename V>
TreeNode<K,V>* NullTreeNode<K,V>::lookup(__attribute__((unused)) K aKey){
	return this;
}

template <typename K, typename V>
TreeNode<K,V>* NullTreeNode<K,V>::bstRemove(){
	throw 7;
	return nullptr;
}

template <typename K, typename V>
V NullTreeNode<K,V>::getValue(){
	throw 9;
}

#include "nodeConfig.h"
