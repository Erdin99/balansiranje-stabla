#ifndef STABLO_H
#define STABLO_H

#include <iostream>
#include <vector>
//#include <stdlib.h>
using namespace std;

template <typename Tip>
class Stablo {
    struct Cvor {
        Tip el;
        Cvor *rod, *ld, *dd;
        int brojElemenataLijevo;
        int brojElemenataDesno;
        int visinaCvora;
        Cvor(Tip el, Cvor *rod = nullptr, Cvor *ld = nullptr, Cvor *dd = nullptr, int brojElemenataLijevo = 0, int brojElemenataDesno = 0, int visinaCvora = 0) : el(el), rod(rod), ld(ld), dd(dd), brojElemenataLijevo(brojElemenataLijevo), brojElemenataDesno(brojElemenataDesno), visinaCvora(visinaCvora) {}
    };

    Cvor *korijen;
    int broj_elemenata;

    void OcistiStablo(Cvor *korijen);
    Cvor* KopirajStablo(Cvor *korijen, Cvor *rod_korijena, int &broj_elemenata);
    void InOrderRek(Cvor *cvor, void (f)(Tip&)) const;
    Cvor *Sljedbenik(Cvor *cvor);
    Cvor *Pocetak(Cvor *trenutni);
    Cvor *FindCvor(Tip element);
    int VisinaRek(Cvor *cvor);
    int BrojElemenataLijevoRek(Cvor *cvor);
    int BrojElemenataDesnoRek(Cvor *cvor);
    bool DaLiJePotrebnoBalansiranje(Cvor *korijen, int visinaElementa, int brojElemenataLijevo, int brojElemenataDesno, Cvor *trenutni, Tip element);
    bool DaLiJePotrebnoBalansiranjeNakonBrisanja(int visinaElementa, int brojElemenataLijevo, int brojElemenataDesno, Cvor *trenutni, Tip element);
    Cvor *Kreiraj(Tip el);
    Cvor *KreirajBalansiranoStablo(vector<Tip> niz, int pocetak, int kraj);
    //void UbaciUStablo(Cvor *korijen1, Tip element);
    //void DodajBalansiranoPodstablo(Cvor *korijen, Tip niz[], int pocetak, int kraj);
    void ResetujPodatkeCvora(Cvor *korijen);

public:
    Stablo() : broj_elemenata(0), korijen(nullptr) {} //konstruktor
    ~Stablo(); //desktruktor
    Stablo(const Stablo<Tip> &s); //konstruktor kopije
    Stablo(Stablo<Tip> &&s); //pomjerajuci konstruktor
    Stablo<Tip>& operator=(const Stablo<Tip> &rhs); //operator dodjele
    Stablo<Tip>& operator=(Stablo<Tip> &&rhs); //pomjerajuci operator dodjele
    void Insert(Tip element);
    bool Empty();
    void InOrder(void (f)(Tip&)) const;
    int Size();
    bool Find(Tip element);
    void Erase(Tip element);
    int Visina(Tip element);
};


#include "stablo.cpp"

#endif // STABLO_H
