#include <stdio.h>
#include <stdlib.h>

/// -------- AVL TREE --------
typedef struct AVL{ int k,h; struct AVL *l,*r; }AVL;
AVL* newAVL(int k){ AVL* n=malloc(sizeof(AVL)); n->k=k;n->l=n->r=NULL;n->h=1;return n;}
AVL* insertAVL(AVL* r,int k){ if(!r) return newAVL(k); if(k<r->k) r->l=insertAVL(r->l,k);
 else if(k>r->k) r->r=insertAVL(r->r,k); return r; }  // (rotations skipped for short)
AVL* searchAVL(AVL* r,int k){ return (!r||r->k==k)?r:(k<r->k?searchAVL(r->l,k):searchAVL(r->r,k)); }
AVL* deleteAVL(AVL* r,int k){ if(!r) return NULL; if(k<r->k) r->l=deleteAVL(r->l,k);
 else if(k>r->k) r->r=deleteAVL(r->r,k); else{ free(r); return NULL;} return r; }
void deleteTreeAVL(AVL* r){ if(r){ deleteTreeAVL(r->l); deleteTreeAVL(r->r); free(r);} }

/// -------- RED-BLACK TREE (skeleton) --------
typedef struct RB{ int k; struct RB *l,*r; }RB;
RB* insertRB(RB* r,int k){ printf("RB insert %d\n",k); return r; }
RB* deleteRB(RB* r,int k){ printf("RB delete %d\n",k); return r; }
RB* searchRB(RB* r,int k){ return NULL; }
void deleteTreeRB(RB* r){ if(r){ deleteTreeRB(r->l); deleteTreeRB(r->r); free(r);} }

/// -------- B TREE (skeleton) --------
typedef struct BTree{ int n,keys[4]; struct BTree* c[5]; int leaf; }BTree;
BTree* createB(){ BTree* t=malloc(sizeof(BTree)); t->n=0;t->leaf=1; return t; }
void insertB(BTree* t,int k){ printf("B insert %d\n",k); }
void deleteB(BTree* t,int k){ printf("B delete %d\n",k); }
BTree* searchB(BTree* t,int k){ return NULL; }
void deleteTreeB(BTree* t){ if(t) free(t); }

/// -------- B+ TREE (skeleton) --------
typedef struct BPlus{ int n,keys[4]; struct BPlus* c[5]; int leaf; struct BPlus* next; }BPlus;
BPlus* createBP(){ BPlus* t=malloc(sizeof(BPlus)); t->n=0;t->leaf=1;t->next=NULL; return t; }
void insertBP(BPlus* t,int k){ printf("B+ insert %d\n",k); }
void deleteBP(BPlus* t,int k){ printf("B+ delete %d\n",k); }
BPlus* searchBP(BPlus* t,int k){ return NULL; }
void deleteTreeBP(BPlus* t){ if(t) free(t); }

/// -------- MAIN --------
int main(){
    AVL* avl=NULL; avl=insertAVL(avl,10); avl=insertAVL(avl,20);
    printf("AVL Search 20: %s\n",searchAVL(avl,20)?"found":"not found");

    RB* rb=NULL; rb=insertRB(rb,15); rb=deleteRB(rb,15);

    BTree* bt=createB(); insertB(bt,5); deleteB(bt,5);

    BPlus* bp=createBP(); insertBP(bp,8); deleteBP(bp,8);
    return 0;
}
