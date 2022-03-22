#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "Hashtable.h"


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
    int counter = 0; //wie oft man versucht hat das nächste zu öffnen
    bool spacefound = false;

    if(Tabelle[hashkey] == NULL){//wenn Eintrag leer ist -> depth wird erhöht -> fügt node ein
        Node->changeDepth(1);
        Tabelle[hashkey] = Node;
        cout << "normal insert" << endl;
        return true;
    }else{ //eintrag nicht leer
        for(counter = 0; counter < 20; counter++){ //geht Array 19 mal durch, sonst stopp -> suche nach leerer Stelle
            pointer += seq(counter);
            if(Tabelle[hash(pointer)] == NULL){
                spacefound = true;
                break;
            }
        }
        if(spacefound){ //platz gefunden, an der Stelle vom Pointer

            //insert code here
            Tabelle[hash(pointer)] = Node;
            Tabelle[hashkey]->changeDepth(1);
            cout << "spaced insert" << endl;
            return true;
        }
    }
    return false; //wenn kein Platz mehr ist
}

int hashTable::hash(int key) //schaut, dass positive WErte zurückgegebn werden
{
    if((key % 20) < 0){
        return -(key % 20);
    }
    return (key % 20);
}

hashNode* hashTable::getNode(int key) //schaut sich an ob node leer ist
{
    if(Tabelle[key] == NULL){
        return NULL;
    }
    return Tabelle[key];
}

hashNode* hashTable::getNode(int key, std::string name)
{
    if (this->getNode(key) == NULL) return NULL; //wenn tabelle am index leer ist

    aktie* myAktie = this->getNode(key)->getAktie();
    int Depth = this->getNode(key)->getDepth();

    if (myAktie == NULL && Depth == 0){ //Aktie am ort gelöscht
        cout << "no Aktien at this Node" << endl;
        return NULL;
    } else if (myAktie == NULL && Depth > 0){ //aktie gelöscht, aber weitere Einträge an der Stelle
        for(int counter = Depth; counter > 1; counter--){//geht "depth" lang
            myAktie = this->getNode(key += seq(counter))->getAktie(); //key + sequence number
            if(myAktie->getName() == name){ //suche Eintrag
                return this->getNode(key += seq(counter)); //Node wird returned
            }
        }
        cout << "Aktie could not be found in search at Node" << endl; //nichts wurde gefunden
    } else if (myAktie != NULL && myAktie->getName() == name){
        return this->getNode(key);
    } else { //unexpected error
        cout << "unrelated error" << endl;
        return NULL;
    }
    return NULL;
}

int hashTable::seq(int key){//sequenzieren
    if(key % 2){
        return (5+key)*(5+key); //5 damit es bei 5^2 beginnt
    } else {
        return -(5+key)*(5+key); // durch 2 teilbar -> negativer Wert
    }
}

int hashTable::toKey(std::string name){ //Hashfunktion
    int key = 0;
    for(std::string::iterator it = name.begin(); it != name.end(); it++){
        key += 33 * key + *it;
    }
    return key;
}

bool hashTable::printAktieAt(int key, std::string name) //eine Aktie
{
    hashNode* temp = this->getNode(key, name);
    if(temp == NULL) return false;
    temp->getAktie()->printAktie();
    return true;
}


void hashTable::printTable() //alle Aktien
{
    for(int x = 0; x < 20; x++){
        cout << "Index " << x << " : ";
        if(Tabelle[x] != NULL){
            cout << " Depth : " << Tabelle[x]->getDepth() << " | ";
            if(Tabelle[x]->getAktie() != NULL){
                Tabelle[x]->getAktie()->printAktie();
            } else {
                cout << " no Aktie at this depth" << endl;
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
        remove("filename");

    }
}
