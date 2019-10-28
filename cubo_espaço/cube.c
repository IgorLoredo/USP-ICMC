#include <stdlib.h>
#include <stdio.h>
#include <cube.h>


cube_plane *create_plane(long int x ,long int y){
    cube_plane *new = (cube_plane*)malloc(sizeof(cube_plane));
    new->xdim = x;
    new->ydim = y;
    new->x_index = (cube_plane_elem**)calloc((int)x,sizeof(cube_plane_elem*));
    new->y_index = (cube_plane_elem**)calloc((int)y,sizeof(cube_plane_elem*));
    return new;
} // cria o plano

CUBE_SPARSE *create_cube(long int x, long int y,long int z, long double constant){
    CUBE_SPARSE *new = (CUBE_SPARSE*)malloc(sizeof(CUBE_SPARSE));
    new->constant = constant;
    new->d1_dim = x;
    new->d2_dim = y;
    new->d3_dim = z;
    new->d1_d2 = create_plane(x,y);
    new->d2_d3 = create_plane(y,z);
    new->d3_d1 = create_plane(z,x);
    return new;
}

cube_plane_elem *plane_put(cube_plane *plane,long int x ,long int y){
    if(!plane) return NULL;

    if(x< 0 || x>= plane->xdim || y< 0 || y>= plane->ydim) return NULL;

    cube_plane_elem **xp = &plane->x_index[(int)x];
    cube_plane_elem **yp = &plane->y_index[(int)y];

    while (*xp && (*xp)->y < y) xp = &(*xp)->y_next ;
	while (*yp && (*yp)->x < x) yp = &(*yp)->x_next;

    if (*xp && *yp && ((*xp)->y == y) && ((*yp)->x == x)){
          return *xp;
    }
    else{  
        cube_plane_elem *new = (cube_plane_elem*)calloc(1,sizeof(cube_plane_elem));
        new->x = x;
        new->y = y;
        new->x_next = *yp;
        new->y_next = *xp;
        *xp = new;
		*yp = new;
        return new;
    }
}

int cube_add(CUBE_SPARSE* cube,long int x ,long int y,long int z,long double elem){
    if(!cube) return INVALID_CUBE ;

    if( x< 0 || x >= cube->d1_dim || y < 0 || y >= cube->d2_dim || z< 0 || z>= cube->d3_dim){
       return INVALID_POS;
    }

    cube_plane_elem *elem_x_y = plane_put(cube->d1_d2,x,y);
    cube_plane_elem *elem_y_z = plane_put(cube->d2_d3,y,z);
    cube_plane_elem *elem_z_x = plane_put(cube->d3_d1,z,x);
    
    cube_elem **x_y = &elem_x_y->elem;
    cube_elem **y_x = &elem_y_z->elem;
    cube_elem **z_x = &elem_z_x->elem;
  
   while (*x_y && (*x_y)->d3 < z) x_y = &(*x_y)->d3_next;
   while (*y_x && (*y_x)->d1 < x) y_x = &(*y_x)->d1_next;
   while (*z_x && (*z_x)->d2 < y) z_x = &(*z_x)->d2_next; // essa parte irei usar em todo codigo


    if((*x_y && *y_x && *z_x) && (*x_y == *y_x) && (*y_x == *z_x)){
        (*x_y)->elem = elem;
    }else{
        cube_elem *new = (cube_elem*)calloc(1,sizeof(cube_elem));
        new->d1 = x;
        new->d2 = y;
        new->d3 = z;
        new->elem = elem;
        new->d1_next = *y_x;
        new->d2_next = *z_x;
        new->d3_next = *x_y;
        *x_y = *z_x = *y_x = new;
       
    }

    return SUCESS;
}

cube_plane_elem *plane_get(cube_plane* plane,long int x, long int y){
    if(!plane) return NULL;
    if(x< 0 || x>plane->xdim || y< 0 || y>plane->ydim) return NULL;

    cube_plane_elem **xp = &plane->x_index[(int)x];
    cube_plane_elem **yp = &plane->y_index[(int)y];

    while (*xp && ((*xp)->y < y)) xp = &(*xp)->y_next;
	while (*yp && ((*yp)->x < x)) yp = &(*yp)->x_next; // anda igual ao plane put, mas n cria um plano se não encontrar algum na posição dada

    if (*xp && *yp && (*xp)->y == y && (*yp)->x == x)
         return *xp; 
    
    return NULL;
} // função que retona o ponteiro do plano

long double cube_get(CUBE_SPARSE* cube,long int x,long int y,long int z){
    if(!cube) return INVALID_CUBE;
    if( x< 0 || x > cube->d1_dim || y < 0 || y > cube->d2_dim || z< 0 || z> cube->d3_dim){
        //printf("%Le    \n",x);
        return cube->constant;
    }
    cube_plane_elem *elem_x_y = plane_get(cube->d1_d2,x,y);
    cube_plane_elem *elem_y_z = plane_get(cube->d2_d3,y,z);
    cube_plane_elem *elem_z_x = plane_get(cube->d3_d1,z,x);

    cube_elem **x_y = &elem_x_y->elem;
    cube_elem **y_z = &elem_y_z->elem;
    cube_elem **z_x = &elem_z_x->elem;

    while (*x_y && (*x_y)->d3 < z) x_y = &(*x_y)->d3_next;
    while (*y_z && (*y_z)->d1 < x) y_z = &(*y_z)->d1_next;
    while (*z_x && (*z_x)->d2 < y) z_x = &(*z_x)->d2_next; // se repete em todo codigo

    //long double res = cube->constant;

    if((*x_y && *y_z && *z_x) && (*x_y == *y_z) && (*y_z == *z_x)){
      return(*x_y)->elem;
    }
        
    return cube->constant; // caso n tenha o elemento na lista
}



int cube_remove(CUBE_SPARSE* cube,long int x,long int y ,long int z){
    if(!cube) return INVALID_CUBE;
    if( x< 0 || x >cube->d1_dim || y < 0 || y >cube->d2_dim || z< 0 || z>cube->d3_dim){  
       return INVALID_POS;
    }

    cube_plane_elem *elem_x_y = plane_get(cube->d1_d2,x,y);
    cube_plane_elem *elem_y_z = plane_get(cube->d2_d3,y,z);
    cube_plane_elem *elem_z_x = plane_get(cube->d3_d1,z,x);

    cube_elem **x_y = &elem_x_y->elem;
    cube_elem **y_z = &elem_y_z->elem;
    cube_elem **z_x = &elem_z_x->elem;

    while (*x_y && (*x_y)->d3 < z) x_y = &(*x_y)->d3_next;
    while (*y_z && (*y_z)->d1 < x) y_z = &(*y_z)->d1_next;
    while (*z_x && (*z_x)->d2 < y) z_x = &(*z_x)->d2_next;  // igual aos anteriores

    cube_elem *aux;

    if((*x_y && *y_z && *z_x) && (*x_y == *y_z) && (*y_z == *z_x)){
        aux = (*x_y);
        *x_y = (*x_y)->d3_next;
        *y_z = (*y_z)->d1_next;
        *z_x = (*z_x)->d2_next; // munda os ponteiros
        free(aux); // dar free no elemento
        return SUCESS;
    }else{
        return ERRO_REMOVE;
    }
} 

int cube_free(CUBE_SPARSE* cube){ // dar free em cada elem percorrendo igual uma lista encadeada
    if(!cube) return ERRO_FREE;
    int i;
    cube_plane_elem *plane;
    cube_elem *elem, *aux;
    for(i=0;i<cube->d1_dim;i++){
        while(plane = cube->d1_d2[i].x_index[i]){
            elem = plane->elem;
            while( aux = elem->d1_next){
                free(elem);
                elem = aux;
            }
        }
        free(plane);
    }

     for(i=0;i<cube->d2_dim;i++){
        while(plane = cube->d2_d3[i].x_index[i]){
            elem = plane->elem;
            while( aux = elem->d2_next){
                free(elem);
                elem = aux;
            }
        }
        free(plane);
    }

     for(i=0;i<cube->d3_dim;i++){
        while(plane = cube->d3_d1[i].x_index[i]){
            elem = plane->elem;
            while( aux = elem->d3_next){
                free(elem);
                elem = aux;
            }
        }
        free(plane);
    }

    free(plane);
    free(elem);
    free(aux);
    free(cube->d1_d2);
    free(cube->d2_d3);
    free(cube->d3_d1);
    free(cube);
    return SUCESS;
}
