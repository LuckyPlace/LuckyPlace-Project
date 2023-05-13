#include "BinaryNode.h"
#include <queue>

template <typename T1, typename T2>
class BinaryTree
{
protected:
	BinaryNode<T1, T2>* root;
public:
	BinaryTree()
	{
		this->root = nullptr;
	}
	bool empty()
	{
		if (this->root == nullptr)
			return true;
		else
			return false;
	}
	void setRoot(BinaryNode<T1, T2>* node)
	{
		this->root = node;
	}
	BinaryNode<T1, T2>* getRoot()
	{
		return this->root;
	}
	void preorder()		//���� ��ȸ(preorder)�� interface function
	{
		cout << "inorder: ";
		preorder(this->root);
		cout << endl;
	}
	void levelorder()		// BFS�� �̿��� ���� ��ȸ(levelorder traversal)
	{
		queue<BinaryNode<T1, T2>*> q;
		q.push(this->root);
		cout << "level_order: ";

		while (!q.empty())
		{
			BinaryNode<T1, T2>* cur_node = q.front();
			q.pop();
			if (cur_node != nullptr)
			{
				cout << cur_node->getData() << " ";
				q.push(cur_node->getLeft());
				q.push(cur_node->getRight());
			}
		}
		cout << endl;
	}
	int getCount()			// Ʈ�� ���� �ִ� ��ü ��� �� ��ȯ
	{
		return (this->empty()) ? 0 : getCount(this->root);
	}
	~BinaryTree()			// �Ҹ��ڸ� ��������� ȣ���� ���� �����Ƿ� ���� worker function�� �����
	{
		removeNodes(this->root);
	}
	int getLeafCount()
	{
		return (this->empty()) ? 0 : getLeafCount(this->root);
	}
	int getHeight()			// root ����� ���� Ʈ���� �ִ� ���� +1�� Ʈ���� ����
	{
		return (this->empty()) ? 0 : getHeight(this->root);
	}
/********************************************************************************/
/*		private member (worker) functions for implementation of recursion and encapsulation				*/
private:
	void preorder(BinaryNode<T1, T2>* node)		// worker function
	{
		if (node != nullptr)
		{
			cout << node->getData() << " ";		// �ι�° �ٷ� �ű�� ���� ��ȸ, ����°�� �ű�� ���� ��ȸ
			preorder(node->getLeft());
			preorder(node->getRight());
		}
	}
	void removeNodes(BinaryNode<T1, T2>* node)	// ���� ��ȸ�� ������ �Ҹ���
	{
		if(node != nullptr)
		{
			removeNodes(node->getLeft());
			removeNodes(node->getRight());
			delete node;
		}
	}
	int getCount(BinaryNode<T1, T2>* node)
	{
		if (node == nullptr)
			return 0;
		
		int count = getCount(node->getLeft());		// �ڱ� ���ʿ� �ִ� ������ �� ��
		count++;													// �ڱ� �ڽŵ� ���� �ϹǷ� 1++
		count += getCount(node->getRight());
		return count;
	}
	int getLeafCount(BinaryNode<T1, T2>* node)
	{
		if (node == nullptr)
			return 0;
		if (node->isLeaf())
			return 1;
		return getLeafCount(node->getLeft()) + getLeafCount(node->getRight());
	}
	int getHeight(BinaryNode<T1, T2>* node)
	{
		if (node == nullptr || node->isLeaf())
			return 0;
		int hLeft = getHeight(node->getLeft());
		int hRight = getHeight(node->getRight());
		return (hLeft > hRight) ? hLeft + 1 : hRight + 1;
	}
};

template<typename T1, typename T2>
class BinarySerarchTree : public  BinaryTree<T1, T2>
{
public:
	//if search succeeds, return the node's value;
	T2 search(T1 key)
	{
		BinaryNode<T1, T2>* node = search(this->root, key);
		if (node == nullptr)
			throw "error: out-of-key";
		return node->getData();
	}
	void insert(T1 key, T2 value)
	{
		if (this->empty())
			this->root = new BinaryNode<T1, T2>(key, value);
		else
			insert(this->root, key, value);
	}
	void remove(T1 key)
	{
		BinaryNode<T1, T2>* node = remove(this->root, nullptr, key);
		if (node == nullptr)
			throw "error: out-of-key";
		delete node;
	}
	BinaryNode<T1, T2>* leftmost(BinaryNode<T1, T2>* node)
	{
		while (node->getLeft() != nullptr)
			node = node->getLeft();
		return node;
	}
	BinaryNode<T1, T2>* rightmost(BinaryNode<T1, T2>* node)
	{
		while (node->getRight() != nullptr)
			node = node->getRight();
		return node;
	}
private:
	BinaryNode<T1, T2>* search(BinaryNode<T1, T2>* node, T1 key)
	{
		if (node == nullptr || key == node->getKey())
			return node;
		else if (key < node->getKey())
			return search(node->getLeft(), key);
		else
			return search(node->getRight(), key);
	}
	void insert(BinaryNode<T1, T2>* node, T1 key, T2 value)
	{
		if (key == node->getKey())			// ���� key�� ���� node�� �����ϸ� value�� �����.
			node->setData(value);
		else if (key < node->getKey())
		{
			if (node->getLeft() == nullptr)		// ���� node�� Ű ���� ã�� Ű ������ ũ�� node�� left�� ��������� insert

				node->setLeft(new BinaryNode<T1, T2>(key, value));
			else
				insert(node->getLeft(), key, value);
		}
		else
		{
			if (node->getRight() == nullptr)
				node->setRight(new BinaryNode<T1, T2>(key, value));
			else
				insert(node->getRight(), key, value);
		}
	}
	BinaryNode<T1, T2>* remove(BinaryNode<T1, T2>* node, BinaryNode<T1, T2>* parent, T1 key)
	{
		if (node == nullptr)
			return nullptr;
		if (key < node->getKey())
			return remove(node->getLeft(), node, key);
		else if (key > node->getKey())
			return remove(node->getRight(), node, key);
		else                            // key == node->getKey()�� ���
		{
			if (node->hasTwoChildren())
			{
				BinaryNode<T1, T2>* succ = leftmost(node->getRight());
				node->setKey(succ->getKey());
				node->setData(succ->getData());
				//���⼭ successor�� child�� 0�� �ƴϸ� 1���̱� ������ remove�� ȣ���ص� ����� �� ���ϱ� �� �� ����
				succ = this->remove(node->getRight(), node, succ->getKey());
				//�̷��� ���ϸ� Ʈ���� ����(������ ����)
				return succ;
			}
			else if (node->hasOneChild())
			{
				BinaryNode<T1, T2>* child = (node->getLeft() != nullptr) ? node->getLeft() : node->getRight();
				if (node == this->root)
					this->root = child;
				else
				{
					if (parent->getLeft() == node)
						parent->setLeft(child);
					else
						parent->setRight(child);
				}
				return node;
			}
			else if (node->isLeaf())
			{
				if (node == this->root)
					this->root = nullptr;
				else
				{
					if (parent->getLeft() == node)
						parent->setLeft(nullptr);
					else
						parent->setRight(nullptr);
				}
				return node;
			}
		}
	}
};

int main() 
{
	BinarySerarchTree<int, char> tree;
	BinaryNode<int, char>* d = new BinaryNode<int, char>(7, 'D', nullptr, nullptr);
	BinaryNode<int, char>* e = new BinaryNode<int, char>(9, 'E', nullptr, nullptr);
	BinaryNode<int, char>* b = new BinaryNode<int, char>(8, 'B', d, e);
	BinaryNode<int, char>* f = new BinaryNode<int, char>(11, 'F', nullptr, nullptr);
	BinaryNode<int, char>* c = new BinaryNode<int, char>(13, 'C', f, nullptr);
	BinaryNode<int, char>* a = new BinaryNode<int, char>(10,'A', b, c);
	tree.setRoot(a);
	cout << tree.search(9) << endl;

	return 0;
}