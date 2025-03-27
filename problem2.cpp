#include <iostream>
#include <string>
using namespace std;
int checkHighestORder(int a,int b){
    if(a<b){
        return b;
    }
    return a;
}
int checkLowestORder(int a,int b){
    if(a>b){
        return b;
    }
    return a;
}

void printPolynomial(int* COoffeint, int Order) {
    bool firstTerm = true;
    int iterator = Order + 1;
    for (int i = iterator; i >= 0; i--) {
        

        if (COoffeint[i] != 0&&Order>=0) {
            if (!firstTerm) {
                if(COoffeint[i]>0){
                    cout << " + ";

                }else{
                    cout << " ";

                }
            }

            if (Order == 1) {
                if(COoffeint[i]==1){
                    cout<<"x";
                }else if(COoffeint[i]==-1){
                    cout<<"-x" << Order;
                }else{
                    cout << COoffeint[i] << "x";

                }
                
            } else if (Order == 0) {
                cout << COoffeint[i];
            } else if(Order<0){
                continue;
            }
            else {
                if(COoffeint[i]==1){
                    cout<<"x^" << Order;
                }else if(COoffeint[i]==-1){
                    cout<<"-x^" << Order;
                }
                else{
                    cout << COoffeint[i] << "x^" << Order;

                }
            }

            firstTerm = false;
        }
        Order--;
    }
    cout << " = " << COoffeint[0] << endl;
}

void inputPolynomial(int Order, int* &COoffeint,int **&equation) {
    int NumOfPoly = Order + 2;
    COoffeint = new int[NumOfPoly]; 
    equation = new int*[NumOfPoly];  
    for (int i = 0; i < NumOfPoly; i++) {
        equation[i] = new int[2]; 
        
        equation[i][0] = 0;  
        equation[i][1] = 0;
    }
    cout << "Enter polynomial: ";
    for (int i = 0; i < NumOfPoly; i++) {
        cin >> COoffeint[i];
        equation[i][0]=COoffeint[i];
        equation[i][1]=i;
    }
    cout << endl;
}

int main(){
    int Order1,Order2;
    cout<<"Order of first polynomial: ";
    cin>>Order1;
    int *COoffeint1;
    int **equations1=nullptr;
    inputPolynomial(Order1, COoffeint1,equations1);

    cout<<"Order of second polynomial: ";
    cin>>Order2;
    int *COoffeint2;
    int **equations2=nullptr;
    inputPolynomial(Order2,COoffeint2,equations2);
    
    cout << "First polynomial: ";
    printPolynomial(COoffeint1,Order1);

    cout<<"Second polynomial: ";
    printPolynomial(COoffeint2,Order2);
   

    cout<<"Sum of polynomials: ";
    int high=checkHighestORder(Order1,Order2);
    int *SumCoeff=new int[high+2];

    for (int i = high+1; i >= 0; i--) {

        
        if (i > Order1+1) {  
           
            SumCoeff[i] = equations2[i][0];
            continue;
        } 
        else if (i > Order2+1) {  
        
            SumCoeff[i] = equations1[i][0];
            continue;
        }
        else if(equations1[i][1]==equations2[i][1]){

            SumCoeff[i]=equations1[i][0]+equations2[i][0];
        }
    }
    printPolynomial(SumCoeff,high);
    cout << "Difference of polynomials: ";
    int *DiffCoeff = new int[high + 2];
    
    for (int i = high+1; i >= 0; i--) {  
     
    
        if (i > Order1+1) {  
           
            DiffCoeff[i] = equations2[i][0];

            continue;
        } 
        else if (i > Order2+1) {  
          
            DiffCoeff[i] = equations1[i][0];

            continue;
        }
        else if (equations1[i][1] == equations2[i][1]) {
    
            DiffCoeff[i] = equations2[i][0] - equations1[i][0];
        }
    
    }
    
    printPolynomial(DiffCoeff, high);
    
}