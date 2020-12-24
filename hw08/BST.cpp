#include "BST.h"

Node ** tree::infix(Node **arr,Node *ptr)
{
    if(ptr)
    {
        arr = infix(arr,ptr -> llink);
        *arr = ptr;
        arr += 1;
        arr = infix(arr,ptr -> rlink);
    }
    return arr;
}

void tree::create(int32_t number,int32_t price,int32_t amount)
{
    size_ += 1;
    if(root == nullptr)
    {
        root = new Node;
        root->number = number;
        root->price = price;
        root->amount = amount;
        root->rlink = nullptr;
        root->llink = nullptr;
        root->parent = nullptr;
    }
    else
    {
        Node *x;
        Node *y;
        Node *insert_node = new Node;
        insert_node->number = number;
        insert_node->price = price;
        insert_node->amount = amount;
        insert_node->rlink = nullptr;
        insert_node->llink = nullptr;
        insert_node->parent = nullptr;
        x = root;
        while(x != nullptr)                                  //search for a proper position
        {
            y = x;
            if(insert_node->number < x->number)
            {
                x = x->llink;
            }
            else if(insert_node->number > x->number)
            {
                x = x->rlink;
            }
        }                   
        insert_node->parent = y;                      //x == null and y is insert_node's parent
        if(y == nullptr)                              //put insert_node into BST
        {
            root = insert_node;
        }
        else if(insert_node->number < y->number)
        {
            y->llink = insert_node;
        }
        else if(insert_node->number > y->number)
        {
            y->rlink = insert_node;
        }
        else if (insert_node->number == y->number)
        {
            size_ -= 1;
            y->amount += insert_node->amount;
        }
    }
}

void tree::show()
{
    Node ** array = infix();
    for(int32_t i = 0 ; i < size_ ; i++)
    {
        cout << "product number: " << setw(3) << setfill('0') << array[i]->number << ",price: " << array[i]->price << ",amount: " << array[i]->amount << endl;
    }
    delete array;
}

Node* tree::search(int32_t number)
{
    Node *current;
    current = root;
    while(current != nullptr && number != current->number)  //current == null (no found)  number == current->number(found)
    {
        if(number < current->number)
        {
            current = current->llink;
        }
        else if(number > current->number)
        {
            current = current->rlink;
        }
    }
    if(current != nullptr)
    {
        return current;
    }
    else
    {
        return nullptr;
    }
}
Node* tree::insucc(Node *current)
{
    Node *tmp = current->rlink;;
    if(!tmp)
    {
        tmp = current;
        if(tmp->parent->llink == tmp)
        {
            return tmp->parent;
        }
        else
        {
            while(tmp->parent->rlink == tmp)
            {
                tmp = tmp->parent;
            }
            return tmp->parent;
        }
        
    }
    else
    {
        while(tmp->llink)
        {
            tmp = tmp->llink;
        }
        return tmp;
    }
}

void tree::remove(Node *current)
{
    size_ -= 1;
    Node *x;
    Node *y;
    x = root;
    while(current->number != x->number)                                  //search for a proper position
    {
        if(current->number < x->number)
        {
            x = x->llink;
        }
        else if(current->number > x->number)
        {
            x = x->rlink;
        }
    }
    if(x->rlink == nullptr && x->llink == nullptr)       //delete node is leaf node
    {
        if(x->parent->llink == x)
        {
            x->parent->llink = nullptr;
        }
        else if(x->parent->rlink == x)
        {
            x->parent->rlink = nullptr;
        }
        free(x);
    }
    else if(x->rlink != nullptr && x->llink == nullptr)  //delete node has one child
    {
        y = x;
        x = x->rlink;
        if(y->parent->rlink == y)
        {
            y->parent->rlink = x;
        }
        else if (y->parent->llink == y)
        {
            y->parent->llink = x;
        }
        free(y);
    }
    else if(x->rlink == nullptr && x->llink != nullptr)  //delete node has one child
    {
        y = x;
        x = x->llink;
        if(y->parent->rlink == y)
        {
            y->parent->rlink = x;
        }
        else if (y->parent->llink == y)
        {
            y->parent->llink = x;
        }
        free(y);
    }
    else if(x->rlink != nullptr && x->llink != nullptr)  //delete node has two children
    {
        y = x;
        x = x->llink;
        while(x->rlink != nullptr)       //find the rightest node
        {
            x = x->rlink;
        }
        int32_t tmpnum = x->number;
        int32_t tmpprice = x->price;
        int32_t tmpamount = x->amount;
        if(x->llink)
        {
            size_ += 1;
            remove(x);
        }
        else
        {
            if(x->parent->rlink == x)
            {
                x->parent->rlink = nullptr;
            }
            else if(x->parent->llink == x)
            {
                x->parent->llink = nullptr;
            }
            free(x);
        }
        y->number = tmpnum;
        y->price = tmpprice;
        y->amount = tmpamount;
    }
}

Node *tree::pricesearch()
{
    Node **array = infix();
    Node *maxprice = root;
    for(int32_t i = 0 ; i < size_ ; i++)
    {
        if(maxprice->price < array[i]->price)
        {
            maxprice = array[i];
        }
    }
    delete array;
    return maxprice;
}
Node **tree::levelorder()
{
    Node **array = new Node*[size_];
    array[0] = root;
    int32_t cnt = 1;
    for(int32_t i = 0 ; i < size_ ; i++)
    {
        if(array[i]->llink)
            array[cnt++] = array[i]->llink;
        if(array[i]->rlink)
            array[cnt++] = array[i]->rlink;
    }
    return array;
}