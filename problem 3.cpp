//Problem 3 Sorted linked list

#include <iostream>

using namespace std;

class Node{
public:
    int data;
    Node* next;
    Node(int value){
        data= value;
        next= nullptr; 
    }
};
class SortedLinkedList{
private:
    Node*head;
public:

    SortedLinkedList(){ 
        head=nullptr;
    }

    void insert (int value){
        Node* newElement= new Node(value);
        Node* temp= head;
        if (head==nullptr|| value<head->data) {
            newElement->next=head;
            head=newElement;
        }
        else{
            while (temp->next!=nullptr) {
                if (temp->next->data>=value) {
                    break;
                }
                temp=temp->next;
            }
                newElement->next=temp->next;
                temp->next=newElement;
        }
    }

    void remove(int index){
        int count=0;
        Node* temp= head;
        Node* del;

        while(temp){
            temp=temp->next;
            count++;
        }

        if(index>=count){
            cout<<"No change (out of bounds)\n";
            return;
        }

        if (index==0) {
            del=head;
            head=head->next;
            delete del;
            return;
        }

        temp=head;
        for (int i=0; i<index-1;i++) {
            temp = temp->next;
        }
        del=temp->next;
        temp->next = temp->next->next;
        delete del;

    }

   
    friend ostream& operator<<(ostream& os, const SortedLinkedList& list) {
        Node* temp=list.head;
        os << "[";
         while (temp) {
            os << temp->data;
            if(temp->next){
                os<<" , ";
            }
            temp = temp->next;
        }
        os << "]";
        return os;
    }

    int operator[](int index){
        int count=0;
        Node* temp= head;

        while(temp){
            if(count==index){
                return temp->data;
            }
            temp=temp->next;
            count++;
        }
        throw out_of_range("Index Out of Range");

    }

    ~SortedLinkedList(){ 
        Node* temp = head;
            while (temp) {
                Node* del = temp;
                temp = del->next;
                delete del;
            }
    }
};
int main()
{
    cout << "--Test Case 1\n";
    SortedLinkedList L;
    L.insert(5);   // L = [5]
    L.insert(8);   // L = [5, 8]
    L.insert(7);   // L = [5, 7, 8]
    L.insert(6);   // L = [5, 6, 7, 8]
    L.insert(6);   // L = [5, 6, 6, 7, 8]
    cout<<L<<endl;

    cout << "\n--Test Case 2\n";
     try {
            cout <<"Index 2: "<<L[2]<< endl; // Output: 6
            cout <<"Index 10: "<<L[10]<< endl;// Output: Index Out of Range
        } catch (const out_of_range&e){
            cout <<e.what()<<endl;
        }

    cout << "\n--Test Case 3\n";
    L.remove(0);       // L = [6, 6, 7, 8]
    cout <<L<<endl;;   // Output: [6, 6, 7, 8]
    L.remove(100);     // No change (out of bounds)
    cout << L<<endl;;  // Output: [6, 6, 7, 8]
    L.remove(2);       // L = [6, 6, 8]
    cout << L<<endl;   // Output: [6, 6, 8]
    L.remove(2);       // L = [6, 6]
    cout << L<<endl;   // Output: [6, 6]

    cout << "\n--Test Case 4\n";
    try{
        cout<<"Index 0: "<<L[0]<<endl; // Output: 6
        cout<<"Index 1: "<<L[1]<<endl; // Output: 6
        cout<<"Index 2: "<<L[2]<<endl; // Output: Index Out of Range
    }catch(const out_of_range&e){
        cout <<e.what()<<endl;
    }
    cout << "\n--Test Case 5\n";
    L.insert(6);   // L = [6, 6, 6]
    L.insert(0);   // L = [0, 6, 6, 6]
    L.insert(7);   // L = [0, 6, 6, 6, 7]
    L.insert(1);   // L = [0, 1, 6, 6, 6, 7]
    L.insert(3);   // L = [0, 1, 3, 6, 6, 6, 7]
    cout<<L<<endl;

    cout << "\n--Test Case 6\n";
    L.remove(3); //L = [0, 1, 3, 6, 6, 7]
    cout<<L<<endl; //Output:[0, 1, 3, 6, 6, 7]
    L.remove(4); //L = [0, 1, 3, 6, 7]
    cout<<L<<endl; //Output:[0, 1, 3, 6, 7]
    L.remove(3); //L = [0, 1, 3, 7]
    cout<<L<<endl; //Output:[0, 1, 3, 7]
    L.remove(50); //No change (out of bounds)
    cout<<L<<endl; //Output:[0, 1, 3, 7]

    cout << "\n--Test Case 7\n";
    try{
        cout<<"Index 8: "<<L[8]<<endl; // Output: Index Out of Range
    }catch(const out_of_range&e){
        cout <<e.what()<<endl;
    }
    try{
        cout<<"Index 1: "<<L[1]<<endl; // Output: 1
    }catch(const out_of_range&e){
        cout <<e.what()<<endl;
    }
    try{
        cout<<"Index 0: "<<L[0]<<endl; // Output: 0
    }catch(const out_of_range&e){
        cout <<e.what()<<endl;
    }

    cout << "\n--Test Case 8\n";
    SortedLinkedList L2;
    L2.insert(0);   // L2 = [0]
    L2.insert(3);   // L2 = [0, 3]
    L2.insert(2);   // L2 = [0, 2, 3]
    L2.insert(5);   // L2 = [0, 2, 3, 5]
    L2.insert(4);   // L2 = [0, 2, 3, 4, 5]
    cout << L2 << endl; // Output: [0, 2, 3, 4, 5]

    cout << "\n--Test Case 9\n";
    L2.remove(1);   // L2 = [0, 3, 4, 5]
    cout <<L2<< endl; // Output: [0, 3, 4, 5]
    L2.remove(3); // L2 = [0, 3, 4]
    cout <<L2<< endl; // Output: [0, 3, 4]
    L2.remove(100); // No change (out of bounds)
    cout << L2 << endl; // Output: [0, 3, 4]

    cout << "\n--Test Case 10\n";
    try{
        cout<<"Index 0: "<<L2[0]<<endl; // Output: 0
    }catch(const out_of_range&e){
        cout <<e.what()<<endl;
    }
    try{
        cout<<"Index 1: "<<L2[1]<<endl; // Output: 3
    }catch(const out_of_range&e){
        cout <<e.what()<<endl;
    }
    try{
        cout<<"Index 5: "<<L2[5]<<endl; // Output: Index Out of Range
    }catch(const out_of_range&e){
        cout <<e.what()<<endl;
    }
    cout << "\n--Test Case 11\n";
    SortedLinkedList L3;
    L3.insert(2);   // L3 = [2]
    L3.insert(4);   // L3 = [2, 4]
    L3.insert(1);   // L3 = [1, 2, 4]
    L3.insert(6);   // L3 = [1, 2, 4, 6]
    L3.insert(5);   // L3 = [1, 2, 4, 5, 6]
    cout << L3 << endl; // Output: [1, 2, 4, 5, 6]

    cout << "\n--Test Case 12\n";
    L3.remove(0);   // L3 = [2, 4, 5, 6]
    cout << L3 << endl; // Output: [2, 4, 5, 6]
    L3.remove(2);   // L3 = [2, 4, 6]
    cout << L3 << endl; // Output: [2, 4, 6]
    L3.remove(5);   // No change (out of bounds)
    cout << L3 << endl; // Output: [2, 4, 6]

    cout << "\n--Test Case 13\n";
    try {
        cout << "Index 1: " << L3[1] << endl; // Output: 4
        cout << "Index 4: " << L3[4] << endl; // Output: Index Out of Range
    } catch (const out_of_range& e) {
        cout << e.what() << endl;
    }

    cout << "\n--Test Case 14\n";
    SortedLinkedList L4;
    L4.insert(3);   // L4 = [3]
    L4.insert(7);   // L4 = [3, 7]
    L4.insert(2);   // L4 = [2, 3, 7]
    L4.insert(6);   // L4 = [2, 3, 6, 7]
    L4.insert(5);   // L4 = [2, 3, 5, 6, 7]
    cout << L4 << endl; // Output: [2, 3, 5, 6, 7]

    cout << "\n--Test Case 15\n";
    L4.remove(1);   // L4 = [2, 5, 6, 7]
    cout << L4 << endl; // Output: [2, 5, 6, 7]
    L4.remove(3);   // L4 = [2, 5, 6]
    cout << L4 << endl; // Output: [2, 5, 6]
    L4.remove(0);   // L4 = [5, 6]
    cout << L4 << endl; // Output: [5, 6]
    L4.remove(200);  // No change (out of bounds)
    cout << L4 << endl; // Output: [5, 6]

    cout << "\n--Test Case 16\n";
    try {
        cout << "Index 1: " << L4[1] << endl; // Output: 6
        cout << "Index 4: " << L4[4] << endl; // Output: Index Out of Range
    } catch (const out_of_range& e) {
        cout << e.what() << endl;
    }


    return 0;
}
