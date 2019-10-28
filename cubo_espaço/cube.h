#ifndef cube_h
#define cube_h

#define SUCESS 0
#define INVALID_CUBE -1
#define INVALID_PLANE -2
#define INVALID_POS -3
#define ERRO_REMOVE -4
#define ERRO_FREE -5


#define HASH_PRIME 10597 //primo para hash table para fazer a alocação sem gastar muita memoria, usa um hash muito simples

struct cube_sparse_elem{
    long int d1,d2,d3;
    long  double elem;
    struct cube_sparse_elem *d1_next,*d2_next,*d3_next;
}; // elemento

struct cube_sparse_plane_elem {
    long int x ,y;
    struct cube_sparse_elem *elem;    
    struct cube_sparse_plane_elem *x_next,*y_next;
}; // ponteiro para o  elemento

struct cube_sparse_plane{
    long int xdim,ydim;
    struct cube_sparse_plane_elem **x_index;
    struct cube_sparse_plane_elem **y_index;
}; // plano com ponteiro->elem

struct cube_sparse{
    long double constant;
    long int d1_dim,d2_dim,d3_dim;
    struct cube_sparse_plane *d1_d2,*d2_d3,*d3_d1;
}; // cubo 


typedef struct cube_sparse_elem cube_elem;
typedef struct cube_sparse_plane_elem cube_plane_elem;
typedef struct cube_sparse_plane cube_plane;
typedef struct cube_sparse CUBE_SPARSE;


// uso tudo long int inves do long double

CUBE_SPARSE *create_cube( long int, long int,long int,long double); // cria o cubo
cube_plane* create_plane( long int, long int); // cria o plano
int cube_add(CUBE_SPARSE*,long int,long int,long int,long double); // adcionar no cubo
cube_plane_elem *plane_put(cube_plane*,long int,long int); // para adicionar no plano
cube_plane_elem *plane_get(cube_plane*,long int,long int); // para dar get no plano
long double cube_get(CUBE_SPARSE*,long int,long int,long int); // para dar get do elemento no cubo
int cube_remove(CUBE_SPARSE*,long int,long int,long int); // para remover
int cube_free(CUBE_SPARSE*); // dar free no cubo

#endif