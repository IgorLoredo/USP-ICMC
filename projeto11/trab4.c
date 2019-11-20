#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<huffman.h>

//Include de TAD’s particulares

int main(int argc,char∗argv[]){
int i; 
char text[10001],textCompac[10001],textDescompac[10001];

 TABELAHUFFMAN ∗tabela= criarTabelaHuffman(); // cria a tabela de huffman
// le o texto que sera compactado

for(i=0;(text[i] = getchar()) != '\n' && i < 10001;++i);
    text[i] = '\0';
    
// compacta o texto e modifica a tabela
textCompac = compactarHuffman(text,&tabela);
 //descompactao texto baseado na tabela criada
textDescompac = descompactarHuffman(textCompac,tabela);

// imprime o tamanho do texto original
printf( "%d\n",(int)strlen(text));
// imprime o tamanho do texto compactado
printf("%d\n",(int)strlen(textCompac));
// imprime o texto descompactado
printf( "%s \n" ,textDescompac) ;
 // libera a memoria alocada para a tabela de Huffman
liberarTabelaHuffman(&tabela);

return 0;
}