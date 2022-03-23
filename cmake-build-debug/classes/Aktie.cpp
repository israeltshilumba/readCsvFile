#include <stdio.h>
#include <stdlib.h>
#include "Aktie.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

aktie::aktie(){
    cout << "\nBitte geben Sie den Pfad an, andem sich Ihr CSV File befindet:\n";
    cin >> this->filename;

    cout << "\nShortName:\n";
    std::cin >> this->shortName;

    cout << "\nLongName:\n";
    std::cin >> this->longName;

    getEntries();
};

void aktie::printArray(){ //printet alle Entries einer Node
    for (int i = 0; i < arrayLength; i++){
        cout << endl;
        for (int j = 0; j < arrayDepth; j++){
            cout << this->entries[i][j] << " /   ";
        }
    }
    cout << endl;
}

void aktie::getEntries() {
    //verfügbare files: AAPL.csv, AMZN.csv, BABA.csv (Alibaba), FB.csv, GOOG.csv, INTC.csv (Intel),
    // MSFT.csv, NTFL.csv, NVDA.csv (Nvidia), TCEHY.csv (Tencent), //alle im data dir gespeichert

    string /*filename,*/ zeile, eintrag;

    //cout << "\nChoose file: FORMAT: 'data/FILENAME.csv'\n";

    fstream FILE;
    FILE.open(filename);

    if (FILE.is_open()){
        cout << "\nFile offen";

        int i = 0; //for array
        int j;

        while(getline(FILE, zeile)){ // var zeile: Eintrag bis newline-char

            j = 0;
            //cout << endl;
            //nach jedem Durchgang, eine neue Zeile

            stringstream zeileFormat(zeile); //wandelt string zeile in ein file-ähnliches Format

            while(getline(zeileFormat, eintrag, ',')){// var eintrag: Wert wird bis zu einem Komma eingelesen
                //cout << eintrag << " "; //debug
                //einfügen in Hashtabelle Zeile
                entries[i][j] = eintrag;
                j++;
            }
            i++;
        }
    } else cout << "\nFile nicht offen";

    //return tmp;
}

aktie::~aktie()
{
    //dtor
}

bool aktie::printAktie()
{
    cout << this->longName << " : " << this->shortName << endl;
    return true;
}

std::string aktie::getName()
{
    return a_name;
}
//new -> a_num getter
int aktie::getAnum(){
    return a_num;
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
