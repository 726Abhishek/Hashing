#include<iostream>
using namespace std;

class Node{
public:
    int data;
    Node *next;
};

Node *Head;

class Operations{
public:
    void _insert(int value){
        // Extra Node
        Node *block = new Node();
        block->data= value;
        block->next= NULL;

        //check if element is to inserted in last or in b/w
        Node *info = traverse(value);
        if(info->next == NULL){
            info->next = block;
        }
        else if(info->next != NULL && value > info->data){
            block->next = info->next;
            info->next = block;
        }
        else{
            block->next = Head;
            Head = block;
        }
    }

    void _delete(int value){
        Node *ptr = Head;
        Node *prev_ptr = Head;

        while(ptr != NULL){
           if(ptr->data == value){

                //condition to check if deleting node is starting or in between or last
                if(ptr == Head)
                    Head = ptr->next;

                else if(ptr->next == NULL)
                    prev_ptr->next = NULL;

                else
                    prev_ptr->next = ptr->next;

                delete(ptr);
                //cout<<"Deletion Successful!!"<<endl;
                break;
            }
         prev_ptr = ptr;
         ptr = ptr->next;
        }
        if(ptr == NULL)
            cout<<"Element not found"<<endl;

    }

    Node* traverse(int element){
        Node *ptr = Head;
        Node *prev_ptr = Head;
        while(ptr != NULL){
            if (ptr->data > element)
                 return prev_ptr;
            prev_ptr = ptr;
            ptr = ptr->next;
        }
        return prev_ptr;
    }

    void print(){
        Node *ptr=new Node();//duumy for head
        ptr = Head;
        cout<<"Linked List : ";
        while(ptr != NULL){
            cout<<ptr->data<<" ";
            ptr = ptr->next;
        }
        cout<<endl;
    }
};

//consider a list: 5,12,23,29

int main(){
    Node *First = new Node();
    Node *Second = new Node();
    Node *Last = new Node();

    Head = First;

    First->data=5;
    First->next=Second;

    Second->data=12;
    Second->next=Last;

    Last->data=23;
    Last->next = NULL;

    Operations obj;
    obj._insert(29);
    obj._insert(2);
    obj._insert(15);
    obj.print();
    obj._delete(2);
    obj._delete(12);
    obj._delete(29);
    obj.print();

return 0;
}
