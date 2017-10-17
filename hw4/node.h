#ifndef NODE_H
#define NODE_H

template <typename K, typename V> class TreeNode;

template <typename K, typename V>
using pfnv = void (*)(TreeNode<K,V> *node);

template <typename K, typename V>
class TreeNode{
public:
	TreeNode<K,V> *parent;
	TreeNode<K,V> *left;
	TreeNode<K,V> *right;
	K key;
	V value;
	bool black;
	TreeNode();
	TreeNode(K key, V newValue, TreeNode<K,V>* parent);
	TreeNode(
		K key, 
		V newValue, 
		TreeNode<K,V> *parent, 
		TreeNode<K,V> *leftNode, 
		TreeNode<K,V> *rightNode);
	virtual ~TreeNode();
	virtual bool isNull();
	virtual bool isLeafNode();
	virtual bool hasTwoChildren();
	virtual bool isRed();
	virtual bool isBlack();
	virtual void setBlack();
	virtual void setRed();
	virtual int height();
	virtual void preOrder(pfnv<K,V> visitor);	
	virtual void inOrder(pfnv<K,V> visitor);	
	virtual void postOrder(pfnv<K,V> visitor);	
	virtual TreeNode<K,V>* lookup(K aKey);
	virtual TreeNode<K,V>* bstRemove();
	virtual V getValue();
	bool isRootNode();
	TreeNode<K,V>* greatest();
	TreeNode<K,V>* rebalanceAdd();
	bool isDirectGrandchild();
	bool isLeftChild();
	TreeNode<K,V>* getUncle();
	// The following methods return a non-nullptr if
	// the node rotates into root position.
	TreeNode<K,V>* rotateRight();
	void rightHelper();
	TreeNode<K,V>* rotateLeft();
	void leftHelper();
	TreeNode<K,V>* rotate();
};

template <typename K, typename V>
class NullTreeNode : public TreeNode<K,V> {
public:
	NullTreeNode(TreeNode<K,V>* parent);
	virtual ~NullTreeNode();
	virtual bool isNull();
	virtual bool isLeafNode();
	virtual bool hasTwoChildren();
	virtual bool isRed();
	virtual bool isBlack();
	virtual void setBlack();
	virtual void setRed();
	virtual int height();
	virtual void preOrder(pfnv<K,V> visitor);	
	virtual void inOrder(pfnv<K,V> visitor);	
	virtual void postOrder(pfnv<K,V> visitor);	
	virtual TreeNode<K,V>* lookup(K aKey);
	virtual TreeNode<K,V>* bstRemove();
	virtual V getValue();
};

#endif

