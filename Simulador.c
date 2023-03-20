#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int vEspecie = 500,vSubsidio = 100,vTax = 30;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void* simulador(void *v){
    srand(time(NULL));
    int pEspecie,pSubsidio,pTax;
    int eEspecie,eSubsidio,eTax;

    int vImovel = rand() % 501;
    int tax = vImovel * 0.05;

    //printf("Valor imovel: %d\n",vImovel);

    int aux = rand() % 41+30;

    pEspecie = vImovel * aux/100;
    pTax = (tax *(rand() % 51+50)/100);
    
    int subsidio = rand()%3;

    switch (subsidio)
    {
    case 0:
        pSubsidio = 5;
        break;

    case 1:
        pSubsidio = 10;
        break;

    case 2:
        pSubsidio = 20;
        break;

    default:
        break;
    }

    pthread_mutex_lock(&m);
    printf("\n=======================\nValores do usuario\n=======================\n");
    printf("Valor do Imovel: %d \nEspecie: %d \nSubisidio: %d\nTaxas: %d\n",vImovel,pEspecie,pSubsidio,pTax);
    pthread_mutex_unlock(&m);

    eSubsidio = (vImovel * pSubsidio)/100;
    eEspecie = vImovel - pEspecie - eSubsidio;
    eTax = tax - pTax;

    pthread_mutex_lock(&m);
    printf("\n=======================\nValores Emprestados\n=======================\n");
    printf("Valor do Imovel: %d \nEspecie: %d \nSubisidio: %d\nTaxas: %d\n",vImovel,eEspecie,eSubsidio,eTax);
    pthread_mutex_unlock(&m);

    pthread_mutex_lock(&m);
    vEspecie = vEspecie - eEspecie;
    vSubsidio = vSubsidio - eSubsidio;
    vTax = vTax - eTax;

    printf("\n=======================\nValores Disponíveis\n=======================\n");
    printf("Especie: %d \nSubisidio: %d\nTaxas: %d\n",vEspecie,vSubsidio,vTax);

    pthread_mutex_unlock(&m);

    sleep(5);

    pthread_mutex_lock(&m);
    vEspecie = vEspecie + eEspecie + pEspecie;
    vSubsidio += eSubsidio;
    vTax = vTax + eTax + pTax;

    printf("\n=======================\nValores Disponíveis apos simulacao\n=======================\n");
    printf("Especie: %d \nSubisidio: %d\nTaxas: %d\n",vEspecie,vSubsidio,vTax);
    pthread_mutex_unlock(&m);
    
}

int main(){
    

    pthread_t pessoa[10];
    pthread_mutex_init(&m, NULL);

    for (int j = 0; j < 3; j++)
    {
        printf("\n=======================\nGrupo %d\n=======================\n",j);
        for (int i = 0; i < 10; i++)
        {           
            pthread_create(&pessoa[i], NULL, &simulador, NULL);
            pthread_join(pessoa[i],NULL);
        }
        vSubsidio = vSubsidio * 1.5;
    }
    
    return 0;
}