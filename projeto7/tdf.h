// igor guilherme pereira loredo nusp: 11275071 

#ifndef tdf_h
#define tdf_h

struct COMPLEX{
    double imag;
    double real;    
};

struct DADOS{
   int pos;
    double mag;
    int fren;
};

typedef struct DADOS dados_audio; // descritor para calcular amplitude, frenquencia e a posição 
typedef struct COMPLEX complex; // struct para os numeros complexos

unsigned char*abrir(FILE*,int*); // pega o arquivo e retona um vetor e seu tamanho
complex *tdf(unsigned char*,int); // aplica a forma da transformada discreta
complex *clear_mag(dados_audio*,complex*,int,int); // coloca na posição correta 
dados_audio *mag(complex *antigo, int tam);//calcula amplitude
dados_audio *vetor_c( dados_audio *,int);
void shell(dados_audio*,int); // algoritmo para ordenação
void clear_audio(unsigned char*,int,int);
unsigned char *tdf_inversa(complex*,int);

#endif
