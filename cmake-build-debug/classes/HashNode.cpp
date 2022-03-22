#include <stdio.h>
#include <stdlib.h>

#include "HashNode.h"

hashNode::hashNode(aktie* Aktie)
{
    n_Aktie = Aktie;
    n_Depth = 0;
    //ctor
}

hashNode::~hashNode()
{
    //dtor
}

int hashNode::getDepth()
{
    return n_Depth;
}

aktie* hashNode::getAktie()
{
    if(n_Aktie == NULL){
        return NULL;
    }
    return n_Aktie;
}

void hashNode::setAktie(aktie* newAktie)
{
    n_Aktie = newAktie;
}

void hashNode::changeDepth(int value){
    n_Depth += value;
}
