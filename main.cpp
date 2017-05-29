#include <iostream>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <sstream>
using namespace std;

int toInt(string str)
{
    stringstream ss;
    int temp;
    ss << str;
    ss >> temp;
    return temp;
}

class Armor {

    string nazwa;
    int armor;
    int szansaNaUnik;
    int dodatkoweZdrowie;
    int cena;

    friend class Bohater;
    friend class Arena;

    public :
        Armor(string nazwa="brak", int armor=0, int dodatkoweZdrowie=0, int szansaNaUnik=0) {
        this -> nazwa = nazwa;
        this -> armor = armor;
        this -> szansaNaUnik = szansaNaUnik;
        this -> dodatkoweZdrowie = dodatkoweZdrowie;
        this -> cena = cena;
    }

    void wyswietlStatystykiArmora() {
    cout<<this -> nazwa<<" +"<<this -> armor<<" pancerza i +"<<this -> szansaNaUnik<<"% szansy na unik +"
    <<this -> dodatkoweZdrowie<<" pkt. zdrowia"<<endl;
    }
};

class Bron {

	string nazwa;
	int atkMin;
	int atkMax;
	int cena;
    int dystans;
    int szansaNaKontre;
    int odejmowanieArmora;
    int szansaNaStuna;

    friend class Bohater;
    friend class Arena;

    public:

		Bron(string nazwa="piesci", int atkMin=1, int atkMax=4, int dystans=1,
        int szansaNaKontre=0, int odejmowanieArmora=0, int szansaNaStuna=0) {
		this -> nazwa = nazwa;
		this -> atkMin = atkMin;
		this -> atkMax = atkMax;
		this -> dystans = dystans;
		this -> szansaNaKontre = szansaNaKontre;
		this -> odejmowanieArmora = odejmowanieArmora;
		this -> szansaNaStuna = szansaNaStuna;

	}
        void wyswietlStatystykiBroni() {
        cout<<nazwa<<" - Atak minimalny: "<<atkMin<<", Atak maksymalny: "<<atkMax<<", Dystans: "<<dystans;
        if(szansaNaKontre != 0) cout<<", Szansa na kontre: "<<szansaNaKontre<<"% ";
        if(odejmowanieArmora != 0) cout<<", Odejmowanie pancerza przy ataku: -"<<odejmowanieArmora;
        if(szansaNaStuna !=0) cout<<", Szansa na ogluszenie: "<<szansaNaStuna<<"% ";
        cout<<endl;
	}

};

class Bohater {

	string nazwa;
	int atk;
	int maxHp;
	int armor;
	int szansaNaUnik; //Bedzie losowana liczba z przedzialu 1-100, jesli twoja szansaNaUnik znajduje sie w tym przedziale to unikasz
	int zloto;
	int wygraneBitwy;
	int level;
	int losujWroga;
	Bron bron;
	Armor glowa;
	Armor klata;
	Armor rece;
	Armor nogi;

	friend class Arena;
	friend void arenaPls();

	public:
		Bohater(string nazwa="Bezimienny", int atk = 1, int maxHp = 30, int armor = 1,
           int szansaNaUnik = 1,int zloto = 60, Bron bron = Bron(),Armor glowa = Armor(),
           Armor klata = Armor(), Armor rece = Armor(), Armor nogi = Armor(), int wygraneBitwy = 0, int level = 1, int losujWroga = 3) {

		this -> nazwa = nazwa;
		this -> atk = atk;
		this -> maxHp = maxHp;
		this -> armor = armor;
		this -> szansaNaUnik = szansaNaUnik;
		this -> zloto = zloto;
		this -> bron = bron;
		this -> glowa = glowa;
		this -> klata = klata;
		this -> rece = rece;
		this -> nogi = nogi;
		this -> wygraneBitwy = wygraneBitwy;
		this -> level = level;
		this -> losujWroga = losujWroga;
	}

void losujPrzeciwnika() {
    losujWroga--;
}

void przywrocLosy() {
    losujWroga = 3;
}

int zwrocLosyPrzeciwnika() {
    return losujWroga;
}

int zwrocLevel() {
    return level;
}

void aktualizujHelm(Armor helm) {

    this -> armor += helm.armor;
    this -> maxHp += helm.dodatkoweZdrowie;
    this -> szansaNaUnik += helm.szansaNaUnik;
    glowa = helm;
}

void aktualizujZbroje(Armor zbroja) {

    this -> armor += zbroja.armor;
    this -> maxHp += zbroja.dodatkoweZdrowie;
    this -> szansaNaUnik += zbroja.szansaNaUnik;
    klata = zbroja;
}

void aktualizujButy(Armor buty) {

    this -> armor += buty.armor;
    this -> maxHp += buty.dodatkoweZdrowie;
    this -> szansaNaUnik += buty.szansaNaUnik;
    nogi = buty;
}

void aktualizujRekawice(Armor rekawice) {

    this -> armor += rekawice.armor;
    this -> maxHp += rekawice.dodatkoweZdrowie;
    this -> szansaNaUnik += rekawice.szansaNaUnik;
    rece = rekawice;
}

void aktualizujBron(Bron bron) {

    this -> bron = bron;
}

void wyswietlAtak() {

	cout<<atk + bron.atkMin<<"~"<<atk + bron.atkMax;

	}

void wyswietlHP() {

	cout<<maxHp;
	}

void wyswietlArmor() {

	cout<<armor;

	}

void wyswietlSzanseNaUnik() {

	cout<<szansaNaUnik<<"%";

	}

void wyswietlDystans() {

	cout<<bron.dystans;

	}

void wyswietlSzanseNaKontre() {

	cout<<bron.szansaNaKontre<<"%";

	}

void wyswietlSzanseNaStuna() {

	cout<<bron.szansaNaStuna<<"%";

	}

void wyswietlOdejmowanieArmora()  {

	cout<<bron.odejmowanieArmora;

	}

void wyswietlNazweBohatera() {

	cout<<nazwa;

	}

int atak() {

    return rand()%(1+bron.atkMax-bron.atkMin) + bron.atkMin + atk;

	}

int odejmowanieArmora() {

	return bron.odejmowanieArmora;
	}

bool stun() {

	bool stun = false;
	int los = rand()%100+1;

	if(los <= bron.szansaNaStuna) stun = true;
	return stun;
	}

bool kontra() {
	bool kontra = false;
	int los = rand()%100+1;

	if(los <= bron.szansaNaKontre) kontra = true;
	return kontra;
	}

bool unik() {
    bool unik = false;
    int los = rand()%100+1;
    int unikZArmora = glowa.szansaNaUnik + klata.szansaNaUnik + nogi.szansaNaUnik + rece.szansaNaUnik;
    if(los <= szansaNaUnik + unikZArmora) unik = true;

    return unik;
}

int otzymajObrazenia(int dmg) {
    if( dmg > armor ) {
        wyswietlNazweBohatera(); cout<<" Otrzymal DMG: "<<dmg - armor<<endl;
        return dmg - armor;
    }
    else {
        cout<<nazwa<<" nie otrzymal obrazen"<<endl;
        return 0;
    }
}

void stracArmora(int minusArmor) {
    if(armor - minusArmor < 0) {
        armor = 0;
    }
    else {
        cout<<"Odjeto "<<minusArmor<<" pancerza"<<endl;
        armor -= minusArmor;
    }
}

void wyswietlStatystykiBohatera()
	{
	    system("cls");
        cout<<"STATYSTYKI BOHATERA"<<endl;
		cout<<"Nazwa: "<<nazwa<<endl;
		cout<<"Poziom bohatera: "<<level<<endl;
        cout<<"Wygrane walki: "<<wygraneBitwy<<endl;
		cout<<"Atak: "<<atk<<endl;
		cout<<"Armor "<<armor<<endl;
		cout<<"Max HP: "<<maxHp<<endl;
		cout<<"Szansa Na Unik: "<<szansaNaUnik<<endl;
		cout<<"Zloto: "<<zloto<<endl;
        bron.wyswietlStatystykiBroni();
		cout<<"Glowa: "; glowa.wyswietlStatystykiArmora();
		cout<<"Klatka: "; klata.wyswietlStatystykiArmora();
		cout<<"Rece: "; rece.wyswietlStatystykiArmora();
		cout<<"Nogi: "; nogi.wyswietlStatystykiArmora();

		cout<<"Nacisnij dowolny przycisk, aby wrocic do menu"<<endl;
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
        if(getch()) this -> menu();
	}

void menu() {
    system("cls");
    char wybor;

    cout<<"Witaj "; wyswietlNazweBohatera(); cout<<"! Wybierz miejsce, w ktore chesz sie udac"<<endl;
    cout<<"Wcisnij odpowiedni przycisk pokazany przy lokalizacji"<<endl;
    cout<<"\'1\' - Arena"<<endl;
    cout<<"\'2\' - Sklep z bronmi"<<endl;
    cout<<"\'3\' - Sklep z opancerzeniem"<<endl;
    cout<<"\'4\' - Statystyki bohatera"<<endl;
    cout<<"\'5\' - Sala chwaly"<<endl;
    cout<<"\'0\' - Wylacz gre"<<endl;
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    wybor = getch();

    switch (wybor) {
    case '1':
        arena();
    break;
    case '2':
        sklepZBronmi();
    break;
    case '3':
        sklepZOpancerzeniem();
    break;
    case '4':
         wyswietlStatystykiBohatera();
    break;
    case '5':
         salaChwaly();
    break;
    case '0':
        zapiszWynik();
        exit(0);
    default:
       this -> menu();
    }
}

void salaChwaly() {
    system("cls");
    int licznik=0;
    int pom=0;
    int ile;
    string linnia;
    ifstream plik;

    plik.open("wyniki.txt");
        while(getline(plik,linnia)) {
            licznik++;
        }
        ile = licznik/3;
     plik.close();
     string nazwa[ile];
     int level[ile];
     int wygrane[ile];
     licznik = 0;
     plik.open("wyniki.txt");
     while(getline(plik,linnia)) {
        switch(pom) {
        case 0:
           nazwa[licznik] = linnia;
        break;
        case 1:
            level[licznik] = toInt(linnia);
        break;
        case 2:
            wygrane[licznik] = toInt(linnia);
        break;
        }
        pom++;
        if(pom>2) {
          pom = 0;
          licznik++;
        }
     }
     plik.close();
     bool sortuj = false;
     do {
        sortuj = false;
            for(int i=1;i<ile;i++) {
                if(wygrane[i] > wygrane[i-1]) {
                    swap(wygrane[i],wygrane[i-1]);
                    swap(nazwa[i],nazwa[i-1]);
                    swap(level[i],level[i-1]);
                    sortuj = true;
                }
            }
     } while(sortuj);
    cout<<"----------Najlepsi z najlepszych----------"<<endl;
        for(int i=0;i<ile;i++) {
            cout<<i+1<<". "<<nazwa[i]<<" - Level: "<<level[i]<<" Wygrane: "<<wygrane[i]<<endl;
        }
    cout<<"\'1\' - Resetuj ranking"<<endl;
    cout<<"\'0\' - Wroc do menu"<<endl;
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    char wybor = getch();
    ofstream plik_usun;
    switch(wybor) {
    case '1':
        plik_usun.open("wyniki.txt",ios::trunc);
        plik_usun.close();
        salaChwaly();
    break;
    case '0':
        menu();
    break;
    default:
        salaChwaly();
    }
}

bool arena() {
    return true;
}

void sklepZBronmi() {
    system("cls");
    char wybor;
    cout<<"\'1\' - Szable"<<endl;
    cout<<"\'2\' - Luki"<<endl;
    cout<<"\'3\' - Topory"<<endl;
    cout<<"\'4\' - Maczugi"<<endl;
    cout<<"\'5\' - Bronie specjalne"<<endl;
    cout<<"\'0\' - Wroc do menu"<<endl;
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    wybor = getch();

    switch (wybor) {
    case '1':
    	sklepSzable();
    break;
    case '2':
    	sklepLuki();
    break;
    case '3':
    	sklepTopory();
    break;
    case '4':
    	sklepMaczugi();
    break;
    case '5':
    	sklepBronieSpecjalne();
    break;
    case '0':
        menu();
    break;
    default:
        sklepZBronmi();
    }
}

void sklepSzable() {
    wczytajSklepBronie(1);
}

void sklepLuki() {
    wczytajSklepBronie(2);
}

void sklepTopory() {
    wczytajSklepBronie(3);
}

void sklepMaczugi() {
    wczytajSklepBronie(4);
}
void sklepBronieSpecjalne() {
    wczytajSklepBronie(5);
}

void wczytajSklepBronie(int sklep) {
    system("cls");
	ifstream plik;
    switch(sklep){
    case 1:
    plik.open("bronie/Szable.txt");
    break;
    case 2:
    plik.open("bronie/Luki.txt");
    break;
    case 3:
    plik.open("bronie/Topory.txt");
    break;
    case 4:
    plik.open("bronie/Maczugi.txt");
    break;
    case 5:
    plik.open("bronie/BronieSpecjalne.txt");
    break;
    }
	if(plik.good()) {
	    string linnia;
        getline(plik,linnia);
        int ileBroni = toInt(linnia);
        int nrBroni = 0;
        int nrLinni = 0;
        string nazwa[ileBroni];
        int atkMin[ileBroni];
        int atkMax[ileBroni];
        int cena[ileBroni];
        int dystans[ileBroni];
        int szansaNaKontre[ileBroni];
        int odejmowanieArmora[ileBroni];
        int szansaNaStuna[ileBroni];
        //cout<<"Ile broni: "<<ileBroni<<endl;
        while(getline(plik,linnia)) {
            switch(nrLinni) {
                case 0:
                    nazwa[nrBroni] = linnia;
                break;
                case 1:
                    atkMin[nrBroni] = toInt(linnia);
                break;
                case 2:
                    atkMax[nrBroni] = toInt(linnia);
                break;
                case 3:
                    cena[nrBroni] = toInt(linnia);
                break;
                case 4:
                    dystans[nrBroni] = toInt(linnia);
                break;
                case 5:
                    szansaNaKontre[nrBroni] = toInt(linnia);
                break;
                case 6:
                    odejmowanieArmora[nrBroni] = toInt(linnia);
                break;
                case 7:
                    szansaNaStuna[nrBroni] = toInt(linnia);
                break;
                default:
                    cout<<"Cos poszlo nie tak!"<<endl;
            }
            if(nrLinni == 7) {
               nrLinni = -1;
               nrBroni++;
            }
            nrLinni++;

        }
        plik.close();
        cout<<"Twoje zloto: "<<zloto<<endl;
        cout<<"Twoja aktualna bron "; bron.wyswietlStatystykiBroni(); cout<<"\n\n";
        for(int i=0;i<ileBroni;i++) {
            cout<<i+1<<". "<<nazwa[i]<<" - Atak: "<<atkMin[i]<<"~"<<atkMax[i]<<", Dystans: "<<dystans[i]<<", Szansa na kontre: "<<szansaNaKontre[i]
            <<"%, Odejmowanie pancerza na atak: "<<odejmowanieArmora[i]<<", Szansa na ogluszenie: "<<szansaNaStuna[i]<<"%, Cena: "<<cena[i]<<" zlociszy"<<endl;
        }
        cout<<"\'0\' - Powrot do menu"<<endl;
        char wybor;
        int wyb;
        FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
        wybor = getch();
        wyb = wybor - '0';
        switch(wybor) {
        case '0':
            menu();
        break;
          default:
         if(wyb>0 && wyb<=ileBroni) {
            if(zloto >= cena[wyb-1]) {
                    char zakupic;
               cout<<"Czy napewno chcesz kupic "<<nazwa[wyb-1]<<" ?"<<endl;
               cout<<"T/N"<<endl;
               FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
                    zakupic = getch();
                    switch(zakupic) {
                case 't':
                case 'T':
                    zloto -= cena[wyb-1];
                    aktualizujBron(Bron(nazwa[wyb-1],atkMin[wyb-1],atkMax[wyb-1],dystans[wyb-1],szansaNaKontre[wyb-1],odejmowanieArmora[wyb-1],szansaNaStuna[wyb-1]));
                    menu();
                break;
                default:
                    switch(sklep) {
                    case 1:
                        sklepSzable();
                    break;
                    case 2:
                        sklepLuki();
                    break;
                    case 3:
                        sklepTopory();
                    break;
                    case 4:
                        sklepMaczugi();
                    break;
                    case 5:
                        sklepBronieSpecjalne();
                    break;
                    }
                }
            }
            else {
                cout<<"Za malo zlota szachraju! Wynocha!"<<endl;
                Sleep(2000);
                menu();
            }
        }
        else {
            cout<<"Nie ma takiej broni"<<endl;
            Sleep(2000);
            switch(sklep) {
                    case 1:
                        sklepSzable();
                    break;
                    case 2:
                        sklepLuki();
                    break;
                    case 3:
                        sklepTopory();
                    break;
                    case 4:
                        sklepMaczugi();
                    break;
                    case 5:
                        sklepBronieSpecjalne();
                    break;
                    }
        }
        }

	}
	else {
		cout<<"Blad przy odczytywaniu pliku"<<endl;
		Sleep(1500);
		menu();
	}
}

void sklepZOpancerzeniem() {
    system("cls");
    char wybor;
    cout<<"\'1\' - Sklep z helmami"<<endl;
    cout<<"\'2\' - Sklep z pancerzami"<<endl;
    cout<<"\'3\' - Sklep z uzbrojeniem na rece"<<endl;
    cout<<"\'4\' - Sklep z uzbrojeniem na nogi"<<endl;
    cout<<"\'0\' - Wroc do menu"<<endl;
    wybor = getch();

    switch (wybor) {
    case '0':
        menu();
    break;
    case '1':
        sklepHelmy();
    break;
    case '2':
        sklepPancerze();
    break;
    case '3':
        sklepRece();
    break;
    case '4':
        sklepNogi();
    break;
    default:
        this -> sklepZOpancerzeniem();
    }
}

void sklepHelmy() {
    wczytajSklepArmor(1);
}

void sklepPancerze() {
    wczytajSklepArmor(2);
}

void sklepRece() {
    wczytajSklepArmor(3);
}

void sklepNogi() {
    wczytajSklepArmor(4);
}

void wczytajSklepArmor(int sklep) {
    system("cls");
	ifstream plik;
    switch(sklep){
    case 1:
    plik.open("armor/Glowa.txt");
    break;
    case 2:
    plik.open("armor/Klata.txt");
    break;
    case 3:
    plik.open("armor/Rece.txt");
    break;
    case 4:
    plik.open("armor/Nogi.txt");
    break;
    }
	if(plik.good()) {
	    string linnia;
        getline(plik,linnia);
        int ileArmora = toInt(linnia);
        int nrArmora = 0;
        int nrLinni = 0;
        string nazwa[ileArmora];
        int armor[ileArmora];
        int hp[ileArmora];
        int szansaNaUnik[ileArmora];
        int cena[ileArmora];
        //cout<<"Ile Uzbrojen: "<<ileArmora<<endl;
        while(getline(plik,linnia)) {
            switch(nrLinni) {
                case 0:
                    nazwa[nrArmora] = linnia;
                break;
                case 1:
                    armor[nrArmora] = toInt(linnia);
                break;
                case 2:
                    hp[nrArmora] = toInt(linnia);
                break;
                case 3:
                    szansaNaUnik[nrArmora] = toInt(linnia);
                break;
                case 4:
                    cena[nrArmora] = toInt(linnia);
                break;
                default:
                    cout<<"Cos poszlo nie tak!"<<endl;
            }
            if(nrLinni == 4) {
               nrLinni = -1;
               nrArmora++;
            }
            nrLinni++;

        }
        plik.close();
        cout<<"Twoje zloto: "<<zloto<<endl;
        switch(sklep) {
                    case 1:
                        cout<<"Twoj aktualny helm: "; glowa.wyswietlStatystykiArmora(); cout<<"\n\n";
                    break;
                    case 2:
                        cout<<"Twoja aktualna zbroja: "; klata.wyswietlStatystykiArmora(); cout<<"\n\n";
                    break;
                    case 3:
                        cout<<"Twoje aktualne uzbrojenie na rece: "; rece.wyswietlStatystykiArmora(); cout<<"\n\n";
                    break;
                    case 4:
                        cout<<"Twoje aktualne uzbrojenie na nogi: "; nogi.wyswietlStatystykiArmora(); cout<<"\n\n";
                    break;
                    }
        for(int i=0;i<ileArmora;i++) {
            cout<<i+1<<". "<<nazwa[i]<<" - Armor: "<<armor[i]<<", Dodatkowe HP: "<<hp[i]<<", Dodatkowa szansa na unik: "<<szansaNaUnik[i]<<"%, Cena: "
            <<cena[i]<<" zlociszy"<<endl;
        }
        cout<<"\'0\' - Powrot do menu"<<endl;
        char wybor;
        int wyb;
        FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
        wybor = getch();
        wyb = wybor - '0';
        switch(wybor) {
        case '0':
            menu();
        break;
          default:
         if(wyb>0 && wyb<=ileArmora) {
            if(zloto >= cena[wyb-1]) {
                    char zakupic;
               cout<<"Czy napewno chcesz kupic "<<nazwa[wyb-1]<<" ?"<<endl;
               cout<<"T/N"<<endl;
               FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
                    zakupic = getch();
                    switch(zakupic) {
                case 't':
                case 'T':
                    zloto -= cena[wyb-1];
                    switch(sklep) {
                    case 1:
                        aktualizujHelm(Armor(nazwa[wyb-1],armor[wyb-1],hp[wyb-1],szansaNaUnik[wyb-1]));
                    break;
                    case 2:
                        aktualizujZbroje(Armor(nazwa[wyb-1],armor[wyb-1],hp[wyb-1],szansaNaUnik[wyb-1]));
                    break;
                    case 3:
                        aktualizujRekawice(Armor(nazwa[wyb-1],armor[wyb-1],hp[wyb-1],szansaNaUnik[wyb-1]));
                    break;
                    case 4:
                        aktualizujButy(Armor(nazwa[wyb-1],armor[wyb-1],hp[wyb-1],szansaNaUnik[wyb-1]));
                    break;
                    }
                    menu();
                break;
                default:
                    switch(sklep) {
                    case 1:
                        sklepHelmy();
                    break;
                    case 2:
                        sklepPancerze();
                    break;
                    case 3:
                        sklepRece();
                    break;
                    case 4:
                        sklepNogi();
                    break;
                    }
                }
            }
            else {
                cout<<"Za malo zlota szachraju! Wynocha!"<<endl;
                Sleep(2000);
                menu();
            }
        }
        else {
            cout<<"Nie ma takiej broni"<<endl;
            Sleep(2000);
            switch(sklep) {
                    case 1:
                        sklepHelmy();
                    break;
                    case 2:
                        sklepPancerze();
                    break;
                    case 3:
                        sklepRece();
                    break;
                    case 4:
                        sklepNogi();
                    break;
                }
            }
        }

	}
	else {
		cout<<"Blad przy odczytywaniu pliku"<<endl;
		Sleep(1500);
		menu();
	}
}

void wygranaBitwa(int zloto){
     przywrocLosy();
	 wygraneBitwy++;
    cout<<"\nWYGRALES BITWE"<<endl;
    if(wygraneBitwy % 4 == 0) levelUp();
    this -> zloto += 15 * level;
    cout<<"Otrzymane zloto "<<15 * level<<endl;
    cout<<"Nacisnij dowolny przycisk aby kontynuowac"<<endl;
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    if(getch()) menu();
}

void koniecGry() {
    cout<<"\nZGINALES DZIELNIE WALCZAC !"<<endl;
    cout<<"Twoje statystyki"<<endl;
        cout<<"Nazwa: "<<nazwa<<endl;
        cout<<"Poziom bohatra: "<<level<<endl;
        cout<<"Wygrane walki: "<<wygraneBitwy<<endl;
		cout<<"Atak: "<<atk<<endl;
		cout<<"Armor "<<armor<<endl;
		cout<<"Max HP: "<<maxHp<<endl;
		cout<<"Szansa Na Unik: "<<szansaNaUnik<<endl;
		cout<<"Zloto: "<<zloto<<endl;
        bron.wyswietlStatystykiBroni();
		cout<<"Glowa: "; glowa.wyswietlStatystykiArmora();
		cout<<"Klatka: "; klata.wyswietlStatystykiArmora();
		cout<<"Rece: "; rece.wyswietlStatystykiArmora();
		cout<<"Nogi: "; nogi.wyswietlStatystykiArmora();
    cout<<"Nacisnij dowolny przycisk aby wylaczyc gre"<<endl;
    zapiszWynik();
    if(getch()) exit(0);
}


void gramDalej(bool wygrana,int zloto) {
    if(wygrana) {
      wygranaBitwa(zloto) ;
    }
    else {
       koniecGry();
    }

}

void levelUp() {
	this -> maxHp += level*4;
	this -> atk += level*2;
	this -> armor += level*1;
	this -> szansaNaUnik += level*0.5;
	level++;
	cout<<"Osiagnieto nowy poziom "<<level<<endl;
	cout<<"HP: +"<<(level-1)*4;
	cout<<", Atak +"<<(level-1)*2;
	cout<<", Pancerz +"<<(level-1)*1;
	cout<<", Szansa na unik +"<<(level-1)*(int)0.5<<"pp"<<endl;
}

void zapiszWynik() {
    fstream plik;

    plik.open("wyniki.txt",ios::app | ios::out);

    if(plik.good()) {
       plik<<nazwa<<endl;
       plik<<level<<endl;
       plik<<wygraneBitwy<<endl;
    }
    else cout<<"Blad przy zapisie !"<<endl;
    plik.close();

}
};

class Wrog {

    string nazwa;
    int atkMin;
    int atkMax;
    int hp;
    int armor;
    int dystans;
    int odejmowanieArmora;
    int szansaNaUnik;
    int szansaNaKontre;
    int szansaNaStuna;

    friend class Arena;

    public:
        Wrog(string nazwa = "Lotrzyk", int atkMin = 1, int atkMax = 10, int hp = 100, int armor = 20, int dystans = 1, int odejmowanieArmora = 0,
             int szansaNaUnik = 30, int szansaNaKontre = 20, int szansaNaStuna = 0) {
             this -> nazwa = nazwa;
             this -> atkMin = atkMin;
             this -> atkMax = atkMax;
             this -> hp = hp;
             this -> armor = armor;
             this -> dystans = dystans;
             this -> odejmowanieArmora = odejmowanieArmora;
             this -> szansaNaKontre = szansaNaKontre;
             this -> szansaNaStuna = szansaNaStuna;
             this -> szansaNaUnik = szansaNaUnik;
             }

void wyswietlStatystyki() {
cout<<"\nPseudonim: "<<nazwa<<endl;
cout<<"Atak: "<<atkMin<<"~"<<atkMax<<endl;
cout<<"HP: "<<hp<<endl;
cout<<"Pancerz: "<<armor<<endl;
cout<<"Zasieg: "<<dystans<<endl;
cout<<"Odejmowanie pancerza: "<<odejmowanieArmora<<endl;
cout<<"Szansa na unik: "<<szansaNaUnik<<"% "<<endl;
cout<<"Szansa na kontre: "<<szansaNaKontre<<"% "<<endl;
cout<<"Szansa na stuna: "<<szansaNaStuna<<"% "<<endl;
}

void wyswietlAtak() {

	cout<<atkMin<<"~"<<atkMax;

	}

void wyswietlHP() {

	cout<<hp;
	}

void wyswietlArmor() {

	cout<<armor;

	}

void wyswietlSzanseNaUnik() {

	cout<<szansaNaUnik<<"%";

	}

void wyswietlDystans() {

	cout<<dystans;

	}

void wyswietlSzanseNaKontre() {

	cout<<szansaNaKontre<<"%";

	}

void wyswietlSzanseNaStuna() {

	cout<<szansaNaStuna<<"%";

	}

void wyswietlOdejmowanieArmora()  {

	cout<<odejmowanieArmora;

	}

void wyswietlNazweWroga() {

	cout<<nazwa;

	}

int atak() {

    return rand()%(1+atkMax-atkMin) + atkMin;

	}

int odejmowanieArmoraWrog() {

	return odejmowanieArmora;

	}

bool stun() {

	bool stun = false;
	int los = rand()%100+1;

	if(los <= szansaNaStuna) stun = true;
	return stun;
	}

bool kontra() {
	bool kontra = false;
	int los = rand()%100+1;

	if(los <= szansaNaKontre) kontra = true;
	return kontra;
	}

bool unik() {
    bool unik = false;
    int los = rand()%100+1;
    if(los <= szansaNaUnik) unik = true;

    return unik;
}

int otzymajObrazenia(int dmg) {

    if( dmg > armor ) {
        wyswietlNazweWroga(); cout<<" Otrzymal DMG: "<<dmg - armor<<endl;
        return dmg - armor;
    }
    else {
        cout<<nazwa<<" nie otrzymal obrazen"<<endl;
        return 0;
    }
}
void stracArmora(int minusArmor) {
    if(armor - minusArmor < 0) {
        armor = 0;
    }
    else {
        cout<<"Odjeto "<<minusArmor<<" pancerza"<<endl;
        armor -= minusArmor;
    }
}

};

class Mecz {
    friend class Arena;
    public:
    int zlotoDoWygrania;
    bool wygrana;
        Mecz(int zloto = 50, bool wygrana = true) {
        zlotoDoWygrania = zloto;
        this -> wygrana = wygrana;
        }
};

class Arena {

    int pozBohatera;
    int pozWroga;
    bool twojaTura;
    bool stun;

    Mecz mecz;
    Bohater bohater;
    Wrog wrog;

    friend class Bohater;
    friend class Wrog;

    public:
        Arena(Bohater bohater = Bohater(), Wrog wrog = Wrog(),Mecz mecz = Mecz(50), bool twojaTura = true,
            int pozBohatera = 4, int pozWroga = 9, bool stun = false) {
        this -> bohater = bohater;
        this -> wrog = wrog;
        this -> twojaTura = twojaTura;
        this -> pozBohatera = pozBohatera;
        this -> pozWroga = pozWroga;
        this -> stun = stun;
        this -> mecz = mecz;
        }

    void informacjeOBohaterach() {
    bohater.wyswietlNazweBohatera(); cout<<"\t\t:VS:\t\t"; wrog.wyswietlNazweWroga(); cout<<endl;
    bohater.wyswietlHP(); cout<<"\t\t:HP:\t\t"; wrog.wyswietlHP(); cout<<endl;
    bohater.wyswietlArmor(); cout<<"\t\t:ARMOR:\t\t"; wrog.wyswietlArmor(); cout<<endl;
    bohater.wyswietlAtak(); cout<<"\t\t:ATAK:\t\t"; wrog.wyswietlAtak(); cout<<endl;
    bohater.wyswietlDystans(); cout<<"\t\t:DYSTANS:\t"; wrog.wyswietlDystans(); cout<<endl;
    bohater.wyswietlOdejmowanieArmora(); cout<<"\t:ODEJMOWANY PANCERZ:\t"; wrog.wyswietlOdejmowanieArmora(); cout<<endl;
    bohater.wyswietlSzanseNaKontre(); cout<<"\t:SZANSA NA KONTRE:\t"; wrog.wyswietlSzanseNaKontre(); cout<<endl;
    bohater.wyswietlSzanseNaStuna(); cout<<"\t:SZANSA NA STUNA:\t"; wrog.wyswietlSzanseNaStuna(); cout<<endl;
    bohater.wyswietlSzanseNaUnik(); cout<<"\t:SZANSA NA UNIK:\t"; wrog.wyswietlSzanseNaUnik(); cout<<endl;
    }

    void poleBitwy() {

       string pole = "(------------)";      // Jest 12 pol
       pole.replace(pozBohatera,1,"@");     // Od 1 do 12
       pole.replace(pozWroga,1,"#");        // Pocztatkowe pozycje to 4 i 9
       cout<<"\n\tBohater -> @, Wrog ->#"<<endl;     //      (---@----#---)
       cout<<"\t"<<pole<<"\n"<<endl;
    }

    void interfejsWalki() {
        if(pozBohatera == 1 && pozBohatera == pozWroga - 1)
        {
            cout<<"\'1\' - Normalny atak"<<endl;
        }
        else if(pozBohatera == 1)
        {
            cout<<"\'1\' - Normalny atak"<<endl;
            cout<<"\'2\' - Krok do przodu"<<endl;
        }
        else if(pozBohatera == pozWroga - 1 && pozBohatera >= 3)
        {
            cout<<"\'1\' - Normalny atak"<<endl;
            cout<<"\'2\' - Krok do tylu"<<endl;
            cout<<"\'3\' - Skok do tylu"<<endl;
        }
        else if(pozBohatera >= 3)
        {
            cout<<"\'1\' - Normalny atak"<<endl;
            cout<<"\'2\' - Krok do tylu"<<endl;
            cout<<"\'3\' - Krok do przodu"<<endl;
            cout<<"\'4\' - Skok do tylu"<<endl;
        }
        else if(pozBohatera < 3 && pozBohatera == pozWroga - 1) {
            cout<<"\'1\' - Normalny atak"<<endl;
            cout<<"\'2\' - Krok do tylu"<<endl;
        }
        else {
            cout<<"\'1\' - Normalny atak"<<endl;
            cout<<"\'2\' - Krok do tylu"<<endl;
            cout<<"\'3\' - Krok do przodu"<<endl;
        }
    }

    void atakBohatera() {
        if(pozWroga-pozBohatera>bohater.bron.dystans) {
                    cout<<"MISS !"<<endl;
                    Sleep(1000);
                }
                else {
                if(!wrog.kontra() || stun || bohater.bron.dystans > 1) {
                    if(!wrog.unik() || stun){
                      wrog.hp -= wrog.otzymajObrazenia(bohater.atak());
                      wrog.stracArmora(bohater.odejmowanieArmora());
                      Sleep(2000);
                      if(bohater.stun()) {
                        wrog.wyswietlNazweWroga(); cout<<" ogluszony "<<endl;
                        Sleep(1000);
                            stun = true;
                        twojaTura = false;
                      }
                      else stun = false;
                    }
                    else {
                      wrog.wyswietlNazweWroga(); cout<<" wykonal unik "<<endl;
                      Sleep(2000);
                    }
                }
                    else {
                    wrog.wyswietlNazweWroga(); cout<<" Skontrowal ";
                    bohater.maxHp -= bohater.otzymajObrazenia(wrog.atak()/2);
                    Sleep(2000);
                    }
                }
    }

    void atakWroga() {
        if(!bohater.kontra() || stun) {
            if(!bohater.unik() || stun){
                bohater.maxHp -= bohater.otzymajObrazenia(wrog.atak());
                bohater.stracArmora(wrog.odejmowanieArmoraWrog());
                Sleep(2000);
                    if(wrog.stun()) {
                        bohater.wyswietlNazweBohatera(); cout<<" ogluszony "<<endl;
                        Sleep(1000);
                        stun = true;
                        twojaTura = true;
                    }
                    else stun = false;
                }
                    else {
                      bohater.wyswietlNazweBohatera(); cout<<" wykonal unik "<<endl;
                      Sleep(2000);
                    }
                }
                    else {
                    bohater.wyswietlNazweBohatera(); cout<<" Skontrowal ";
                    wrog.hp -= wrog.otzymajObrazenia(bohater.atak()/2);
                    Sleep(2000);
                    }

    }

    Mecz walka() {

    do {
        system("cls");
        informacjeOBohaterach();
        poleBitwy();
        interfejsWalki();

        if(twojaTura) {
                char wybor;
                FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
            wybor = getch();
          if(pozBohatera == 1 && pozBohatera == pozWroga - 1)  {
            switch(wybor) {
            case '1':
                atakBohatera();
            break;
            case 'k':
            wrog.hp = 0;
            break;
            default :
                walka();
            }
          }
          else if(pozBohatera == 1) {
            switch(wybor) {
            case '1':
                atakBohatera();
            break;
            case '2':
                pozBohatera++;
                bohater.wyswietlNazweBohatera(); cout<<" Krok w przod"<<endl;
                Sleep(1000);
            break;
            case 'k':
                wrog.hp = 0;
                break;
            default :
                walka();
            }
          }
          else if(pozBohatera == pozWroga - 1 && pozBohatera < 3) {
            switch(wybor) {
                case '1':
                    atakBohatera();
                break;
                case '2':
                    pozBohatera--;
                    bohater.wyswietlNazweBohatera(); cout<<" Krok w tyl"<<endl;
                    Sleep(1000);
                break;
                case 'k':
                wrog.hp = 0;
                break;
                default :
                    walka();
                }
            }
            else if(pozBohatera == pozWroga - 1 && pozBohatera >= 3) {
               switch(wybor) {
                case '1':
                    atakBohatera();
                break;
                case '2':
                    pozBohatera--;
                    bohater.wyswietlNazweBohatera(); cout<<" Krok w tyl"<<endl;
                    Sleep(1000);
                break;
                case '3':
                    pozBohatera -= 2;
                    bohater.wyswietlNazweBohatera(); cout<<" Skok w tyl"<<endl;
                break;
                case 'k':
                wrog.hp = 0;
                break;
                default :
                    walka();
                }
             }
             else if(pozBohatera >= 3) {
                 switch(wybor) {
                case '1':
                    atakBohatera();
                break;
                case '2':
                    pozBohatera--;
                    bohater.wyswietlNazweBohatera(); cout<<" Krok w tyl"<<endl;
                    Sleep(1000);
                break;
                case '3':
                    pozBohatera++;
                    bohater.wyswietlNazweBohatera(); cout<<" Krok w przod"<<endl;
                    Sleep(1000);
                break;
                case '4':
                    pozBohatera -= 2;
                    bohater.wyswietlNazweBohatera(); cout<<" Skok w tyl"<<endl;
                    Sleep(1000);
                break;
                case 'k':
                wrog.hp = 0;
                break;
                default :
                    walka();
                }
             }
            else if(pozBohatera < 3 && pozBohatera == pozWroga - 1) {
                 switch(wybor) {
                case '1':
                    atakBohatera();
                break;
                case '2':
                    pozBohatera--;
                    bohater.wyswietlNazweBohatera(); cout<<" Krok w tyl"<<endl;
                    Sleep(1000);
                break;
                case 'k':
                wrog.hp = 0;
                break;
                default :
                    walka();
                }
            }
          else {
            switch(wybor) {
            case '1':
                atakBohatera();
            break;
            case '2':
                pozBohatera--;
                bohater.wyswietlNazweBohatera(); cout<<" Krok w tyl"<<endl;
                Sleep(1000);
            break;
            case '3':
                pozBohatera++;
                bohater.wyswietlNazweBohatera(); cout<<" Krok w przod"<<endl;
                Sleep(1000);
            break;
            case '4':
                if(pozBohatera >= 3) {
                pozBohatera -= 2;
                bohater.wyswietlNazweBohatera(); cout<<" Skok w tyl"<<endl;
                Sleep(1000);
                }
                else walka();
            break;
            case 'k':
                wrog.hp = 0;
            break;
            default :
                walka();
            }
          }
        }
        else {
        	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
            if(pozWroga - pozBohatera > wrog.dystans) {
                pozWroga--;
                wrog.wyswietlNazweWroga(); cout<<" Krok w przod "<<endl;
                Sleep(1000);
            }
            else if(pozWroga - wrog.dystans <= pozBohatera && pozWroga - 1 == pozBohatera && wrog.dystans > 1) {
                if(pozWroga + 2 <= 12) {
                pozWroga += 2;
                wrog.wyswietlNazweWroga(); cout<<" Skok do tylu "<<endl;
                Sleep(1000);
                }
                else atakWroga();
            }
            else {
             atakWroga();
            }
        }

    twojaTura = !twojaTura;
    //Sleep(2000);
    } while( bohater.maxHp > 0 && wrog.hp > 0);
    if(bohater.maxHp < wrog.hp) mecz.wygrana = false;
    system("cls");
    informacjeOBohaterach();
    poleBitwy();
    return mecz;
    }

};

Wrog generujWroga(int level) {
    int klasa = rand()%8;
    string nazwa = "Lotrzyk";
    int atkMin = 0;
    int atkMax = 0;
    int hp = 0;
    int armor = 0;
    int dystans = 1;
    int odejmowanieArmora = 0;
    int szansaNaUnik = 0;
    int szansaNaKontre = 0;
    int szansaNaStuna = 0;

    switch(klasa) {
    case 0: //tank
        nazwa = "Tank";
        atkMin = 1.5 * level;
        atkMax = 2.5 * level;
        hp = 32 * level;
        armor = 3.5 * level;
        odejmowanieArmora = 0.5 * level;
        szansaNaUnik = level;
        szansaNaStuna = level;
    break;
    case 1: //dmg
        nazwa = "Potezny zbir";
        atkMin = 2.5 * level;
        atkMax = 5.5 * level;
        hp = 20 * level;
        armor = 1.5 * level;
        szansaNaUnik = 1.5 * level;
        szansaNaKontre = 3 * level;
    break;
    case 2: //przebicie
        nazwa = "Topornik";
        atkMin = 1 * level;
        atkMax = 2.5 * level;
        hp = 25 * level;
        armor = 1.2 * level;
        odejmowanieArmora = 1.5 * level;
        szansaNaStuna = 2 * level;
    break;
    case 3: //lucznik
        nazwa = "Legolas";
        atkMin = level;
        atkMax = 3 * level;
        hp = 17 * level;
        armor = level;
        dystans = 1.9 * level;
        odejmowanieArmora = 0.4 * level;
        szansaNaUnik = 3.5 * level;
    break;
    case 4: //maczuga
        nazwa = "Flinston";
        atkMin = level;
        atkMax = 4.5 * level;
        hp = 30 * level;
        armor = 2.4 * level;
        odejmowanieArmora = 0.5 * level;
        szansaNaStuna = 4 * level;
    break;
    case 5: //kontra
        nazwa = "Fiora";
        atkMin = 3 * level;
        atkMax = 4.5 * level;
        hp = 22 * level;
        armor = 2 * level;
        szansaNaUnik = 1.5 * level;
        szansaNaKontre = 5 * level;
    break;
    case 6: //balanced
        nazwa = "Mistrz broni";
        atkMin = 2 * level;
        atkMax = 4 * level;
        hp = 20 * level;
        armor = 1.5 * level;
        odejmowanieArmora = 0.9 * level;
        szansaNaKontre = 1.5 * level;
        szansaNaStuna = level;
        szansaNaUnik = 2 * level;
    break;
    case 7: //op
        nazwa = "Master disaster";
        atkMin = 3 * level;
        atkMax = 4.5 * level;
        hp = 25 * level;
        armor = 2 * level;
        odejmowanieArmora = 1 * level;
        szansaNaKontre = 1.5 * level;
        szansaNaStuna = 1.4 * level;
        szansaNaUnik = 2 * level;
    break;
    }
    return Wrog(nazwa, atkMin, atkMax, hp, armor, dystans, odejmowanieArmora, szansaNaUnik, szansaNaKontre, szansaNaStuna);
}

Bohater startGry() {
    system("cls");
    string nazwa;
	cout<<"Witaj w Szable I Pantofle v 0.1"<<endl;
	cout<<"Podaj nazwe bohatera: ";
	getline(cin,nazwa);

	if(nazwa == "jestemoszustem") {
            ifstream plik;
            string tekst;
            int licznik = 0;
            int atak;
            int hp;
            int armor;
            int szansaNaUnik;
            int zloto;
            plik.open("postac.txt");
            if(plik.good()) {
                while(getline(plik,tekst)) {

                    switch(licznik) {
                    case 0:
                        nazwa = tekst;
                    break;
                    case 1:
                        atak = toInt(tekst);
                    break;
                    case 2:
                        hp = toInt(tekst);
                    break;
                    case 3:
                        armor = toInt(tekst);
                    break;
                    case 4:
                        szansaNaUnik = toInt(tekst);
                    break;
                    case 5:
                        zloto = toInt(tekst);
                    break;
                    }
                    licznik++;
                }
            }
            else {
                cout<<"Blad przy wczytywaniu postaci"<<endl;
                return Bohater();
            }
            plik.close();
            return Bohater(nazwa,atak,hp,armor,szansaNaUnik,zloto);

	}
	else return Bohater(nazwa);
}

int main()
{
    srand(time(0));
    Bohater bohater = startGry();
    Wrog wrog;
    Arena arena;
    Mecz mecz;
    Bohater bohaterKopia;
    bohater.menu();
    // Paskudna arena
    bool reset = false;
    do {
    system("cls");
    char wybor;
    if(bohater.zwrocLosyPrzeciwnika()-1 < 0 && !reset) cout<<"Losy: "<<0<<endl;
    else cout<<"Losy: "<<bohater.zwrocLosyPrzeciwnika()-1<<endl;
    if(bohater.zwrocLosyPrzeciwnika() >= 1 && !reset) {
      wrog = generujWroga(bohater.zwrocLevel());
    }
    reset = false;
    wrog.wyswietlStatystyki();
    cout<<"\n\'1\' - Walcz"<<endl;
    cout<<"\'2\' - Wylosuj innego przeciwnika"<<endl;
    cout<<"\'0\' - Wroc do menu"<<endl;
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    wybor = getch();
        switch (wybor) {
        case '0':
            bohater.menu();
        break;
        case '1':
            bohaterKopia = bohater;
            arena = Arena(bohaterKopia,wrog);
            mecz = arena.walka();
            bohater.gramDalej(mecz.wygrana, mecz.zlotoDoWygrania);
        break;
        case '2':
            if(bohater.zwrocLosyPrzeciwnika() > 0) bohater.losujPrzeciwnika();
        break;
        default:
            reset = true;
        break;
        }
    } while(bohater.arena());
// Koniec paskudnej areny
}
