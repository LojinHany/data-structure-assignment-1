#include <iostream>
#include <string>
#include<fstream>
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

void inputPolynomial(int Order, int* &COoffeint,int **&equation,ifstream& file) {
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
        file >> COoffeint[i];
        cout<<COoffeint[i]<<" ";
        equation[i][0]=COoffeint[i];
        equation[i][1]=i;
    }
    cout << endl;
}

int main(){
    int Order1,Order2;
    cout << "\n--- First example ---" << endl;

    cout<<"Order of first polynomial: ";
    int *COoffeint1;
    int **equations1=nullptr;
    ifstream file("example1.txt");
    file>>Order1;
    cout<<Order1<<endl;
    inputPolynomial(Order1, COoffeint1,equations1,file);

    cout<<"Order of second polynomial: ";
   
    int *COoffeint2;
    int **equations2=nullptr;
    file>>Order2;
    cout<<Order2<<endl;
    inputPolynomial(Order2,COoffeint2,equations2,file);
    
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

    delete[] COoffeint1;
    delete[] COoffeint2;
    delete[] SumCoeff;
    delete[] DiffCoeff;

    // Now we will read from example2.txt and perform the same operations
    ifstream file2("example2.txt");
    if (!file2) {
        cerr << "Error opening the second file!" << endl;
        return 1;
    }

    // Read first polynomial order and coefficients from the second file
    file2 >> Order1;
    cout << "\n--- Second example ---" << endl;
    cout << "Order of first polynomial: " << Order1 << endl;
    int* COoffeint1_2;
    int** equations1_2 = nullptr;
    inputPolynomial(Order1, COoffeint1_2, equations1_2, file2);

    // Read second polynomial order and coefficients from the second file
    file2 >> Order2;
    cout << "Order of second polynomial: " << Order2 << endl;
    int* COoffeint2_2;
    int** equations2_2 = nullptr;
    inputPolynomial(Order2, COoffeint2_2, equations2_2, file2);
    
    file2.close();  // Close the file after reading

    // Print first polynomial
    cout << "First polynomial: ";
    printPolynomial(COoffeint1_2, Order1);

    // Print second polynomial
    cout << "Second polynomial: ";
    printPolynomial(COoffeint2_2, Order2);

    // Sum of polynomials
    cout << "Sum of polynomials: ";
    high = checkHighestORder(Order1, Order2);
    SumCoeff = new int[high + 2];
    
    for (int i = high + 1; i >= 0; i--) {
        if (i > Order1 + 1) {
            SumCoeff[i] = equations2_2[i][0];
            continue;
        } else if (i > Order2 + 1) {
            SumCoeff[i] = equations1_2[i][0];
            continue;
        } else if (equations1_2[i][1] == equations2_2[i][1]) {
            SumCoeff[i] = equations1_2[i][0] + equations2_2[i][0];
        }
    }
    printPolynomial(SumCoeff, high);

    // Difference of polynomials
    cout << "Difference of polynomials: ";
    DiffCoeff = new int[high + 2];

    for (int i = high + 1; i >= 0; i--) {
        if (i > Order1 + 1) {
            DiffCoeff[i] = equations2_2[i][0];
            continue;
        } else if (i > Order2 + 1) {
            DiffCoeff[i] = equations1_2[i][0];
            continue;
        } else if (equations1_2[i][1] == equations2_2[i][1]) {
            DiffCoeff[i] = equations2_2[i][0] - equations1_2[i][0];
        }
    }

    printPolynomial(DiffCoeff, high);

    // Clean up dynamically allocated memory
    delete[] COoffeint1_2;
    delete[] COoffeint2_2;
    delete[] SumCoeff;
    delete[] DiffCoeff;


    return 0;
}