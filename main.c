
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include "fonksiyon.h"
char alfaNum[256];
Hash* hashSet;
unsigned int addrInTH;
unsigned int zeroNode;
unsigned int *positionInTH;
unsigned int toplamKelimeSayisi = 0;
unsigned int farkliKelimeSayisi = 0;
unsigned int enUzunBoyut=0;
void kelimeCikar(Buffer *b)	//ETDC'den al?nma
{
    unsigned char *p, *son;
    unsigned int boyut = 0,j=0;
    p = b->veri;
    son = p + (strlen((char *)b->veri));
    unsigned char *kelime;
    while (p < son)
    {
        boyut = 0;
        kelime = p;
        if (alfaNum[*p])
        {
            while (alfaNum[*p] && p < son)
            {
                boyut++;
                p++;
            }
        }
        else
        {
            if (*p != ' ')
            {
                while (!alfaNum[*p] && p < son)
                {
                    boyut++;
                    p++;
                }
            }
            else
            {
                p++;
                if (alfaNum[*p])
                {
                    kelime = p;
                    while (alfaNum[*p] && p < son)
                    {
                        boyut++;
                        p++;
                    }
                }
                else
                {
                    boyut++;
                    while (!alfaNum[*p] && p < son)
                    {
                        boyut++;
                        p++;
                    }
                }
            }
        }
        toplamKelimeSayisi++;
        if(boyut>enUzunBoyut)enUzunBoyut = boyut;
        j = search(hashSet, (unsigned char *)kelime, boyut, &addrInTH);
        if (j == zeroNode)
        {
            insertElement(hashSet, (unsigned char *)kelime, boyut, &addrInTH);
            farkliKelimeSayisi++;
            hashSet[addrInTH].uzunluk = boyut;
            positionInTH[zeroNode] = addrInTH;
            zeroNode++;
        }
        hashSet[addrInTH].frekans += 1;
    }
}
void hashSetAc(unsigned int kelimeSayisi)
{
    unsigned int hashBuyuklugu = kelimeSayisi;
    hashBuyuklugu = NearestPrime(hashBuyuklugu);
    hashBuyukluguBelirle(hashBuyuklugu);
    hashSet = (Hash *)calloc(hashBuyuklugu, sizeof(Hash));
    positionInTH = (unsigned int*)malloc(hashBuyuklugu * sizeof(unsigned int));
    for (int i = 0; i < hashBuyuklugu; i++)
        positionInTH[i] = -1;
}

int main(int argc, const char * argv[]) {
    alfaNumDoldur(alfaNum);
    hashSetAc(158372138);
    char *dosyaAdi = argv[1];
    long dosyaBoyutu = dosyaBoyutuVer(dosyaAdi);
    int parcaSayisi = (int)ceil((double)dosyaBoyutu / (BUFFER_BOYUTU));
    FILE *fp = fopen(dosyaAdi, "r");
    Buffer *b = (Buffer *)calloc(1, sizeof(Buffer));
    b->veri = (unsigned char *)calloc(1, BUFFER_BOYUTU+1);
    for (int i = 0; i < parcaSayisi; i++)
    {
        fseek(fp, i*BUFFER_BOYUTU, SEEK_SET);
        fread(b->veri, BUFFER_BOYUTU, 1, fp);
        b->uzunluk = (unsigned int)strlen((char *)b->veri);
        kelimeCikar(b);
    }
    printf("Toplam:%u\n",toplamKelimeSayisi);
    printf("Farkli:%u\n",farkliKelimeSayisi);
    printf("En Uzun:%u\n",enUzunBoyut);
    return 0;
}
