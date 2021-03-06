//
// Created by Kellen Long on 4/6/2021.
//

#ifndef SKIPLIST_SKIPLIST_H
#define SKIPLIST_SKIPLIST_H

#include <bits/stdc++.h>

using namespace std;

template <class t>
class Node{
public:
    t value;

    //Arrays to hold pointers to nodes on different levels
    Node **forward;

    Node(t value,int level){
        this->value = value;

        //Free up space for forward
        forward = new Node*[level+1];

        //Fill forward as a blank array
        memset(forward,0, sizeof(Node*)*(level+1));
    };
};


template <class t>
class SkipList {
    //Maximum level for this skip list
    int MAX_LEVEL;

    //the ratio deciding if a node will have a pointer one level above the next
    float p;

    //pointer pointing to the head node
    Node<t>* header;

    //placeholder for current level being traversed
    int level;

public:
    SkipList<t>(int m, float p) {
        this->MAX_LEVEL = m;
        this->p = p;
        level = 0;

        header = new Node<t>(*(new t()), MAX_LEVEL);
    }


    Node<t>* createnode(t value, int level) {
        auto *n = new Node<t>(value, level);
        return n;
    }


    int randomlevel() {
        float r = (float)rand()/RAND_MAX;
        int lvl = 0;
        while(r < p && lvl < MAX_LEVEL){        //loops until random() has decided
            lvl++;                              //how many levels a node will span
            r = (float)rand()/RAND_MAX;
        }
        return lvl;
    }


    void insert(t value) {
        Node<t> *curr = header;

        //create temp array to operate with
        Node<t> *temp[MAX_LEVEL + 1];
        memset(temp, 0, sizeof(Node<t> *) * (MAX_LEVEL + 1));

        /* traverse array by starting from the highest level
         * and moving down each level when the next node is
         * larger than the value to be found, should result in
         * a node looking at level 0 with the forward node pointing
         * to a value larger than the local value variable */
        for (int i = level; i >= 0; i--) {
            while (curr->forward[i] != NULL && curr->forward[i]->value < value) {
                curr = curr->forward[i];
            }
            temp[i] = curr;
        }

        /* the search algorithm has found the place to be
         * inserted and is at level 0 */
        curr = curr->forward[0];

        /* if curr is NULL then it has reached the end of
         * the level or the SkipList is empty, and the next
         * place to insert is between temp[0] and the curr node */
        if (curr == NULL || curr->value != value) {
            //create a random level for the node to span
            int rlevel = randomlevel();

            /* if rlevel is higher than level, then the header
             * needs to point to all levels higher than the current
             * highest, and level must be updated. */
            if (rlevel > level) {
                for (int i = level + 1; i < rlevel + 1; i++) {
                    temp[i] = header;
                }
                level = rlevel;
            }

            //generate new node
            Node<t> *n = createnode(value, rlevel);

            //insert node
            for (int i = 0; i <= rlevel; i++) {
                n->forward[i] = temp[i]->forward[i];
                temp[i]->forward[i] = n;
            }
            cout << "successfully inserted value " << value << endl;
        }
    }


    void remove(t value) {
        Node<t>* curr = header;

        //create temp array to operate with
        Node<t>* temp[MAX_LEVEL+1];
        memset(temp, 0, sizeof(Node<t>*)*(MAX_LEVEL+1));

        /* traverse array by starting from the highest level
         * and moving down each level when the next node is
         * larger than the value to be found, should result in
         * a node looking at level 0 with the forward node pointing
         * to a value larger than the local value variable */
        for (int i = level; i >= 0; i--){
            while (curr->forward[i] != NULL && curr->forward[i]->value < value) {
                curr = curr->forward[i];
            }
            temp[i] = curr;
        }

        /* the search algorithm has found the place to be
         * deleted and is at level 0 */
        curr = curr->forward[0];

        //if current node is the target node
        if(curr != NULL && curr->value == value){
            /* start from the lowest point and rearrange
             * the pointers to not include the current value */
            for(int i =0; i<=level; i++){
                /* if at level i, the next node is not the
                 * target node and the loop needs to be broken.*/
                if(temp[i]->forward[i] != curr){
                    break;
                }
                temp[i]->forward[i] = curr->forward[i];

            }
            //remove levels with no elements
            while(level>0 && header->forward[level] == 0) {
                level--;
            }
            cout<<"Successfully deleted key "<<value<<"\n";
        }
    }


    bool find(t value) {
        Node<t>* curr = header;

        //create temp array to operate with
        Node<t>* temp[MAX_LEVEL+1];
        memset(temp, 0, sizeof(Node<t>*)*(MAX_LEVEL+1));

        /* traverse array by starting from the highest level
         * and moving down each level when the next node is
         * larger than the value to be found, should result in
         * a node looking at level 0 with the forward node pointing
         * to a value larger than the local value variable */
        for (int i = level; i >= 0; i--){
            while (curr->forward[i] != NULL && curr->forward[i]->value < value) {
                curr = curr->forward[i];
            }
            temp[i] = curr;
        }

        /* the search algorithm has found the place to be
         * found and is at level 0 */
        curr = curr->forward[0];

        /* if the search key found is equal to the value
         * local variable, then the target node has been found. */
        if(curr && curr->value == value){
            return true;
        }else{
            return false;
        }
    }


    void print() {
        cout<<"\n*****Skip List*****"<<"\n";
        for (int i=0;i<=level;i++)
        {
            Node<t> *node = header->forward[i];
            cout << "Level " << i << ": ";
            while (node != NULL)
            {
                cout << node->value<<" ";
                node = node->forward[i];
            }
            cout << "\n";
        }
    }

    Node<t>* getHead(){
        return header;
    }

};


#endif //SKIPLIST_SKIPLIST_H