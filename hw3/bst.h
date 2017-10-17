#ifndef BST_H
#define BST_H

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
	virtual int height();
	virtual void preOrder(pfnv<K,V> visitor);	
	virtual void inOrder(pfnv<K,V> visitor);	
	virtual void postOrder(pfnv<K,V> visitor);
	virtual void add(K, V);
	virtual TreeNode<K,V>* lookup(K);
	virtual void remove();
	int childCount();
	TreeNode<K,V>* leastOfGreatest();
};

template <typename K, typename V>
class NullTreeNode : public TreeNode<K,V> {
public:
	NullTreeNode(TreeNode<K,V>* parent);
	virtual ~NullTreeNode();
	virtual bool isNull();
	virtual int height();
	virtual void preOrder(pfnv<K,V> visitor);	
	virtual void inOrder(pfnv<K,V> visitor);	
	virtual void postOrder(pfnv<K,V> visitor);
	virtual void add(K, V);
	virtual void remove();
	virtual TreeNode<K,V>* lookup(K);
};

template <typename K, typename V>
class Bst{
private:
	
public:
	TreeNode<K,V> *root;
	Bst(TreeNode<K,V> *aNode);
	~Bst();
	bool isEmpty();
	int height(void);
	void preOrder(pfnv<K,V> visitor);
	void inOrder(pfnv<K,V> visitor);
	void postOrder(pfnv<K,V> visitor);
	void add(K, V);
	bool includes(K);
	V retrieve(K);
	void remove(K);
};
#endif
