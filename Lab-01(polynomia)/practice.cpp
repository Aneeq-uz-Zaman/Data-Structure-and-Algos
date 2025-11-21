#include <cmath>
#include <iostream>
using namespace std;

class polynomial
{
private:
    double *coff;
    int size;


public:
    polynomial(){
        size = 1;
        coff = new double[size];
        coff[0] = 0;
    }
    polynomial(int s) : size(s)
    {
        coff = new double[size];
        for (int i = 0; i < size; i++)
        {
            coff[i]=0;
        }
    }
    polynomial(const polynomial &rhs)
    {
        size = rhs.size;
        coff = new double[size];
        for (int i = 0; i < size; i++)
        {
            coff[i] = rhs.coff[i];
        }
    }
    void printpoly()
    {
        for (int i = size-1; i >= 0; i--)
        {
            if(coff[i]==0)
            {
            }
            else{
            if(coff[i]<0 || i==size-1){
                cout << coff[i] << "x^" << i <<" ";
            }
            else{
                cout << "+ " << coff[i] << "x^" << i << " ";
            }

            }
            
            
        }
        cout << endl;
    }

    void addTerm(double coefficient, int power)
    {
        coff[power] = coefficient;
    }

    double getCoefficient(int power)
    {
        return coff[power];
    }

    int getDegree()
    {
        for(int i=size-1;i<0;i--)
        {
            if(i!=0)
            {
                return size;
            }
        }
        return 0;
        
    }
     
    double operator()(double x)
    {
        double result = 0;
        for (int i = 0; i < size; i++)
        {
            result += coff[i] * pow(x, i);
        }
        return result;
    }
    polynomial operator+(const polynomial &p)
    {
        int newS = max(size, p.size);
        polynomial r(newS);
        for (int i = 0; i < newS; i++)
        {
            r.coff[i] = coff[i] + p.coff[i];
        }
        return r;
    }
    polynomial operator-(const polynomial &p)
    {
        int newS = max(size, p.size);
        polynomial r(newS);
        for (int i = 0; i < newS; i++)
        {
            r.coff[i] = coff[i] - p.coff[i];
        }
        return r;
    }
    polynomial derivative()
    {
        polynomial result(size - 1);
        for (int i = 1; i < size; i++)
        {
            result.coff[i - 1] = coff[i] * i;
        }
        return result;
    }
    polynomial Antiderivative()
    {
        polynomial result(size + 1);
        for (int i = 0; i < size; i++)
        {
            result.coff[i + 1] = coff[i] / (i + 1);
        }
        return result;
    }
    void addToCoefficient(double coefficient, int power)
    {
        coff[power] += coefficient;
    }
    void clear()
    {
        for (int i = 0; i < size; i++)
        {
            coff[i]=0;
        }
    }
    void setCoefficient(double newCoefficient,int power)
    {
        coff[power] = newCoefficient;

    }
    friend ostream& operator<<(ostream &out, const polynomial &p)
    {
        for (int i = p.size-1; i >= 0; i--)
        {
            if(p.coff[i]<0 || i==p.size-1){
                out << p.coff[i] << "x^" << i <<" ";
            }
            else{
                out << "+ " << p.coff[i] << "x^" << i << " ";
            }
            
        }
        return out;
    }
    ~polynomial()
    {
        delete[] coff;
    }

};

int main()
{
    polynomial p1(2);
    p1.addTerm(4, 2);
    p1.addTerm(7, 1);

    p1.printpoly();

    cout << "Degree: " << p1.getDegree() << endl;
    cout << "Value at x=2: " << p1(2) << endl;
    polynomial p2(2);
    p2.addTerm(6, 1);
    p2.addTerm(2, 0);
    p2.printpoly();

    polynomial p3 = p1 + p2;
    cout<<endl<<endl<<endl;

    cout<<"Sum of Polynomials: ";
    p3.printpoly();
    cout<<"Derivative of p2: ";
    p2.derivative().printpoly();
    cout<<"Anti derivative:";
    p1.Antiderivative().printpoly();
    cout<<"+C";

    return 0;
}
