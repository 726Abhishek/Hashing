#include<iostream>
#include<math.h>
#include<vector>
#include<string>

using namespace std;

static int Global_depth=1;
static int Local_Depth=1; //point to the max Local_Depth in overall buckets

class Bucket{
public:
    int Local_depth=1;
    int key1=-1;
    int key2=-1;
};

int SIZE = int(pow(2,Global_depth)+0.5);

vector<Bucket *> directory;
//vector<Bucket *> key_arr; //Store Bucket inserted into Hash Table

class Dynamic_Hashing
{
public:

    void Key_Insert(int key,int LD){

        Bucket *b1 = new Bucket();
        int index = Index_Calculator(key,LD);

        /*
            if Index location is empty then insert new bucket
            else
                check if current active address have empty slot for key
                    if true then Insert key
                    else
                        declare 'OVERFLOW'
                        *increase local_depth of bucket
                        *empty the slot for new element then

                            *check if Global Depth is lesser than Local Depth then
                                *increase Global Depth
                                *increase overall Local Depth
                                *Increase size of HashTable
                                *reinsert element of the bucket & key(due to which overflow occured)

                            else (in case local depth <= Global_depth)
                                *reinsert element of the bucket & key(due to which overflow occured)

        */

        if(directory[index] == NULL){
            b1->key1 = key;
            b1->Local_depth = LD;
            directory[index] = b1;
            //key_arr.push_back(b1);
        }
        else{
            b1 = directory[index];
            if(b1->key2 == -1)
                directory[index]->key2 = key;
            else{
                cout<<"OverFlow : "<<key<<" Present_key : "<<b1->key1<<" , "<<b1->key2<<endl;
                directory[index] = NULL;
                b1->Local_depth += 1;

                if(Global_depth < b1->Local_depth){
                    Local_Depth +=1;
                    Global_depth += 1;
                    create_Hashtable();
                    re_insert(b1,key);
                }
                else{
                    re_insert(b1,key);
                }
            }
        }
    }

    void Key_Delete(int key){

        for(int i=Local_Depth;i>0;i--){
            int index = Index_Calculator(key,Local_Depth);

            if(directory[index]->key1 == key){
                if(directory[index]->key2 == -1)
                    directory[index] = NULL;
                else{
                    directory[index]->key1 = directory[index]->key2;
                    directory[index]->key2 = -1;
                }
                break;
            }
            else if(directory[index]->key2 == key){
                directory[index]->key2 = -1;
                break;
            }
            else
                continue;
        }
    }

    void re_insert(Bucket *b2,int key){

        Key_Insert(b2->key1,b2->Local_depth);
        Key_Insert(b2->key2,b2->Local_depth);
        Key_Insert(key,b2->Local_depth);
        delete(b2);
    }

    void create_Hashtable();
    void print();
    int Index_Calculator(int,int);
};

//Responsible for Directory Expand
void Dynamic_Hashing::create_Hashtable(){

    int SIZE = int(pow(2,Global_depth)+0.5)-directory.size();
    for(int i=0;i<SIZE;i++){
        directory.push_back(NULL);
    }

}

//printing Dynamic Hash Table
void Dynamic_Hashing::print(){
        for(int i=0;i<directory.size();i++){
            if(directory[i] == NULL)
                cout<<i<<endl;
            else{
                Bucket *b2 = directory[i];
                cout<<i<<" --> "<<b2->Local_depth<<" , "<<b2->key1<<" , "<<b2->key2<<endl;
            }
        }
    }


/*
    Index_Calculator provide Index to directory by
        *Converting key into binary form and obtaining LSB-bits (from Global_depth Help)
        *Convert the obtained LSB bits into decimal wala Index obtained
*/

int Dynamic_Hashing::Index_Calculator(int num,int loop_count){
    int index=0;
    vector<int> binary;

    //Obtain LSB-bits
    while(loop_count != 0){
        binary.push_back(num%2);
        num = num/2;
        loop_count--;
    }

    //Convert LSB in binary (Index Obtained)
    for(int i=0;i<binary.size();i++){
        index += binary.at(i)*pow(2,i);
    }

    return index;
}

int main(){

    int arr[11] = {16,4,6,22,24,10,31,7,9,20,26};

    Dynamic_Hashing obj;
    obj.create_Hashtable();

    cout<<"Insertion Operation"<<endl;

    for(int i=0;i<11;i++){
        obj.Key_Insert(arr[i],Local_Depth);
    }
    obj.print();

    cout<<"Deletion Operation"<<endl;

    obj.Key_Delete(4);
    obj.Key_Delete(9);
    obj.Key_Delete(22);
    obj.print();

    return 0;
}
