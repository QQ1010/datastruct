#include <iostream>
#include <fstream>
#include <cstdio>
#include <stdint.h>
#include <cstdlib>
#include <iomanip>
#include "BST.h"

using namespace std;
int32_t menu()
{
    system("cls");
    cout << "------- Menu -------" << endl;
    cout << "(1)    Search" << endl;
    cout << "(2)    Import" << endl;
    cout << "(3)    Delete" << endl;
    cout << "(4)    Export" << endl;
    cout << "(5)    List all product" << endl;
    cout << "------ additional option ------" << endl;
    cout << "(6)    Modify" << endl;
    cout << "(7)    Highest Price Search" << endl;
    cout << "(8)    Exit" << endl;
    cout << "please enter your option:";
    int32_t option = 0;
    cin >> option;
    system("cls");
    switch(option)
    {
        case 1:
            cout << "(1)    search" << endl;
            break;
        case 2:
            cout << "(2)    Import" << endl;
            break;
        case 3:
            cout << "(3)    Delete" << endl;
            break;
        case 4:
            cout << "(4)    Export" << endl;
            break;
        case 5:
            cout << "(5)    List all product" << endl;
            break;
        case 6:
            cout << "(6)    Modify" << endl;
            break;
        case 7:
            cout << "(7)    Highest Price Search" << endl;
            break;
        case 8:
            cout << "(8)    Exit" << endl;
            break;
        default:
            cout << "Worng Input." << endl;
            break;
    }
    return option;
}
void Search(tree product)
{
    int32_t number = 0;
    cout << "Please enter the product number:";
    cin >> number;
    Node *find;
    find = product.search(number);
    if(find)
    {
        cout << "product number: " << setw(3) << setfill('0') << find->number << endl;
        cout << "price: " << find->price << endl;
        cout << "amount: " << find->amount << endl;
        char skill;
        while(skill != 'R')
        {
            cout << "Press N -> Next || Press R -> END" << endl;
            cin >> skill;
            if(skill == 'N')
            {
                find = product.insucc(find);
                cout << "product number: " << setw(3) << setfill('0') << find->number << endl;
                cout << "price: " << find->price << endl;
                cout << "amount: " << find->amount << endl;
            }
            else if(skill != 'N' && skill != 'R')
            {
                cout << "Wrong Input.Please enter again." << endl;
            }
        }
    }
    else
    {
        cout << "The product you want to search does not exist in database." << endl;
        char a;
        cout << endl << "Enter any character to return menu..." << endl;
        cin >> a;
    }
}

void Import(tree product)
{
    int32_t number,amount;
    cout << "Please enter the product number: ";
    cin >> number;
    cout << "Please enter the product amount: ";
    cin >> amount;
    Node *tmp;
    tmp = product.search(number);
    if(tmp)
    {
        cout << "product number: " << setw(3) << setfill('0') << tmp->number << endl;
        cout << "price: " << tmp->price << endl;
        cout << "amount: " << tmp->amount << endl;
        cout << "=== inserted: ===" << endl;
        tmp->amount += amount;
        cout << "product number: " << setw(3) << setfill('0') << tmp->number << endl;
        cout << "price: " << tmp->price << endl;
        cout << "amount: " << tmp->amount << endl;
        char a;
        cout << endl << "Enter any character to return menu..." << endl;
        cin >> a;
    }
    else
    {
        int32_t price = 0;
        cout << "The product you want to insert is not in the database." << endl;
        cout << "Please input the price:";
        cin >> price;
        product.create(number,price,amount);
        Node *find;
        find = product.search(number);
        cout << "=== inserted: ===" << endl;
        cout << "product number: " << setw(3) << setfill('0') << find->number << endl;
        cout << "price: " << find->price << endl;
        cout << "amount: " << find->amount << endl;
        cout << "=== into the tree  ===" << endl;
        char a;
        cout << endl << "Enter any character to return menu..." << endl;
        cin >> a;
    }
}

void Delete(tree product)
{
    int32_t number;
    cout << "Please enter the product number you want to delete:";
    cin >> number;
    Node *find;
    find = product.search(number);
    if(find)
    {
        cout << "=== you have just deleted: === " << endl;
        cout << "product number: " << setw(3) << setfill('0') << find->number << endl;
        cout << "price: " << find->price << endl;
        cout << "amount: " << find->amount << endl;
        product.remove(find);
    }
    else
    {
        cout << "The product you want to delete is not exists in database." << endl;
    }
    char a;
    cout << endl << "Enter any character to return menu..." << endl;
    cin >> a;
}

void Export(tree product)
{
    int32_t number,amount;
    cout << "Please enter the product number you want to export:";
    cin >> number;
    cout << "Please enter thr product amount you want to export:";
    cin >> amount;
    Node *find;
    find = product.search(number);
    if(find)
    {
        if((find->amount - amount) >= 0)
        {
            cout << "=== you have just export: ===" << endl;
            cout << "product number: " << setw(3) << setfill('0') << find->number << endl;
            cout << "price: " << find->price << endl;
            cout << "amount: " << find->amount << endl;
            find->amount -= amount;
            cout << "=== remains ===" << endl;
            cout << "product number: " << setw(3) << setfill('0') << find->number << endl;
            cout << "price: " << find->price << endl;
            cout << "amount: " << find->amount << endl;
        }
        else
        {
            cout << "The product you want to export is not enough in database." << endl;
        }
        
    }
    else
    {
        cout << "The product you want to export is not exists in database." << endl;
    }
    char a;
    cout << endl << "Enter any character to return menu..." << endl;
    cin >> a;
}
void List(tree product)
{
    product.show();
    char a;
    cout << endl << "Enter any character to return menu..." << endl;
    cin >> a;
}

void Modify(tree product)
{
    int32_t number,newnum;
    cout << "Please enter the product number you want to Modify:";
    cin >> number;
    cout << "Please enter thr product new number you want to Modify:";
    cin >> newnum;
    Node *find;
    find = product.search(number);
    if(find)
    {
        cout << "=== you have just modified the product number of product " << setw(3) << setfill('0') << find->number << endl;
        cout << "=== the new data is ===" << endl;
        find->number = newnum;
        cout << "product number: " << setw(3) << setfill('0') << find->number << endl;
        cout << "price: " << find->price << endl;
        cout << "amount: " << find->amount << endl;
    }
    else
    {
        cout << "The product you want to modify the number is not exist in database." <<endl;
    }
    char a;
    cout << endl << "Enter any character to return menu..." << endl;
    cin >> a;
}

void highestprice(tree product)
{
    Node *find;
    find = product.pricesearch();
    cout << "The product number with highest price: " << setw(3) << setfill('0') << find->number << endl;
    char a;
    cout << endl << "Enter any character to return menu..." << endl;
    cin >> a;
}

void Exit(tree product)
{
    char ans;
    cout << "Do you want to save your change?(Y/N)" << endl;
    cin >> ans;
    if(ans == 'Y')
    {
        string filename;
        cout << "Please enter the output file name:";
        cin >> filename;
        ofstream file;
        file.open(filename);
        Node **array = new Node*[product.size()];
        array = product.levelorder();
        for(int32_t i = 0 ; i < product.size() ; i++)
        {
            file << setw(3) << setfill('0') << array[i]->number << " " << array[i]->price << " " << array[i]->amount << endl;
        }
    }
    cout << "Bye Bye~" << endl;
}

int main()
{
    string filename;
    ifstream file;
    cout << "please enter file name:";
    cin >> filename;
    file.open(filename);
    if(!file)
    {
        printf("There is no this file.\n");
        return 0;
    }
    tree product;
    int32_t num,price,amount;
    while(file >> num >> price >> amount)
    {
        product.create(num,price,amount);
    }
    file.close();
    while(1)
    {
        int32_t option = menu();
        switch(option)
        {
            case 1:
                Search(product);
                break;
            case 2:
                Import(product);
                break;
            case 3:
                Delete(product);
                break;
            case 4:
                Export(product);
                break;
            case 5:
                List(product);
                break;
            case 6:
                Modify(product);
                break;
            case 7:
                highestprice(product);
                break;
            case 8:
                Exit(product);
                return 0;
            default:
                break;
        }
    }
}
