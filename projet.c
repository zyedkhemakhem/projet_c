#include<stdio.h>
#include<ctype.h>
#include<malloc.h>
#include<conio.h>
#include<stdlib.h>


typedef struct date{
int j,m,a;
};
typedef struct operation operation;
struct operation {
int numOP;
 char typeOp[1];
 struct date dateOp;
 int montantOp;
 operation*svtOp
};
typedef struct compte compte;
struct compte {
    int numCpt;
    char nomClt[15];
    char typeCpt[1];
    int soldCpt;
    operation *op;
    compte*svtCpt;
};
int comparerDate(struct date d1, struct date d2)
{
int Nb1, Nb2;
 Nb1=d1.a*10000 + d1.m*100 + d1.j;
 Nb2=d2.a*10000 + d2.m*100 + d2.j;
if(Nb1 > Nb2)
 return 1;
else
if(Nb1 < Nb2)
 return 2;
else
 return 0;
}
compte* verifcpt(compte*tete,int numc){
while(tete && tete->numCpt!=numc){
    tete=tete->svtCpt;
}
return tete;
}
ajouterCpt(compte**tete,compte*p){
    compte*q;int i=1;

    if(!*tete){
        *tete=p;
        (*tete)->soldCpt=0;
        (*tete)->numCpt=1;
        printf("nom de cpt:");
        scanf("%s",(*tete)->nomClt);
        do{
        printf("type de cpt C OU E:");
        scanf("%s",(*tete)->typeCpt);
        }while(toupper((*tete)->typeCpt[0])!='E'&& toupper((*tete)->typeCpt[0])!='C');
        (*tete)->op=NULL;


    }else
    {
        q=*tete;
        i=i+1;
        while(q->svtCpt){
            i=i+1;
            q=q->svtCpt;

            }
        q->svtCpt=p;
        p->numCpt=i;
        printf("nom de cpt:");
        scanf("%s",p->nomClt);
        do{
        printf("type de cpt:");
        scanf("%s",p->typeCpt);
        }while(toupper(p->typeCpt[0])!='E'&& toupper(p->typeCpt[0])!='C');
        p->op=NULL;
        p->soldCpt=0;

    }
}
void saisirOp(compte**c,struct date d){
operation *p, *q; int nb, i;
i=0;
p=malloc(sizeof(operation));

if((*c)->op==NULL){
    (*c)->op=p;
    i+=1;}
else{ q=(*c)->op;
while(q->svtOp){
    q=q->svtOp;
    i+=1;
}
q->svtOp=p;
}
printf("le montant: ");
scanf("%d",&nb);
do{
printf("R ou  E:");
scanf("%s",&(p->typeOp));}while(toupper(p->typeOp[0])!='R'&&toupper(p->typeOp[0])!='E');
if ((p->typeOp[0]=='R')&&(nb > (*c)->soldCpt)){
    printf("impossible de faire cette operation \n");
    free(p);
    }

else{

if(p->typeOp[0]=='E'){
    (*c)->soldCpt += nb;}

else if(p->typeOp[0]=='R') {(*c)->soldCpt -=nb;}
p->numOP=i;
p->montantOp=nb;
p->svtOp=NULL;
p->dateOp=d;
}
}

void supp(compte**tete, int v) {
compte *p,*prec;
p = *tete;
while (p != NULL && p->numCpt != v) {
    prec = p;
    p = p->svtCpt;
}

if (p != NULL) {
    if (p == *tete)
        *tete = (*tete)->svtCpt;
     else
        prec->svtCpt = p->svtCpt;
    free(p->op);
    free(p);
}else
    printf("La valeur %d n'existe pas !!\n", v);

}
void affichecp(compte* tete) {
    compte*c= tete;
    printf("Liste des comptes:\n");
    while (c!= NULL) {
        printf("Numero de compte: %d\n", c->numCpt);
        printf("Solde du compte: %d\n", c->soldCpt);
        printf("--------------------\n");
        c = c->svtCpt;
    }
}

void afficheop(compte* c, struct date d) {
    printf("Extrait des operations pour le compte ne%d:\n", c->numCpt);
    operation* op = c->op;
    while (op != NULL) {
        if (comparerDate(d,op->dateOp)==0) {
            printf("Numero d'operation: %d\n", op->numOP);
            printf("Type d'operation: %c\n", op->typeOp[0]);
            printf("Date d'operation: %d-%d-%d\n", op->dateOp.j, op->dateOp.m, op->dateOp.a);
            printf("Montant d'operation: %d\n", op->montantOp);
            printf("--------------------\n");
        }
        op = op->svtOp;
    }
}
void afficherDetailsCompte(compte* c) {
  printf("**Détails du compte**\n");
  printf("Numéro de compte : %d\n", c->numCpt);
  printf("Nom du client : %s\n", c->nomClt);
  printf("Type de compte : %s\n", c->typeCpt);
  printf("Solde du compte : %d\n", c->soldCpt);

  operation* op = c->op;
  while (op != NULL) {
    printf("**Opération**\n");
    printf("Numéro d'opération : %d\n", op->numOP);
    printf("Type d'opération : %c\n", op->typeOp[0]);
    printf("Date d'opération : %d-%d-%d\n", op->dateOp.j, op->dateOp.m, op->dateOp.a);
    printf("Montant de l'opération : %d\n", op->montantOp);
    op = op->svtOp;
  }
}
int calculerSoldeTotal(compte* tete) {
    int soldeTotal = 0;
    while (tete != NULL) {
        soldeTotal += tete->soldCpt;
        tete = tete->svtCpt;
    }
    return soldeTotal;
}


int main(){
struct date d={18,5,2023};
compte*a;
compte*tete=NULL,*p;
int choix,n;
do{
    printf("****banc****\n");
    printf("1- creation de compt \n");
    printf("2- une operation \n");
    printf("3- supression \n");
    printf("4- afficher comptes \n");
    printf("5- afficher operation \n");
    printf("6- le solde total de tous les comptes \n");
    printf("7- detail d'un compte \n");


    printf("- Quitter \n");
    printf("    Tapez votre choix:");
    scanf("%d",&choix);
    switch(choix){
        case 1: p=malloc(sizeof(compte));
                p->svtCpt=NULL;
                ajouterCpt(&tete,p);break;
        case 2:
            printf("le numero de compte : ");
            scanf("%d",&n);
            if(verifcpt(tete,n)!=NULL){
                    a=verifcpt(tete,n);
                saisirOp(&a,d);}
            else printf("le compte n'existe pas ");break;
        case 3:  printf("le numero de compte a suprimer: ");
            scanf("%d",&n);
            supp(&tete,n);break;
        case 4:
            affichecp(tete);break;
       case 5:
              printf("le numero de compte : ");
            scanf("%d",&n);
            if(verifcpt(tete,n)!=NULL){
                    a=verifcpt(tete,n);
                afficheop(a,d);}
            else printf("le compte n'existe pas ");break;
        case 6:
    printf("Solde total de tous les comptes : %d\n", calculerSoldeTotal(tete));
    break;
    case 7:
  printf("**Afficher les détails d'un compte**\n");
  printf("Entrez le numéro de compte : ");
  scanf("%d", &n);
  a = verifcpt(tete, n);
  if (a != NULL) {
    afficherDetailsCompte(a);
  } else {
    printf("Le compte n'existe pas");
  }
  break;

                }
if (choix!=4&&choix!=5){

    system("cls");}
}while(choix<6);
}
