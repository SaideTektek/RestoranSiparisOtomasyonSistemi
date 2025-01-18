/*Saide Tektek
 Restoran Sipariþ Otomasyon Sistemi*/ 

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

struct urun {
    char ad[50];
    double ucret;
};

struct masa {
    bool dolu = false;
    urun siparisler[10];
    int siparisSayisi = 0;
    double toplamHesap = 0.0;
};

urun burgermenu[4] = {{"klasikburger", 250}, {"cheeseburger", 200}, {"tavukburger", 230}, {"glutensizburger", 250}};
urun pizzamenu[4] = {{"margarita", 200}, {"dortpeynirli", 200}, {"tavuklu", 250}, {"tonbalikli", 250}};
urun etyemeklerimenu[4] = {{"iskender", 300}, {"izgara kofte", 300}, {"balaban kofte", 350}, {"dana kavurma", 400}};
urun tavukmenu[4] = {{"fajita", 300}, {"barbeku tavuk", 250}, {"kori tavuk", 250}, {"tavuk kavurma", 150}};
urun salatamenu[4] = {{"akdeniz", 200}, {"sezar", 200}, {"tonbalikli", 200}, {"diyet", 200}};
urun tatlimenu[4] = {{"magnolya", 150}, {"limonlu cheesecake", 150}, {"profiterol", 150}, {"sutlac", 150}};
urun icecekmenu[4] = {{"kola", 50}, {"cay", 30}, {"su", 15}, {"ayran", 30}};

void menuKaydet(const urun menu[], int boyut, const char* dosyaAdi) {
    ofstream yaz(dosyaAdi, ios::binary | ios::out);
    if (!yaz) {
        cout << "Dosya acilamadi: " << dosyaAdi << endl;
        return;
    }
    for (int i = 0; i < boyut; i++) {
        yaz.write(reinterpret_cast<const char*>(&menu[i]), sizeof(menu[i]));
    }
    yaz.close();
}

void menuOku(const char* dosyaAdi) {
    ifstream oku(dosyaAdi, ios::binary | ios::in);
    if (!oku) {
        cout << "Dosya acilamadi: " << dosyaAdi << endl;
        return;
    }

    urun okunanUrun;
    while (oku.read(reinterpret_cast<char*>(&okunanUrun), sizeof(okunanUrun))) {
        cout << "- " << okunanUrun.ad << ": " << okunanUrun.ucret << " TL\n";
    }
    oku.close();
}

void masaDurumlariniGoster(masa masalar[], int boyut) {
    cout << "\tTum Masalarin Durumu:\n";
    for (int i = 0; i < boyut; i++) {
        cout << "Masa " << i + 1 << ": ";
        if (masalar[i].dolu) {
            cout << "Dolu - Toplam Hesap: " << masalar[i].toplamHesap << " TL\n";
        } else {
            cout << "Bos\n";
        }
    }
}

void siparisEkle(masa &m, urun menu[], int boyut) {
    if (m.siparisSayisi >= 10) {
        cout << "Bu masa icin maksimum siparis sinirina ulasildi.\n";
        return;
    }

    int secim;
    cout << "Siparis vermek istediginiz urunun numarasini secin: ";
    cin >> secim;

    if (cin.fail() || secim < 1 || secim > boyut) {
        cout << "Gecersiz secim.\n";
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }

    m.siparisler[m.siparisSayisi] = menu[secim - 1];
    m.toplamHesap += menu[secim - 1].ucret;
    m.dolu = true;
    m.siparisSayisi++;
    cout << menu[secim - 1].ad << " siparise eklendi!\n";
}

void menuSec(const char* menuAdi, urun menu[], int boyut) {
    cout << "\n" << menuAdi << " Menu:\n";
    for (int i = 0; i < boyut; i++) {
        cout << i + 1 << ". " << menu[i].ad << " - " << menu[i].ucret << " TL\n";
    }
}

int main() {

    masa masalar[10];  
    int secim, masaNo;

    while (true) {
        cout << "\n1. Burger Menusunu Goster\n"
             << "2. Pizza Menusunu Goster\n"
             << "3. Et Yemekleri Menusunu Goster\n"
             << "4. Tavuk Menusunu Goster\n"
             << "5. Salata Menusunu Goster\n"
             << "6. Tatli Menusunu Goster\n"
             << "7. Icecek Menusunu Goster\n"
             << "8. Siparis Ver\n"
             << "9. Masa Durumlarini Goster\n"
             << "10. Cikis\n"
             << "Seciminiz: ";
        cin >> secim;

        switch (secim) {
            case 1:
                menuSec("Burger", burgermenu, 4);
                break;
            case 2:
                menuSec("Pizza", pizzamenu, 4);
                break;
            case 3:
                menuSec("Et Yemekleri", etyemeklerimenu, 4);
                break;
            case 4:
                menuSec("Tavuk", tavukmenu, 4);
                break;
            case 5:
                menuSec("Salata", salatamenu, 4);
                break;
            case 6:
                menuSec("Tatli", tatlimenu, 4);
                break;
            case 7:
                menuSec("Icecek", icecekmenu, 4);
                break;
            case 8:
                cout << "Masa numarasini giriniz (1-10): ";
                cin >> masaNo;
                if (masaNo < 1 || masaNo > 10) {
                    cout << "Gecersiz masa numarasi!\n";
                    continue;
                }

                int secim2;
                cout << "Bir menu seciniz:\n";
                cout << "1. Burger\n2. Pizza\n3. Et Yemekleri\n4. Tavuk\n5. Salata\n6. Tatli\n7. Icecek\n";
                cin >> secim2;

                switch (secim2) {
                    case 1:
                        siparisEkle(masalar[masaNo - 1], burgermenu, 4);
                        break;
                    case 2:
                        siparisEkle(masalar[masaNo - 1], pizzamenu, 4);
                        break;
                    case 3:
                        siparisEkle(masalar[masaNo - 1], etyemeklerimenu, 4);
                        break;
                    case 4:
                        siparisEkle(masalar[masaNo - 1], tavukmenu, 4);
                        break;
                    case 5:
                        siparisEkle(masalar[masaNo - 1], salatamenu, 4);
                        break;
                    case 6:
                        siparisEkle(masalar[masaNo - 1], tatlimenu, 4);
                        break;
                    case 7:
                        siparisEkle(masalar[masaNo - 1], icecekmenu, 4);
                        break;
                    default:
                        cout << "Gecersiz secenek!\n";
                }
                break;
            case 9:
                masaDurumlariniGoster(masalar, 10);
                break;
            case 10:
                cout << "Cikis yapiliyor.\n";
                return 0;
            default:
                cout << "Gecersiz secim!\n";
        }
    }
}

