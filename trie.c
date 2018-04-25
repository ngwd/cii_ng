#define tagLEAF 0x2
#define maskTO_POINTER 0xFFFFFFFC
#define ALPHSIZE 26

typedef struct {
    unsigned int branch[ALPHSIZE];
} Trie;

/** Initialize data structure here. */
Trie* trieCreate() {
    Trie *_b = (Trie*) malloc(sizeof(Trie));
    memset(_b, 0x0, sizeof(Trie));
    return _b;
}

/** Inserts a word into the trie. */
void trieInsert(Trie* obj, char* word) {
    int idx;
    unsigned int p, eow;
    for (int i=0; word[i]!='\0'; ++i) {
        idx = word[i]-'a';
        if (word[i+1]=='\0') {
            obj->branch[idx] |= tagLEAF;
            break;
        }
        p = obj->branch[idx];
        eow = (p&tagLEAF); /* get the last 2 bits, end of word*/
        p &= maskTO_POINTER;
        if( p==0x0 ) {
            p = (unsigned int)(trieCreate());
            p |= eow;          /* add the last 2 bits of p*/
            obj->branch[idx] = p;
        }
        p &= maskTO_POINTER;
        obj = (Trie*)p;
    }
}

/** Returns if the word is in the trie. */
bool trieSearch(Trie* obj, char* word) {
    unsigned int p, eow;
    for(int i=0; word[i]!='\0'; ++i) {
        p = obj->branch[word[i]-'a'];
        eow = ( p&tagLEAF ); /* get the last 2 bits, end of word*/ 
        p &= maskTO_POINTER;
        if (word[i+1]=='\0')  /* last character of word*/
            break;
        else if (p==0x0) 
            return false; 
        obj = (Trie*)p;
    }
    return  eow==tagLEAF;
}

/** Returns if there is any word in the trie that starts with the given prefix. */
bool trieStartsWith(Trie* obj, char* prefix) {
    unsigned int p, eow;
    for(int i=0; prefix[i]!='\0'; ++i) {
        p = (unsigned int)(obj->branch[prefix[i]-'a']);
        eow = ( p&tagLEAF ); /* get the last 2 bits, end of word*/ 
        p &= maskTO_POINTER;
        if (p==0x0) {
            return prefix[i+1]=='\0' && eow==tagLEAF; 
        }
        obj = (Trie*)p;
    }
    return true;
}

void trieFree(Trie* obj) {
    unsigned int ui;
    for(int i=0; i<ALPHSIZE; ++i) {
        ui = obj->branch[i];
        ui &= maskTO_POINTER;
        Trie *p = (Trie*)(ui);
        if (p!=0x0) trieFree(p);
    }
    free(obj);
}

/**
 * the Trie struct will be instantiated and called as such:
 * struct Trie* obj = trieCreate();
 * trieInsert(obj, word);
 * bool param_2 = trieSearch(obj, word);
 * bool param_3 = trieStartsWith(obj, prefix);
 * trieFree(obj);
 */


