#include <iostream>
#include "stablo.h"
using namespace std;

void Ispisi(int &broj) {
    cout << broj << " ";
}

int main() {
    Stablo<int> s; //konstruktor bez parametara
    //poziv Insert funkcije vise puta, radi probavanja raznih kombinacija kreiranja binarnog stabla. Iz tog razloga neki
    //pozivi ce biti zakomentarisani
    s.Insert(50);
    //s.Insert(55);
    s.Insert(30);
    s.Insert(10);
    s.Insert(60);
    s.Insert(100);
    s.Insert(80);
    s.Insert(40);
    s.Insert(70);
    s.Insert(90);
    //s.Insert(50);
    s.Insert(8);
    s.Insert(55);
    //s.Insert(20);
    //s.Insert(2);
    //s.Insert(3);
    s.Insert(35);
    s.Insert(42);
    s.Insert(57);
    s.Insert(58);
    s.Insert(56);
    s.Insert(9);
    s.Insert(75);
    s.Insert(68);
    s.Insert(74);
    s.Insert(37);
    //s.Insert(67);
    //s.Insert(73);
    //s.Insert(72);
    //s.Insert(103);


    //situacija kada brisemo element gdje je potrebno balansirati citavo stablo, te potom unos novog elementa na novo
    //balansirano stablo. Npr za elemente: 55,30,10,60,100,80,40,70,90,50,75.
    //s.Erase(30);
    //s.Insert(8);


    //situacija kada brisemo element gdje je potrebno balansirati podstablo, te potom unos novog elementa na novo
    //balansirano stablo. Npr za elemente: 50,30,10,60,100,80,40,70,90,8,55,9,35,42,57,58,56,75,68,74,37
    //s.Erase(10);
    //s.Insert(12);

    //ispis elemenata stabla zajedno sa njegovim lijevim i desnim dijetetom preko operatora <<
    //cout << "ispis sa operatorom << : " << endl;
    cout << s << endl;

    /*
    //ispis elemenata stabla pomocu funkcije InOrder i funkcije Ispisi koja se prosljedjuje kao parametar
    //funkcije InOrder
    s.InOrder(Ispisi);
    cout << endl;
    */

    //ispisivanja broja elemenata stabla
    //cout << "broj elemenata: " << s.Size() << endl;


    /*
    //prikaz da li se odredjeni element nalazi unutar stabla
    if(s.Find(40))
        cout << "Element se nalazi u stablu!" << endl;
    else
        cout << "Element se ne nalazi u stablu!" << endl;
    */


    //prikaz visine odredjenog cvora unutar stabla
    //cout << "visina: " << s.Visina(50) << endl;


    /*
    Stablo<int> s1;

    s1 = Stablo<int>(s); //konstruktor kopije i pomjerajuci operator dodjele
    cout << "s1: " << endl;
    cout << s1 << endl;

    Stablo<int> s2;

    s2 = s; //operator dodjele
    cout << "s2: " << endl;
    cout << s2 << endl;
    */

    /*
    Stablo<int> s4(s); //konstruktor kopije
    cout << "s4: " << endl;
    cout << s4 << endl;
    cout << "broj elemenata s4 je: " << s4.Size() << endl;
    if(s4.Empty())
        cout << "Stablo s4 je prazno!" << endl;
    else
        cout << "Stablo s4 nije prazno!" << endl;
    */

    /*
    //provjera da li je stablo prazno ili ne
    Stablo<int> s5;
    if(s5.Empty())
        cout << "Stablo s5 je prazno!" << endl;
    else
        cout << "Stablo s5 nije prazno!" << endl;
    */

    return 0;
}
