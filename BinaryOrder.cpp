#include<iostream>
using namespace std;
#include<stack>
#include<queue>
template<class T>
struct BinaryTreeNode{
	T data;
	BinaryTreeNode<T>* _left;
	BinaryTreeNode<T>* _right;
	BinaryTreeNode(const T& x):data(x),_left(NULL),_right(NULL)
	{}
};

template<class T>
class BinaryTree{
	typedef BinaryTreeNode<T> Node;
	public:
	//无参的构造函数
	BinaryTree();
	BinaryTree(T* a,size_t size,const T& invalid){
		size_t index = 0;
		_root = _CreateBinaryTree(a,size,invalid,index);
	}
	
	//拷贝构造函数
	BinaryTree(const BinaryTree<T>& t)
	{
		_Copy(_root);	
	}

	//赋值重载
	BinaryTree operator=(BinaryTree<T>& t){
		swap(_root,t._root);
		return *this;
	}
	//析构函数
	~BinaryTree(){
		_Destroy(_root)	;
		_root = NULL;
	}
	//非递归层序遍历
	void levelOrder(){
		queue<Node*> q;
		q.push(_root);
		while(!q.empty()){
			Node* front = q.front();
			cout<<front->data<<" ";
			q.pop();
			if(front->_left)
			  q.push(front->_left);
			if(front->_right)
			  q.push(front->_right);
		}
		cout<<endl;
	}
	//递归前序
	void PreOrder_R(){
		_PreOrder_R(_root);
	cout<<endl;

	}

	//递归中序
	void MidOrder_R(){
		_MidOrder_R(_root);
		cout<<endl;
	}

	//递归后序
	void PostOrder_R(){
		_PostOrder_R(_root);
		cout<<endl;
	}

	//非递归前序
	void PreOrder(){
		
		Node* cur = _root;
		stack<Node*> s;
		while(cur||!s.empty()){
			while(cur){
				cout<<cur->data;	
				s.push(cur);
				cur = cur->_left;
			}	
			Node* top = s.top();
			s.pop();
			cur = top->_right;
		}
		cout<<endl;
	}

	//非递归中序
	void MidOrder(){
		Node* cur = _root;
		stack<Node*> s;
		while(cur||!s.empty()){
			while(cur){
				s.push(cur);
				cur = cur->_left;
			}
			Node* top = s.top();
			cout<<top->data;
			s.pop();
			cur = top->_right;
		}
		cout<<endl;
	}
	//非递归后序
	void PostOrder(){
		Node* cur = _root;
		Node* prev = NULL;
		stack<Node*> s;
		while(cur||!s.empty()){
			while(cur){
			s.push(cur);
			cur = cur->_left;
			}			
			Node* top = s.top();
			if(top->_right ==NULL || top->_right==prev){
				cout<<top->data;
				s.pop();
				prev = top;
			}
			else{
				cur = top->_right;	
			}
		}
	}
	//获得第K层的节点个数
	size_t GetKNode(){
		size_t k = 3;
		size_t size=_GetKNode(_root,k);
		return size;
	}
	//求叶子节点的个数
	size_t leafNode(){
		size_t size = 0;
		_leafNode(_root,size);
		return size;
	}
	//求两个节点的公共祖先
	Node CommonAncestor(Node* root,Node x1,Node x2){
		if(root==NULL||x1==NULL||x2==NULL)
		  return NULL;
		if(x1==root&&IsNodeInTree(root,x2))
		  return root;
		if(x2==root&&IsNodeInTree(root,x1))
		  return root;
		bool x1Inleft,x1Inright,x2Inleft,x2Inright;
		x1Inleft = IsNodeInTree(root->_left,x1);
		x2Inright = IsNodeInTree(root->_right,x2);
		if(x1Inleft&&x2Inright)
		  return root;
		x2Inleft = IsNodeInTree(root->_left,x2);
		x1Inright = IsNodeInTree(root->_right,x1);
		if(x1Inright&&x2Inleft)
		  return root;
		if(x1Inleft && x2Inleft)
		  return CommonAncestor(root->_left,x1,x2);
		if(x1Inright && x2Inright)
		  return CommonAncestor(root->_right,x1,x2);

	}
	size_t  Depth(){
		return _Depth(_root);	
	}
	//求二叉树中两个最远节点的距离
	void MaxLen(Node* root){
			if(root==NULL)
			  return 0;
			int left = Depth(root->_left);
			int right = Depth(root->_right);
			int maxlen = left+right;

			int leftMax = MaxLen(root->_left);
			int rightMax = MaxLen(root->_right);

			if(leftMax>rightMax)
			  return leftMax>maxlen?leftMax:maxlen;
			else
			  return rightMax>maxlen?rightMax:maxlen;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	private:
	Node* _CreateBinaryTree(T* a,size_t n,const T& invalid,size_t& index)
	{
		Node* root = NULL;
			if(a[index]!=invalid){
					root= new Node(a[index]);
					root->_left = _CreateBinaryTree(a,n,invalid,++index);
					root->_right = _CreateBinaryTree(a,n,invalid,++index);
			}
			return root;
	}
	void _Copy(BinaryTree<T>& root)
	{
			if(root==NULL)
			  return NULL;
			Node* newTree = new Node(root->data);
			newTree->_left = _Copy(root->_left);
			newTree->_right = _Copy(root->_right);
	}
	void _Destroy(Node* root){

		if(root == NULL)
		  return;
		_Destroy(root->_left);
		_Destroy(root->_right);
		
		delete root;
	}

	size_t _Depth(Node* root){
		if(root==NULL)
		  return 0;
		int left = _Depth(root->_left);
		int right = _Depth(root->_right);
		return left>right?left+1:right+1;
	}
	void _PreOrder_R(Node* root){
		if(root==NULL)
		  return;
		cout<<root->data;
		_PreOrder_R(root->_left);
		_PreOrder_R(root->_right);
	}
	void _MidOrder_R(Node* root){
		if(root==NULL)
		  return ;
		_MidOrder_R(root->_left);
		cout<<root->data;
		_MidOrder_R(root->_right);

	}
	void _PostOrder_R(Node* root){
		if(root==NULL)
		  return;
		_PreOrder_R(root->_left);
		_PreOrder_R(root->_right);
		cout<<root->data<<endl;
	}
	size_t _GetKNode(Node* root,size_t k){
		if(root==NULL)	
		  return 0;
		if(k==1)
		  return 1;
		return _GetKNode(root->_left,k-1)+_GetKNode(root->_right,k-1);
	}
	void _leafNode(Node* root,size_t& size){
		if(root==NULL)
		  return;
		if(root->_left==NULL&&root->_right==NULL)
		  size++;
		_leafNode(root->_left,size);
		_leafNode(root->_right,size);
	}
	bool IsNodeInTree(Node root,Node x){
		if(root==NULL)	
		  return false;
		if(root==x)
		  return true;
		if(IsNodeInTree(root->_left))
		  return true;
		return 	IsNodeInTree(root->_right);
	}
	Node* _root;
};

int main()
{
	int arr[]={ 1, 2, 3, '#', '#', 4, 7, '#', '#', '#', 5, 6, '#', '#', '#' };
	int n = sizeof(arr)/sizeof(int);
	BinaryTree<int> bt(arr,n,'#');
//	bt.PreOrder_R();
//	bt.MidOrder_R();
//	bt.PostOrder_R();
	//bt.PreOrder();
	//bt.MidOrder();
	//bt.PostOrder();
	//bt.levelOrder();
	//cout<<bt.GetKNode()<<endl;
	//cout<<bt.leafNode()<<endl;
	cout<<bt.Depth()<<endl;
	return 0;
}











