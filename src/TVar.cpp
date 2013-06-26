#include "TVar.h"

TVar::TVar()
{
    hidden = false;
    name = "";
    reference = false;
    pointer = 0;
}

TVar::TVar(TVar * p)
{
    parent = p;
    hidden = false;
    name = "";
    reference = false;
    pointer = 0;
}

TVar::TVar(TVar * p, QString kName, int kt, QString val, int vt){
    parent = p;
    name = kName;
    kType = kt;
    value = val;
    vType = vt;
    hidden = false;
    reference = false;
    pointer = 0;
}

void TVar::setReference(bool s){
    reference = s;
}

void TVar::addChild(TVar * c){
    children.append(c);
}

QString TVar::getName(){
    return name;
}

QList<TVar *> TVar::getChildren(){
    return children;
}

bool TVar::isReference(){
    return reference;
}

void TVar::setParent(TVar * t){
    parent = t;
}

void TVar::removeChild(TVar * t){
    children.removeAll(t);
}

int TVar::getKeyType(){
    return kType;
}

QString TVar::getValue(){
    return value;
}

int TVar::getValueType(){
    return vType;
}

void TVar::setNewName(QString n){
    nName = n;
}

void TVar::setNewName(QString n, int t){
    nName = n;
    nkType = t;
}

int TVar::getNewKeyType(){
    return nkType;
}

QString TVar::getNewName(){
    return nName;
}

void TVar::clearNewName(){
    name = nName;
    kType = nkType;
    nName = "";
    nkType = 0;
}

bool TVar::setValue(QString val){
    value = val;
    return 1;
}

bool TVar::setValue(QString val, int t){
    value = val;
    vType = t;
    return 1;
}

bool TVar::setValueType(int t){
    vType = t;
    return 1;
}

bool TVar::setName(QString n, int kt){
    name = n;
    kType = kt;
}

bool TVar::setName(QString n){
    name = n;
}

TVar * TVar::getParent(){
    return parent;
}
