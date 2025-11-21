#include<iostream>
#include<string>

using namespace std;

void printND(int n)
{
    for(int i=1;i<=n;i++)
    {
        cout<<"I"<<i;
        for(int j=i;j<=n;j++)
        {
            if(j!=n)
            {
                cout<<"U"<<j+1;
            }
        }
        if(i!=n){
            cout<<"+";

        }
        
    }
}


int main()
{
    printND(5);



    return 0;
}