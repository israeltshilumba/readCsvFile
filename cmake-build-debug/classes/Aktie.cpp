#include <stdio.h>
#include <stdlib.h>
#include "Aktie.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

aktie::aktie(){
    //cout << "\nBitte geben Sie den Pfad an, andem sich Ihr CSV File befindet:\n";
    //cin >> this->filename;



    cout << "\nLongName:\n";
    std::cin >> this->longName;

    cout << "\nShortName:\n";
    std::cin >> this->shortName;
    // getEntries();
};

void aktie::setFilename(){
    cout << "\n Please enter the csv filename\n";
    cin >> this->filename;
    filename = "data/" + filename + ".csv";
    getEntries();
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
/*aktie::aktie(std::string name, std::string shortname, int num)
{
    a_shortname = shortname;
    a_name = name;
    a_num = num;
    /* --INSERT YOUR CODE HERE-- */
// Constructor der Daten der Aktien
//}

aktie::~aktie()
{
    //dtor
}

bool aktie::printAktie()
{
    cout << this->longName << " : " << this->shortName << endl;
    return true;
}

void aktie::printArray(){ //printet alle Entries einer Node
    for (int i = 0; i < arrayLength; i++){
        cout << endl;
        for (int j = 0; j < arrayDepth; j++){
            cout << this->entries[i][j] << " /   ";
        }
    }
    cout << endl;
}

std::string aktie::getName()
{
    return longName;
}

//new -> a_num getter
int aktie::getAnum(){
    return a_num;
}

std::string aktie::getShortName()
{
    return shortName;
}

bool aktie::deleteAktie(hashTable* nameTable, hashTable* shortTable)
{
    int namehash = hashTable::hash(hashTable::toKey(this->longName));
    int shorthash = hashTable::hash(hashTable::toKey(this->shortName));

    hashNode* temp = nameTable->getNode(namehash, this->longName, true);
    hashNode* temp2 = shortTable->getNode(shorthash, this->shortName, false);
    if(temp == NULL){
        cout << "Error: couldnt find name" << endl;
        return false;
    } else if (temp2 == NULL){
        cout << "Error: couldnt find shortname" << endl;
        return false;
    }
    temp->setAktie(NULL);
    temp = nameTable->getNode(namehash);

    cout << "   Deleting from nameTable" << endl;
    // cout << "Starting to shuffle" << endl;
    if(nameTable->shuffle(namehash, nameTable)){
        // cout << "Shuffle was successfull" << endl;
    } else {
        // cout << "Shuffle was unsuccessfull" << endl;
        // cout << "decrease by: 1" << endl;
        nameTable->getNode(namehash)->changeDepth(-1); //if something was deleted but nothing could be swapped, decrease the depth by 1
        nameTable->cleanNode(hashTable::hash(namehash + hashTable::seq(nameTable->getNode(namehash)->getDepth()))); // cleans the last node at the maximum Depth
    }

    namehash = shorthash;
    temp = temp2;
    if(temp == NULL) return false;
    temp->setAktie(NULL);
    temp = shortTable->getNode(namehash);

    cout << "   Deleting from shortTable" << endl;
    // cout << "Starting to shuffle" << endl;
    if(shortTable->shuffle(namehash, shortTable)){
        // cout << "Shuffle was successfull" << endl;
    } else {
        // cout << "Shuffle was unsuccessfull" << endl;
        // cout << "decrease by: 1" << endl;
        shortTable->getNode(namehash)->changeDepth(-1); //if something was deleted but nothing could be swapped, decrease the depth by 1
        shortTable->cleanNode(hashTable::hash(namehash + hashTable::seq(shortTable->getNode(namehash)->getDepth()))); // cleans the last node at the maximum Depth
    }
    return true;
}
