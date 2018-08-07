#include<iostream>
using namespace std;
#include<stack>
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
	bt.PreOrder();
	bt.MidOrder();
	bt.PostOrder();
	return 0;
}











