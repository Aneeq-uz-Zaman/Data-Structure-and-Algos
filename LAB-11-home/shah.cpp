#include <iostream>
#include <limits>
using namespace std;

template<typename T>
class Node {
public:
    T data;
    Node<T>* left;
    Node<T>* right;

    Node(T value) {
        data = value;
        left = right = nullptr;
    }
};

template<typename T>
class BST {
private:
    Node<T>* root;

    Node<T>* FindMinHelper(Node<T>* root) {
        if (!root) return nullptr;  // Fix: check nullptr
        while (root->left != nullptr) {
            root = root->left;
        }
        return root;
    }
 
    Node<T>* findMaxHelper(Node<T>* root)
    {
    	if(!root)
    	{
    		return nullptr;
		}
		
		while(root->right!=nullptr)
		{
			root=root->right;
		}
		
		return root;
	}
	
    Node<T>* deleteNodeHelper(Node<T>* root, T value) {
        if (root == nullptr) {
            return root;
        }

        if (value < root->data) {
            root->left = deleteNodeHelper(root->left, value);  // Fix: call deleteNodeHelper
        }
        else if (value > root->data) {
            root->right = deleteNodeHelper(root->right, value);  // Fix: call deleteNodeHelper
        }
        else {
            if (root->left == nullptr && root->right == nullptr) {
                delete root;
                return nullptr;
            }
            else if (root->left == nullptr) {
                Node<T>* temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr) {
                Node<T>* temp = root->left;
                delete root;
                return temp;
            }

            Node<T>* temp = FindMinHelper(root->right);
            root->data = temp->data;
            root->right = deleteNodeHelper(root->right, temp->data);  // Fix: call deleteNodeHelper
        }
        return root;
    }

    void inOrderHelper(Node<T>* root) {
        if (root != nullptr) {
            inOrderHelper(root->left);
            cout << root->data << " ";
            inOrderHelper(root->right);
        }
    }

    void preOrderHelper(Node<T>* root) {
        if (root != nullptr) {
            cout << root->data << " ";
            preOrderHelper(root->left);
            preOrderHelper(root->right);
        }
    }

    void postOrderHelper(Node<T>* root) {
        if (root != nullptr) {
            postOrderHelper(root->left);
            postOrderHelper(root->right);
            cout << root->data << " ";
        }
    }

    bool isBSTHelper(Node<T>* root, T minVal, T maxVal) {
        if (root == nullptr)
            return true;

        if (root->data <= minVal || root->data >= maxVal)
            return false;

        return isBSTHelper(root->left, minVal, root->data) &&
               isBSTHelper(root->right, root->data, maxVal);
    }
    
    int totalNodesHelper(Node<T>* root)
    {
    	int count=0;
    	if(!root)
    	{
    		return 0;
		}
		
		count++;
		
      if(root->left)
      {
      	count+=totalNodesHelper(root->left);
	  }
    
     if(root->right)
     {
     	count+=totalNodesHelper(root->right);
    
	 }
    
    return count;
	}

   int sumNodesHelper(Node<T>*root)
   {
   	  int sum=0;
   	  if(!root)
		{
			return 0;
		}
		
		sum+=root->data;
		
		if(root->left)
		{
			sum+=sumNodesHelper(root->left);
		}
		
		if(root->right)
		{
			sum+=sumNodesHelper(root->right);
		}
		
		return sum;
   }
   
   bool searchHelper(Node<T>* root,T val)
   {
   	  if(!root)
   	  {
   	     return false;
      }
      
      if(root->data==val)
      {
      	return true;
	  }
	  
	  if(val>root->data)
	  {
	  	return searchHelper(root->right,val);
	  }
	  
	  if(val<root->data)
	  {
	  	return searchHelper(root->left,val);
	  }
  
   }
   
   Node<T>* successorHelper(Node<T>* root)
   {
   	  if(!root)
   	  {
   	  	 return nullptr;
	  }
	  
   if(!root->right)
	  {
	     return nullptr;
	  	
      }
    
    Node<T>* curr=root->right;
    while(curr->left)
    {
    	curr=curr->left;
	}
	
	return curr;
      
  }
  
    Node<T>* predecessorHelper(Node<T>* root)
    {
    	if(!root|| !root->left)
    	{
    		return nullptr;
		}
		
		Node<T>* curr=root->left;
		while(curr->right)
		{
			curr=curr->right;
		}
		
		return curr;
	}
	
	Node<T>* LCAHelper (Node<T>* root, T n1, T n2)
	{
	   if(!root)
	   {
	   	  return nullptr;
	   }
	   
	   if (!searchHelper(root, n1) || !searchHelper(root, n2))
        return nullptr;
	   
	   if(n1<root->data && n2<root->data)
	   {
	   	  return LCAHelper(root->left,n1,n2);
	   	  
		}
		
		if(n1>root->data && n2>root->data)
		{
			return LCAHelper(root->right,n1,n2);
		}
			
		return root;
	}
	
    void KthLargestHelper(Node<T>* root,int &k)
   {
   	 if(!root)
   	 {
   	 	return;
	 }
	 
	 	KthLargestHelper(root->right,k)
	 	
	 	k--;
	 	if(k==0)
	 	{
	 		cout<<root->data;
	 		return;
		}
		
		KthLargestHelper(root->left,k);
	
   }

    void KthSmallestHelper(Node<T>* root,int &k)
   {
   	 if(!root)
   	 {
   	 	return;
	 }
	 
	 	KthSmallestHelper(root->left,k)
	 	
	 	k--;
	 	if(k==0)
	 	{
	 		cout<<root->data;
	 		return;
		}
		
		KthSmallestHelper(root->right,k);
	
   }
   
   int minDiffHelper(Node<int>*root,int &prev, int &minDiff)
   {
   	 if(!root)
   	 {
   	 	return 0;
	 }
	 
	 minDiffHelper(root->left,prev,minDiff);
	 if(prev=-1)
	 {
	 	int diff=root->data-prev;
	 	if(diff<minDiff)
	 	{
	 		minDiff=diff;
		}
	 }
	 prev=root->data;
	 
	 minDiffHelper(root->right,prev,minDiff);
	 
	 return minDiff;
		 
   }
   
   int distanceFromRootHelper(Node<T>* root,T key)
   {
   	 if(!root)
   	 {
   	 	return -1;
	 }
	 
	 if(root->data==key)
	 {
	 	
	 	return 0;
	 }
	 
	 else if(key<root->data)
	 {
	 	int leftdist=distanceFromRootHelper(root->left,key);
	 	if(leftdist==-1)
	 	{
	 		return -1
		}
		
		else
		{
			return leftdist+1;
		}	 
	 }
	 
	 else
	 {
	 	int rightdist=distanceFromRootHelper(root->righht,key);
	 	if(rightdist==-1)
		 {
		 	return -1;
		 }
		 
		 else
		 {
		 	return leftdist+1;
		 }
	 } 
	 
   }
   
   int countInRangeHelper(Node<T>* root,int high,int low)
   {
   	 int count=0;
   	 if(!root)
   	  {
   	  	 return 0;
      }
      
      if (root->data < low)
        return countInRangeHelper(root->right, low, high);

   
     if (root->data > high)
        return countInRangeHelper(root->left, low, high);
     
	  count++;
	  
	  if(root->left)
	  {
	    count+=countInRangeHelper(root->left,high,low);
	  }
	  
	  if(root->right)
	  {
	  	count+=countInRangeHelper(root->right,high,low);
	  }
	  
      return count;
      
   }
  	
	public:

    void insert(T value) {
        Node<T>* newNode = new Node<T>(value);

        if (root == nullptr) {
            root = newNode;
            return;
        }

        Node<T>* current = root;
        Node<T>* parent = nullptr;

        while (current != nullptr) {
            parent = current;
            if (value < current->data)
                current = current->left;
            else
                current = current->right;
        }

        if (value < parent->data)
            parent->left = newNode;
        else
            parent->right = newNode;
    }

    bool search(T value) {
        
        return searchHelper(this->root,value);

    }

    void deleteMethod(T value) {
        root = deleteNodeHelper(root, value);  // Fix: call deleteNodeHelper
    }

    void inOrder() {
        inOrderHelper(root);
        cout << endl;
    }

    void preOrder() {
        preOrderHelper(root);
        cout << endl;
    }

    void postOrder() {
        postOrderHelper(root);
        cout << endl;
    }

    int totalNodes()
    {
    	return totalNodesHelper(this->root);
	}
	
	int sumNodes()
	{
		return sumNodesHelper(this->root);
	}
	
    bool isBST() {
        return isBSTHelper(this->root, numeric_limits<T>::min(), numeric_limits<T>::max());  // Fix: add min/max
    }
    
    Node<T>* sortedArrayToBST(int arr[], int start, int end) {
     if (start > end) 
	 {
		 return nullptr;
	 }

     int mid = start+end/ 2;
     Node<T>* root = new Node<T>(arr[mid]);
 
     root->left = sortedArrayToBST(arr, start, mid - 1);   // Left subtree
     root->right = sortedArrayToBST(arr, mid + 1, end);    // Right subtree

     return root;
   }

    Node<T>* successor()
    {
	  return successorHelper(this->root);
    }
 
    Node<T>* predecessor()
   {
 	  return predecessorHelper(this->root);
   }
   
   Node<T>* LCA(T n1,T n2)
   {
   	  return LCAHelper(this->root,n1,n2);
   }
 
   void kthLargest(int k)
   {
   	  kthLargestHelper(this->root,k);
   }
   
   int minDiff()
{
    int prev = -1;             
    int minDiffVal = INT_MAX;
    minDiffHelper(this->root, prev, minDiffVal);
    return minDiffVal;
}

int distanceFromRoot(T value)
{
   return distanceFromRootHelper(this->root,value);
}

  int distanceNodes(T n1,T n2)
  {
  	Node<T>*lca=LCA(n1,n2);
  	if(!lca)
  	{
  		return -1;
	  }
	  
	  int d1=distanceFromRootHelper(lca,n1);
	  int d2=distanceFromRootHelper(lca,n2);
	  
	  return d1+d2;
	   
	  }
 

};

int main() {
    BST<int> obj;
    obj.insert(5);
    obj.insert(3);
    obj.insert(7);
    obj.insert(2);
    obj.insert(4);
    obj.insert(6);
    obj.insert(8);

    obj.inOrder();
    obj.preOrder();
    obj.postOrder();

    obj.deleteMethod(2);
    obj.inOrder();

    cout << "Is BST? " << (obj.isBST() ? "Yes" : "No") << endl;

    return 0;
}