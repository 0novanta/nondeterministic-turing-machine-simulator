//AGGIORNATO A MERCOLEDÌ 29 AGOSTO
//FUNZIONA CON TUTTO TRANNE: ToCOrNotToC (privati)
//VERSIONE CON '@' IN us[101]
//FATTO PASSAGGIO DA QUINTUPLE A TRIPLE
//MESSO UN SOLO INDICATORE AL POSTO DI ultimo->dx E ultimo->sx
//MESSO UN SOLO INDICATORE AL POSTO DI ultimo->pos E ultimo->posSX
//MESSO UNA VARIABILE AL POSTO DELL'ARRAY risultati
//MESSO CONTROLLO SUI LOOP SEMPRE A DX/SX--->forse mi fa perdere più tempo di quello che guadagno
//TOLTE LE SOTTOFUNZIONI aggiungiElem E eliminaElem COSÌ NON PERDO TEMPO NELLE CHIAMATE
//INVERTITO USO DELLA CODA
//DIMINUITO USO DI strlen
//DIMINUITO USO DI malloc E realloc--->RIUSO LA TESTA DELLA CODA PER CREARE UN NUOVO ELEMENTO
//USA memmove, memset AL POSTO DI strcpy, strcat--->DA FARE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nodo {
  struct nodo *next;
  char scritto;
  char mov;
  int sfin;
};
typedef struct nodo nodo_t;

struct transizione {
  struct transizione *next;
  unsigned int mosse, pos, lungh, lunghSX, del;
  unsigned int DXSX; //=1 (sono a dx), =0 (sono a sx)
  unsigned int statoCorr, alloc; //alloc=0 (non allocare), =1 (alloca a dx), =2 (alloca a sx)
  char *stringa, *stringaSX;
};
typedef struct transizione tr_t;


char calcolo(char*, nodo_t***, int, unsigned long int, int*, int);



int main (int argc, char*argv[]){
  nodo_t ***arr=NULL, **nuovoArr=NULL, **help=NULL, *nuovoNodo=NULL, **p=NULL, *coda=NULL;
  char s[30], ch1, ch2, b, c, d;
  char *str=NULL, charFinale;
  int a, e, carLetti, numLetto, len, *A=NULL, i, t;
  unsigned long int max;
  int statoMax, lunghArr=0;


  //MEMORIZZAZIONE DELLE TRANSIZIONI
  scanf("%c%c", &ch1, &ch2);
  if(ch1=='t' && ch2=='r'){
    carLetti=scanf("%d %c %c %c %d", &a, &b, &c, &d, &e);
    while(carLetti==5){
      if(arr==NULL){
        if(a==0){
          arr = (nodo_t***) malloc(sizeof(nodo_t**));
          nuovoArr = (nodo_t**) malloc(75*sizeof(nodo_t*));
          nuovoNodo = (nodo_t*) malloc(sizeof(nodo_t));
          nuovoNodo->scritto=c;
          nuovoNodo->mov=d;
          nuovoNodo->sfin=e;
          nuovoNodo->next=NULL;
          for(t=0; t<75; t++){
            nuovoArr[t]=NULL;
          }
          nuovoArr[b-48]=nuovoNodo;
          arr[0]=nuovoArr;
          statoMax=a;
        }
        else{
          arr = (nodo_t***) malloc((a+1)*sizeof(nodo_t**));
          nuovoArr = (nodo_t**) malloc(75*sizeof(nodo_t*));
          nuovoNodo = (nodo_t*) malloc(sizeof(nodo_t));
          nuovoNodo->scritto=c;
          nuovoNodo->mov=d;
          nuovoNodo->sfin=e;
          nuovoNodo->next=NULL;
          for(t=0; t<75; t++){
            nuovoArr[t]=NULL;
          }
          nuovoArr[b-48]=nuovoNodo;
          arr[a]=nuovoArr;
          for(i=0; i<a; i++){
            arr[i]=NULL;
          }
          statoMax=a;
        }
      }
      else{
        if(a<=statoMax){
          nuovoNodo = (nodo_t*) malloc(sizeof(nodo_t));
          nuovoNodo->scritto=c;
          nuovoNodo->mov=d;
          nuovoNodo->sfin=e;
          if(arr[a]==NULL){
            nuovoArr = (nodo_t**) malloc(75*sizeof(nodo_t*));
            arr[a]=nuovoArr;
            nuovoNodo->next=NULL;
            for(t=0; t<75; t++){
              nuovoArr[t]=NULL;
            }
            nuovoArr[b-48]=nuovoNodo;
          }
          else{
            help=arr[a];
            nuovoNodo->next=help[b-48];
            help[b-48]=nuovoNodo;
          }
        }
        else if(a==statoMax+1){
          arr = (nodo_t***) realloc(arr, (a+1)*sizeof(nodo_t**));
          nuovoArr = (nodo_t**) malloc(75*sizeof(nodo_t*));
          nuovoNodo = (nodo_t*) malloc(sizeof(nodo_t));
          nuovoNodo->scritto=c;
          nuovoNodo->mov=d;
          nuovoNodo->sfin=e;
          nuovoNodo->next=NULL;
          for(t=0; t<75; t++){
            nuovoArr[t]=NULL;
          }
          nuovoArr[b-48]=nuovoNodo;
          arr[a]=nuovoArr;
          statoMax=a;
        }
        else if(a>statoMax+1){
          arr = (nodo_t***) realloc(arr, (a+1)*sizeof(nodo_t**));
          nuovoArr = (nodo_t**) malloc(75*sizeof(nodo_t*));
          nuovoNodo = (nodo_t*) malloc(sizeof(nodo_t));
          nuovoNodo->scritto=c;
          nuovoNodo->mov=d;
          nuovoNodo->sfin=e;
          nuovoNodo->next=NULL;
          for(t=0; t<75; t++){
            nuovoArr[t]=NULL;
          }
          nuovoArr[b-48]=nuovoNodo;
          arr[a]=nuovoArr;
          for(i=statoMax+1; i<a; i++){
            arr[i]=NULL;
          }
          statoMax=a;
        }
      }
      carLetti=scanf("%d %c %c %c %d", &a, &b, &c, &d, &e);
    }
  }
  lunghArr = statoMax +1;


  //MEMORIZZAZIONE DEGLI STATI DI ACCETTAZIONE
  len=0;
  fgets(s, 30, stdin);
  if(strcmp(s, "acc\n")==0){
    fgets(s, 30, stdin);
    while(strcmp(s, "max\n")!=0){
      sscanf(s, "%d", &numLetto);
      if(A==NULL){
        A=(int*) malloc((numLetto+1)*sizeof(int));
        A[numLetto]=1;
        //statoMax=numLetto;
        for(i=0; i<numLetto; i++){
          A[i]=2;
        }
        len=numLetto+1;
      }
      else{
        if(numLetto<len){
          A[numLetto]=1;
        }
        else if(numLetto>=len){
          A=(int*) realloc(A, (numLetto+1)*sizeof(int));
          A[numLetto]=1;
          for(i=len; i<numLetto; i++){
            A[i]=2;
          }
          len=numLetto+1;
        }
      }
      fgets(s, 30, stdin);
    }
  }

  //MEMORIZZAZIONE NUMERO MASSIMO DI MOSSE
  if(strcmp(s, "max\n")==0){
    fgets(s, 30, stdin);
    sscanf(s, "%lu", &max);
  }

  exit(1);

  //MEMORIZZAZIONE DELLE STRINGHE DI RUN E CHIAMATA DI calcolo PER ESEGUIRLE
  fgets(s, 30, stdin);
  if(strcmp(s, "run\n")==0){
    //i=1;
    //scanf("%ms", &str); //da cancellare
    while(scanf("%ms", &str)!=EOF){ //da mettere scanf("%ms", &str)!=EOF
      if(str[0]=='\0'){
        return 0;
      }
      else{
        charFinale = calcolo(str, arr, lunghArr, max, A, len);
        printf("%c\n", charFinale);
        free(str);
        //i=0;
      }
    }
  }

  //FREE DEGLI STATI DI ACCETTAZIONE
  free(A);

  //FREE DELLE QUINTUPLE
  for(i=0; i<lunghArr; i++){
    p=arr[i];
    if(p!=NULL){
      for(t=0; t<75; t++){
        coda=p[t];
        if(coda!=NULL){
          while(coda->next!=NULL){
            nuovoNodo=coda->next;
            free(coda);
            coda=NULL;
            coda=nuovoNodo;
          }
          free(coda);
        }
      }
      free(p);
    }
  }

  free(arr);
  return 0;
}

char calcolo(char* run, nodo_t*** tr, int lenArr, unsigned long int maxMosse, int* statiAcc, int len){
  int lungh, t, posiz;
  int ris;
  char us[101];
  nodo_t **punt=NULL, *puntChar=NULL;
  tr_t *coda=NULL, *head=NULL, *ultimo=NULL, *temp=NULL;

  lungh=strlen(run);
  ris=0;

  //INIZIALIZZO ARRAY STATICO PER ALLUNGARE NASTRO
  for(t=0; t<100; t++){
    us[t]='@'; //dovrei mettere un simbolo come @ per il controllo sui loop a dx e sx
  }
  us[100]='\0';

  //INIZIALIZZO LA CODA INSERENDO I PRIMI ELEMENTI
  punt=tr[0];
  if(punt!=NULL && punt[run[0]-48]!=NULL){
    puntChar=punt[run[0]-48];
      coda = (tr_t*) malloc(sizeof(tr_t));
      coda->del=0;
      coda->DXSX=1;
      coda->mosse=0;
      coda->pos=0;
      coda->statoCorr=0;
      coda->alloc=0;
      coda->lungh=lungh;
      coda->lunghSX=0;
      coda->stringaSX=NULL;
      coda->stringa = (char*) malloc((lungh+1)*sizeof(char));
      coda->stringa[0]='\0';
      strcpy(coda->stringa, run);
      coda->next=NULL;
      head=coda;
      ultimo=coda;
  }
  //FINE INIZIALIZZAZIONE

  //INIZIA L'ANALISI VERA E PROPRIA
  while(head!=NULL){ //questo while è quello principale al cui interno c'è tutta la computazione


    //ALLOCO LO SPAZIO NECESSARIO A DX O SX
    if(head->alloc==1){
      head->stringa = (char*) realloc(head->stringa, (head->lungh+101)*sizeof(char));
      //strcat(head->stringa, us);
      memcpy(head->stringa+head->lungh, us, 100);
      head->lungh=head->lungh+100;
      head->stringa[head->lungh]='\0';
    }
    else if(head->alloc==2){
      if(head->stringaSX==NULL){
        head->stringaSX = (char*) malloc(101*sizeof(char));
        memcpy(head->stringaSX, us, 100);
        head->stringaSX[100]='\0';
        //strcpy(head->stringaSX, us);
        head->lunghSX=head->lunghSX+100;
      }
      else{
        head->stringaSX = (char*) realloc(head->stringaSX, (head->lunghSX+101)*sizeof(char));
        //strcat(head->stringaSX, us);
        memcpy(head->stringaSX+head->lunghSX, us, 100);
        head->lunghSX=head->lunghSX+100;
        head->stringaSX[head->lunghSX]='\0';
      }
    }

    //MODIFICO IL NASTRO E AGGIUNGO ALTRI ELEMENTI
    if(head->DXSX==1){
      if(head->statoCorr<lenArr && tr[head->statoCorr]!=NULL){
        punt=tr[head->statoCorr];
        if(punt[head->stringa[head->pos]-48]!=NULL || (head->stringa[head->pos]=='@' && punt[47]!=NULL) ){ //cambia condizione if
          if(head->stringa[head->pos]=='@'){
            puntChar=punt[47];
          }
          else{
            puntChar=punt[head->stringa[head->pos]-48];
          }
          if(head->mosse<=maxMosse){
            posiz = head->pos;
            while(puntChar!=NULL){
              if(head->stringa[head->pos]==puntChar->scritto && head->statoCorr==puntChar->sfin && puntChar->mov=='S'){//CONTROLLO LOOP 0 a a S 0
                ris=1;
                if(puntChar->next==NULL){
                  head->del=1;
                }
              }//qui inserisci un else if(vedo @, scrivo _, mi muovo a R, torno nelle stesso stato) allora metto U
              else if(head->stringa[head->pos]=='@' && puntChar->scritto=='_' && puntChar->mov=='R' && puntChar->sfin==head->statoCorr){ //CONTROLLO PER LOOP SCORRIMENTO SEMPRE A DX
                ris=1;
                if(puntChar->next==NULL){
                  head->del=1;
                }
              }
              else{//SE TOGLI L'IF E L'ELSE IF SOPRA DEVI TOGLIERE ANCHE L'ELSE E LA SUA PARENTESI DI CHIUSURA
                head->stringa[posiz]=puntChar->scritto;
                if(puntChar->mov=='R'){
                  head->pos=posiz+1;
                  head->alloc=0;
                  if(head->pos==head->lungh){
                    head->alloc=1;
                  }
                  head->DXSX=1;
                }
                else if(puntChar->mov=='L'){
                  if(posiz==0){
                    if(head->stringaSX==NULL){
                      head->alloc=2;
                      head->DXSX=0;
                      head->pos=0;
                    }
                    else if(head->stringaSX!=NULL){
                      head->alloc=0;
                      head->DXSX=0;
                      head->pos=0;
                    }
                  }
                  else if(posiz>0){
                    head->DXSX=1;
                    head->alloc=0;
                    head->pos=posiz-1;
                  }
                }
                else if(puntChar->mov=='S'){
                  head->pos=posiz;
                  head->DXSX=1;
                  head->alloc=0;
                }
                //AGGIUNGO UN ELEMENTO
                if(puntChar->next!=NULL){
                  coda = (tr_t*) malloc(sizeof(tr_t));
                  coda->del=0;
                  coda->DXSX=head->DXSX;
                  coda->pos=head->pos;
                  coda->mosse=head->mosse+1;
                  coda->alloc=head->alloc;
                  coda->lungh=head->lungh;
                  coda->lunghSX=head->lunghSX;
                  coda->statoCorr=puntChar->sfin;
                  coda->stringa = (char*) malloc((head->lungh+1)*sizeof(char));
                  coda->stringa[0]='\0';
                  strcpy(coda->stringa, head->stringa);
                  if(head->stringaSX!=NULL){
                    coda->stringaSX = (char*) malloc((head->lunghSX+1)*sizeof(char));
                    coda->stringaSX[0]='\0';
                    strcpy(coda->stringaSX, head->stringaSX);
                  }
                  else{
                    coda->stringaSX=NULL;
                  }
                  coda->next=NULL;
                  ultimo->next=coda;
                  ultimo=coda;
                }
                else{
                  head->del=0;
                  head->mosse=head->mosse+1;
                  head->statoCorr=puntChar->sfin;
                  coda=head;
                  if(head->next!=NULL){
                    head=head->next;
                    coda->next=NULL;
                    ultimo->next=coda;
                    ultimo=coda;
                  }
                  else{
                    head=coda;
                  }
                }
              }
              puntChar=puntChar->next;
            }
          }
          else{
            head->del=1;
            ris=1;
          }
        }
        else{
          head->del=1;
        }
      }
      else{
        head->del=1;
      }
    }
    else if(head->DXSX==0){
      if(head->statoCorr<lenArr && tr[head->statoCorr]!=NULL){
        punt=tr[head->statoCorr];
        if(punt[head->stringaSX[head->pos]-48]!=NULL || (head->stringaSX[head->pos]=='@' && punt[47]!=NULL)){
          if(head->stringaSX[head->pos]=='@'){
            puntChar=punt[47];
          }
          else{
            puntChar=punt[head->stringaSX[head->pos]-48];
          }
          if(head->mosse<=maxMosse){
            posiz = head->pos;
            while(puntChar!=NULL){
              if(head->stringaSX[head->pos]==puntChar->scritto && head->statoCorr==puntChar->sfin && puntChar->mov=='S'){ //CONTROLLO LOOP 0 a a S 0
                ris=1;
                if(puntChar->next==NULL){
                  head->del=1;
                }
              }
              else if(head->stringaSX[head->pos]=='@' && puntChar->scritto=='_' && puntChar->mov=='L' && puntChar->sfin==head->statoCorr){//CONTROLLO LOOP SCORRIMENTO SEMPRE A SX
                head->del=1;
                ris=1;
                if(puntChar->next==NULL){
                  head->del=1;
                }
              }
              else{//SE TOGLI L'IF E L'ELSE IF SOPRA DEVI TOGLIERE ANCHE L'ELSE E LA SUA PARENTESI DI CHIUSURA
                head->stringaSX[posiz]=puntChar->scritto;
                if(puntChar->mov=='R'){
                  if(head->pos==0){
                    head->pos=0;
                    head->DXSX=1;
                  }
                  else if(head->pos>0){
                    head->DXSX=0;
                    head->pos=posiz - 1;
                  }
                  head->alloc=0;
                }
                else if(puntChar->mov=='L'){
                  head->pos=posiz+1;
                  if(head->pos==head->lunghSX){
                    head->alloc=2;
                  }
                  head->DXSX=0;
                }
                else if(puntChar->mov=='S'){
                  head->pos = posiz;
                  head->DXSX=0;
                  head->alloc=0;
                }
                //AGGIUNGO NUOVO ELEMENTO
                if(puntChar->next!=NULL){
                  coda = (tr_t*) malloc(sizeof(tr_t));
                  coda->del=0;
                  coda->DXSX=head->DXSX;
                  coda->pos=head->pos;
                  coda->mosse=head->mosse+1;
                  coda->alloc=head->alloc;
                  coda->lungh=head->lungh;
                  coda->lunghSX=head->lunghSX;
                  coda->statoCorr=puntChar->sfin;
                  coda->stringa = (char*) malloc((head->lungh+1)*sizeof(char));
                  coda->stringa[0]='\0';
                  strcpy(coda->stringa, head->stringa);
                  if(head->stringaSX!=NULL){
                    coda->stringaSX = (char*) malloc((head->lunghSX+1)*sizeof(char));
                    coda->stringaSX[0]='\0';
                    strcpy(coda->stringaSX, head->stringaSX);
                  }
                  else{
                    coda->stringaSX=NULL;
                  }
                  coda->next=NULL;
                  ultimo->next=coda;
                  ultimo=coda;
                }
                else{
                  head->del=0;
                  head->mosse=head->mosse+1;
                  head->statoCorr=puntChar->sfin;
                  coda=head;
                  if(head->next!=NULL){
                    head=head->next;
                    coda->next=NULL;
                    ultimo->next=coda;
                    ultimo=coda;
                  }
                  else{
                    head=coda;
                  }
                }
              }
              puntChar=puntChar->next;
            }
          }
          else{
            head->del=1;
            ris=1;
          }
        }
        else{
          head->del=1;
        }
      }
      else{
        head->del=1;
      }
    }

    //CONTROLLO SE STATO CORRENTE È DI ACCETTAZIONE
      if(ultimo->statoCorr<=len-1 && statiAcc[ultimo->statoCorr]==1){
        coda=head;
        if(coda!=NULL){
          while(coda->next!=NULL){
            temp=coda->next;
            free(coda->stringa);
            free(coda->stringaSX);
            free(coda);
            coda=NULL;
            coda=temp;
          }
          free(coda->stringa);
          free(coda->stringaSX);
          free(coda);
          coda=NULL;
        }
        return '1'; //ACCETTO perchè lo stato finale della quintupla è di accettazione
      }



    //ELIMINA PRIMO ELEMENTO DELLA CODA
    if(head->del==1){
      if(head->next==NULL){
        free(head->stringa);
        free(head->stringaSX);
        free(head);
        head=NULL;
      }
      else{
        temp=head;
        head=head->next;
        free(temp->stringa);
        free(temp->stringaSX);
        free(temp);
      }
    }


  }//parentesi di chiusura di while(head!=NULL) riga 290 circa


  if(ris==1){
    return 'U';
  }
  else{
    return '0';
  }

  free(head);
  return '0';

} //parentesi di chiusura della funzione calcolo
