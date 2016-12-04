#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <cctype>
#include <ctype.h>
#include <ctime>
#include <strings.h>

#define nil NULL
#define info(P) (P)->info
#define next(P) (P)->next
#define nextC(P) (P)->nextC
#define nextC(Q) (Q)->nextC
#define prevC(Q) (Q)->prevC
#define first(S) S.first
#define last(S) S.last

using namespace std;

typedef struct elementlistP *addressP;
typedef struct elementlistC *addressC;

struct v_spbu{
    string id;
    string jenis;
    int stok;
    int harga;
    int pendapatan;
};

struct v_pelanggan{
    int beli;
    int biaya;
};

struct elementlistP{
    v_spbu info;
    addressP next;
    addressC nextC;
};

struct elementlistC{
    v_pelanggan info;
    addressC nextC;
    addressC prevC;
};

struct spbu{
    addressP first;
    addressP last;
};


void inputSPBU (v_spbu X);
void createList(spbu &S);
addressP alokasi(v_spbu X);
void insertLastP(spbu &S, addressP P);
void insertfirstP(spbu &S, addressP P);
void insertafterP(spbu &S, addressP P);
void insertP(spbu &S, addressP P) ;
addressP find_id(spbu &S, string id);
bool EmptyStock(int X, addressP P);
void update_parent(addressP P, v_pelanggan X);
void inputPLG(v_pelanggan X, addressP P);
addressC alokasiChild(v_pelanggan X);
void insertLastChild(spbu &S, addressC P);
void deletelastChild(spbu &S);
void dealokasi(addressP P);
void dealokasiChild(addressC P);
void show_parent(spbu &S);
addressP findMax(spbu &S) ;
void printinfo(spbu &S);
void menu(); 

#endif // HEADER_H_INCLUDED
