#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "fonksiyon.h"
#define SEED 1159241
#define JUMP 101
unsigned int elemanSayisi;
int hashBuyuklugu = 158372138;

int hashBuyukluguDondur()
{
    return hashBuyuklugu;
}
void alfaNumDoldur(char *alfaNum)
{
    for (int i = 0; i < 256; i++)
        alfaNum[i] = isalnum(i);
}
void hashBuyukluguBelirle(int buyukluk)
{
    hashBuyuklugu = buyukluk;
}
int kelimeSayisiTahmini(long dosyaBoyutu)
{
    //y = -1.786785785∑10-40 x6 + 6.673138864∑10-32 x5 - 7.296802889∑10-24 x4 + 2.490561647∑10-16 x3 - 1.177918929∑10-9 x2 + 7.201465545∑10-3 x + 19895.82178
    //Online Polynomial Regression - www.xuru.org/rt/PR.asp#Manually
    unsigned int kelimeSayisi = 158372138;
    return kelimeSayisi;
}
unsigned int dosyaBoyutuVer(char *input)
{
    FILE *fp = fopen(input, "r");
    fseek(fp, 0L, SEEK_END);
    long boyut = ftell(fp);
    fclose(fp);
    return (unsigned int)boyut;
}
unsigned int NearestPrime(unsigned int n)
{
    unsigned int position;
    unsigned int index;
    
    for (position = n; ; position++)
    {
        for (index = 2; index <= (unsigned long)sqrt((double)position) && position % index != 0; index++);
        if (position % index != 0)
            break;
    }
    return position;
}
unsigned int hashFunction(const unsigned char *aWord, unsigned int len)
{
    char c;
    unsigned int h;
    unsigned char *last;
    last = aWord + (len - 1);
    
    h = SEED;
    
    for (; (aWord <= last); )
    {
        c = *(aWord++);
        h ^= ((h << 5) + c + (h >> 2));
    }
    return((unsigned int)((h & 0x7fffffff) % hashBuyuklugu));
}

unsigned int insertElement(Hash *hashSet, unsigned char *kelime, unsigned int uzunluk, unsigned int *addr)
{
    hashSet[*addr].kelime = (unsigned char *)malloc(uzunluk*sizeof(unsigned char));
    strncpy((char *)hashSet[*addr].kelime, (char *)kelime, uzunluk);
    hashSet[*addr].kelime[uzunluk] = '\0';
    hashSet[*addr].frekans = 0;
    elemanSayisi++;
    return *addr;
}

unsigned int search(Hash *hashSet, unsigned char *kelime, unsigned uzunluk, unsigned int *returnedAddr) {
    
    unsigned int addr, Saddr;
    addr = hashFunction(kelime, uzunluk);
    Saddr = addr;
    while ((hashSet[addr].kelime != NULL) && ((strcomp(hashSet[addr].kelime, kelime, hashSet[addr].uzunluk, uzunluk)) != 0))
        addr = ((addr + JUMP) % hashBuyuklugu);
    *returnedAddr = addr;
    if (hashSet[addr].kelime == NULL)
        return elemanSayisi;
    return 0;
}
int strcomp(const unsigned char *s1, const unsigned char *s2, unsigned int ws1, unsigned int ws2)
{
    if (ws1 != ws2)
        return -1;
    unsigned int iters = 1;
    while (iters < ws1 && *s1 == *s2)
    {
        s1++;
        s2++;
        iters++;
    }
    return(*s1 - *s2);
}
void e_strcat(unsigned char *anaDizi, unsigned char *parca, unsigned int konum, unsigned int boyut)
{
    for (unsigned int i = konum; i < konum + boyut; i++)
        anaDizi[i] = parca[i - konum];
}