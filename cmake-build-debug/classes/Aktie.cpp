#include <stdio.h>
#include <stdlib.h>
#include "Aktie.h"
#include <iostream>

using namespace std;

aktie::aktie(){
};

aktie::aktie(std::string name, int num)
{
    a_name = name;
    a_num = num;
}

aktie::~aktie()
{
    //dtor
}

bool aktie::printAktie()
{
    cout << a_name << " : " << a_num << endl;
    return true;
}

std::string aktie::getName()
{
    return a_name;
}

void aktie::deleteAktie(hashTable* nameTable, hashTable* shortTable)  //nameTable: vollen Namen short: kürzel
{
    std::string name = a_name;//holt sich derzeitige Aktie
    int key = hashTable::toKey(name); //toKey static -> wandelt in hashwert(nummer)
    int hash = hashTable::hash(key); //hash -> wandelt in index
    hashNode* temp = nameTable->getNode(hash, name); //depth und name gespeichert, getNode: checkt auf index und Namen
    temp->setAktie(NULL); //node wird NULL gesetzt
    temp = nameTable->getNode(hash); //sucht das erste Element am Index
    temp->changeDepth(-1); //depth wird um 1 verringert
}
