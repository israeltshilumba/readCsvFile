//Files werden nur gelesen, wenn sie im cmake-build-debug sind
//test
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

void readFile(){
    //verfügbare files: AAPL.csv, AMZN.csv, BABA.csv (Alibaba), FB.csv, GOOG.csv, INTC.csv (Intel),
    // MSFT.csv, NTFL.csv, NVDA.csv (Nvidia), TCEHY.csv (Tencent), //alle im data dir gespeichert
    string filename, zeile, eintrag;

    cout << "\nChoose file: FORMAT: 'data/FILENAME.csv'\n";
    cin >> filename; //muss noch als path angegeben. data/"name des File".csv

    fstream FILE;
    FILE.open(filename);

    if (FILE.is_open()){
        cout << "\nFile offen";
        while(getline(FILE, zeile)){ // var zeile: Eintrag bis newline-char

            cout << endl;
            //nach jedem Durchgang, eine neue Zeile

            stringstream zeileFormat(zeile); //wandelt string zeile in ein file-ähnliches Format

            while(getline(zeileFormat, eintrag, ',')){// var eintrag: Wert zwischen zwei kommas oder newline
                cout << eintrag << " ";//debug
                //einfügen in Hashtabelle Zeile
            }
        }
    } else cout << "\nFile nicht offen";

    //return hashtable;
}
int main () {
    readFile();

    return 0;
}