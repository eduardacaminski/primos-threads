#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int n, proximo=1, totalPrimos=0;
pthread_mutex_t mutex;

int isPrimo(int n){
	int i;
	if(n<2) return 0;
	
	for(i=2;i*i<=n;i++){
		if(n%i == 0) return 0;
	}
	return 1;
}

void *trabalho(void *arg){
	int id= *(int *)arg;
	int numero;
	
	while(1){
		pthread_mutex_lock(&mutex);
		numero=proximo;
		proximo++;
		pthread_mutex_unlock(&mutex);
		
		if(numero>n) break;
		
		if(isPrimo(numero)){
			pthread_mutex_lock(&mutex);
			totalPrimos++;
			pthread_mutex_unlock(&mutex);
			printf("Thread %i: O numero %i é primo\n",id,numero);
		}else{
			printf("Thread %i: O numero %i nao é primo\n",id,numero);
		}
	}
	return NULL;
}

int main(){
	int t, i;
    pthread_t *threads;
    int *ids;
    
    printf("Digite a quantidade de números a processar: ");
    scanf("%d", &n);
    printf("Digite a quantidade de threads a criar: ");
    scanf("%d", &t);
    
    
    if (n< 1 || t< 1) {
        printf("Valores inválidos.\n");
        return 1;
    }
    
    threads = (pthread_t *) malloc(t * sizeof(pthread_t));
    ids     = (int *) malloc(t * sizeof(int));
    
    pthread_mutex_init(&mutex, NULL);
    
    for (i = 0; i < t; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, trabalho, &ids[i]);
    }
    
    for (i = 0; i < t; i++) {
        pthread_join(threads[i], NULL);
    }
    
     printf("O número total de números primos encontrados foi: %d\n", totalPrimos);
     
    pthread_mutex_destroy(&mutex);
    free(threads);
    free(ids);
    
    system("pause");
    return 0;
}
