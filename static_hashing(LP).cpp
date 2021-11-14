#include<iostream>
using namespace std;

static int SIZE = 20;

class Page{
public:
    int key;
    int value;
};

Page *HashTable[20];

class Operations{
public:
    int Hashing(int value){
        return value%SIZE;
    };

    void _insert(int _key,int _value){

        Page *Hash_data = new Page();
        Hash_data->key = _key;
        Hash_data->value = _value;

        int HashIndex = Hashing(_key);

        for(int i=0;i<SIZE;i++){

            if(HashTable[HashIndex] == NULL){
                HashTable[HashIndex] = Hash_data;
                break;
                //return 1;
            }
            else{
                ++HashIndex;
                HashIndex %= SIZE;
            }
        }
        // logic for creating HashTable of double it size and further putting data in it and releasing previous array
        //return 0;
    }

    int _search(int key){
        int HashIndex = Hashing(key);
        for(int i=0;i<SIZE;i++){
            if(HashTable[HashIndex]->key == key){
                return HashIndex;
            }
            else{
                ++HashIndex;
                HashIndex %= SIZE;
            }
        }
        return -1;
    }

    void _delete(int key){
        int index = _search(key);
        if( index != -1)
            HashTable[index] = NULL;
        else
            cout<<"Key Doesn't Exist"<<endl;
    }

    void print(){
        cout<<"Hash_Table --> Linear Probing <-- "<<endl;
        cout<<"--------------------------------- "<<endl;
        cout<<"Index    KEY          Value"<<endl;
        for(int i=0;i<SIZE;i++){
            Page *data = HashTable[i];
            if(data != NULL)
                cout<<i<<"    "<<data->key<<"           "<<data->value<<endl;
            else
                continue;
        }
    }
};

int main(){

    for(int i=0;i<SIZE;i++){
        HashTable[i] = NULL;
    }

    Operations obj;
    obj._insert(1,12);
    obj._insert(10,22);
    obj._insert(22,45);
    obj._insert(15,11);
    obj._insert(18,102);
    obj._insert(11,121);
    obj._insert(21,121);
    obj._delete(21);
    obj.print();

    return 0;
}

