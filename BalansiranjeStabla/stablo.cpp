#ifndef STABLO_CPP
#define STABLO_CPP
#include "stablo.h"

template <typename Tip>
void Stablo<Tip>::OcistiStablo(Cvor *korijen) {
    if(korijen == nullptr)
        return;

    if(korijen->ld != nullptr)
        OcistiStablo(korijen->ld);
    if(korijen->dd != nullptr)
        OcistiStablo(korijen->dd);

    if(korijen->rod != nullptr) {
        if(korijen->rod->ld == korijen)
            korijen->rod->ld = nullptr;
        else
            korijen->rod->dd = nullptr;
    }
    else
        this->korijen = nullptr;

    delete korijen;
    broj_elemenata--;
}

template <typename Tip>
Stablo<Tip>::~Stablo() {
    OcistiStablo(korijen);
}

template <typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::KopirajStablo(Cvor *korijen, Cvor *rod_korijena, int &broj_elemenata) {
    if(korijen == nullptr)
        return nullptr;

    Cvor *noviCvor = new Cvor(korijen->el, rod_korijena, nullptr, nullptr, korijen->brojElemenataLijevo, korijen->brojElemenataDesno, korijen->visinaCvora);
    broj_elemenata++;

    noviCvor->ld = KopirajStablo(korijen->ld, noviCvor, broj_elemenata);
    noviCvor->dd = KopirajStablo(korijen->dd, noviCvor, broj_elemenata);

    return noviCvor;
}

template <typename Tip>
Stablo<Tip>::Stablo(const Stablo<Tip> &s) : Stablo() {
    korijen = KopirajStablo(s.korijen, nullptr, broj_elemenata);
}

template <typename Tip>
Stablo<Tip>::Stablo(Stablo<Tip> &&s) : korijen(s.korijen), broj_elemenata(s.broj_elemenata) {
    s.korijen = nullptr;
    s.broj_elemenata = 0;
}

template <typename Tip>
Stablo<Tip>& Stablo<Tip>::operator=(const Stablo<Tip> &rhs) {
    if(this == &rhs)
        return *this;

    OcistiStablo(korijen);
    korijen = KopirajStablo(rhs.korijen, nullptr, broj_elemenata);

    return *this;
}

template <typename Tip>
Stablo<Tip>& Stablo<Tip>::operator=(Stablo<Tip> &&rhs) {
    Cvor *tempKorijen = korijen;
    korijen = rhs.korijen;
    rhs.korijen = tempKorijen;

    int tempBrojElemenata = broj_elemenata;
    broj_elemenata = rhs.broj_elemenata;
    rhs.broj_elemenata = tempBrojElemenata;

    return *this;
}

template <typename Tip>
int Stablo<Tip>::BrojElemenataLijevoRek(Cvor *cvor) {
    if(cvor == nullptr)
        return 0;

    int l = BrojElemenataLijevoRek(cvor->ld);
    int d = BrojElemenataLijevoRek(cvor->dd);

    return 1 + l + d;
}

template <typename Tip>
int Stablo<Tip>::BrojElemenataDesnoRek(Cvor *cvor) {
    if(cvor == nullptr)
        return 0;

    int l = BrojElemenataDesnoRek(cvor->ld);
    int d = BrojElemenataDesnoRek(cvor->dd);

    return 1 + l + d;
}

template <typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::Kreiraj(Tip el) {
    Cvor *temp = new Cvor(el);
    temp->ld = nullptr;
    temp->dd = nullptr;
    temp->brojElemenataLijevo = 0;
    temp->brojElemenataDesno = 0;
    temp->visinaCvora = 0;

    return temp;
}

template <typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::KreirajBalansiranoStablo(vector<Tip> niz, int pocetak, int kraj) {
    if(pocetak > kraj)
        return nullptr;

    int sredina = (pocetak + kraj) / 2;
    Cvor *temp = Kreiraj(niz[sredina]);

    temp->ld = KreirajBalansiranoStablo(niz, pocetak, sredina-1);
    temp->dd = KreirajBalansiranoStablo(niz, sredina+1, kraj);

    return temp;
}

/*
template <typename Tip>
void Stablo<Tip>::UbaciUStablo(Cvor *korijen1, Tip element) {

    Cvor *trenutni = korijen1, *prethodni = nullptr;
    //cout << "Ubacujem element: " << element << endl;
    while(trenutni != nullptr) {
        prethodni = trenutni;
        if(element < trenutni->el)
            trenutni = trenutni->ld;
        else if(element > trenutni->el)
            trenutni = trenutni->dd;
        else
            return;
    }

    if(element < prethodni->el)
        prethodni->ld = new Cvor(element, prethodni);
    else
        prethodni->dd = new Cvor(element, prethodni);

    broj_elemenata++;
}
*/

/*
template <typename Tip>
void Stablo<Tip>::DodajBalansiranoPodstablo(Cvor *korijen, Tip niz[], int pocetak, int kraj) {
    if(pocetak > kraj)
        return;

    int sredina = (pocetak + kraj) / 2;
    UbaciUStablo(korijen, niz[sredina]);

    DodajBalansiranoPodstablo(korijen, niz, pocetak, sredina-1);
    DodajBalansiranoPodstablo(korijen, niz, sredina+1, kraj);
}
*/

template <typename Tip>
bool Stablo<Tip>::DaLiJePotrebnoBalansiranje(Cvor *korijen, int visinaElementa, int brojElemenataLijevo, int brojElemenataDesno, Cvor *trenutni, Tip element) {
    if(korijen->ld == nullptr && visinaElementa >= 3 && brojElemenataDesno >= 2 && trenutni->el < element)
        return true;

    else if(korijen->dd == nullptr && visinaElementa >= 3 && brojElemenataLijevo >= 2 && trenutni->el > element)
        return true;

    if((visinaElementa >= 3 && 2*brojElemenataLijevo <= brojElemenataDesno+1 && trenutni->el < element) || (visinaElementa >= 3 && 2*brojElemenataDesno <= brojElemenataLijevo+1 && trenutni->el > element)){
        return true;
    }
    return false;
}

template <typename Tip>
bool Stablo<Tip>::DaLiJePotrebnoBalansiranjeNakonBrisanja(int visinaElementa, int brojElemenataLijevo, int brojElemenataDesno, Cvor *trenutni, Tip element) {
    if((visinaElementa >= 3 && 2*(brojElemenataLijevo-1) < brojElemenataDesno+1 && element < trenutni->el) || (visinaElementa >= 3 && 2*(brojElemenataDesno-1) < brojElemenataLijevo+1 && element > trenutni->el))
        return true;
    return false;
}

template <typename Tip>
void Stablo<Tip>::ResetujPodatkeCvora(Cvor *korijen) {
    if(korijen == nullptr)
        return;

    if(korijen->ld != nullptr)
        ResetujPodatkeCvora(korijen->ld);
    if(korijen->dd != nullptr)
        ResetujPodatkeCvora(korijen->dd);

    if(korijen->rod != nullptr) {
        if(korijen->rod->ld == korijen){
            korijen->rod->ld->brojElemenataLijevo = BrojElemenataLijevoRek(korijen->rod->ld->ld);
            korijen->rod->ld->brojElemenataDesno = BrojElemenataDesnoRek(korijen->rod->ld->dd);
            korijen->rod->ld->visinaCvora = Visina(korijen->rod->ld->el);
        }
        else{
            korijen->rod->dd->brojElemenataLijevo = BrojElemenataLijevoRek(korijen->rod->dd->ld);
            korijen->rod->dd->brojElemenataDesno = BrojElemenataDesnoRek(korijen->rod->dd->dd);
            korijen->rod->dd->visinaCvora = Visina(korijen->rod->dd->el);
        }
    }
}

template <typename Tip>
void Stablo<Tip>::Insert(Tip element) {
    if(Empty()){
        korijen = new Cvor(element);
        broj_elemenata++;
        return;
    }

    if(Find(element))
        return;

    bool potrebnoBalansiranje = false;
    bool lijevoDijete = false;
    Cvor *gdjeTrebaBalansirati;
    Cvor *roditelj;
    vector<Tip> niz;

    Cvor *trenutni = korijen, *prethodni = nullptr;
    while(trenutni != nullptr) {
        prethodni = trenutni;

        if(!potrebnoBalansiranje && DaLiJePotrebnoBalansiranje(korijen, trenutni->visinaCvora, trenutni->brojElemenataLijevo, trenutni->brojElemenataDesno, trenutni, element)){
            potrebnoBalansiranje = true;
            gdjeTrebaBalansirati = trenutni;
            roditelj = trenutni->rod;
            //pamtim da li je lijevo dijete ili desno dijete korijen podstabla koji se treba balansirati
            if(gdjeTrebaBalansirati != korijen && gdjeTrebaBalansirati->rod->ld == gdjeTrebaBalansirati)
                lijevoDijete = true;
        }

        if(element < trenutni->el){
            trenutni->brojElemenataLijevo += 1;
            trenutni = trenutni->ld;
        }
        else if(element > trenutni->el) {
            trenutni->brojElemenataDesno += 1;
            trenutni = trenutni->dd;
        }
        else
            return;
    }


    Cvor *noviCvor = Kreiraj(element);
    if(element < prethodni->el)
        prethodni->ld = noviCvor;
    else
        prethodni->dd = noviCvor;

    noviCvor->rod = prethodni;


    Cvor *trenutniTemp = noviCvor;
    while (trenutniTemp->rod != nullptr && trenutniTemp->rod->visinaCvora < trenutniTemp->visinaCvora+1) {
      trenutniTemp->rod->visinaCvora = trenutniTemp->visinaCvora+1;
      trenutniTemp = trenutniTemp->rod;
    }
    broj_elemenata++;

    if(potrebnoBalansiranje) {
        //cout << "Balansiranje se vrsi u cvoru: " << gdjeTrebaBalansirati->el << endl;

        Cvor *pocetni = Pocetak(gdjeTrebaBalansirati);
        //uslov gdje se balansiranje vrsi sa lijeve strane korijena ili kada treba balansirati citav korijen
        if(gdjeTrebaBalansirati->el <= korijen->el){
            while(pocetni != gdjeTrebaBalansirati->rod) {
                niz.push_back(pocetni->el);
                pocetni = Sljedbenik(pocetni);
            }
        }
        //uslov gdje se balansiranje vrsi sa desne strane korijena
        else {
            while(pocetni != nullptr) {
                niz.push_back(pocetni->el);
                pocetni = Sljedbenik(pocetni);
            }
        }
        /*
        cout << endl << "niz: ";
        for(int j = 0; j < niz.size(); j++)
            cout << niz[j] << " ";
        cout << endl;
        */
        OcistiStablo(gdjeTrebaBalansirati);

        if(korijen == nullptr) { //slucaj kada je potrebno balansirati citavo stablo po kriterijumu koji je zadat
            Cvor *noviKorijen = KreirajBalansiranoStablo(niz, 0, niz.size()-1);
            korijen = KopirajStablo(noviKorijen, nullptr, broj_elemenata);
            //prilikom promjene pozicija u stablu tokom balansiranja, potrebno je promijeniti broj elemenata lijevo,
            //broj elemenata desno i visinu
            ResetujPodatkeCvora(korijen);
        }
        else { //slucaj kada je potrebno balansirati podstablo u odredjenom cvoru po kriterijumu koji je zadat
            //DodajBalansiranoPodstablo(korijen, niz, 0, i-1);
            if(lijevoDijete)
                roditelj->ld = KreirajBalansiranoStablo(niz, 0, niz.size()-1);
            else
                roditelj->dd = KreirajBalansiranoStablo(niz, 0, niz.size()-1);
            korijen = KopirajStablo(korijen, nullptr, broj_elemenata);
            //prilikom promjene pozicija u stablu tokom balansiranja, potrebno je promijeniti broj elemenata lijevo,
            //broj elemenata desno i visinu
            ResetujPodatkeCvora(korijen);
        }
    }
}

template <typename Tip>
void Stablo<Tip>::Erase(Tip element) {
    if(!Find(element))
        return;

    Cvor *trenutni = korijen;
    bool potrebnoBalansiranje = false;
    bool lijevoDijete = false;
    Cvor *gdjeTrebaBalansirati;
    Cvor *roditelj;
    vector<Tip> niz;
    while(trenutni != nullptr) {
        if(!potrebnoBalansiranje && DaLiJePotrebnoBalansiranjeNakonBrisanja(trenutni->visinaCvora, trenutni->brojElemenataLijevo, trenutni->brojElemenataDesno, trenutni, element)) {
            potrebnoBalansiranje = true;
            gdjeTrebaBalansirati = trenutni;
            roditelj = gdjeTrebaBalansirati->rod;
            //pamtim da li je lijevo dijete ili desno dijete korijen podstabla koji se treba balansirati
            if(gdjeTrebaBalansirati != korijen && gdjeTrebaBalansirati->rod->ld == gdjeTrebaBalansirati)
                lijevoDijete = true;
        }

        if(element < trenutni->el){
            trenutni->brojElemenataLijevo -= 1;
            trenutni = trenutni->ld;
        }
        else if(element > trenutni->el) {
            trenutni->brojElemenataDesno -= 1;
            trenutni = trenutni->dd;
        }
        else
            break;
    }

    if(trenutni == nullptr)
        return;

    //uslov ako je u pitanju list
    if(trenutni->ld == nullptr && trenutni->dd == nullptr) {
        if(trenutni == korijen) {
            korijen = nullptr;
        }
        else {
            if(trenutni == trenutni->rod->ld)
                trenutni->rod->ld = nullptr;
            else
                trenutni->rod->dd = nullptr;
        }
    }
    //uslov ako cvor nema desnog djeteta
    else if(trenutni->dd == nullptr) {
        Cvor *dijete = trenutni->ld;
        dijete->rod = trenutni->rod;
        if(trenutni == korijen) {
            korijen = dijete;
        }
        else {
            if(trenutni->rod->ld == trenutni)
                trenutni->rod->ld = dijete;
            else
                trenutni->rod->dd = dijete;
        }
    }
    //uslov ako cvor nema lijevog djeteta
    else if(trenutni->ld == nullptr) {
        Cvor *dijete = trenutni->dd;
        dijete->rod = trenutni->rod;
        if(trenutni == korijen) {
            korijen = dijete;
        }
        else {
            if(trenutni->rod->ld == trenutni)
                trenutni->rod->ld = dijete;
            else
                trenutni->rod->dd = dijete;
        }
    }
    //uslov ako cvor ima oba djeteta
    else {
        Cvor *sljedbenik = Sljedbenik(trenutni);
        if(sljedbenik == sljedbenik->rod->ld)
            sljedbenik->rod->ld = sljedbenik->dd;
        else
            sljedbenik->rod->dd = sljedbenik->dd;

        if(sljedbenik->dd != nullptr)
            sljedbenik->dd->rod = sljedbenik->rod;

        sljedbenik->ld = trenutni->ld;
        sljedbenik->dd = trenutni->dd;
        sljedbenik->rod = trenutni->rod;
        trenutni->ld->rod = sljedbenik;
        trenutni->dd->rod = sljedbenik;

        if(korijen == trenutni)
            korijen = sljedbenik;
        else {
            if(trenutni == trenutni->rod->ld)
                trenutni->rod->ld = sljedbenik;
            else
                trenutni->rod->dd = sljedbenik;
        }

    }

    Cvor *trenutniTemp = Pocetak(trenutni);
    while (trenutniTemp->rod != nullptr && trenutniTemp->rod->visinaCvora == trenutniTemp->visinaCvora+1) {
        trenutniTemp->rod->visinaCvora -= 1;
        trenutniTemp = trenutniTemp->rod;
    }

    delete trenutni;
    broj_elemenata--;

    if(potrebnoBalansiranje) {
        //cout << "Balansiranje se vrsi u cvoru: " << gdjeTrebaBalansirati->el << endl;

        Cvor *pocetni = Pocetak(gdjeTrebaBalansirati);

        //uslov gdje se balansiranje vrsi sa lijeve strane korijena ili kada treba balansirati citav korijen
        if(gdjeTrebaBalansirati->el <= korijen->el){
            while(pocetni != gdjeTrebaBalansirati->rod) {
                niz.push_back(pocetni->el);
                pocetni = Sljedbenik(pocetni);
            }
        }
        //uslov gdje se balansiranje vrsi sa desne strane korijena
        else {
            while(pocetni != nullptr) {
                niz.push_back(pocetni->el);
                pocetni = Sljedbenik(pocetni);
            }
        }
        /*
        cout << "niz: ";
        for(int j = 0; j < niz.size(); j++)
            cout << niz[j] << " ";
        cout << endl;
        */

        OcistiStablo(gdjeTrebaBalansirati);

        if(korijen == nullptr) {
            Cvor *noviKorijen = KreirajBalansiranoStablo(niz, 0, niz.size()-1);
            korijen = KopirajStablo(noviKorijen, nullptr, broj_elemenata);
            //prilikom promjene pozicija u stablu tokom balansiranja, potrebno je promijeniti broj elemenata lijevo,
            //broj elemenata desno i visinu
            ResetujPodatkeCvora(korijen);
        }
        else {
            //DodajBalansiranoPodstablo(korijen, niz, 0, i-1);
            if(lijevoDijete)
                roditelj->ld = KreirajBalansiranoStablo(niz, 0, niz.size()-1);
            else
                roditelj->dd = KreirajBalansiranoStablo(niz, 0, niz.size()-1);

            korijen = KopirajStablo(korijen, nullptr, broj_elemenata);
            //prilikom promjene pozicija u stablu tokom balansiranja, potrebno je promijeniti broj elemenata lijevo,
            //broj elemenata desno i visinu
            ResetujPodatkeCvora(korijen);
        }
    }
}

template <typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::Pocetak(Cvor *trenutni) {
    if(trenutni == nullptr)
        return nullptr;
    while(trenutni->ld != nullptr)
        trenutni = trenutni->ld;

    return trenutni;
}

template <typename Tip>
bool Stablo<Tip>::Find(Tip element) {
    Cvor *trenutni = korijen;
    while(trenutni != nullptr) {
        if(element < trenutni->el)
            trenutni = trenutni->ld;
        else if(element > trenutni->el)
            trenutni = trenutni->dd;
        else
            return true;
    }

    return false;
}

template <typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::FindCvor(Tip element) {
    Cvor *trenutni = korijen;
    while(trenutni != nullptr) {
        if(element < trenutni->el)
            trenutni = trenutni->ld;
        else if(element > trenutni->el)
            trenutni = trenutni->dd;
        else
            return trenutni;
    }

    return nullptr;
}

template <typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::Sljedbenik(Cvor *cvor) {
    if(cvor->dd != nullptr) {
        Cvor *ciljaniCvor = cvor->dd;
        while(ciljaniCvor->ld != nullptr)
            ciljaniCvor = ciljaniCvor->ld;
        return ciljaniCvor;
    }
    else {
        Cvor *ciljaniCvor = cvor;
        while(ciljaniCvor->rod != nullptr && ciljaniCvor->rod->dd == ciljaniCvor)
            ciljaniCvor = ciljaniCvor->rod;
        return ciljaniCvor->rod;
    }
}


template <typename Tip>
int Stablo<Tip>::VisinaRek(Cvor *cvor){
    if(cvor == nullptr)
        return 0;

    return 1 + max(VisinaRek(cvor->ld), VisinaRek(cvor->dd));
}

template <typename Tip>
int Stablo<Tip>::Visina(Tip element){
    Cvor *trenutni = FindCvor(element);
    return VisinaRek(trenutni) - 1;
}

template <typename Tip>
bool Stablo<Tip>::Empty() {
    return broj_elemenata == 0;
}

template <typename Tip>
int Stablo<Tip>::Size(){
    return broj_elemenata;
}

template <typename Tip>
void Stablo<Tip>::InOrderRek(Cvor *cvor, void (f)(Tip&)) const {
    if(cvor->ld != nullptr)
        InOrderRek(cvor->ld, f);
    f(cvor->el);

    cout << "LD: ";
    if(cvor->ld != nullptr) f(cvor->ld->el);
    else
        cout << endl;
    cout << "DD: ";
    if(cvor->dd != nullptr) f(cvor->dd->el);
    else
        cout << endl;
    cout << endl;

    if(cvor->dd != nullptr)
        InOrderRek(cvor->dd, f);
}

template <typename Tip>
void Stablo<Tip>::InOrder(void (f)(Tip&)) const {
    if(korijen != nullptr)
        InOrderRek(korijen, f);
}

template<typename Tip>
void ispisi(Tip e){
    cout << e << endl;
}

template <typename Tip>
ostream& operator<<(ostream &ispis, const Stablo<Tip> &s){
    s.InOrder(ispisi);
    return ispis;
}

#endif // STABLO_CPP
