#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#define CLEAR "CLS"

unsigned long long current_timestamp() {
    struct timeval tv;
    unsigned long long tim;
    gettimeofday(&tv, NULL);
    tim = 1000000 * tv.tv_sec + tv.tv_usec;
    return tim;
}

void imprimirArray(int *array, int tam) {
    for (int i = 0; i < tam; i++) {
        printf("%d ", array[i]);
    }
}

int *criarArray(int tam) {
    int *array = (int *) malloc(sizeof(int) * tam);
    for (int i = 0; i < tam; i++) {
        array[i] = i + 1;
    }
    return array;
}

int *desorganizar(int *array, int tam) {
    time_t tim;
    srand((unsigned) time(&tim));
    for (int i = 0; i < tam; i++) {
        int rand_pos = (int)(((double)rand()/RAND_MAX) * tam);
        int t = array[rand_pos];
        array[rand_pos] = array[i];
        array[i] = t;
    }
    return array;
}

void imprimeMenu() {
    printf("================================================================\n");
    printf("|     Tempo de execucao de diferentes metodos de ordenacao     |\n");
    printf("================================================================\n");
    printf("| Operacoes:                                                   |\n");
    printf("| 1) Insertion Sort                                            |\n");
    printf("| 2) Shell Sort                                                |\n");
    printf("| 3) Bubble Sort                                               |\n");
    printf("| 4) Quick Sort                                                |\n");
    printf("| 5) Merge Sort                                                |\n");
    printf("| 7) Imprimir array original                                   |\n");
    printf("| 8) Imprimir array ordenado                                   |\n");
    printf("| 9) Sair                                                      |\n");
    printf("+--------------------------------------------------------------+\n");
    printf("  Pressione a opcao desejada ");
}

void insertionSort(int *array, int tam) {
    int i, k, aux;
    for (k = 1; k < tam; k++) {
        aux = array[k];
        for (i = k - 1; i >= 0 && aux < array[i]; i--) {
            array[i + 1] = array[i];
        }
        array[i + 1] = aux;
    }

}
void bubblesort(int v[], int n) {
    int i, j, aux;
    for(j = n - 1; j > 0; j--) {
        for(i = 0; i < j; i++) {
            if(v[i] > v[i + 1]) {
                aux = v[i];
                v[i] = v[i + 1];
                v[i + 1] = aux;
            }
        }
    }
}


void shellSort(int *array, int tam) {
    int gap, j, k, aux;
    for(gap = tam / 2; gap >= 1; gap = gap / 2) {
        for(j = gap; j < tam; j++) {
            aux = array[j];
            for(k = j - gap; k >= 0 && aux < array[k]; k-=gap) {
                array[k + gap] = array[k];
            }
            array[k + gap] = aux;
        }
    }
}

void quicksort(int x[], int p, int u) {
    int i, j, pivo, aux;
    i = p;
    j = u;
    pivo = x[(i + j)/2];
    do{
        while(x[i] < pivo && i < u) i++;
        while(x[j] > pivo && j > p) j--;
        if(i <= j){
            aux = x[i];
            x[i] = x[j];
            x[j] = aux;
            i++;
            j--;
        }
    } while(i <= j);
    if(p < j) quicksort(x, p, j);
    if(i < u) quicksort(x, i, u);
}
void merge(int *x, int *temp, int esq, int meio, int dir) {
    int i, esq_fim, tam, tmp_pos;
    esq_fim = meio - 1;
    tmp_pos = esq;
    tam = dir - esq + 1;
    while ((esq <= esq_fim) && (meio <= dir)) { //Junção ordenada em temp
        if (x[esq] <= x[meio]) {                //Se elemento da esquerda menor
            temp[tmp_pos] = x[esq];
            tmp_pos++;
            esq++;
        }
        else {
            temp[tmp_pos] = x[meio];            //Se elemento da direita menor
            tmp_pos++;
            meio++;
        }
    }
    if (esq <= esq_fim) {                       //Sobraram elementos na esquerda
        memcpy(&temp[tmp_pos], &x[esq], (esq_fim - esq + 1)*sizeof(int));
    }
    if (meio <= dir) {                          //Sobraram elementos na direita
        memcpy(&temp[tmp_pos], &x[meio], (dir - meio + 1)*sizeof(int));
    }
    memcpy(&x[dir - tam + 1], &temp[dir - tam + 1], tam*sizeof(int));
}

void mergesort(int *x, int *temp, int esq, int dir) {
    int meio;
    if (dir > esq) {
        meio = (dir + esq) / 2;
        mergesort(x, temp, esq, meio);
        mergesort(x, temp, meio+1, dir);
        merge(x, temp, esq, meio+1, dir);
    }
}



int main() {
    int *original,*original2, *ordenado, tam;
    //pedir e ler o valor de tam, e substituir a atribuicao abaixo
    printf("Insira o tamanho do array: ");
    scanf("%d",&tam);
    getchar();
    getchar();
    //criando o array original
    original = desorganizar(criarArray(tam), tam);
    original2 = (int *) malloc(sizeof(int) * tam);
    memcpy(original2, original, sizeof(int) * tam);
    //alocando memoria para o array ordenado
    ordenado = (int *) malloc(sizeof(int) * tam);
    //imprimindo o menu. Colocar dentro de um laço de while e chamar as funcoes, controlar encerramento com switch
    int teste = 0;
    char opcao = '0';
    unsigned long long t1, t2;
    while(opcao != '9') {
        system("CLS");
        imprimeMenu();
        opcao = getchar();
        switch(opcao) {
            case '1':   memcpy(ordenado, original, sizeof(int) * tam);
                        t1 = current_timestamp();
                        insertionSort(ordenado,tam);
                        t2 = current_timestamp();
                        printf("\nDuracao em microssegundos: %lld\n", t2 - t1);
                        teste=1;
                        getchar();
                        getchar();
                        break;
            case '2':   memcpy(ordenado, original, sizeof(int) * tam);
                        t1 = current_timestamp();
                        shellSort(ordenado,tam);
                        t2 = current_timestamp();
                        printf("\nDuracao em microssegundos: %lld\n", t2 - t1);
                        teste =1;
                        getchar();
                        getchar();
                        break;
            case '3':   memcpy(ordenado, original, sizeof(int) * tam);
                        t1 = current_timestamp();
                        bubblesort(ordenado,tam);
                        t2 = current_timestamp();
                        printf("\nDuracao em microssegundos: %lld\n", t2 - t1);
                        teste =1;
                        getchar();
                        getchar();
                        break;
            case '4':   memcpy(ordenado, original, sizeof(int) * tam);
                        t1 = current_timestamp();
                        quicksort(ordenado,0,tam-1);
                        t2 = current_timestamp();
                        printf("\nDuracao em microssegundos: %lld\n", t2 - t1);
                        teste =1;
                        getchar();
                        getchar();
                        break;
            case '5':   memcpy(ordenado, original, sizeof(int) * tam);
                        t1 = current_timestamp();
                        mergesort(ordenado,original2,0,tam-1);
                        t2 = current_timestamp();
                        printf("\nDuracao em microssegundos: %lld\n", t2 - t1);
                        teste =1;
                        getchar();
                        getchar();
                        break;
            case '7':   imprimirArray(original,tam);
                        getchar();
                        getchar();
                        break;
            case '8':   if(teste){
                            imprimirArray(ordenado,tam);
                        }else{
                            printf("Utilize um dos metodos de ordenacao primeiramente");
                        }
                        getchar();
            getchar();
                        break;
            case '9':   break;
            default:    printf("\nOpcao invalida!\n");
                        getchar();
                        getchar();
                        break;
        }
    }
    return (EXIT_SUCCESS);
}
