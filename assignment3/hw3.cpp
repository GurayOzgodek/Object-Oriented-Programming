#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

using namespace std;

class Items{

    struct node{
        string name;
        int count;
        float price;
        node *next; 
    };
    node *head;

    public:
        virtual void push(string, int, float);
        virtual void create();
};
void Items::create(){
    head = NULL;
}

void Items::push(string name, int count, float price){
    node *newNode = new node;
    newNode->name = name;
    newNode->count = count;
    newNode->price = price;
    if(!head){
        create();
        head = newNode;
        newNode->next = NULL;
    }
    else{
        newNode->next = head;
        head = newNode;
    }
}

class Type1 : public Items{

    public:
        virtual void push(string, int, float);
        virtual void create();
};

class Type2 : public Items{

    public:
        virtual void push(string, int, float);
        virtual void create();
};

class Type3 : public Items{

    public:
        virtual void push(string, int, float);
        virtual void create();
};

int main(){
    ifstream file("stock.txt");
    string word;
    char character;
    getline(file, word);
    while(!file.eof()){
        if(character == '\t'){
            cout << word;
            word = "";
        }
        else word = word + character;
    }
}