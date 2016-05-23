
//  Created by Sadman Ahmed on 10/11/15.
//  Copyright © 2015 Sadman Ahmed. All rights reserved.
//


#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<iomanip>
#include<fstream>
#include<string>


using namespace std;



/*
 * Node Declaration
 */
struct node
{
    string info;
    int ID;
    node *next;
}*start;

/*
 * Class Declaration
 */
class List
{
public:
    node* create_node(int,string);
    void insert_begin(string);
    void delete_pos(int);
    void sort();
    void search();
    int dsearch();
    void reverse();
    void display();
    void insert_file(string);
    void delete_file(int);
    void sortfile();
    void searchfile(string);
    int dsearchfile(string);
    void reversefile();
    void displayfile();
    List()
    {
        start = NULL;
    }
};
int id=0;

int main()
{
    int nodes, element, position, i;
    string name;
    string choice;
    string cmd;
    string entry;
    string path;
    int dcnt = 0;
    List sl;
    start = NULL;
    
    
    do
    {
        cout<<endl<<"   ADDRESS BOOK   "<<endl;
        cout<<endl<<"------------------"<<endl;
        cout<<endl<<"AVAILABLE COMMANDS"<<endl;
        cout<<endl<<"------------------"<<endl;
        cout<<"add<name>"<<endl;
        cout<<"search<name>"<<endl;
        cout<<"remove<name>"<<endl;
        cout<<"print"<<endl;
        cout<<"file <path>"<<endl;
        cout<<"exit"<<endl;
        cout<<endl;
        
        cout<<"CMD> ";
        
        cin>>choice;
        
            if(choice == "add" || choice == "ADD")
            {
                cin>>name;
                id++;
                sl.insert_begin(name);
                cout<<endl;
                sl.sort();
            }
        
            else if(choice == "remove" || choice == "REMOVE")
            {
                dcnt = sl.dsearch();
            
                sl.delete_pos(dcnt);
            }
        
            else if(choice == "search" || choice == "SEARCH")
            {
                cout<<endl;
                sl.search();
                cout<<endl;
            }
        
            else if(choice == "print" || choice == "PRINT")
            {
    
                cout<<endl;
                sl.display();
                cout<<endl;
            }
        
            else if(choice == "file" || choice == "FILE")
            {
                cin>>path;
            
                ifstream tweety(path.c_str());
                
                getline(tweety,cmd,',');
                getline(tweety,entry,'\n');
                
                if(tweety.is_open())
                {
                    while(!tweety.eof())
                    {
                        getline(tweety,cmd,',');
                        getline(tweety,entry,'\n');
                        
                        if(cmd == "add")
                        {
                            id++;
                            sl.insert_file(entry);
                            cout<<endl;
                            sl.sortfile();
                        }
                        
                        else if(cmd == "remove")
                        {
                            dcnt = sl.dsearchfile(entry);
                            
                            sl.delete_pos(dcnt);
                        }
                        
                        else if(cmd == "search")
                        {
                            cout<<endl;
                            sl.searchfile(entry);
                            cout<<endl;
                        }
                        
                        else if(cmd == "print")
                        {
                            
                            cout<<endl;
                            sl.displayfile();
                            cout<<endl;
                        }


                    }
                    
                    tweety.close();
                }
                else
                    cout<< " ERROR: CANNOT OPEN INPUT FILE" << endl;
                
            }
        
            else
                cout<<endl;
        
        
        
    }
    while(choice != "exit");
}

/*
 * Creating Node
 */
node *List::create_node(int id,string name)
{
    struct node *temp, *s;
    temp = new(struct node);
    if (temp == NULL)
    {
        cout<<"Memory not allocated "<<endl;
        return 0;
    }
    else
    {
        temp->info = name;
        temp->ID= id;
        temp->next = NULL;
        return temp;
    }
}

/*
 * Inserting element in beginning
 */
void List::insert_begin(string name)
{
    struct node *temp, *p;
    temp = create_node(id,name);
    if (start == NULL)
    {
        start = temp;
        start->next = NULL;
    }
    else
    {
        p = start;
        start = temp;
        start->next = p;
    }
    cout<<"ADDED : "<<"ID"<< setfill ('0') << setw(3) << id << name << endl;
    
}

/*Sorting the list
 */

void List::sort()
{
    string name;
    struct node *ptr, *s;
    if (start == NULL)
    {
        cout<<"The List is empty"<<endl;
        return;
    }
    ptr = start;
    while (ptr != NULL)
    {
        for (s = ptr->next;s !=NULL;s = s->next)
        {
            if (ptr->info > s->info && ptr->ID > s->ID)
            {
                name = ptr->info;
                id = ptr->ID;
                ptr->info = s->info;
                ptr->ID = s->ID;
                s->info = name;
                s->ID = id;
            }
        }
        ptr = ptr->next;
    }
}


/*
 * Delete element at a given position
 */
void List::delete_pos(int pos)
{
    int i, counter = 0;
    if (start == NULL)
    {
        cout<<"List is empty"<<endl;
        return;
    }
    struct node *s, *ptr;
    s = start;
    if (pos == 1)
    {
        start = s->next;
    }
    else
    {
        while (s != NULL)
        {
            s = s->next;
            counter++;
        }
        if (pos > 0 && pos <= counter)
        {
            s = start;
            for (i = 1;i < pos;i++)
            {
                ptr = s;
                s = s->next;
            }
            ptr->next = s->next;
        }
        else
        {
            cout<<"ERROR: NOT FOUND FOR REMOVAL"<<endl;
        }
        free(s);
        cout<<"Removal Successful"<<endl;;
    }
}

/*
 * Searching an element
 */
void List::search()
{
    string name;
    int pos = 0;
    bool flag = false;
    if (start == NULL)
    {
        cout<<"List is empty"<<endl;
        return;
    }
    cin>>name;
    struct node *s;
    s = start;
    while (s != NULL)
    {
        pos++;
        if (s->info == name)
        {
            flag = true;
            cout<<"TRUE : "<< name << endl;
        }
        s = s->next;
    }
    if (!flag)
        cout<<"FALSE :"<< name <<endl;
}

int List::dsearch()
{
    string name;
    int pos = 0;
    int baal;
    bool flag = false;
    if (start == NULL)
    {
        cout<<"List is empty"<<endl;
        return 0;
    }
    cin>>name;
    struct node *s;
    s = start;
    while (s != NULL)
    {
        pos++;
        if (s->info == name)
        {
            flag = true;
            return pos;
        }
        s = s->next;
    }
    baal = pos;
    
    return baal;
}

/*
 * Reverse Link List
 */
void List::reverse()
{
    struct node *ptr1, *ptr2, *ptr3;
    if (start == NULL)
    {
        cout<<"List is empty"<<endl;
        return;
    }
    if (start->next == NULL)
    {
        return;
    }
    ptr1 = start;
    ptr2 = ptr1->next;
    ptr3 = ptr2->next;
    ptr1->next = NULL;
    ptr2->next = ptr1;
    while (ptr3 != NULL)
    {
        ptr1 = ptr2;
        ptr2 = ptr3;
        ptr3 = ptr3->next;
        ptr2->next = ptr1;
    }
    start = ptr2;
}

/*
 * Display Elements of a link list
 */
void List::display()
{
    struct node *temp;
    if (start == NULL)
    {
        cout<<"NO NAMES IN THE LIST"<<endl;
        return;
    }
    temp = start;
    cout<<endl;
    while (temp != NULL)
    {
        cout<<"ID "<< setfill ('0') << setw(3) << temp->ID << temp->info<< endl;
        temp = temp->next;
    }
    cout<<endl;
}






/*
 * Inserting element in beginning
 */
void List::insert_file(string name)
{
    struct node *temp, *p;
    temp = create_node(id,name);
    if (start == NULL)
    {
        start = temp;
        start->next = NULL;
    }
    else
    {
        p = start;
        start = temp;
        start->next = p;
    }
    cout<<"ADDED : "<<"ID "<< setfill ('0') << setw(3) << id << name << endl;
    
}

/*Sorting the list
 */

void List::sortfile()
{
    string name;
    struct node *ptr, *s;
    if (start == NULL)
    {
        cout<<"The List is empty"<<endl;
        return;
    }
    ptr = start;
    while (ptr != NULL)
    {
        for (s = ptr->next;s !=NULL;s = s->next)
        {
            if (ptr->info > s->info && ptr->ID > s-> ID)
            {
                name = ptr->info;
                id = ptr->ID;
                ptr->info = s->info;
                ptr->ID = s->ID;
                s->info = name;
                s->ID = id;
            }
        }
        ptr = ptr->next;
    }
}


/*
 * Delete element at a given position
 */
void List::delete_file(int pos)
{
    int i, counter = 0;
    if (start == NULL)
    {
        cout<<"List is empty"<<endl;
        return;
    }
    struct node *s, *ptr;
    s = start;
    if (pos == 1)
    {
        start = s->next;
    }
    else
    {
        while (s != NULL)
        {
            s = s->next;
            counter++;
        }
        if (pos > 0 && pos <= counter)
        {
            s = start;
            for (i = 1;i < pos;i++)
            {
                ptr = s;
                s = s->next;
            }
            ptr->next = s->next;
        }
        else
        {
            cout<<"ERROR:NOT FOUND FOR REMOVAL"<<endl;
        }
        free(s);
        cout<<"Removal Successful"<<endl;
    }
}

/*
 * Searching an element
 */
void List::searchfile(string name)
{
    int pos = 0;
    bool flag = false;
    if (start == NULL)
    {
        cout<<"List is empty"<<endl;
        return;
    }
    struct node *s;
    s = start;
    while (s != NULL)
    {
        pos++;
        if (s->info == name)
        {
            flag = true;
            cout<<"TRUE : "<< name << endl;
        }
        s = s->next;
    }
    if (!flag)
        cout<<"FALSE :"<< name <<endl;
}

int List::dsearchfile(string name)
{
    int pos = 0;
    int baal;
    bool flag = false;
    if (start == NULL)
    {
        cout<<"List is empty"<<endl;
        return 0;
    }
    struct node *s;
    s = start;
    while (s != NULL)
    {
        pos++;
        if (s->info == name)
        {
            flag = true;
            return pos;
        }
        s = s->next;
    }
    baal = pos;
    
    return baal;
}

/*
 * Reverse Link List
 */
void List::reversefile()
{
    struct node *ptr1, *ptr2, *ptr3;
    if (start == NULL)
    {
        cout<<"List is empty"<<endl;
        return;
    }
    if (start->next == NULL)
    {
        return;
    }
    ptr1 = start;
    ptr2 = ptr1->next;
    ptr3 = ptr2->next;
    ptr1->next = NULL;
    ptr2->next = ptr1;
    while (ptr3 != NULL)
    {
        ptr1 = ptr2;
        ptr2 = ptr3;
        ptr3 = ptr3->next;
        ptr2->next = ptr1;
    }
    start = ptr2;
}

/*
 * Display Elements of a link list
 */
void List::displayfile()
{
    struct node *temp;
    if (start == NULL)
    {
        cout<<"NO NAMES IN THE LIST"<<endl;
        return;
    }
    temp = start;
    cout<<endl;
    while (temp != NULL)
    {
        cout<<"ID "<< setfill ('0') << setw(3) << temp->ID << temp->info<< endl;
        temp = temp->next;
    }
    cout<<endl;
}