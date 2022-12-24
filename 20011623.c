

//
//  main.c
//  assignment4FilePart
//
//  Created by Asude Merve Ekiz on 15.12.2022.
//

#include <stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct person{
    int vertex;
    char name[20];
    char surname[20];
    int followingPersonNumber;
    int * followingPersonArray;
}PERSON;

int counter;
int getTotalSampleNumber(void);
void getDataFromFile(PERSON * persons,int sampleNumber);
void printPerson(PERSON person);
int ** allocateAdjMatrix(int n);
void printMatrix(int ** matrix,int n);
void fillTheAdjMatrix(int **adjMatrix,PERSON * people,int m);
void fillinDegreeArray(int *personFollowers, int **AdjMatrix,int n);
void printinDegreeArray(int * personFollowers, int n);
void updateTheinDegreeArray(int **adjMatrix, int * inDegreeArray,int n,int m);
int findCandidateInfNumber(int * inDegreeArray, int n,int m);
void findCandidateInfluencers(int* inDegreeArray, int * candidateInfluencers, int candidateNumber,int n,int m);
void printCandidateInfluencers(int * candidateInfluencers, int candidateNumber,int n,int m);
void printNumberOfConnectedPeopleOfCandidates(int * numberOfConnectedPeopleOfCandidateInfluencers, int candidateNumber,int n,int m);
void BFS(int v,int ** adjMatrix,int *queue,int *visited,int n,int f,int r);
void applyBFSforAllCandidates(int candidateNumber,int n,int *queue,int * visited, int **adjMatrix, int *candidateInfluencers,int * numberOfConnectedPersonToCandidates);
void findInfluencersV1(int x, int y, int n, int candidateNumber, int * inDegreeArray,int * candidateInfluencers, int *numberOfConnectedPersonToCandidates,PERSON * people);
void findInfluencersV2(int x, int y, int n, int candidateNumber, int * inDegreeArray,int * candidateInfluencers, int *numberOfConnectedPersonToCandidates,PERSON * people,int *queue, int * visited, int **adjMatrix);
void transferArray(int *tmpArray, int *inDegreeArray,int n);

//inDegreeArray starts from index 1
//adjMatrix starts from index (1,1)
//people array starts from index 0
//candidateInfluencers array starts from index 0
//queue and visited arrays start from index 1


int main(int argc, const char * argv[]) {
    int i,j,m,x,y;
    int n =getTotalSampleNumber();
    int mode=-1;
    int flag=0;
    int hito;
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
          printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
          printf("\n\t\t\t        =            Find the Influencer            =");
          printf("\n\t\t\t        =         created by Asude Merve Ekiz       =");
          printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
          printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
   
    printf("You will see general information first.\nThen you can access the information according to the mode you selected.\n");
   
    
    printf("************************ GENERAL INFORMATIONS**********************\n");
    printf("Total Node Number: %d\n\n",n);
    m=2; x=4; y=10;
    printf("M value: %d  X value: %d  Y value:  %d\n",m,x,y);
    PERSON * people= (PERSON*)malloc(n*sizeof(PERSON));
    getDataFromFile(people, n);
    //printf("Printing all person informations which read from file\n");
    /*
    for (i=0; i<n; i++) {
        printPerson(people[i]);
        printf("\n");
    }*/
    // kimin kimle bağlantısı olduğunun anlaşılması için matris 12x12 degil 13x13
    int ** adjMatrix = allocateAdjMatrix(n+1);
    //printMatrix(adjMatrix, m);
    fillTheAdjMatrix(adjMatrix, people, n+1);
    printf("\n****** Adj Matrix ********\n");
    printMatrix(adjMatrix, n+1);
    int *inDegreeArray=(int*)calloc(n+1, sizeof(int)); //baslangıcta followers sayisini tutuyor
    int *inDegreeFirst=(int*)calloc(n+1, sizeof(int));
    int *inDegreeLast=(int*)calloc(n+1, sizeof(int));
    fillinDegreeArray(inDegreeArray, adjMatrix, n);
    //printinDegreeArray(inDegreeArray, n);
    transferArray(inDegreeFirst, inDegreeArray, n);
    updateTheinDegreeArray(adjMatrix, inDegreeArray, n, m);
    transferArray(inDegreeLast, inDegreeArray, n);
    //printinDegreeArray(inDegreeArray, n);
    int candidateNumber = findCandidateInfNumber(inDegreeArray, n, m);
    int * candidateInfluencers=(int *)calloc(candidateNumber, sizeof(int));
    int * numberOfConnectedPersonToCandidates=(int *)calloc(candidateNumber, sizeof(int));
    findCandidateInfluencers(inDegreeArray, candidateInfluencers, candidateNumber, n, m);
    
    int *queue=(int*)calloc(n+1, sizeof(int));
    int *visited=(int*)calloc(n+1, sizeof(int));
    queue[0]=-2;
    visited[0]=-2;
    counter=0;
    printCandidateInfluencers(candidateInfluencers, candidateNumber, n, m);
    applyBFSforAllCandidates(candidateNumber, n, queue, visited, adjMatrix, candidateInfluencers, numberOfConnectedPersonToCandidates);
    
    printNumberOfConnectedPeopleOfCandidates(numberOfConnectedPersonToCandidates, candidateNumber, n, m);
    printf("*************************END OF THE GENERAL INFORMATIONS*********************\n\n");
    
    
    printf("Please choose the mode:\n");
    printf("\nFor the Normal Mode, Enter 1.\n For the Detail Mode, Enter 2.\n To Exit, Enter 0.\n");
    while (mode!=0 ) {
        printf("MODE:\n");
        scanf("%d",&mode);
        if (mode==1) {
            printf("\n**************Finding influencers for Normal Mode *************\n");
            printf("\n-------The Following People Are Influencers!-----------\n");
            findInfluencersV1(x, y, n, candidateNumber, inDegreeArray, candidateInfluencers, numberOfConnectedPersonToCandidates, people);
           
        }
        else if (mode==2){
            printf("\n***************Finding influencers for Detail Mode *************\n");
            
            printf("This is the first version of inDegreeArray\n");
            printinDegreeArray(inDegreeFirst, n);
            printf("This is the last version of inDegreeArray\n");
            printinDegreeArray(inDegreeLast, n);
            printf("Information of people who are not eliminated according to the given M value:\n");
            for (i=0; i<candidateNumber; i++) {
                hito=candidateInfluencers[i];
                printPerson(people[hito -1]);
            }
            printf("\n-------The Following People Are Influencers!-----------\n");
            findInfluencersV2(x, y, n, candidateNumber, inDegreeArray, candidateInfluencers, numberOfConnectedPersonToCandidates, people, queue, visited, adjMatrix);
            
        }
        
    }
    
    return 0;

}

void transferArray(int *tmpArray, int *inDegreeArray,int n){
    int i;
    for (i=1; i<=n; i++) {
        tmpArray[i]=inDegreeArray[i];
    }
}


void findInfluencersV1(int x, int y, int n, int candidateNumber, int * inDegreeArray,int * candidateInfluencers, int *numberOfConnectedPersonToCandidates,PERSON * people){
    int i,j;

    for (i=1; i<=n; i++) {
        if (inDegreeArray[i]>=x) {
            for (j=0; j<candidateNumber; j++) {
                if (candidateInfluencers[j]==i && numberOfConnectedPersonToCandidates[j]>=y) {
                    
                    printPerson(people[i-1]);
                    printf("---------------------\n");
                }
            }
        }
    }
}

void findInfluencersV2(int x, int y, int n, int candidateNumber, int * inDegreeArray,int * candidateInfluencers, int *numberOfConnectedPersonToCandidates,PERSON * people,int *queue, int * visited, int **adjMatrix){
    int i,j,k;
    int f,r,v;
    for (k=1; k<=n; k++) {
        if (inDegreeArray[k]>=x) {
            for (j=0; j<candidateNumber; j++) {
                if (candidateInfluencers[j]==k && numberOfConnectedPersonToCandidates[j]>=y) {
                    for (i=1; i<=n; i++) {
                        queue[i]=0;
                        visited[i]=0;
                    }
                    f=1;
                    r=1;
                    counter=0;
                    v=k;
                    queue[r]=v;
                    visited[v]=1;
                    printf("\nDirectly or indirectly followers of %d:\n",v);
                    BFS(v, adjMatrix, queue, visited, n, f, r);
                    printPerson(people[k-1]);
                    printf("---------------------\n");
                }
            }
        }
    }
}



void applyBFSforAllCandidates(int candidateNumber,int n,int *queue,int * visited, int **adjMatrix, int *candidateInfluencers,int * numberOfConnectedPersonToCandidates){
    int i,j,f,r,v;
    for (j=0; j<candidateNumber; j++) {
        for (i=1; i<=n; i++) {
            queue[i]=0;
            visited[i]=0;
        }
        f=1;
        r=1;
        counter=0;
        v=candidateInfluencers[j];
        queue[r]=v;
        visited[v]=1;
        printf("\nDirectly or indirectly followers of %d:\n",v);
        BFS(v, adjMatrix, queue, visited, n, f, r);
        numberOfConnectedPersonToCandidates[j]=counter;
        //printf("\nNumber of connected people %d.\n ",counter);
        //printf("--------------------------------------------------\n");
    }
}

//void applyBFStoTheCandidateInfluencers(int v,int ** adjMatrix,int *queue,int *visited,int n,int f,int r);

void BFS(int v,int ** adjMatrix,int *queue,int *visited,int n,int f,int r){
    int i;
    for (i=1; i<=n; i++) {
        if (adjMatrix[i][v]!=0 &&visited[i]==0) {
            r+=1;
            queue[r]=i;
            visited[i]=1;
            printf("%d ",i);
            counter+=1;
        }
    }
    f+=1;
    if (f<=r) {
        BFS(queue[f], adjMatrix, queue, visited, n, f, r);
    }
}


void findCandidateInfluencers(int* inDegreeArray, int * candidateInfluencers, int candidateNumber,int n,int m){
    int i,j=0;
    for (i=1; i<=n; i++) {
        if (inDegreeArray[i]>=m) {
            candidateInfluencers[j]=i;
            j++;
        }
    }
}
void printCandidateInfluencers(int * candidateInfluencers, int candidateNumber,int n,int m){
    int i;
    printf("\nCandidate Influencers are:\n");
    for (i=0; i<candidateNumber; i++) {
        printf("%d ",candidateInfluencers[i]);
    }
    printf("\n");
}
void printNumberOfConnectedPeopleOfCandidates(int * numberOfConnectedPeopleOfCandidateInfluencers, int candidateNumber,int n,int m){
    int i;
    printf("\nNumber of Connected People :\n");
    for (i=0; i<candidateNumber; i++) {
        printf("%d ",numberOfConnectedPeopleOfCandidateInfluencers[i]);
    }
    printf("\n");
}

int findCandidateInfNumber(int * inDegreeArray, int n,int m){
    int count=0;
    int i;
    for (i=1; i<=n; i++) {
        if (inDegreeArray[i]>=m) {
            count++;
        }
    }
    return count;
}

void updateTheinDegreeArray(int **adjMatrix, int * inDegreeArray,int n,int m){
    int i,j,k,t;
    k=1;
    for (k=1; k<=n; k++) {
        if (inDegreeArray[k]<m && inDegreeArray[k]!=-1) {
            i=k;
            for (j=1; j<=n; j++) {
                if (adjMatrix[i][j]==1) {
                    t=j;
                    if (inDegreeArray[t]!=-1) {
                        inDegreeArray[t]-=1;
                    }
                    
                }
            }
            inDegreeArray[k]=-1;
        }
        //printf("inDegreeArrayUpdated:\n");
    }
}

void fillinDegreeArray(int *inDegreeArray, int **AdjMatrix,int n){
    int i,j;
    
    for(j=1;j<=n;j++){
        for (i=1; i<=n; i++) {
            if (AdjMatrix[i][j]==1) {
                inDegreeArray[j]+=1;
            }
           //people arrayi 0.indisten başlasa da okunaklı olması
            //ve matrisle eşleşmesi açısından bu arraye yerleşim 1. indisten başlatıldı
        }
        
       
    }
    inDegreeArray[0]=-2; //ilk elemanı -2 olarak atandi
}
void printinDegreeArray(int * inDegreeArray, int n){
    int i;
    //printf("In Degree Array :\n");
    for (i=1; i<=n; i++) {
        printf("%d->%d  ",i,inDegreeArray[i]);
    }
    printf("\n");
}



void fillTheAdjMatrix(int **adjMatrix,PERSON * people,int m){
    int i,j,k;
    for (i=1; i<m; i++) {
        k=people[i-1].followingPersonNumber;
        for (j=0; j<k; j++) {
            adjMatrix[i][people[i-1].followingPersonArray[j]]=1;
        }
       
    }
}


void printPerson(PERSON person){
    int j;
    printf("\nNumber:%d\nName:%s\nSurname:%s\nFollowingNumber:%d\n",person.vertex,person.name,person.surname,person.followingPersonNumber);
    printf("Following them:");
    for (j=0; j<person.followingPersonNumber; j++) {
        printf("%d ",person.followingPersonArray[j]);
    }
    printf("\n");
}

int ** allocateAdjMatrix(int m){
    int **AdjMatrix;
    int i,j;
    AdjMatrix= (int**) calloc(m,sizeof(int*));
        for(i=0;i<m;i++){
            AdjMatrix[i] = (int*) calloc(m,sizeof(int));
        }
    for (j=1; j<m; j++) {
        AdjMatrix[0][j]=j;
    }
    for (i=0; i<m; i++) {
        AdjMatrix[i][0]=i;
    }
    
    return AdjMatrix;
}

void printMatrix(int ** matrix,int m){
    int i,j;
    for(i=0;i<m;i++){
        for(j=0;j<m;j++){
            printf("%3d",matrix[i][j]);
        }
        printf("\n");
    }
}

int getTotalSampleNumber(){
    FILE *fsample;
    int count=1;
    char ch;
    fsample=fopen("socialNET.txt", "r");
    if (fsample==NULL){
        printf("File couldn't open");
        return -1;
    }
    else{
        while ((ch=getc(fsample)) != EOF) {
            if (ch=='\n') {
                count++;
            }
        }
        fclose(fsample);
        return count /2;
    }
    
    return 0;
}
void getDataFromFile(PERSON * people,int sampleNumber){
    FILE *fsample;
    int i;
  
    fsample=fopen("socialNET.txt","r");
    if (fsample == NULL) {
        printf("Could not open the file.\n");
    }
    
    for (i=0; i<sampleNumber; i++) {
        fscanf(fsample," %d %s %s %d",&people[i].vertex,people[i].name,people[i].surname, &people[i].followingPersonNumber);
        //printf("personNumber:%d\n",people[i].personNumber);
        people[i].followingPersonArray = (int*)malloc(people[i].followingPersonNumber*sizeof(int));
        if (people[i].followingPersonNumber==1) {
            fscanf(fsample," %d",&people[i].followingPersonArray[0]);
        }
       else if (people[i].followingPersonNumber==2) {
            fscanf(fsample," %d %d",&people[i].followingPersonArray[0],&people[i].followingPersonArray[1]);
        }
        else if (people[i].followingPersonNumber==3) {
            fscanf(fsample," %d %d %d",&people[i].followingPersonArray[0],&people[i].followingPersonArray[1],&people[i].followingPersonArray[2]);
        }
        else{
            printf("Error\n");
        }
        
    }
    fclose(fsample);
}



