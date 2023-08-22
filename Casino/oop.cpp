#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

#define MAX 81
#define MAX2 31

class Igrac {

public:
    static int count;
    Igrac(char *ime, int balans) {
        this->identifikator = count+1;
        strcpy(this->ime, ime);
        this->balans = balans;
        count++;
    }

    Igrac(const Igrac& igrac) {
        this->identifikator = igrac.identifikator;
        this->ime[MAX] = igrac.ime[MAX];
        this->balans = igrac.balans;
    }

    int getIdentifikator() {
        return identifikator;
    }

    char* getIme() {
        return ime;
    }

    int getBalans() {
        return balans;
    }

    void setBalans(int balans) {
        this->balans = balans;
    }

private:
    int identifikator;
    char ime[MAX];
    int balans;
};
int Igrac::count;

class Skor {

public:
    double getRezultat() {
        return rezultat;
    }

    Igrac getIgraca() {
        return igrac;
    }

    void setRezultat(double rezultat) {
        this->rezultat = rezultat;
    }

    void setIgrac(const Igrac& igrac) {
        this->igrac = igrac;
    }

private:
    double rezultat = 0;
    Igrac igrac;
};

class Igra {

public:

    char* getNaziv() {
        return naziv;
    }

    vector<Skor> getListaSkorova() {
        return listaSkorova;
    }

private:
    char naziv[MAX2];
    vector<Skor> listaSkorova;
};

class Pseudorulet: public Igra {
private:
    int krajnjiIshod = 0;
    bool niz[36];
    char boja;
    bool parniBrojevi;

public:
    Pseudorulet() {
        for(int i = 0; i < 36; i++) {
            niz[i] = false;
        }
        this->boja = 'r';
        this->parniBrojevi = false;
    }

    void postaviNiz(int j) {
        for(int i = 0; i < 36; i++) {
            niz[i] = false;
        }
        niz[j] = true;
    }

    void postaviParnost(bool paranBr) {
        this->parniBrojevi = paranBr;
    }

    void ponistiParnost(bool paranBr) {
        parniBrojevi = false;
    }

    void postaviBoju(char boja) {
        this->boja = boja;
    }

    void smestiUKrajnjiIshod() {
        krajnjiIshod = rand() % 37;
    }

    int getKrajnjiIshod() {
        return krajnjiIshod;
    }

    bool parnostBroja() {
        return krajnjiIshod % 2 == 0;
    }

    bool daLijeBojaCrvena() {
        if (krajnjiIshod > 0 && krajnjiIshod < 10 && krajnjiIshod % 2 == 1) {
            return true;
        }
        else if (krajnjiIshod > 10 && krajnjiIshod < 19 && krajnjiIshod % 2 == 0) {
            return true;
        }
        else if (krajnjiIshod > 18 && krajnjiIshod < 28 && krajnjiIshod % 2 == 1) {
            return true;
        }
        else if (krajnjiIshod > 29 && krajnjiIshod < 37 && krajnjiIshod % 2 == 0) {
            return true;
        }
        return false;
    }

};

class Blekdzek : public Igra {
private:
    int spilKarata[52];
    int rukaIgraca[9];
    int rukaDiler[9];

public:
    Blekdzek() {
        for (int i = 0, j = 1; i < 52; i++) {
            if (i % 4 == 0 && i != 0) {
                j++;
            }
            spilKarata[i] = j;
        }
        for (int i = 0; i < 52; i++) {
            int k1 = rand() % 52; int k2 = rand() % 52;
            int tmp = spilKarata[k1];
            spilKarata[k1] = spilKarata[k2];
            spilKarata[k2] = tmp;


        }
        for (int i = 0; i < 9; i++) {
            rukaIgraca[i] = 0;
        }
        for (int i = 0; i < 9; i++) {
            rukaDiler[i] = 0;
        }
    }

    int slucajanBroj(){
        return rand() % 13 + 1;
    }

    int trenutanRezultat() {
        int sum = 0;
        for (int i = 0; i < 9; i++) {
            if (rukaIgraca[i] > 1 && rukaIgraca[i] < 11) {
                sum += rukaIgraca[i];
            }
            else if (rukaIgraca[i] > 10 && rukaIgraca[i] < 14) {
                sum += 1;
            }
            else if(rukaIgraca[i] != 0){
                if (sum > 10){
                    sum += 1;
                }
                else {
                    sum += 11;
                }
            }
        }
        return sum;
    }

    void izvuciKartu() {
        int izvucenaKarta = 0;

        for (int i = 0; i < 52; i++) {
            if (spilKarata[i] != 0) {
                izvucenaKarta = spilKarata[i];
                spilKarata[i] = 0;
                break;
            }
        }
        for (int i = 0; i < 9; i++) {
            if (rukaIgraca[i] == 0) {
                rukaIgraca[i] = izvucenaKarta;
                break;
            }
        }
    }

    int trenutanRezultatDiler() {
        int sum = 0;
        for (int i = 0; i < 9; i++) {
            if (rukaDiler[i] > 1 && rukaDiler[i] < 11) {
                sum += rukaDiler[i];
            }
            else if (rukaDiler[i] > 10 && rukaDiler[i] < 14) {
                sum += 1;
            }
            else if(rukaDiler[i] != 0){
                if (sum > 10){
                    sum += 1;
                }
                else {
                    sum += 11;
                }
            }
        }
        return sum;
    }

    void izvuciKartuDiler() {
        int izvucenaKarta = 0;

        for (int i = 0; i < 52; i++) {
            if (spilKarata[i] != 0) {
                izvucenaKarta = spilKarata[i];
                spilKarata[i] = 0;
                break;
            }
        }
        for (int i = 0; i < 9; i++) {
            if (rukaDiler[i] == 0) {
                rukaDiler[i] = izvucenaKarta;
                break;
            }
        }
    }

    bool randomGenerisan() {
        int k = (rand() % 11) + 15;
        if(k > trenutanRezultat() && k < 22) {
            return false;
        }
        else {
            return true;
        }
    }

};

class Kazino {

public:
    Kazino(int budzet) {
        this->budzet = budzet;
    }

    int getBudzet() {
        return budzet;
    }

    void setBudzet(int budzet) {
        this->budzet = budzet;
    }

    void dodajIgru(Igra igra) {
        listaIgara.push_back(igra);
    }

private:
    vector<Igra> listaIgara;
    int budzet;
};

void blekdzekIspis(Igrac& noviIgrac, int zbirIgraca, int zbirDilera) {
    string ispis = " ------------------------------------------------------------\n";
    for(int i = 0; i < 13; i++) {
        ispis += "|";
        if(i == 1) {
            ispis += "   IGRAC:                  KAZINO                           ";
        }
        else if(i == 2) {
            ispis += "   ";
            ispis += noviIgrac.getIme();
            for(int j = 0; j < 57 - strlen(noviIgrac.getIme()); j++) {
                ispis += " ";
            }
        }
        else if(i == 3) {
            ispis += "                          BLEKDZEK                          ";
        }
        else if(i == 6) {
            ispis += "                IGRAC: ";
            if(zbirIgraca < 10) {
                ispis += "0";
            }
            ispis += to_string(zbirIgraca);
            ispis += "     ";
            ispis += "     DILER: ";
            if(zbirDilera < 10) {
                ispis += "0";
            }
            ispis += to_string(zbirDilera);
            ispis += "                ";
        }
        else if(i == 9) {
            ispis += "        IZVUCI KARTU(1)                  FOLD(2)            ";
        }
        else {
            ispis += "                                                            ";
        }
        ispis += "|\n";
    }
    ispis += " ------------------------------------------------------------\n";

    printf("%s", ispis.c_str());
}

void blekdzek(Igrac& noviIgrac, Kazino& kazino) {

    Blekdzek igra;
    igra.izvuciKartu();
    igra.izvuciKartu();
    igra.izvuciKartuDiler();
    igra.izvuciKartuDiler();
    int zbirIgrac = igra.trenutanRezultat();
    int zbirDiler = igra.trenutanRezultatDiler();
    char c;

    while(1) {
        blekdzekIspis(noviIgrac, zbirIgrac, zbirDiler);
        if(zbirIgrac == 21) {
            printf("WIN\n");
            noviIgrac.setBalans(noviIgrac.getBalans()+3);
            kazino.setBudzet(kazino.getBudzet()-3);
            break;
            // WIN
        }
        else if(zbirIgrac > 21 || zbirDiler == 21) {
            printf("LOSE\n");
            noviIgrac.setBalans(noviIgrac.getBalans()-3);
            kazino.setBudzet(kazino.getBudzet()+3);
            break;
            // LOSE
        }
        else if(zbirDiler > 21) {
            printf("WIN\n");
            noviIgrac.setBalans(noviIgrac.getBalans()+3);
            kazino.setBudzet(kazino.getBudzet()-3);
            break;
            // WIN
        }
        scanf("%c", &c);
        getchar();
        if(c == '1') {
            igra.izvuciKartu();
            igra.izvuciKartuDiler();
            zbirIgrac = igra.trenutanRezultat();
            zbirDiler = igra.trenutanRezultatDiler();
            // IZVUCI KARTU
        }
        else if(c == '2') {
            if(igra.randomGenerisan()) {
                printf("WIN\n");
                noviIgrac.setBalans(noviIgrac.getBalans()+3);
                kazino.setBudzet(kazino.getBudzet()-3);
            }
            else {
                printf("LOSE\n");
                noviIgrac.setBalans(noviIgrac.getBalans()-3);
                kazino.setBudzet(kazino.getBudzet()+3);
            }
            break;
            // FOLD
        }
    }
}

void rulijaIzaberi(Igrac& noviIgrac) {
    string ispis = " ------------------------------------------------------------\n";
    for(int i = 0; i < 13; i++) {
        ispis += "|";
        if(i == 1) {
            ispis += "   IGRAC:                  KAZINO                           ";
        }
        else if(i == 2) {
            ispis += "   ";
            ispis += noviIgrac.getIme();
            for(int j = 0; j < 57 - strlen(noviIgrac.getIme()); j++) {
                ispis += " ";
            }
        }
        else if(i == 3) {
            ispis += "                           RULIJA                           ";
        }
        else if(i == 6) {
            ispis += "                NA STA ZELITE DA SE KLADITE?                ";
        }
        else if(i == 7) {
            ispis += "                      POSTAVI BROJ(+=)                      ";
        }
        else if(i == 8) {
            ispis += "                      POSTAVI BOJU(*=)                      ";
        }
        else if(i == 9) {
            ispis += "                   POSTAVI PARAN BROJ(/=)                   ";
        }
        else {
            ispis += "                                                            ";
        }
        ispis += "|\n";
    }
    ispis += " ------------------------------------------------------------\n";

    printf("%s", ispis.c_str());
}

void rulijaB(Igrac& noviIgrac) {
    string ispis = " ------------------------------------------------------------\n";
    for(int i = 0; i < 13; i++) {
        ispis += "|";
        if(i == 1) {
            ispis += "   IGRAC:                  KAZINO                           ";
        }
        else if(i == 2) {
            ispis += "   ";
            ispis += noviIgrac.getIme();
            for(int j = 0; j < 57 - strlen(noviIgrac.getIme()); j++) {
                ispis += " ";
            }
        }
        else if(i == 3) {
            ispis += "                           RULIJA                           ";
        }
        else if(i == 6) {
            ispis += "                      PONISTI BROJ([])                      ";
        }
        else if(i == 8) {
            ispis += "                      POTVRDI IZBOR(1)                      ";
        }
        else {
            ispis += "                                                            ";
        }
        ispis += "|\n";
    }
    ispis += " ------------------------------------------------------------\n";

    printf("%s", ispis.c_str());
}

void rulijaPB(Igrac& noviIgrac) {
    string ispis = " ------------------------------------------------------------\n";
    for(int i = 0; i < 13; i++) {
        ispis += "|";
        if(i == 1) {
            ispis += "   IGRAC:                  KAZINO                           ";
        }
        else if(i == 2) {
            ispis += "   ";
            ispis += noviIgrac.getIme();
            for(int j = 0; j < 57 - strlen(noviIgrac.getIme()); j++) {
                ispis += " ";
            }
        }
        else if(i == 3) {
            ispis += "                           RULIJA                           ";
        }
        else if(i == 6) {
            ispis += "                   PONISTI PARAN BROJ(-=)                   ";
        }
        else if(i == 8) {
            ispis += "                      POTVRDI IZBOR(1)                      ";
        }
        else {
            ispis += "                                                            ";
        }
        ispis += "|\n";
    }
    ispis += " ------------------------------------------------------------\n";

    printf("%s", ispis.c_str());
}

void rulijaIzaberiBr(Igrac& noviIgrac) {
    string ispis = " ------------------------------------------------------------\n";
    for(int i = 0; i < 13; i++) {
        ispis += "|";
        if(i == 1) {
            ispis += "   IGRAC:                  KAZINO                           ";
        }
        else if(i == 2) {
            ispis += "   ";
            ispis += noviIgrac.getIme();
            for(int j = 0; j < 57 - strlen(noviIgrac.getIme()); j++) {
                ispis += " ";
            }
        }
        else if(i == 3) {
            ispis += "                           RULIJA                           ";
        }
        else if(i == 6) {
            ispis += "         UNESITE BROJ NA KOJI ZELITE DA SE KLADITE          ";
        }
        else if(i == 7) {
            ispis += "                      (BROJEVI 1 - 36)                      ";
        }
        else {
            ispis += "                                                            ";
        }
        ispis += "|\n";
    }
    ispis += " ------------------------------------------------------------\n";

    printf("%s", ispis.c_str());
}

void rulijaIzaberiBoju(Igrac& noviIgrac) {
    string ispis = " ------------------------------------------------------------\n";
    for(int i = 0; i < 13; i++) {
        ispis += "|";
        if(i == 1) {
            ispis += "   IGRAC:                  KAZINO                           ";
        }
        else if(i == 2) {
            ispis += "   ";
            ispis += noviIgrac.getIme();
            for(int j = 0; j < 57 - strlen(noviIgrac.getIme()); j++) {
                ispis += " ";
            }
        }
        else if(i == 3) {
            ispis += "                           RULIJA                           ";
        }
        else if(i == 6) {
            ispis += "         UNESITE BOJU NA KOJI ZELITE DA SE KLADITE          ";
        }
        else if(i == 7) {
            ispis += "                BOJA: r(crvena) ili c(crna)                 ";
        }
        else {
            ispis += "                                                            ";
        }
        ispis += "|\n";
    }
    ispis += " ------------------------------------------------------------\n";

    printf("%s", ispis.c_str());
}

void rulijaIzaberiParnost(Igrac& noviIgrac) {
    string ispis = " ------------------------------------------------------------\n";
    for(int i = 0; i < 13; i++) {
        ispis += "|";
        if(i == 1) {
            ispis += "   IGRAC:                  KAZINO                           ";
        }
        else if(i == 2) {
            ispis += "   ";
            ispis += noviIgrac.getIme();
            for(int j = 0; j < 57 - strlen(noviIgrac.getIme()); j++) {
                ispis += " ";
            }
        }
        else if(i == 3) {
            ispis += "                           RULIJA                           ";
        }
        else if(i == 6) {
            ispis += "        UNESITE PARNOST NA KOJU ZELITE DA SE KLADITE        ";
        }
        else if(i == 7) {
            ispis += "              PARNOST: p(paran) ili n(neparan)              ";
        }
        else {
            ispis += "                                                            ";
        }
        ispis += "|\n";
    }
    ispis += " ------------------------------------------------------------\n";

    printf("%s", ispis.c_str());
}

void rulija(Igrac& noviIgrac, Kazino& kazino) {

    Pseudorulet rulija;

    char izbor[3];
    int br;
    char c;

    while(1) {
        rulijaIzaberi(noviIgrac);
        scanf("%s", izbor);
        getchar();
        if(strcmp(izbor, "+=") == 0) {
            rulijaIzaberiBr(noviIgrac);
            scanf("%d", &br);
            rulijaB(noviIgrac);
            scanf("%s", izbor);
            if(strcmp(izbor, "[]") == 0) {
                continue;
            }
            rulija.postaviNiz(br);
            rulija.smestiUKrajnjiIshod();
            printf("IZVUCEN BROJ: %d\n", rulija.getKrajnjiIshod());
            if(br == rulija.getKrajnjiIshod()) {
                // WIN
                printf("WIN\n");
                noviIgrac.setBalans(noviIgrac.getBalans()+3);
                kazino.setBudzet(kazino.getBudzet()-3);
            }
            else {
                // LOSE
                printf("LOSE\n");
                noviIgrac.setBalans(noviIgrac.getBalans()-3);
                kazino.setBudzet(kazino.getBudzet()+3);
            }
        }
        else if(strcmp(izbor, "*=") == 0) {
            rulijaIzaberiBoju(noviIgrac);
            scanf("%c", &c);
            rulija.postaviBoju(c);
            rulija.smestiUKrajnjiIshod();
            if(rulija.daLijeBojaCrvena()) {
                printf("BOJA: CRVENA\n");
            }
            else {
                printf("BOJA: CRNA\n");
            }
            if(rulija.daLijeBojaCrvena() && c == 'r' || !rulija.daLijeBojaCrvena() && c == 'c') {
                // WIN
                printf("WIN\n");
                noviIgrac.setBalans(noviIgrac.getBalans()+3);
                kazino.setBudzet(kazino.getBudzet()-3);
            }
            else {
                // LOSE
                printf("LOSE\n");
                noviIgrac.setBalans(noviIgrac.getBalans()-3);
                kazino.setBudzet(kazino.getBudzet()+3);
            }
        }
        else if(strcmp(izbor, "/=") == 0) {
            rulijaIzaberiParnost(noviIgrac);
            scanf("%c", &c);
            getchar();
            rulijaPB(noviIgrac);
            scanf("%s", izbor);
            if(strcmp(izbor, "-=") == 0) {
                continue;
            }
            rulija.postaviParnost(c);
            rulija.smestiUKrajnjiIshod();
            if(rulija.parnostBroja()) {
                printf("PARNOST: PARAN\n");
            }
            else {
                printf("PARNOST: NEPARAN\n");
            }
            if(rulija.parnostBroja() && c == 'p' || !rulija.parnostBroja() && c == 'n') {
                // WIN
                printf("WIN\n");
                noviIgrac.setBalans(noviIgrac.getBalans()+3);
                kazino.setBudzet(kazino.getBudzet()-3);
            }
            else {
                // LOSE
                printf("LOSE\n");
                noviIgrac.setBalans(noviIgrac.getBalans()-3);
                kazino.setBudzet(kazino.getBudzet()+3);
            }
        }
        break;
    }
}

void pocetniProzor() {
    string ispis = " ------------------------------------------------------------\n";
    for(int i = 0; i < 13; i++) {
        ispis += "|";
        if(i == 3) {
            ispis += "                           KAZINO                           ";
        }
        else if(i == 6) {
            ispis += "             PRITISNITE ENTER DA ZAPOCNETE IGRU             ";
        }
        else if(i == 10) {
            ispis += "                                              Made by:      ";
        }
        else if(i == 11) {
            ispis += "                                            Marko Mileski   ";
        }
        else {
            ispis += "                                                            ";
        }
        ispis += "|\n";
    }
    ispis += " ------------------------------------------------------------\n";

    printf("%s", ispis.c_str());
}

void izaberiIgraca() {
    string ispis = " ------------------------------------------------------------\n";
    for(int i = 0; i < 13; i++) {
        ispis += "|";
        if(i == 3) {
            ispis += "                           KAZINO                           ";
        }
        else if(i == 6) {
            ispis += "                     UNESITE IME IGRACA                     ";
        }
        else if(i == 7) {
            ispis += "                         (JEDNA REC)                        ";
        }
        else {
            ispis += "                                                            ";
        }
        ispis += "|\n";
    }
    ispis += " ------------------------------------------------------------\n";

    printf("%s", ispis.c_str());
}

void potrosenBalans() {
    string ispis = " ------------------------------------------------------------\n";
    for(int i = 0; i < 13; i++) {
        ispis += "|";
        if(i == 3) {
            ispis += "                           KAZINO                           ";
        }
        else if(i == 6) {
            ispis += "                 IGRAC POTROSIO SAV BALANS!                 ";
        }
        else {
            ispis += "                                                            ";
        }
        ispis += "|\n";
    }
    ispis += " ------------------------------------------------------------\n";

    printf("%s", ispis.c_str());
}

void izaberiIgru(Igrac& noviIgrac) {
    string ispis = " ------------------------------------------------------------\n";
    for(int i = 0; i < 13; i++) {
        ispis += "|";
        if(i == 1) {
            ispis += "   IGRAC:                                    BALANS:   ";
            if(noviIgrac.getBalans() < 10) {
                ispis += "0";
            }
            ispis += to_string(noviIgrac.getBalans());
            ispis += "   ";
        }
        else if(i == 2) {
            ispis += "   ";
            ispis += noviIgrac.getIme();
            for(int j = 0; j < 57 - strlen(noviIgrac.getIme()); j++) {
                ispis += " ";
            }
        }
        else if(i == 3) {
            ispis += "                           KAZINO                           ";
        }
        else if(i == 6) {
            ispis += "                       IZABERITE IGRU                       ";
        }
        else if(i == 7) {
            ispis += "              PSEUDORULET(1)       BLEKDZEK(2)              ";
        }
        else if(i == 11) {
            ispis += "     PROMENI IGRACA(3)                                      ";
        }
        else {
            ispis += "                                                            ";
        }
        ispis += "|\n";
    }
    ispis += " ------------------------------------------------------------\n";

    printf("%s", ispis.c_str());
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    srand(time(NULL));

    pocetniProzor();
    Kazino kazino(1000);
    Blekdzek bl;
    kazino.dodajIgru(bl);
    
    if(cin.get() == '\n') {
        while(1) {
            izaberiIgraca();
            char imeIgraca[MAX];
            cin >> imeIgraca;
            Igrac noviIgrac(imeIgraca, 30);
            while(1) {
                izaberiIgru(noviIgrac);
                int igra;
                cin >> igra;
                if(igra == 1) {
                    rulija(noviIgrac, kazino);
                }
                else if(igra == 2){
                    blekdzek(noviIgrac, kazino);
                }
                else if(igra == 3){
                    break;
                }
                else if(noviIgrac.getBalans() <= 0) {
                    
                    break;
                }
            }
            if(kazino.getBudzet() <= 0) {
                break;
            }
        }
    }


    return 0;
}