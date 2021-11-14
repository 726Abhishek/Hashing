#include<iostream>
using namespace std;

class Node{
public:
    Node *prev;
    int data;
    Node *next;
};

Node *Head;

class Operations{
public:

    void _insert(int value){
        Node *block = new Node();
        block->prev=NULL;
        block->data = value;
        block->next=NULL;

        Node *info=traverse(value,1);
        if(info->prev == NULL && value < info->data ){
            block->next = Head;
            Head = block;
        }
        else if(info->next == NULL){
            block->prev = info;
            info->next = block;
        }
        else{
            block->prev = (info->next)->prev;
            block->next = info->next;
            info->next = block;
            (block->next)->prev = block;

        }
    }

    void _delete(int value){
        Node *elm = traverse(value,2);
        Node *blk;
        if(elm->prev == NULL){
            Head = elm->next;
        }
        else if(elm->next == NULL){
            (elm->prev)->next = NULL;
        }
        else{
            (elm->prev)->next = elm->next;
            (elm->next)->prev = elm->prev;
        }
        delete(elm);
    }

    Node* traverse(int element,int no){
        Node* ptr = Head;
        Node *prev_ptr;
        while(ptr != NULL){
            if(no == 1){
                if(ptr->data > element)
                    return ptr->prev;
            }
            else{
                if(ptr->data == element)
                    return ptr;
            }
            prev_ptr = ptr;
            ptr=ptr->next;
        }
        return prev_ptr;
    }

    void print(){
        Node *ptr = Head;
        while(ptr != NULL){
            cout<<ptr->data<<" ";
            ptr = ptr->next;
        }
        cout<<endl;
    }
};

int main(){
    Node *first=new Node();
    Node *second=new Node();
    Node *third =new Node();

    Head=first;

    first->prev = NULL;
    first->data = 12;
    first->next = second;

    second->prev=first;
    second->data=15;
    second->next=third;

    third->prev=second;
    third->data=20;
    third->next=NULL;

    Operations obj;
    obj.print();
    obj._insert(29);
    obj._insert(13);
    obj._insert(16);
    obj._insert(21);
    obj._insert(45);
    obj.print();
    obj._delete(15);
    obj.print();

    return 0;
}
