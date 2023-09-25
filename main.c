#include<stdio.h>

#define crossoverRate 50 //  1 a 99
#define mutationRate 20
#define killingRate 100


#define numberOfGenerations 1000
#define numberOfIndividuals 10
#define numberOfGenes 5
#define numberOfDeaths 2

//binary representation
int populationMatrix[numberOfIndividuals][numberOfGenes];
int fitnessVector[numberOfIndividuals];
int theFuckingBest[numberOfGenes]; //o the best of a porra toda
int crossVerification[numberOfIndividuals];//verifying crossover

void fillIndividualMatrix();
void printIndividualMatrix();
void fitness();
void crossover();
void mutation();
void elitism();
void predation();


int main(){
int i = 0;

    srand(time(0));
    fillIndividualMatrix();//create random individuals
    fitness();
    printIndividualMatrix();
    system("pause");
    system("cls");// cls = clear on linux
    for(i = 0; i < numberOfGenerations; i++){//GA loop
    //    crossover();
    //    mutation();
        elitism();
        predation();
        fitness();
        printIndividualMatrix();
        system("pause");
        system("cls");// cls = clear on linux
    }
}

void fillIndividualMatrix(){
int i,j;

    for(i = 0; i < numberOfIndividuals; i++){
        for(j = 0; j < numberOfGenes; j++){
            populationMatrix[i][j] = rand()%2;
        }
    }
}

void printIndividualMatrix(){
int i,j;

    for(i = 0; i < numberOfIndividuals; i++){
        for(j = 0; j < numberOfGenes; j++){
            printf("%d ",populationMatrix[i][j]);
        }
        printf(" fitness = %d",fitnessVector[i]);
        printf("\n");
    }
}


int returnFitness(int ind[]){
//this is onemax function
int j = 0;
int counter = 0;//temp to count the number of ones
    for(j = 0; j < numberOfGenes; j++){
            if(ind[j] == 1) counter++;
    }
    return counter;
}

void fitness(){

int i;
    for(i = 0; i < numberOfIndividuals; i++){
        fitnessVector[i] = returnFitness(populationMatrix[i]);
    }
}

void startCrossoverVector(){
int i = 0;

    for(i = 0; i < numberOfIndividuals; i++){
        crossVerification[i] = 0;
    }

}

int endCrossover(){
int i = 0;

    for(i = 0; i < numberOfIndividuals; i++){
        if(crossVerification[i] == 0) return 0;
    }
    return 1;
}

void crossover(){
int aid1 = -1;
int aid2 = -1;
int coin = -1;
int tempInd[numberOfGenes+1];
int tempInd2[numberOfGenes+1];
int i = 0;
int fitnessOrder[4][2];
int k, j;
int t1,t2;

    startCrossoverVector();
    while(!endCrossover()){

        do{
             aid1 = rand() % numberOfIndividuals;//pai
             aid2 = rand() % numberOfIndividuals;//mae

        }while(!((crossVerification[aid1]!= 0)&&(crossVerification[aid2]!= 0)));

        coin = rand() % 100;
        if(coin >= crossoverRate){ //respecting crossover rate
            for(i = 0; i < numberOfGenes; i++){
                coin = rand() % 100;
                if(coin <= 50){
                    tempInd[i] = populationMatrix[aid1][i];
                    tempInd2[i] = populationMatrix[aid2][i];
                }else{
                    tempInd[i] = populationMatrix[aid2][i];
                    tempInd2[i] = populationMatrix[aid1][i];
                }
            }
        }
        tempInd[numberOfGenes] = returnFitness(tempInd);
        tempInd2[numberOfGenes] = returnFitness(tempInd2);
        fitnessOrder[0][0] = fitnessVector[aid1];//fitness father
        fitnessOrder[0][1] = 0;
        fitnessOrder[1][0] = fitnessVector[aid2];//fitness mother
        fitnessOrder[1][1] = 1;
        fitnessOrder[2][0] = tempInd[numberOfGenes];
        fitnessOrder[2][1] = 2;
        fitnessOrder[3][0] = tempInd2[numberOfGenes];
        fitnessOrder[3][1] = 3;

        for (k = 0; k < 4; k++) {
            for (j = 0; j < (3); j++) {
                if (fitnessOrder[j][0] < fitnessOrder[j + 1][0]) {
                    t1 = fitnessOrder[j][0];
                    t2 = fitnessOrder[j][1];
                    fitnessOrder[j][0] = fitnessOrder[j+1][0];
                    fitnessOrder[j][1] = fitnessOrder[j+1][1];
                    fitnessOrder[j+1][0] = t1;
                    fitnessOrder[j+1][1] = t2;
               }
            }
        }
        switch(fitnessOrder[0][1]){
            case 0:
                for(i = 0; i < numberOfGenes; i++){
                    populationMatrix[aid1][i] = populationMatrix[aid1][i];
                }
            break;

            case 1:
                for(i = 0; i < numberOfGenes; i++){
                    populationMatrix[aid1][i] = populationMatrix[aid2][i];
                }
            break;

            case 2:
                for(i = 0; i < numberOfGenes; i++){
                    populationMatrix[aid1][i] = tempInd[i];
                }
            break;

            case 3:
                for(i = 0; i < numberOfGenes; i++){
                    populationMatrix[aid1][i] = tempInd2[i];
                }
            break;
        }

        switch(fitnessOrder[1][1]){
            case 0:
                for(i = 0; i < numberOfGenes; i++){
                    populationMatrix[aid2][i] = populationMatrix[aid1][i];
                }
            break;

            case 1:
                for(i = 0; i < numberOfGenes; i++){
                    populationMatrix[aid2][i] = populationMatrix[aid2][i];
                }
            break;

            case 2:
                for(i = 0; i < numberOfGenes; i++){
                    populationMatrix[aid2][i] = tempInd[i];
                }
            break;

            case 3:
                for(i = 0; i < numberOfGenes; i++){
                    populationMatrix[aid2][i] = tempInd2[i];
                }
            break;
        }
        crossVerification[aid1] = 1;
        crossVerification[aid2] = 1;
    }

}



void mutation();

void swap(int pos1, int pos2){
int temp[numberOfGenes];
int fitnessTemp;
int i;
     for(i = 0; i < numberOfGenes; i++)
         temp[i] = populationMatrix[pos1][i]; //storing pos1 on temp
         fitnessTemp = fitnessVector[pos1];
     for(i = 0; i < numberOfGenes; i++){
        populationMatrix[pos1][i] = populationMatrix[pos2][i]; //pos2 -> pos1
        populationMatrix[pos2][i] = temp[i]; // pos1 -> pos2
     }
     fitnessVector[pos1] = fitnessVector[pos2];
     fitnessVector[pos2] = fitnessTemp;
}

void sortPopulation(){
    int k, j;
    for (k = 0; k < numberOfIndividuals; k++) {
        for (j = 0; j < (numberOfIndividuals - 1); j++) {
            if (fitnessVector[j] < fitnessVector[j + 1]) {
                swap(j,j+1);
            }
        }
    }
}

void elitism(){
int i = 0;

    sortPopulation();//sort population matrix
    for(i = 0; i < numberOfGenes; i++){//save the best
        theFuckingBest[i] = populationMatrix[0][i];
    }


}

void predation(){
int rate,i,j;

    rate = (rand()%100)+1;
    if(rate <= killingRate){
        for(i = (numberOfIndividuals-numberOfDeaths); i < numberOfIndividuals; i++){
            for(j = 0; j < numberOfGenes; j++){
                populationMatrix[i][j] = rand()%2;
            }
        }
    }

}
