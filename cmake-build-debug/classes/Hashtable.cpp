#include <stdio.h>
#include <stdlib.h>
#include "Hashtable.h"
#include <iostream>
#include <fstream>

using namespace std;

hashTable::hashTable()
{
    for(int x = 0; x < 20; x++){
        Tabelle[x] = NULL;
    }
}

hashTable::~hashTable()
{
    //dtor
}

bool hashTable::addAktie(int key, hashNode* Node)
{
    int hashkey = hash(key);
    int pointer = hashkey;
    int counter = 0;
    bool spacefound = false;

    if(Tabelle[hashkey] == NULL){
        Node->changeDepth(1);
        Tabelle[hashkey] = Node;
        cout << "normal insert" << endl;
        return true;
    }else{
        for(counter = 1; counter < 20; counter++){
            if(Tabelle[hashTable::hash(pointer + seq(counter))] == NULL){
                spacefound = true;
                break;
            }
        }
        if(spacefound){
            Tabelle[hash(pointer + seq(counter))] = Node;
            Tabelle[hashkey]->changeDepth(1);
            cout << "spaced insert" << endl;
            return true;
        }
    }
    return false;
}

int hashTable::hash(int key)
{
    if((key % 20) < 0){
        return -(key % 20);
    }
    return (key % 20);
}

hashNode* hashTable::getNode(int key)
{
    if(Tabelle[key] == NULL){
        return NULL;
    }
    return Tabelle[key];
}

hashNode* hashTable::getNode(int key, std::string name, bool mode) // mode gibt ob nach Name oder ShortName gesucht wird
{
    if (this->getNode(key) == NULL){
        cout << "Name could not be resolved" << endl;
        return NULL;
    }

    aktie* myAktie = this->getNode(key)->getAktie();
    int Depth = this->getNode(key)->getDepth();

    if (myAktie == NULL && Depth == 0){
        cout << "no Aktien at this Node" << endl;
        return NULL;
    } else if (myAktie == NULL && Depth > 0){
        for(int counter = Depth; counter > 1; counter--){
            myAktie = this->getNode(hashTable::hash(key += seq(counter)))->getAktie();
            if((mode && myAktie->getName() == name) || (!mode && myAktie->getShortName() == name)){
                return this->getNode(hashTable::hash(key += seq(counter)));
            }
        }
        cout << "Aktie could not be found in search at Node" << endl;
    } else if (myAktie != NULL && ((mode && myAktie->getName() == name) || (!mode && myAktie->getShortName() == name))){
        return this->getNode(key);
    } else {
        cout << "Name could not be found" << endl;
        return NULL;
    }
    return NULL;
}

int hashTable::seq(int key)
{
    if (key == 0){
        return 0;
    }
    if(key % 2){
        return (5+key)*(5+key);
    } else {
        return -(5+key)*(5+key);
    }
}

int hashTable::toKey(std::string name)
{
    int key = 0;
    for(std::string::iterator it = name.begin(); it != name.end(); it++){
        key += 33 * key + *it;
    }
    return key;
}

bool hashTable::printAktieAt(int key, std::string name, bool mode)
{
    hashNode* temp = this->getNode(key, name, mode);
    if(temp == NULL) return false;
    temp->getAktie()->printAktie();
    return true;
}

void hashTable::printTable()
{
    for(int x = 0; x < 20; x++){
        cout << "Index " << x << " : ";
        if(Tabelle[x] != NULL){
            cout << " Depth : " << Tabelle[x]->getDepth() << " | ";
            if(Tabelle[x]->getAktie() != NULL){
                Tabelle[x]->getAktie()->printAktie();
            } else {
                cout << " NULL Aktie at this depth" << endl;
            }
        } else {
            cout << "is Empty" << endl;
        }
    }
}


//new Tabelle wird in ein Textfile abgespeichert
void hashTable::saveTable(bool saveState){ //Tabelle wird in Form der printTable() methode gespeichert, wird bisher nur appended

    string filename;

    filename = "data/saveData.txt";
    fstream FILE;



    if (!saveState){
        FILE.open(filename, ios_base::app);
        if (FILE.is_open()) {
            cout << "\nFile has been saved!\n";

            for (int x = 0; x < 20; x++) {
                FILE << "Index " << x << " : ";
                if (Tabelle[x] != NULL) {
                    FILE << " Depth : " << Tabelle[x]->getDepth() << " | ";
                    if (Tabelle[x]->getAktie() != NULL) {
                        FILE << Tabelle[x]->getAktie()->getName() << " : " << Tabelle[x]->getAktie()->getAnum() << endl;
                    } else {
                        FILE << " no Aktie at this depth" << endl;
                    }
                } else {
                    FILE << "is Empty" << endl;
                }
            }
        } else cout << "\nFile could not open";
    } else {
        remove("src/saveData.txt");
        FILE.close();
    }
}


bool hashTable::shuffle(int key, hashTable* Table) // fills empty Nodes with other Nodes at that hash
{
    int maxDepth = Table->getNode(key)->getDepth();
    int counter = 0; // counts how many objects have been moved forward
    for(int Depth = 0; Depth < maxDepth-1; Depth++){ // looks at <number of Depth> Nodes, starting with the node at index <key>
        // cout << "           Looking at index: " << hashTable::hash(key + seq(Depth)) << endl;
        if(Table->getNode(hashTable::hash(key + seq(Depth)))->getAktie() == NULL){ // if the Node at Index<key>+seq was empty...
            for(int counterDepth = maxDepth-1; counterDepth > Depth; counterDepth--){ // go through the Table from the back...
                // cout << "           Searching at Depth: " << counterDepth << endl;
                // cout << "           Searching at index: " << hashTable::hash(key + seq(counterDepth)) << endl;
                if(Table->getNode(hashTable::hash(key + seq(counterDepth)))->getAktie() != NULL){ // ... if the node at that table isnt empty
                    hashTable::swapAktie(Table->getNode(hashTable::hash(key + seq(counterDepth))), Table->getNode(hashTable::hash(key + seq(Depth))));  // swap the node from the back and the empty node at the front
                    counter++;
                    Table->getNode(key)->changeDepth(-1);
                    Table->cleanNode(hashTable::hash(key + seq(counterDepth))); // cleans the last Node that was just moved
                    break;
                }
            }
        }
    }
    if(counter > 0){ // if things got moved
        return true; // return true
    } else {
    }
    return false; // return false
}

void hashTable::swapAktie(hashNode* Node1, hashNode* Node2) //swaps two Nodes
{
    if(&Node1 == &Node2) return; // if its the same Node no need to swap
    aktie* temp = Node1->getAktie();
    Node1->setAktie(Node2->getAktie());
    Node2->setAktie(temp);
}

void hashTable::clean()
{
    for(int x = 0; x < 20; x++){
        if(this->getNode(x) != NULL && this->getNode(x)->getAktie() == NULL){
            cleanNode(x);
        }
    }
}

void hashTable::cleanNode(int key)
{
    if(this->getNode(key)->getAktie() == NULL){ // cleans the node if its Aktie doesnt point anywhere
        Tabelle[key] = NULL;
    }
}
