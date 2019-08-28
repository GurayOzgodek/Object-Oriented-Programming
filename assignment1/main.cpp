#include <iostream>
#include <fstream>
#include "Vector.h"
#include "Polynomial.h"
using namespace std;

int main(){
    ifstream read_vectors("Vector.txt");
    int vector_number;
    read_vectors >> vector_number;
    Vector *vectors[vector_number];
    int *arr = new int[20];
    int *new_arr = new int[20];
    int value , i=0 , j=0;
    while(read_vectors>>value){
        arr[j] = value;
        if(j==arr[0]){
            for(int k=0;k<j;k++){
                new_arr[k] = arr[k+1];
            }
            vectors[i] = new Vector(j , new_arr);
            i++;
            j=0;
        }
        else j++;
    }

    ifstream read_polynomials("Polynomial.txt");
    int polynom_number;
    read_polynomials>>polynom_number;
    Polynomial *polynomials[polynom_number];
    int *pol_arr = new int[20];
    int *new_pol_arr = new int[20];
    i=0;
    j=0;
    while(read_polynomials>>value){
        pol_arr[j] = value;
        if(j==pol_arr[0]+1){
            for(int k=0;k<j;k++){
                new_pol_arr[k] = pol_arr[k+1];
            }
            polynomials[i] = new Polynomial(j-1 , new_pol_arr);
           
            i++;
            j=0;
        }
        else j++;
    }

    cout << "Polynomial and Vector List Program!"<<endl;
    cout << "Polynomials and Vectors are read from text files!"<<endl<<endl;
    cout << "Possible actions:"<<endl;
    cout << "1. Print Polynomial and Vector lists"<<endl;
    cout << "2. Do a polynomial operation"<<endl;
    cout << "3. Do a vector operation"<<endl;
    cout << "4. Help: print possible actions"<<endl;
    cout << "0. Exit the program"<<endl<<endl<<endl;
    cout << "Enter an option: ";
    int election;
    cin >> election;
    while(election){
        switch (election){
            case 1:
                cout << "Vectors:"<<endl;
                for(int i=0;i<vector_number;i++){
                    cout << i+1<< ". "<<*(vectors[i]) << endl;
                }  
                cout << "Polynomials:"<<endl;
                for(int i=0;i<polynom_number;i++){
                    cout << i+1 << ". " << *(polynomials[i]) << endl;
                }
                break;
            case 2:
                cout << "Which polynomial operation would you like to do?((+:addition, *:multiplication):";
                int first , second;
                char operation;
                cin >> first >> operation >> second;
                if(operation == '*'){
                    Polynomial result = *(polynomials[first-1]) * *(polynomials[second-1]);
                    cout << *(polynomials[first-1]) << " * " << *(polynomials[second-1]) << " = " << result ;
                }
                if(operation=='+'){
                    Polynomial result = *(polynomials[first-1]) + *(polynomials[second-1]);
                    cout << *(polynomials[first-1]) << " + " << *(polynomials[second-1]) << " = " << result ;
                }
                break;
            case 3:
                cout << "Which vector operation would you like to do?((+:addition, *:scalar multiplication, .:dot product):"<<endl;
                cin >> first >> operation >> second;   
                if(operation == '*'){
                    Vector result = *(vectors[first-1]) * second;
                    cout << *(vectors[first-1]) << " * " << second << " = " << result;
                }    
                if(operation == '+'){
                    if(vectors[first-1]->get_size() == vectors[second-1]->get_size()){
                    Vector result = *(vectors[first-1]) + *(vectors[second-1]);
                    cout << *(vectors[first-1]) << " + " << *(vectors[second-1]) << " = " << result;
                    }
                    else cout << "Vectors are not at the same size! Please select another option."<<endl;
                }    
                if(operation == '.'){
                    if(vectors[first-1]->get_size() == vectors[second-1]->get_size()){
                    int result = *(vectors[first-1]) * *(vectors[second-1]);
                    cout << *(vectors[first-1]) << " + " << *(vectors[second-1]) << " = " << result;
                    }
                    else cout<< "Vectors are not at the same size! Please select another option."<< endl;
                }    
                break;
            case 4:
                cout << "1. Print Polynomial and Vector lists"<<endl;
                cout << "2. Do a polynomial operation"<<endl;
                cout << "3. Do a vector operation"<<endl;
                cout << "4. Help: print possible actions"<<endl;
                cout << "0. Exit the program"<<endl<<endl<<endl;
                break;
            case 0:
                return 0;
            default:
                cout << "Wrong option!"<<endl;
                break;
        }
        cout << "Enter an option: ";
        cin >> election;
    }
    return 0;
} 