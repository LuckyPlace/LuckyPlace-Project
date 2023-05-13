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
	void preorder()		//전위 순회(preorder)의 interface function
	{
		cout << "inorder: ";
		preorder(this->root);
		cout << endl;
	}
	void levelorder()		// BFS를 이용한 레벨 순회(levelorder traversal)
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
	int getCount()			// 트리 내에 있는 전체 노드 수 반환
	{
		return (this->empty()) ? 0 : getCount(this->root);
	}
	~BinaryTree()			// 소멸자를 재귀적으로 호출할 수는 없으므로 따로 worker function을 만든다
	{
		removeNodes(this->root);
	}
	int getLeafCount()
	{
		return (this->empty()) ? 0 : getLeafCount(this->root);
	}
	int getHeight()			// root 노드의 서브 트리의 최대 높이 +1이 트리의 높이
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
			cout << node->getData() << " ";		// 두번째 줄로 옮기면 중위 순회, 세번째로 옮기면 후위 순회
			preorder(node->getLeft());
			preorder(node->getRight());
		}
	}
	void removeNodes(BinaryNode<T1, T2>* node)	// 후위 순회를 응용한 소멸자
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
		
		int count = getCount(node->getLeft());		// 자기 왼쪽에 있는 노드들의 총 합
		count++;													// 자기 자신도 세야 하므로 1++
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
		if (key == node->getKey())			// 같은 key를 가진 node가 존재하면 value만 덮어쓴다.
			node->setData(value);
		else if (key < node->getKey())
		{
			if (node->getLeft() == nullptr)		// 현재 node의 키 값이 찾은 키 값보다 크고 node의 left가 비어있으면 insert

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
		else                            // key == node->getKey()인 경우
		{
			if (node->hasTwoChildren())
			{
				BinaryNode<T1, T2>* succ = leftmost(node->getRight());
				node->setKey(succ->getKey());
				node->setData(succ->getData());
				//여기서 successor는 child가 0개 아니면 1개이기 때문에 remove를 호출해도 여기로 안 오니까 쓸 수 있음
				succ = this->remove(node->getRight(), node, succ->getKey());
				//이렇게 안하면 트리가 끊김(교수님 설명)
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