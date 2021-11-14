#include<iostream>
using namespace std;

static int SIZE = 10;

class Bucket{
    public:
        int key;
        Bucket *pointer = NULL;
};

Bucket *HashTable[10];

class Hash{
    public:

        int hashFunction(int k){
            return (k%SIZE);
        }

        void insert_key(int k){

            //Create New Bucket to be inserted in System

            Bucket *node = new Bucket();
            node->key = k;

            int HashIndex = hashFunction(k);

            /*
                Check
                if Given Index Empty then
                    store new bucket pointer in given index
                else
                    traverse through linked list at NULL insert the new bucket
            */

            if( HashTable[HashIndex] != NULL){

                Bucket *ptr = HashTable[HashIndex];

                while(ptr != NULL){

                    if(ptr->pointer == NULL){
                        ptr->pointer = node;
                        break;
                    }
                    ptr = ptr->pointer;
                }
            }
            else{
                HashTable[HashIndex] = node;
            }
        }

        void delete_key(int k){

            int HashIndex = hashFunction(k);

            /*
                Check if Index Value is not NULL then
                    Traverse through linked list
                        if pointer key is same key then
                            check location of bucket in linked list(start, end , mid)
                            based on than create logic and then bailout


            */

            if( HashTable[HashIndex] != NULL){

                Bucket *ptr = HashTable[HashIndex];
                Bucket *prev_ptr = HashTable[HashIndex];

                while(ptr != NULL){

                    if(ptr->key == k){

                        if(ptr->pointer == NULL)

                                if(prev_ptr == HashTable[HashIndex])
                                    HashTable[HashIndex] = NULL;

                                else{
                                    prev_ptr->pointer = NULL;
                                    delete(ptr);
                                    break;
                                }

                        else{
                                if(prev_ptr == HashTable[HashIndex]){

                                        HashTable[HashIndex] = ptr->pointer;
                                        delete(ptr);
                                        break;

                                }
                                else{
                                    prev_ptr->pointer = ptr->pointer;
                                    delete(ptr);
                                    break;
                                }
                        }
                    }

                    prev_ptr = ptr;
                    ptr = ptr->pointer;
                }
            }
            else
                cout<<"Element Doesn't Exist"<<endl;
        }

        void print(){
            cout<<"Hash Table : --> Chaining <--"<<endl;
            for(int i=0;i<SIZE;i++){
                cout<<i<<" - ";
                if(HashTable[i] != NULL){

                    Bucket *ptr=HashTable[i];
                    while(ptr != NULL){
                        cout<<ptr->key<<" ";
                        ptr = ptr->pointer;
                    }
                }
                else
                    cout<<"NULL";
                cout<<endl;
            }
        }

};

int main(){
    for(int i=0;i<SIZE;i++){
        HashTable[i] = NULL;
    }
    Hash obj;
    obj.insert_key(1);
    obj.insert_key(10);
    obj.insert_key(22);
    obj.insert_key(15);
    obj.insert_key(18);
    obj.insert_key(11);
    obj.insert_key(21);
    obj.delete_key(21);
    obj.print();


    return 0;
}
