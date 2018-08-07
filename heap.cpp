#include<iostream>
using namespace std;
#include<vector>

template<class T>
struct Less{
	bool operator()(const T& left,const T& right) const{
		return left<right;	
	}
};
template<class T>
struct Great{
	bool operator()(const T& left,const T& right) const{
		return left>right;	
	}
};

template<class T,class Compare=Great<T> >
class Heap{
	public:
		Heap(){	}
		//构造函数建堆
		Heap(T* a,size_t n){
			_a.reserve(n);
			for(int i = 0;i<n;i++){
				_a.push_back(a[i]);
			}
			for(int i=(n-2)/2;i>=0;i--){
				AdjustDown(i,n);	
			}
		}
		//该函数以仿函数判断是大堆还是小堆
		void AdjustDown(int root,size_t n){
			Compare cmp;
			int parent = root;
			int child = parent*2+1;
			while(child<n){
				if(child+1<n &&cmp( _a[child+1], _a[child]))
				  child++;
				if(cmp(_a[parent],_a[child])){
					swap(_a[parent],_a[child]);
					parent = child;
					child = parent*2+1;
				}
				else{
					break;	
				}
			}
		}
		void AdjustDown(T* a,int n,int root){
			int parent = root;
			int child = parent*2+1;
			while(child<n){
				if(child+1<n &&( a[child]< a[child+1]))
				  child++;
				if((a[child]>a[parent])){
					swap(a[parent],a[child]);
					parent = child;
					child = parent*2+1;
				}
				else{
					break;	
				}
			}

		}
		//求最大的前k个数，建小堆，保证堆顶是整个堆里最小堆的那个数
		void GetTopK(T* a,int n,int k){
			T* heap = new T[k];
			//先压入k个数进入heap
			for(int i = 0;i<k;i++){
				heap[i] = a[i];	
			}
			//将k个数调整为小堆
			for(int i=(k-2)/2;i>=0;i--){
				AdjustDown(heap,k,i);	
			}
			//再将原数组中剩余的数依次和heap中的堆顶进行比较，若大于堆顶，则进行交换
			for(int i = k;i<n;i++){
				if(a[i]>heap[0]){
					swap(a[i],heap[0]);
					AdjustDown(heap,k,0);
				}	
			}
			for(int i = 0;i<k;i++){
				cout<<heap[i]<<" ";
			}
			cout<<endl;
		}
		//实现堆排序
		void heapSort(T* a,int n){
			for(int i = (n-2)/2;i>=0;--i){
				AdjustDown(a,n,i);	
			}
			int end = n-1;
			while(end>0){
				swap(a[0],a[end]);
				AdjustDown(a,end,0);
				end--;
			}
		}
	private:
		vector<T> _a;
};
int main(){
	int a[] = { 10, 24, 23, 27, 18, 16, 17 };
	int n = sizeof(a)/sizeof(a[0]);
	Heap<int> h(a,n);
	//h.GetTopK(a,sizeof(a)/sizeof(a[0]),4);
	h.heapSort(a,n);
	for(int i = 0;i<n;i++){
		cout<<a[i]<<"  ";	
	}
	cout<<endl;
	return 0;
}
