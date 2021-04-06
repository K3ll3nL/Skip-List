//
// Created by Kellen Long on 4/6/2021.
//

#ifndef SKIPLIST_SKIPLIST_H
#define SKIPLIST_SKIPLIST_H

#include <bits/stdc++.h>

using namespace std;

class Node{
public:
    int value;

    //Arrays to hold pointers to nodes on different levels
    Node **forward;
    Node(int,int);
};



class SkipList {
    //Maximum level for this skip list
    int MAX_LEVEL;

    //the ratio deciding if a node will have a pointer one level above the next
    float p;

    //pointer pointing to the head node
    Node* header;

    //placeholder for current level being traversed
    int level;

public:
    SkipList(int,float);
    Node* createnode(int,int);
    int randomlevel();
    void insert(int);
    void remove(int);
    void find(int);
    void print();
};


#endif //SKIPLIST_SKIPLIST_H
