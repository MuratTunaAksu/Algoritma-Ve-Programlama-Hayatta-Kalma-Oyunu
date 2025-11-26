#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int main() {
    // Rastgelelik icin cekirdek olustur
    srand(time(NULL));

    // --- TUM DEGISKENLER EN BASTA TANIMLANDI ---
    int saglik = 100;
    int enerji = 100;
    int yemek = 0;
    int siginak = 0; // 0: Yok, 1: Var
    
    char komut;
    int oyunDevam = 1;
    
    // Gecici degiskenler 
    int sans = 0;
    int s_sans = 0;
    int hasar = 0;
    int tehlikeGucu = 0;
    int i = 0;           // For dongusu sayacý
    int girilenSifre = 0;
    int dogruSifre = 1234;

    printf("=== HAYATTA KALMA SIMULATORU ===\n");
    printf("Komutlar: [A]vlan, [S]iginak, [E]nvanter, [R]Dinlen, [F]Tehlike, [P]Sifre, [X]Cikis\n");

    // Ana Oyun Döngüsü
    do {
        printf("\nBir komut giriniz > ");
        // scanf oncesi bosluk, tampon bellegi temizler
        scanf(" %c", &komut);

        // Kücük harfi buyuk harfe cevirme
        if(komut >= 'a' && komut <= 'z') {
            komut = komut - 32;
        }

        switch (komut) {
            case 'A': // Avlanma
                if (enerji >= 15) {
                    enerji -= 15;
                    printf("Avlanmaya ciktin...\n");
                    
                    sans = rand() % 100; // Degisken yukarýda tanýmlý
                    if (sans > 50) {
                        yemek++;
                        printf("Basarili! Bir yemek buldun. (Yemek: %d)\n", yemek);
                    } else {
                        saglik -= 10;
                        printf("Basarisiz! Av sirasinda yaralandin. (Saglik -10)\n");
                    }
                } else {
                    printf("Yetersiz enerji! Avlanmak icin dinlenmelisin.\n");
                }
                break;

            case 'S': // Sýgýnak Ara
                if (siginak == 1) {
                    printf("Zaten bir siginagin var!\n");
                } else {
                    if (enerji >= 20) {
                        enerji -= 20;
                        s_sans = rand() % 100;
                        if (s_sans > 60) {
                            siginak = 1;
                            printf("Tebrikler! Guvenli bir siginak buldun.\n");
                        } else {
                            printf("Siginak bulamadin, enerji bosa gitti.\n");
                        }
                    } else {
                        printf("Siginak aramak icin cok yorgunsun.\n");
                    }
                }
                break;

            case 'E': // Envanter
                printf("\n--- DURUM RAPORU ---\n");
                printf("Saglik : %d\n", saglik);
                printf("Enerji : %d\n", enerji);
                printf("Yemek  : %d\n", yemek);
                // Ternary yapýsý:
                if(siginak == 1) printf("Siginak: VAR\n"); else printf("Siginak: YOK\n");
                printf("--------------------\n");
                break;

            case 'R': // Dinlen
                printf("Dinleniyorsun...\n");
                enerji += 20;
                if (enerji > 100) enerji = 100;

                if (siginak == 1) {
                    saglik += 15;
                    printf("Siginaginda guvende uyudun. (Saglik +15, Enerji +20)\n");
                } else {
                    saglik += 5;
                    printf("Disarida uyudun, pek rahat degildi. (Saglik +5, Enerji +20)\n");
                }
                
                if (saglik > 100) saglik = 100;
                
                // Otomatik yemek yeme
                if (yemek > 0 && saglik < 90) {
                    yemek--;
                    saglik += 10;
                    printf("Yemek yedin. (Saglik +10)\n");
                }
                break;

            case 'F': // Tehlike Dalgasý
                printf("!!! TEHLIKE DALGASI YAKLASIYOR !!!\n");
                hasar = 0; // Sýfýrla
                
                // For dongusu 
                for (i = 1; i <= 3; i++) {
                    tehlikeGucu = rand() % 20;
                    printf("%d. Dalga geliyor... (Guc: %d)\n", i, tehlikeGucu);
                    
                    if (siginak == 1) {
                        tehlikeGucu /= 2;
                        printf("Siginak hasari azaltti.\n");
                    }
                    
                    saglik -= tehlikeGucu;
                    hasar += tehlikeGucu;
                }
                printf("Tehlike gecti. Toplam alinan hasar: %d\n", hasar);
                break;

            case 'P': // Sifre
                printf("Kilitli bir sandik buldun. Sifreyi cozmelisin.\n");
                
                do {
                    printf("4 haneli sifreyi giriniz: ");
                    scanf("%d", &girilenSifre);
                    
                    if (girilenSifre != dogruSifre) {
                        printf("Hatali sifre! Tekrar dene.\n");
                        enerji -= 5;
                    }
                } while (girilenSifre != dogruSifre && enerji > 0);
                
                if (enerji > 0) {
                    printf("Sifre dogru! Sandiktan ekstra yemek cikti.\n");
                    yemek += 2;
                } else {
                    printf("Sifreyi denerken bayildin...\n");
                }
                break;

            case 'X': // Cýkýs
                printf("Simulasyondan cikiliyor...\n");
                oyunDevam = 0;
                break;

            default:
                printf("Gecersiz komut! Lutfen A, S, E, R, F, P veya X giriniz.\n");
        }

        // Oyun Bitis Kontrolu
        if (saglik <= 0) {
            printf("\nXXX OLDUN! OYUN BITTI XXX\n");
            oyunDevam = 0;
        }

    } while (oyunDevam == 1);

    return 0;
}
