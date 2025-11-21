#include <iostream>
#include <cmath>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

template <typename T>
class Binary_Tree_Array
{
protected:
    int height;
    int maxSize;
    T *data;
    bool *exists;
   


public:
    Binary_Tree_Array(int h = 0)
    {
        height = h;
        maxSize = pow(2, height) - 1;
        data = new T[maxSize];
        exists = new bool[maxSize];

        for (int i = 0; i < maxSize; i++)
            exists[i] = false;
    }

    ~Binary_Tree_Array()
    {
        delete[] data;
        delete[] exists;
    }

    int MaxSize() { 
        return maxSize;
     }
    int Height() { 
        return height; 
    }

    bool IsEmpty() { 
        return !exists[0];
     }


    void SetRoot(T val)
    {
        data[0] = val;
        exists[0] = true;
    }

    void SetLeftChild(T parent, T val)
    {
        for (int i = 0; i < maxSize; i++)
        {
            if (exists[i] && data[i] == parent)
            {
                int left = 2 * i + 1;
                if (left < maxSize)
                {
                    data[left] = val;
                    exists[left] = true;
                }
                return;
            }
        }
    }

    void SetRightChild(T parent, T val)
    {
        for (int i = 0; i < maxSize; i++)
        {
            if (exists[i] && data[i] == parent)
            {
                int right = 2 * i + 2;
                if (right < maxSize)
                {
                    data[right] = val;
                    exists[right] = true;
                }
                return;
            }
        }
    }

    T getParent(T node) const {
        int i;
        for(i=0;i<maxSize;i++)
        {
            if(data[i]==int(node) && exists[i]){
                break;
            }
                
        }
        if (i <= 1 || i > maxSize)
            throw out_of_range("No parent");
        return data[(i-1) / 2];
    }

    void displayan(T node)
    {
        int i;
        for(i=0;i<maxSize;i++)
        {
            if(data[i]==int(node) && exists[i]){
                break;
            }
                
        }
        if (i <= 1)
            throw out_of_range("No parent");
        cout<<"anxestors of "<<node<<":";
        while(i!=0)
        {
            i=(i-1) / 2;
            cout<<"ancestor :"<< data[i]<<endl;
            
        }
        

    }
    void heightOfTree() 
    {
        int h=0;
        for(int i=0;i<maxSize;i++)
        {
            if(exists[i])
            {
                int level=0;
                int j=i;
                while(j!=0)
                {
                    level++;
                    j=(j-1)/2;
                }
                if(level>h)
                    h=level;
            }
        }
        cout<< h+1;

    }

    void displayde(T node)
    {
        int i;
        for(i=0;i<maxSize;i++)
        {
            if(data[i]==int(node) && exists[i]){
                break;
            }
                
        }
        if (!exists[2*i+1])
            throw out_of_range("No left chil exist");
        cout<<"Left Descendent of"<<node<<":"<<data[2*i+1];
        if (!exists[2*i+2])
            throw out_of_range("No right chil exist");
        cout<<"Left Descendent of"<<node<<":"<<data[2*i+2];

    }
    void remove(T node)
    {
        int i;
        for(i=0;i<maxSize;i++)
        {
            if(data[i]==int(node) && exists[i]){
                break;
            }
                
        }

        if(i>=maxSize || !exists[i])
            return;
        remove(data[2*i+1]);
        remove(data[2*i+2]);
        exists[i]=false;
        
    }
    
    void PreOrder(int i = 0)
    {
        if (i >= maxSize || !exists[i])
            return;
        cout << data[i] << " ";
        PreOrder(2 * i + 1);
        PreOrder(2 * i + 2);
    }

    void InOrder(int i = 0)
    {
        if (i >= maxSize || !exists[i])
            return;
        InOrder(2 * i + 1);
        cout << data[i] << " ";
        InOrder(2 * i + 2);
    }

    void PostOrder(int i = 0)
    {
        if (i >= maxSize || !exists[i])
            return;
        PostOrder(2 * i + 1);
        PostOrder(2 * i + 2);
        cout << data[i] << " ";
    }

    void LevelOrder()
    {
        if (!exists[0])
            return;

        queue<int> q;
        q.push(0);
        while (!q.empty())
        {
            int i = q.front();
            q.pop();
            cout << data[i] << " ";

            int left = 2 * i + 1;
            int right = 2 * i + 2;

            if (left < maxSize && exists[left])
                q.push(left);
            if (right < maxSize && exists[right])
                q.push(right);
        }
    }

    void displayLevel(int levelNo) 
    {
        if (levelNo < 1 || levelNo > height)
            throw out_of_range("Invalid level number");

        int start = pow(2, levelNo - 1) - 1;
        int end = pow(2, levelNo) - 2;

        cout << "Nodes at level " << levelNo << ": ";
        for (int i = start; i <= end ; i++)
        {
            if (exists[i])
                cout << data[i] << " ";
        }

    }
    int findLevelOfNode(T node)
    {
        int i;
        for(i=0;i<maxSize;i++)
        {
            if(data[i]==int(node) && exists[i]){
                break;
            }
                
        }
        int j=1;
        while(i!=0)
        {
            j++;
            i=(i-1)/2;
        }
        return j;
        
    }
    
    


   
   

    


};


int main()
{
    Binary_Tree_Array<int> tree(3); // height = 3 -> maxSize = 7
    tree.SetRoot(1);
    tree.SetLeftChild(1, 2);
    tree.SetRightChild(1, 3);
    tree.SetLeftChild(2, 4);
    tree.SetRightChild(2, 5);
    tree.SetLeftChild(3, 6);
    tree.SetRightChild(3, 7);

    cout << "PreOrder: ";
    tree.PreOrder();
    cout << "\nInOrder: ";
    tree.InOrder();
    cout << "\nPostOrder: ";
    tree.PostOrder();
    cout << "\nLevelOrder: ";
    tree.LevelOrder();
    cout<<endl;
    int r=tree.getParent(5);
    cout<<"parent of 5:"<<r;
    cout<<endl;
    tree.displayan(4);
    cout<<endl;
    tree.displayde(3);
    cout<<endl;
    int x=tree.findLevelOfNode(4);
    cout<<"LEvel of 4:"<<x<<endl;
    tree.heightOfTree();
    cout<<endl;
    tree.displayLevel(2);
    cout<<endl;
    tree.remove(2);
    tree.LevelOrder();
    return 0;
}
