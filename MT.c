//THIS IS THE CODE OF THE SIMULATOR
//I HOPE YOU CAN DO BETTER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node { //this struct represents a transition stored in the memory structure built in the main function
  struct node *next;
  char written;
  char mov;
  int finalState;
};
typedef struct node node_t;

struct transition { //this struct represents the single possibility in the non deterministic solution
  struct transition *next;
  unsigned int moves, pos, length, lengthSX, del;
  unsigned int DXSX; //=1 (right), =0 (left)
  unsigned int currentState, alloc; //alloc=0 (do not alloc), =1 (alloc on right), =2 (alloc on left)
  char *string, *stringSX;
};
typedef struct transition tr_t;


char evaluate(char*, node_t***, int, unsigned long int, int*, int);


//IN THE MAIN IS DONE THE MEMORIZATION WORK, STORING EVERY INFORMATION FROM THE INPUT TXT FILE
int main (int argc, char*argv[]){
  node_t ***arr=NULL, **newArr=NULL, **help=NULL, *newNode=NULL, **p=NULL, *queue=NULL;
  char s[30], ch1, ch2, b, c, d;
  char *str=NULL, finalChar;
  int a, e, numLetto, len, *A=NULL, i, t;
  unsigned long int max;
  int maxState, lengthArr=0;


  //TRANSITIONS MEMORIZATION
  scanf("%c%c", &ch1, &ch2);
  if(ch1=='t' && ch2=='r'){
    while(scanf("%d %c %c %c %d", &a, &b, &c, &d, &e)==5){
      if(arr==NULL){
        if(a==0){
          arr = (node_t***) malloc(sizeof(node_t**));
          newArr = (node_t**) malloc(75*sizeof(node_t*));
          newNode = (node_t*) malloc(sizeof(node_t));
          newNode->written=c;
          newNode->mov=d;
          newNode->finalState=e;
          newNode->next=NULL;
          for(t=0; t<75; t++){
            newArr[t]=NULL;
          }
          newArr[b-48]=newNode;
          arr[0]=newArr;
          maxState=a;
        }
        else{
          arr = (node_t***) malloc((a+1)*sizeof(node_t**));
          newArr = (node_t**) malloc(75*sizeof(node_t*));
          newNode = (node_t*) malloc(sizeof(node_t));
          newNode->written=c;
          newNode->mov=d;
          newNode->finalState=e;
          newNode->next=NULL;
          for(t=0; t<75; t++){
            newArr[t]=NULL;
          }
          newArr[b-48]=newNode;
          arr[a]=newArr;
          for(i=0; i<a; i++){
            arr[i]=NULL;
          }
          maxState=a;
        }
      }
      else{
        if(a<=maxState){
          newNode = (node_t*) malloc(sizeof(node_t));
          newNode->written=c;
          newNode->mov=d;
          newNode->finalState=e;
          if(arr[a]==NULL){
            newArr = (node_t**) malloc(75*sizeof(node_t*));
            arr[a]=newArr;
            newNode->next=NULL;
            for(t=0; t<75; t++){
              newArr[t]=NULL;
            }
            newArr[b-48]=newNode;
          }
          else{
            help=arr[a];
            newNode->next=help[b-48];
            help[b-48]=newNode;
          }
        }
        else if(a==maxState+1){
          arr = (node_t***) realloc(arr, (a+1)*sizeof(node_t**));
          newArr = (node_t**) malloc(75*sizeof(node_t*));
          newNode = (node_t*) malloc(sizeof(node_t));
          newNode->written=c;
          newNode->mov=d;
          newNode->finalState=e;
          newNode->next=NULL;
          for(t=0; t<75; t++){
            newArr[t]=NULL;
          }
          newArr[b-48]=newNode;
          arr[a]=newArr;
          maxState=a;
        }
        else if(a>maxState+1){
          arr = (node_t***) realloc(arr, (a+1)*sizeof(node_t**));
          newArr = (node_t**) malloc(75*sizeof(node_t*));
          newNode = (node_t*) malloc(sizeof(node_t));
          newNode->written=c;
          newNode->mov=d;
          newNode->finalState=e;
          newNode->next=NULL;
          for(t=0; t<75; t++){
            newArr[t]=NULL;
          }
          newArr[b-48]=newNode;
          arr[a]=newArr;
          for(i=maxState+1; i<a; i++){
            arr[i]=NULL;
          }
          maxState=a;
        }
      }
    }
  }
  lengthArr = maxState +1;


  //ACCEPTANCE STATES MEMORIZATION
  len=0;
  fgets(s, 30, stdin);
  if(strcmp(s, "acc\n")==0){
    fgets(s, 30, stdin);
    while(strcmp(s, "max\n")!=0){
      sscanf(s, "%d", &numLetto);
      if(A==NULL){
        A=(int*) malloc((numLetto+1)*sizeof(int));
        A[numLetto]=1;
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

  //MAX NUMBER OF MOVES MEMORIZATION
  if(strcmp(s, "max\n")==0){
    fgets(s, 30, stdin);
    sscanf(s, "%lu", &max);
  }


  //STRINGS MEMORIZATION (one at a time) AND CALL TO evaluate TO PROCESS IT
  fgets(s, 30, stdin);
  if(strcmp(s, "run\n")==0){
    while(scanf("%ms", &str)!=EOF){
      if(str[0]=='\0'){
        return 0;
      }
      else{
        finalChar = evaluate(str, arr, lengthArr, max, A, len);
        printf("%c\n", finalChar);
        free(str);
      }
    }
  }

  //ACCEPTANCE STATES FREE
  free(A);

  //TRANSITIONS FREE
  for(i=0; i<lengthArr; i++){
    p=arr[i];
    if(p!=NULL){
      for(t=0; t<75; t++){
        queue=p[t];
        if(queue!=NULL){
          while(queue->next!=NULL){
            newNode=queue->next;
            free(queue);
            queue=NULL;
            queue=newNode;
          }
          free(queue);
        }
      }
      free(p);
    }
  }

  free(arr);
  return 0;
}

char evaluate(char* run, node_t*** tr, int lenArr, unsigned long int movesMax, int* accStates, int len){
  int length, position;
  int ris, space;
  char *us=NULL;
  node_t **punt=NULL, *puntChar=NULL;
  tr_t *queue=NULL, *head=NULL, *last=NULL, *temp=NULL;

  length=strlen(run);
  ris=0;

  //QUEUE INIZIALIZATION
  punt=tr[0];
  if(punt!=NULL && punt[run[0]-48]!=NULL){
    puntChar=punt[run[0]-48];
      queue = (tr_t*) malloc(sizeof(tr_t));
      queue->del=0;
      queue->DXSX=1;
      queue->moves=0;
      queue->pos=0;
      queue->currentState=0;
      queue->alloc=0;
      queue->length=length;
      queue->lengthSX=0;
      queue->stringSX=NULL;
      queue->string = (char*) malloc((length+1)*sizeof(char));
      queue->string[0]='\0';
      strcpy(queue->string, run);
      queue->next=NULL;
      head=queue;
      last=queue;
  }
  //INIZIALIZATION ENDS


  //STARTS EVALUATION
  while(head!=NULL){


    //ALLOC OF NECESSARY SPACE ON RIGHT OR LEFT PORTION OF TAPE
    if(head->alloc==1){//ALLOC ON RIGHT
      if(us!=NULL){
        free(us);
      }
      if(head->length>3){
        space=head->length/4;
      }
      else{
        space=10;
      }
      head->string = (char*) realloc(head->string, (head->length+space+1)*sizeof(char));
      us = (char*) malloc((space)*sizeof(char));
      memset(us, '@', space);
      memcpy(&head->string[head->length], us, space);
      head->length=head->length+space;
      head->string[head->length]='\0';
    }
    else if(head->alloc==2){//ALLOC ON LEFT
      if(us!=NULL){
        free(us);
      }
      if(head->stringSX==NULL){//ALLOC ON LEFT FROM SCRATCH
        space=10;
        head->stringSX = (char*) malloc((space+1)*sizeof(char));
        us = (char*) malloc(space*sizeof(char));
        memset(us, '@', space);
        memcpy(head->stringSX, us, space);
        head->lengthSX=space;
        head->stringSX[head->lengthSX]='\0';
      }
      else{//ALLOC ON LEFT IF LEFT ALREADY EXISTS
        space=head->lengthSX/4;
        head->stringSX = (char*) realloc(head->stringSX, (head->lengthSX+space+1)*sizeof(char));
        us = (char*) malloc(space*sizeof(char));
        memset(us, '@', space);
        memcpy(&head->stringSX[head->lengthSX], us, space);
        head->lengthSX=head->lengthSX+space;
        head->stringSX[head->lengthSX]='\0';
      }
    }

    //TAPE MODIFICATION AND ADDING NEW ELEMENTS TO THE QUEUE
    if(head->DXSX==1){//RIGHT
      if(head->currentState<lenArr && tr[head->currentState]!=NULL){
        punt=tr[head->currentState];
        if(punt[head->string[head->pos]-48]!=NULL || (head->string[head->pos]=='@' && punt[47]!=NULL) ){
          if(head->string[head->pos]=='@'){
            puntChar=punt[47];
          }
          else{
            puntChar=punt[head->string[head->pos]-48];
          }
          if(head->moves<=movesMax){
            position = head->pos;
            while(puntChar!=NULL){
              if(head->string[head->pos]==puntChar->written && head->currentState==puntChar->finalState && puntChar->mov=='S'){//CHECK LOOP 0 a a S 0
                ris=1;
                if(puntChar->next==NULL){
                  head->del=1;
                }
              }
              else if(head->string[head->pos]=='@' && puntChar->written=='_' && puntChar->mov=='R' && puntChar->finalState==head->currentState){ //CHECK FOR LOOP GOING TO THE RIGHT NONSTOP
                ris=1;
                if(puntChar->next==NULL){
                  head->del=1;
                }
              }
              else if(head->string[head->pos]=='@' && puntChar->mov=='R' && puntChar->finalState==head->currentState){ //CHECK LOOP 0 _ 'char' R 0
                ris=1;
                if(puntChar->next==NULL){
                  head->del=1;
                }
              }
              else{
                head->string[position]=puntChar->written;
                if(puntChar->mov=='R'){
                  head->pos=position+1;
                  head->alloc=0;
                  if(head->pos==head->length){
                    head->alloc=1;
                  }
                  head->DXSX=1;
                }
                else if(puntChar->mov=='L'){
                  if(position==0){
                    if(head->stringSX==NULL){
                      head->alloc=2;
                      head->DXSX=0;
                      head->pos=0;
                    }
                    else if(head->stringSX!=NULL){
                      head->alloc=0;
                      head->DXSX=0;
                      head->pos=0;
                    }
                  }
                  else if(position>0){
                    head->DXSX=1;
                    head->alloc=0;
                    head->pos=position-1;
                  }
                }
                else if(puntChar->mov=='S'){
                  head->pos=position;
                  head->DXSX=1;
                  head->alloc=0;
                }
                //ADD NEW ELEMENT
                if(puntChar->next!=NULL){
                  queue = (tr_t*) malloc(sizeof(tr_t));
                  queue->del=0;
                  queue->DXSX=head->DXSX;
                  queue->pos=head->pos;
                  queue->moves=head->moves+1;
                  queue->alloc=head->alloc;
                  queue->length=head->length;
                  queue->lengthSX=head->lengthSX;
                  queue->currentState=puntChar->finalState;
                  queue->string = (char*) malloc((head->length+1)*sizeof(char));
                  memcpy(queue->string, head->string, head->length);
                  queue->string[head->length]='\0';
                  if(head->stringSX!=NULL){
                    queue->stringSX = (char*) malloc((head->lengthSX+1)*sizeof(char));
                    memcpy(queue->stringSX, head->stringSX, head->lengthSX);
                    queue->stringSX[head->lengthSX]='\0';
                  }
                  else{
                    queue->stringSX=NULL;
                  }
                  queue->next=NULL;
                  last->next=queue;
                  last=queue;
                }
                else{
                  head->del=0;
                  head->moves=head->moves+1;
                  head->currentState=puntChar->finalState;
                  queue=head;
                  if(head->next!=NULL){
                    head=head->next;
                    queue->next=NULL;
                    last->next=queue;
                    last=queue;
                  }
                  else{
                    head=queue;
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
    else if(head->DXSX==0){//LEFT
      if(head->currentState<lenArr && tr[head->currentState]!=NULL){
        punt=tr[head->currentState];
        if(punt[head->stringSX[head->pos]-48]!=NULL || (head->stringSX[head->pos]=='@' && punt[47]!=NULL)){
          if(head->stringSX[head->pos]=='@'){
            puntChar=punt[47];
          }
          else{
            puntChar=punt[head->stringSX[head->pos]-48];
          }
          if(head->moves<=movesMax){
            position = head->pos;
            while(puntChar!=NULL){
              if(head->stringSX[head->pos]==puntChar->written && head->currentState==puntChar->finalState && puntChar->mov=='S'){ //CHECK LOOP 0 a a S 0
                ris=1;
                if(puntChar->next==NULL){
                  head->del=1;
                }
              }
              else if(head->stringSX[head->pos]=='@' && puntChar->written=='_' && puntChar->mov=='L' && puntChar->finalState==head->currentState){//CHECK LOOP GOING TO LEFT NONSTOP
                head->del=1;
                ris=1;
                if(puntChar->next==NULL){
                  head->del=1;
                }
              }
              else if(head->stringSX[head->pos]=='@' && puntChar->mov=='L' && puntChar->finalState==head->currentState){ //CHECK LOOP 0 _ 'char' L 0
                ris=1;
                if(puntChar->next==NULL){
                  head->del=1;
                }
              }
              else{
                head->stringSX[position]=puntChar->written;
                if(puntChar->mov=='R'){
                  if(head->pos==0){
                    head->pos=0;
                    head->DXSX=1;
                  }
                  else if(head->pos>0){
                    head->DXSX=0;
                    head->pos=position - 1;
                  }
                  head->alloc=0;
                }
                else if(puntChar->mov=='L'){
                  head->pos=position+1;
                  if(head->pos==head->lengthSX){
                    head->alloc=2;
                  }
                  head->DXSX=0;
                }
                else if(puntChar->mov=='S'){
                  head->pos = position;
                  head->DXSX=0;
                  head->alloc=0;
                }
                //ADD NEW ELEMENT
                if(puntChar->next!=NULL){
                  queue = (tr_t*) malloc(sizeof(tr_t));
                  queue->del=0;
                  queue->DXSX=head->DXSX;
                  queue->pos=head->pos;
                  queue->moves=head->moves+1;
                  queue->alloc=head->alloc;
                  queue->length=head->length;
                  queue->lengthSX=head->lengthSX;
                  queue->currentState=puntChar->finalState;
                  queue->string = (char*) malloc((head->length+1)*sizeof(char));
                  memcpy(queue->string, head->string, head->length);
                  queue->string[head->length]='\0';
                  if(head->stringSX!=NULL){
                    queue->stringSX = (char*) malloc((head->lengthSX+1)*sizeof(char));
                    memcpy(queue->stringSX, head->stringSX, head->lengthSX);
                    queue->stringSX[head->lengthSX]='\0';
                  }
                  else{
                    queue->stringSX=NULL;
                  }
                  queue->next=NULL;
                  last->next=queue;
                  last=queue;
                }
                else{
                  head->del=0;
                  head->moves=head->moves+1;
                  head->currentState=puntChar->finalState;
                  queue=head;
                  if(head->next!=NULL){
                    head=head->next;
                    queue->next=NULL;
                    last->next=queue;
                    last=queue;
                  }
                  else{
                    head=queue;
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

    //CHECK WHETHER currentState IS AN ACCEPTANCE STATE
      if(last->currentState<=len-1 && accStates[last->currentState]==1){
        queue=head;
        if(queue!=NULL){
          while(queue->next!=NULL){
            temp=queue->next;
            free(queue->string);
            free(queue->stringSX);
            free(queue);
            queue=NULL;
            queue=temp;
          }
          free(queue->string);
          free(queue->stringSX);
          free(queue);
          queue=NULL;
        }
        free(us);
        return '1'; //ACCEPT
      }



    //ERASE FIRST ELEMENT OF QUEUE
    if(head->del==1){
      if(head->next==NULL){
        free(head->string);
        free(head->stringSX);
        free(head);
        head=NULL;
      }
      else{
        temp=head;
        head=head->next;
        free(temp->string);
        free(temp->stringSX);
        free(temp);
      }
    }

  }

  //RETURNING U OR 0
  if(ris==1){
    free(us);
    return 'U';
  }
  else{
    free(us);
    return '0';
  }

  //FREE THE LAST ELEMENT IN THE QUEUE
  free(head);
  free(us);
  return '0';

}
