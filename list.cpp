#include "header.h"

using namespace std;

void inputSPBU (v_spbu X)
{
    X.pendapatan = 0;
    cout<<"Masukkan id              :";
    cin>>X.id;
    cout<<"Masukkan Jenis Bensin    :";
    cin>>X.jenis;
    cout<<"Masukkan Stock           :";
    cin>>X.stok;
    cout<<"Masukkan Harga / liter   :";
    cin>>X.harga;
}

void createList(spbu &S)
{
    first(S) = nil;
    last(S) = nil;
}

addressP alokasi(v_spbu X)
{
    addressP P = new elementlistP;
    if (P!=nil)
    {
        info(P) = X;
        next(P) = nil;
        nextC(P) = nil;
    }
    else
    {
        cout << "Alokasi Gagal" << endl;
    }

    return P;
}


void insertLastP(spbu &S, addressP P)
{
    if(first(S)==nil)
    {
        P = first(S);
        P = last(S);
    }
    else
    {
        next(last(S))=P;
        last(S) = P;
        next(last(S)) = first(S);
    }
}

void insertfirstP(spbu &S, addressP P)
{
    if(first(S)==nil)
    {
        P = first(S);
        P = last(S);
    }
    else
    {
        next(P) = first(S);
        next(last(S)) = P;
        first(S) = P;
    }
}

void insertafterP(spbu &S, addressP P)
{
    addressP prec = first(S);
    if(first(S)==nil)
    {
        P = first(S);
        P = last(S);
    }
    else
    {
        while (info(P).harga > info(prec).harga)
        {
            prec = next(prec);
        }
        if (prec != last(S))
        {
            next(P) = next(prec);
            next(prec) = P;
        }
        else
        {
            next(P) = first(S);
            next(prec) = P;
            last(S) = P;
        }
    }
}

void insertP(spbu &S, addressP P)      // insertP(S,alokasi(X))
{
   
    if (first(S) == nil)
    {
        first(S) = P;
        last(S) = P;
    }
    else if (info(first(S)).harga > info(P).harga )
    {
        insertfirstP(S,P);
    }
    else //if ( info(first(S)).harga < info(P).harga )
    {
        //insertLastP(S,P);
        insertafterP(S,P);
    }
    /*
    else //( info(first(S)).harga = info(P).harga ) ??
    {
        insertafterP(S,P);
    }
    */
}

addressP find_id(spbu &S, string id)
{
    addressP P = first(S);
    bool cek;
    if ( P == last(S))
    {
        if ( info(P).id == id)
        {
            cek = true;
        }
        else
        {
            cek = false;
        }
    }
    else
    {
        while ((info(P).id != id) && (next(P)!=first(S))) 
        {
            P = next(P);
        }
        if (info(P).id == id)
        {
            cek = true;
        }
        else
        {
            if (info(last(S)).id == id)
            {
                cek = true;
            }
            else
            {
                cek = false;
            }
        }
    }

    if (cek == true)
    {
        return P;
    }
    else
    {
        return nil;
    }
}

bool EmptyStock(int X, addressP P)
{
    if (info(P).stok < X)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void update_parent(addressP P, v_pelanggan X)
{
    info(P).stok = info(P).stok - X.beli;
    info(P).pendapatan = info(P).pendapatan + X.biaya;
}

void inputPLG(v_pelanggan X, addressP P)
{
    cout<<"Liter            = "<<X.beli;
    if (EmptyStock(X.beli, P))
    {
        cout<<"Stok Kurang"<<endl;
    }
    else
    {
        X.biaya = X.beli * info(P).harga;
        cout<<"Harga / liter    = "<<X.biaya<<endl;
        update_parent(P, X);
    }
}

addressC alokasiChild(v_pelanggan X)
{

    addressC P = new elementlistC;
    if (P!=nil)
    {
        info(P) = X;
        nextC(P) = nil;
        prevC(P) = nil;
    }
    else
    {
        cout << "Alokasi Gagal" << endl;
    }
    return P;
}

void insertLastChild(spbu &S, addressC Q, addressP P)
{
    if(nextC(P) == nil)
    {
        nextC(P)=Q;
        //prevC(Q)=????
    }
    else
    {
        addressC R = nextC(P);
        while (nextC(R)!=nil)
        {
            R=nextC(R);
        }
        nextC(R)=Q;
        prevC(Q)=R;
    }
}

void deletelastChild(spbu &S, addressP P)
{
    if (nextC(P)= nil)
    {
        cout<<"data kosong"<<endl;
    }
    else if (nextC(nextC(P))=nil)
    {
        nextC(P)=nil;
    }
    else
    {
        addressC Q;
        Q = nextC(P);
        while (nextC(Q)!=nil)
        {
            Q= nextC(Q);
        }
        nextC(prevC(Q))=nil;
        prevC(Q)=nil;
    }
}

void dealokasi(addressP P)
{
    v_spbu X;
    X = info(P);
    P = nil;
}
void dealokasiChild(addressC P)
{
    v_pelanggan X;
    X = info(P);
    P = nil;
}

addressP findMax(spbu &S) //mencari penjualan terbanyak berdasarkan stok terkecil
{

    addressP P = first(S);
    addressP Q = next(first(S));
    while (Q != last(S))
    {
        if (info(P).stok > info(Q).stok)
        {
            P = Q;
        }
        Q = next(Q);
    }
    Q = last(S);
    if (info(P).stok > info(Q).stok)
    {
        P = Q;
    }
    return P;
}

void printinfo(spbu &S)
{

    addressP Q = first(S);
    if (Q == nil)
    {
        cout << "Data Kosong" << endl;
        getch();
    }
    else if (Q == last(S))
    {
        cout<<"id               :"<<info(Q).id<<endl;
        cout<<"Jenis Bensin     :"<<info(Q).jenis<<endl;
        cout<<"Stock            :"<<info(Q).stok<<endl;
        cout<<"Harga / liter    :"<<info(Q).harga<<endl;
        cout<<"Pendapatan       :"<<info(Q).pendapatan<<endl;
        getch();
    }
    else
    {
        while(Q != last(S))
        {
            cout<<"id               :"<<info(Q).id<<endl;
            cout<<"Jenis Bensin     :"<<info(Q).jenis<<endl;
            cout<<"Stock            :"<<info(Q).stok<<endl;
            cout<<"Harga / liter    :"<<info(Q).harga<<endl;
            cout<<"Pendapatan       :"<<info(Q).pendapatan<<endl;
            cout<<" "<<endl;
            Q = next(Q);
        }
            cout<<"id               :"<<info(last(S)).id<<endl;
            cout<<"Jenis Bensin     :"<<info(last(S)).jenis<<endl;
            cout<<"Stock            :"<<info(last(S)).stok<<endl;
            cout<<"Harga / liter    :"<<info(last(S)).harga<<endl;
            cout<<"Pendapatan       :"<<info(last(S)).pendapatan<<endl;
            cout<<" "<<endl;
    }
}

void menu()
{

    spbu S;
    int pil;
    v_spbu X;
    v_pelanggan Y;
    string id;
    addressP P;
    do
    {
        system("cls");
        cout<<"Aplikasi Pengelolaan Data SPBU"<<endl;
        cout<<"=============================="<<endl;
        cout<<"1. Input Data SPBU"<<endl;
        cout<<"2. Input Data Pembeli"<<endl;
        cout<<"3. Data Penjualan Terbanyak"<<endl;
        cout<<"4. Tampil Data Keseluruhan"<<endl;
        cout<<"5. Exit" << endl;
        cout<<"Masukkan Pilihan Menu : ";
        cin>>pil;
        cout<<endl;

        switch(pil)
        {
        case 1 :
        {
            system("cls");
            inputSPBU(X);
            P = alokasi(X);
            insertP(S,P);
            break;
        }

        case 2 :
        {
            system("cls");
            cout<<"Masukkan ID bensin : ";
            cin>>id;
            P = find_id(S,id);
            if ( P = nil)
            {
                cout<<"Id Tidak Ditemukan"<<endl;
            }
            else
            {
                inputPLG(Y,P);
                insertLastChild(S,alokasiChild(Y),P);
                deletelastChild(S,P);
            }
            break;
        }

        case(3) :
        {
            system("cls");
            P = findMax(S);
            cout<<"id               :"<<info(P).id<<endl;
            cout<<"Jenis Bensin     :"<<info(P).jenis<<endl;
            cout<<"Stock            :"<<info(P).stok<<endl;
            cout<<"Harga / liter    :"<<info(P).harga<<endl;
            cout<<"Pendapatan         :"<<info(P).pendapatan<<endl;
            cout<<" "<<endl;
            break;
        }

        case 4 :
        {
            system("cls");
            printinfo(S);
            break;
        }

        case 5 :
        {
            exit(0);
            break;
        }

        default :
        {
            cout<<"Angka yang anda masukan salah"<<endl;
            getch();
            break;
        }

        }
    }
    while (pil!=5);
}


