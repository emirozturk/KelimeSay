#define BUFFER_BOYUTU 100*1024*1024

struct buffer {
    unsigned char *veri;
    unsigned uzunluk;
}typedef Buffer;

struct hash {
    unsigned char *kelime;
    unsigned int uzunluk;
    unsigned int frekans;
    unsigned int kod;
}typedef Hash;

unsigned int dosyaBoyutuVer(char *);
unsigned int NearestPrime(unsigned int n);
unsigned int hashFunction(const unsigned char *aWord, unsigned int len);
unsigned int insertElement(Hash *hashSet, unsigned char *kelime, unsigned int uzunluk, unsigned int *addr);
unsigned int search(Hash *hashSet, unsigned char *kelime, unsigned uzunluk, unsigned int *returnedAddr);
int strcomp(const unsigned char *s1, const unsigned char *s2, register unsigned int ws1, unsigned int ws2);
int kelimeSayisiTahmini(long dosyaBoyutu);
void hashBuyukluguBelirle(int buyukluk);
void alfaNumDoldur();
int hashBuyukluguDondur();
void e_strcat(unsigned char *anaDizi, unsigned char *parca, unsigned int konum, unsigned int boyut);