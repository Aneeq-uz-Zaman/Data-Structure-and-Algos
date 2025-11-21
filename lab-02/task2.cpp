// Requirements: 
// Even though the multidimensional array is provided as a standard data object in C++, it is often useful 
// to define your own class for multidimensional arrays. This gives a more robust class that: 
// • Does require the index set in each dimension to start at any number (Є Set of Integers). 
// • Selects range of each dimension of the array during runtime. 
// • Provide mechanism to determine the size of array. 
// No specific data structure is being told to you for this task so intelligently do a proper structure 
// selection yourself and when feels confident then also discuss your structure with Instructor before 
// start coding. USING TEAMPLATES
// Sample Program Run 
// int dim-size[3]={5,3,10}; 
// NDArray arr(3, dim-size); 
// int index-set[3]={4,2,8}; 
// cout<<arr.calculateIndex( indexset )<<endl; 
// arr.setValue( index-set , val); 
// cout<<arr.getValue(index-set); 



#include<iostream>
#include<string>

using namespace std;
template<typename T>
class NDArray
{
    private:
        T* arr;
        int d;
    public:
        NDArray()
        {
            d=0;
            arr=nullptr;
        }
        NDArray(int n,T* a)
        {
            int s=1;
            for(int i=0;i<n;i++)
            {
                s=s*a[i];
            }
            d=n;
            arr= new T[s];
        }
        int calculateindex(T* a)
        {
            int r=0;
            int s=1;
            for(int i=d-1;i>=0;i--)
            {
                r=r+a[i]*s;
                s=s*a[i];
            }
            return r;


        }
        void setValue(T* a,T val)
        {
            int index=calculateindex(a);
            arr[index]=val;

        }
        T getValue(T* a)
        {
            int index=calculateindex(a);
            return arr[index];

        }
        ~NDArray()
        {
            delete[] arr;
        }


};
int main()
{
    int dim_size[3]={5,3,10}; 
    NDArray <int>arr(3, dim_size); 
    int index_set[3]={1,2,1}; 
    cout<<arr.calculateindex( index_set )<<endl; 
    arr.setValue( index_set , 78); 
    cout<<arr.getValue(index_set); 




    return 0;
}