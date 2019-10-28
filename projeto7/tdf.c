// igor guilherme pereira loredo nusp: 11275071
#include <stdlib.h>
#include <stdio.h>
#include <tdf.h>
#include <math.h>
 
void shell(dados_audio *vet,int tam){ // algoritmo de ordenamento
	double aux;
    int i,j,h = tam/2;
    int temp = 1;
	while(h>0){
		i=h;
		while(i<tam){
            temp = vet[i].pos;
			aux = vet[i].mag;
			j=i;
			while(j>=h && aux > vet[j-h].mag){
				vet[j].mag=vet[j-h].mag;
                vet[j].pos=vet[j-h].pos;
				j = j - h;
			}
            vet[j].pos = temp;
			vet[j].mag = aux;
			i++;
		}
	h=h/2;
    }
}

unsigned char *abrir(FILE *arquivo,int *tam){
// abre o arquivo e manda tudo para um vetor
    int cont=0;
    unsigned char *vet = (unsigned char *)malloc(1);
    while(fread(&vet[cont],1,sizeof(unsigned char),arquivo) && ++cont){
        vet = (unsigned char*)realloc(vet, sizeof(unsigned char)*cont+1);
    }
    *tam = cont;
    return vet;
}

complex *tdf(unsigned char *invet,int tam){
// faz a transformada 
    int i,j;
    complex *outvet = (complex *)malloc((tam /2+1)*sizeof(complex));
    double r;
    for(i=0;i<tam/2+1;i++){ // tam/2+1 ver depois se ta certo
    outvet[i].real = 0.0;
    outvet[i].imag = 0.0;

        for(j=0;j<tam;j++){
            r = (i*2.0*M_PI*j)/tam;
            outvet[i].real += invet[j]* cos(r);
            outvet[i].imag += invet[j]* sin(r);     
        }

    if( i > 0){
        outvet[i].real *= (2.0/tam);
        outvet[i].imag *= (-2.0/tam);
    }else{
        outvet[i].real *= (1.0/tam);
        outvet[i].imag *= (-1.0/tam);        
    }

    } 
    return outvet;
} 

dados_audio *mag(complex *coe, int tam){
//calcula a amplitude e a a frenquecia acima de 0.1
    int i;
    dados_audio *new_dados = (dados_audio*)calloc(tam,sizeof(dados_audio));
    for(i =0;i<tam;i++){
        new_dados[i].mag = sqrt(pow(coe[i].real,2) + pow(coe[i].imag,2));
        new_dados[i].pos = i;
        if  (new_dados[i].mag >0.1)
            new_dados->fren++; 
    }
    return new_dados;
}

dados_audio *vetor_c( dados_audio*vet, int c){
// faz um vetor com c primeiros valoros do vetor
    int i;
    dados_audio *new = (dados_audio*)calloc(c,sizeof(dados_audio));
    for(i=0;i<c;i++){
        new[i].mag = vet[i].mag;
        new[i].pos = vet[i].pos;
    }
    return new;
}

complex *clear_mag(dados_audio* mag,complex *invet ,int c,int tam){
//coloca o cofiente no lugar certo e deixa tudo zerado
    int i,pos;
    double aux;
    complex *new = (complex*)calloc(tam,sizeof(complex));
    for(i =0; i< c;i++){
        pos = mag[i].pos;
       new[pos].real = invet[pos].real;
        new[pos].imag = invet[pos].imag;
    }
    return new;
} 

unsigned char *tdf_inversa(complex* invet,int tam){
// faz a transformada inversa e printa os valores 
    int i,j;
    unsigned char *new = (unsigned char*)calloc(tam,sizeof(unsigned char));
    double r,temp;
    double aux;
    for(i=0;i<tam;i++){
        temp = 0;
        aux =0;
        for(j=0;j<tam/2+1;j++){
            r = (i*2.0*M_PI*j)/tam;
            r = (i*2.0*M_PI*j)/tam;
            aux += invet[j].real* cos(r);
            temp  += invet[j].imag* sin(r);
        }
        aux= aux - temp;
        new[i] = round(aux); 
       printf("%d\n",new[i]);
    }
    
    return new;
}

void clear_audio(unsigned char *audio,int tam,int c){
    int i;
   complex *result = tdf(audio,tam); // aplica a tdf

    dados_audio *coe = mag(result,tam/2+1); // gerar uma mag magnitude
    printf("%d\n",coe->fren); // amplitudes acima de 0.1
    shell(coe,tam/2+1); // ordena
    dados_audio *vet_c = vetor_c(coe,c); // gera um vetor com c 
    for(i=0;i<c;i++)
        printf("%d ",(unsigned)vet_c[i].mag); // print dos valores da amplitude
    printf("\n");

     complex *dado_limpo = clear_mag(vet_c,result,c,tam);// coloca no lugar o os coficientes         
    unsigned char *new = tdf_inversa(dado_limpo ,tam); // faz a transformada inversa

    // criando arquivo binario
    FILE *arquivo;
    if((arquivo = fopen("arquivo.bin","wb")) == NULL)
        printf("erro criar binario\n");

    for(i=0;i<tam;i++)
        fwrite(&new[i], sizeof(unsigned char),1,arquivo);

    fclose(arquivo);
    free(new);
    free(coe);
    free(result);
    free(dado_limpo);
    free(vet_c);
}