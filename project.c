#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct entity{
    char entity_name[40];
    struct entity *sx_entity;
    struct entity *dx_entity;
    struct entity *parent;
}entity_t;

typedef struct relazione{
    char relazione[40];
    int max_in_rel;
    struct entity_in_rel* first_entity_in_rel;
    struct relazione* rel_prec;
    struct relazione* next_rel;
}relazione_t;

typedef struct entity_in_rel{
    char entity_in_rel[40];
    int num_rel;
    struct entity_in_rel *prec_entity_in_rel;
    struct entity_in_rel *next_entity_in_rel;
    struct entity_in_tree *first_entity_in_tree;
}entity_in_rel_t;

typedef struct entity_in_tree{
    char entity_in_tree[40];
    struct entity_in_tree *sx_entity_in_tree;
    struct entity_in_tree *dx_entity_in_tree;
    struct entity_in_tree *parent_in_tree;
}entity_in_tree_t;


void addent(entity_t *entity_root, char *id_ent);
void addent(entity_t *entity_root, char *id_ent) {
    entity_t *punt_entity = entity_root;
    entity_t *new_entity;
    int confronta_ordine;
    int trova_void = 0;

    trova_void = strcmp(punt_entity -> entity_name, "vuota");
    if (trova_void == 0){
        strcpy(punt_entity -> entity_name, id_ent);
    }
    else {
        confronta_ordine = strcmp(punt_entity -> entity_name, id_ent);
        if (confronta_ordine < 0) {
            if (punt_entity -> dx_entity != NULL) {
                addent(punt_entity -> dx_entity, id_ent);
            } else {
                new_entity = (entity_t *) malloc(sizeof(entity_t));
                strcpy(new_entity -> entity_name, id_ent);
                new_entity -> dx_entity = NULL;
                new_entity -> sx_entity = NULL;
                new_entity -> parent = punt_entity;
                punt_entity -> dx_entity = new_entity;
            }
        } else if (confronta_ordine > 0) {
            if (punt_entity -> sx_entity != NULL) {
                addent(punt_entity -> sx_entity, id_ent);
            } else {
                new_entity = (entity_t *) malloc(sizeof(entity_t));
                strcpy(new_entity -> entity_name, id_ent);
                new_entity -> dx_entity = NULL;
                new_entity -> sx_entity = NULL;
                new_entity -> parent = punt_entity;
                punt_entity -> sx_entity = new_entity;
            }
        }
    }
}


int check_presenza_entity(entity_t *entity_root, char *id_ent);
int check_presenza_entity(entity_t *entity_root, char *id_ent){
    entity_t *punt_entity = entity_root;
    int confronta_entity;

    while((punt_entity -> dx_entity != NULL) || (punt_entity -> sx_entity != NULL)){
        confronta_entity = strcmp(punt_entity -> entity_name, id_ent);
        if(confronta_entity < 0){
            if(punt_entity -> dx_entity != NULL){
                punt_entity = punt_entity -> dx_entity;
            }
            else{
                return 0;
            }
        }
        else if(confronta_entity > 0){
            if(punt_entity -> sx_entity != NULL){
                punt_entity = punt_entity -> sx_entity;
            }
            else{
                return 0;
            }
        }
        else{
            return 1;
        }
    }
    confronta_entity = strcmp(punt_entity -> entity_name, id_ent);
    if(confronta_entity == 0){
        return 1;
    }
    return 0;
}


entity_t* find_entity(entity_t* entityRoot, char* idEntity);
entity_t* find_entity(entity_t* entityRoot, char* idEntity){
    entity_t* puntEntity = entityRoot;
    int confrontaEntity;

    while((puntEntity -> dx_entity != NULL) || (puntEntity -> sx_entity != NULL)){
        confrontaEntity = strcmp(puntEntity -> entity_name, idEntity);
        if(confrontaEntity < 0){
            if(puntEntity -> dx_entity != NULL){
                puntEntity = puntEntity -> dx_entity;
            }
            else{
                return  NULL;
            }
        }
        else if(confrontaEntity > 0){
            if(puntEntity -> sx_entity != NULL){
                puntEntity = puntEntity -> sx_entity;
            }
            else{
                return NULL;
            }
        }
        else{
            return puntEntity;
        }
    }
    confrontaEntity = strcmp(puntEntity -> entity_name, idEntity);
    if(confrontaEntity == 0){
        return puntEntity;
    }
    return NULL;
}


entity_in_tree_t* findEntityInTree(entity_in_tree_t* entityRoot, char* idEntity);
entity_in_tree_t* findEntityInTree(entity_in_tree_t* entityRoot, char* idEntity){
    entity_in_tree_t* puntEntity = entityRoot;
    int confrontaEntity;

    while(((puntEntity -> dx_entity_in_tree != NULL) || (puntEntity -> sx_entity_in_tree != NULL))){  // SEGSEV DOVUTO A PUNTENTITY CHE ARRIVA A NULL E PROVO AD ACCEDERE ->DX||->SX
        confrontaEntity = strcmp(puntEntity -> entity_in_tree, idEntity);
        if(confrontaEntity < 0){
            if(puntEntity -> dx_entity_in_tree != NULL){
                puntEntity = puntEntity -> dx_entity_in_tree;
            }
            else{
                return NULL;
            }
        }
        else if(confrontaEntity > 0){
            if(puntEntity -> sx_entity_in_tree != NULL){
                puntEntity = puntEntity -> sx_entity_in_tree;
            }
            else{
                return NULL;
            }
        }
        else{
            return puntEntity;
        }
    }
    if(puntEntity != NULL) {
        confrontaEntity = strcmp(puntEntity -> entity_in_tree, idEntity);
        if (confrontaEntity == 0) {
            return puntEntity;
        }
    }
    return NULL;
}


relazione_t* check_presenza_rel_type(relazione_t* rel_head, char *rel_type);
relazione_t* check_presenza_rel_type(relazione_t* rel_head, char *rel_type){
    relazione_t *punt_rel = rel_head;
    int compare;

    while(punt_rel != NULL){
        compare = strcmp(punt_rel -> relazione, rel_type);
        if(compare == 0){
            return punt_rel;
        }
        punt_rel = punt_rel -> next_rel;
    }
    return NULL;
}


entity_in_tree_t* check_presenza_entity_in_rel_tree(entity_in_tree_t *first_entity_in_tree, char *id_ent);
entity_in_tree_t* check_presenza_entity_in_rel_tree(entity_in_tree_t *first_entity_in_tree, char *id_ent){
    entity_in_tree_t *punt_entity = first_entity_in_tree;
    int confronta_entity;

    while((punt_entity -> dx_entity_in_tree != NULL) || (punt_entity -> sx_entity_in_tree != NULL)){
        confronta_entity = strcmp(punt_entity -> entity_in_tree, id_ent);
        if(confronta_entity < 0){
            if(punt_entity -> dx_entity_in_tree != NULL){
                punt_entity = punt_entity -> dx_entity_in_tree;
            }
            else{
                return NULL;
            }
        }
        else if(confronta_entity > 0){
            if(punt_entity -> sx_entity_in_tree != NULL){
                punt_entity = punt_entity -> sx_entity_in_tree;
            }
            else{
                return NULL;
            }
        }
        else{
            return punt_entity;
        }
    }
    confronta_entity = strcmp(punt_entity -> entity_in_tree, id_ent);
    if(confronta_entity == 0){
        return punt_entity;
    }
    return NULL;
}


relazione_t* add_new_rel_type(relazione_t *rel_head, char *rel_type, char *id_orig, char *id_dest);
relazione_t* add_new_rel_type(relazione_t *rel_head, char *rel_type, char *id_orig, char *id_dest) {
    relazione_t *punt_rel = rel_head;
    relazione_t *new_rel_type;
    entity_in_tree_t *new_ent_orig;
    entity_in_rel_t *new_ent_dest;
    int confronta_per_ordine;

    new_ent_orig = (entity_in_tree_t *) malloc(sizeof(entity_in_tree_t));
    strcpy(new_ent_orig -> entity_in_tree, id_orig);
    new_ent_orig -> sx_entity_in_tree = NULL;
    new_ent_orig -> dx_entity_in_tree = NULL;
    new_ent_orig -> parent_in_tree = NULL;

    new_ent_dest = (entity_in_rel_t *) malloc(sizeof(entity_in_rel_t));
    strcpy(new_ent_dest -> entity_in_rel, id_dest);
    new_ent_dest -> num_rel = 1;
    new_ent_dest -> prec_entity_in_rel = NULL;
    new_ent_dest -> next_entity_in_rel = NULL;
    new_ent_dest -> first_entity_in_tree = new_ent_orig;

    confronta_per_ordine = strcmp(rel_head -> relazione, "vuota");
    if (confronta_per_ordine == 0) {
        strcpy(rel_head -> relazione, rel_type);
        rel_head -> max_in_rel = 1;
        rel_head -> first_entity_in_rel = new_ent_dest;
        return rel_head;
    } else {
        new_rel_type = (relazione_t *) malloc(sizeof(relazione_t));
        strcpy(new_rel_type -> relazione, rel_type);
        new_rel_type -> max_in_rel = 1;
        new_rel_type -> first_entity_in_rel = new_ent_dest;

        confronta_per_ordine = strcmp(punt_rel -> relazione, rel_type);
        while ((confronta_per_ordine < 0) && (punt_rel -> next_rel != NULL)) {
            punt_rel = punt_rel -> next_rel;
            confronta_per_ordine = strcmp(punt_rel -> relazione, rel_type);
        }
        if (confronta_per_ordine < 0) {
            punt_rel -> next_rel = new_rel_type;
            new_rel_type -> rel_prec = punt_rel;
            new_rel_type -> next_rel = NULL;
            return rel_head;
        } else {
            new_rel_type -> next_rel = punt_rel;
            //punt_rel -> rel_prec = new_rel_type;
            if (punt_rel -> rel_prec != NULL) {
                new_rel_type -> rel_prec = punt_rel -> rel_prec;
                punt_rel -> rel_prec -> next_rel = new_rel_type;
                punt_rel -> rel_prec = new_rel_type;
                return rel_head;
            } else {
                new_rel_type -> rel_prec = NULL;
                punt_rel -> rel_prec = new_rel_type;
                return  new_rel_type;
            }
        }
    }
}


void add_entity_in_tree(relazione_t *punt_rel_type, entity_in_rel_t *punt_ent_in_rel, entity_in_tree_t *punt_ent_in_tree, char *id_orig);
void add_entity_in_tree(relazione_t *punt_rel_type, entity_in_rel_t *punt_ent_in_rel, entity_in_tree_t *punt_ent_in_tree, char *id_orig) {
    entity_in_tree_t *punt_ent_orig_in_tree = punt_ent_in_tree;
    entity_in_tree_t *new_ent_in_tree;
    int confronta_ordine;

    confronta_ordine = strcmp(punt_ent_orig_in_tree -> entity_in_tree, id_orig);
    if (confronta_ordine < 0) {
        if (punt_ent_orig_in_tree -> dx_entity_in_tree != NULL){
            add_entity_in_tree(punt_rel_type, punt_ent_in_rel, punt_ent_orig_in_tree -> dx_entity_in_tree, id_orig);
        }
        else{
            new_ent_in_tree = (entity_in_tree_t*) malloc(sizeof(entity_in_tree_t));
            strcpy(new_ent_in_tree -> entity_in_tree, id_orig);
            new_ent_in_tree -> sx_entity_in_tree = NULL;
            new_ent_in_tree -> dx_entity_in_tree = NULL;
            new_ent_in_tree -> parent_in_tree = punt_ent_orig_in_tree;
            punt_ent_orig_in_tree -> dx_entity_in_tree = new_ent_in_tree;
            punt_ent_in_rel -> num_rel = punt_ent_in_rel -> num_rel + 1;
            if(punt_ent_in_rel -> num_rel > punt_rel_type -> max_in_rel){
                punt_rel_type -> max_in_rel = punt_ent_in_rel -> num_rel;
            }

        }
    } else if(confronta_ordine > 0){
        if(punt_ent_orig_in_tree -> sx_entity_in_tree != NULL){
            add_entity_in_tree(punt_rel_type, punt_ent_in_rel, punt_ent_orig_in_tree -> sx_entity_in_tree, id_orig);
        }
        else{
            new_ent_in_tree = (entity_in_tree_t*) malloc(sizeof(entity_in_tree_t));
            strcpy(new_ent_in_tree -> entity_in_tree, id_orig);
            new_ent_in_tree -> sx_entity_in_tree = NULL;
            new_ent_in_tree -> dx_entity_in_tree = NULL;
            new_ent_in_tree -> parent_in_tree = punt_ent_orig_in_tree;
            punt_ent_orig_in_tree -> sx_entity_in_tree = new_ent_in_tree;
            punt_ent_in_rel -> num_rel = punt_ent_in_rel -> num_rel + 1;
            if(punt_ent_in_rel -> num_rel > punt_rel_type -> max_in_rel){
                punt_rel_type -> max_in_rel = punt_ent_in_rel -> num_rel;
            }
        }
    }
}


void checkadd_entity_in_tree(relazione_t *punt_rel_type, entity_in_rel_t *punt_ent_in_rel, char *id_orig);
void checkadd_entity_in_tree(relazione_t *punt_rel_type, entity_in_rel_t *punt_ent_in_rel, char *id_orig){
    entity_in_tree_t *punt_ent_in_tree = punt_ent_in_rel -> first_entity_in_tree;
    entity_in_tree_t *new_ent_in_tree;

    if(punt_ent_in_tree == NULL){
        new_ent_in_tree = (entity_in_tree_t*) malloc(sizeof(entity_in_tree_t));
        strcpy(new_ent_in_tree -> entity_in_tree, id_orig);
        new_ent_in_tree -> sx_entity_in_tree = NULL;
        new_ent_in_tree -> dx_entity_in_tree = NULL;
        new_ent_in_tree -> parent_in_tree = NULL;
        punt_ent_in_rel -> first_entity_in_tree = new_ent_in_tree;
        punt_ent_in_rel -> num_rel = 1;
        if (punt_ent_in_rel -> num_rel > punt_rel_type -> max_in_rel){
            punt_rel_type -> max_in_rel = punt_ent_in_rel -> num_rel;
        }
    }
    else{
        add_entity_in_tree(punt_rel_type, punt_ent_in_rel, punt_ent_in_tree, id_orig);
    }
}


entity_in_rel_t* checkadd_entity_in_rel(relazione_t *punt_rel_type, char *id_orig, char *id_dest);
entity_in_rel_t* checkadd_entity_in_rel(relazione_t *punt_rel_type, char *id_orig, char *id_dest) {
    entity_in_rel_t *punt_ent_in_rel = punt_rel_type -> first_entity_in_rel;
    entity_in_rel_t *new_ent_in_rel;
    entity_in_tree_t *new_ent_in_tree;
    int compare;
    
    compare = strcmp(punt_ent_in_rel -> entity_in_rel, id_dest);
    while ((compare < 0) && (punt_ent_in_rel -> next_entity_in_rel != NULL)) {
        punt_ent_in_rel = punt_ent_in_rel -> next_entity_in_rel;
        compare = strcmp(punt_ent_in_rel -> entity_in_rel, id_dest);
    }
    if (compare == 0) {
        checkadd_entity_in_tree(punt_rel_type, punt_ent_in_rel,id_orig); //Se la dest e` presente deve verificare soltanto l`origine nell`albero di quella entity)
    } else if (compare > 0) {

        new_ent_in_tree = (entity_in_tree_t *) malloc(sizeof(entity_in_tree_t));
        strcpy(new_ent_in_tree -> entity_in_tree, id_orig);
        new_ent_in_tree -> sx_entity_in_tree = NULL;
        new_ent_in_tree -> dx_entity_in_tree = NULL;
        new_ent_in_tree -> parent_in_tree = NULL;

        new_ent_in_rel = (entity_in_rel_t *) malloc(sizeof(entity_in_rel_t));
        strcpy(new_ent_in_rel -> entity_in_rel, id_dest);
        new_ent_in_rel -> num_rel = 1;
        new_ent_in_rel -> first_entity_in_tree = new_ent_in_tree;
        new_ent_in_rel -> next_entity_in_rel = punt_ent_in_rel;
        new_ent_in_rel -> prec_entity_in_rel = punt_ent_in_rel -> prec_entity_in_rel;
        if (punt_ent_in_rel -> prec_entity_in_rel != NULL) {
            punt_ent_in_rel -> prec_entity_in_rel -> next_entity_in_rel = new_ent_in_rel;
        }
        punt_ent_in_rel -> prec_entity_in_rel = new_ent_in_rel;
        if(new_ent_in_rel -> prec_entity_in_rel == NULL){
            return new_ent_in_rel;
        }
    }
    else if(compare < 0){
        new_ent_in_tree = (entity_in_tree_t *) malloc(sizeof(entity_in_tree_t));
        strcpy(new_ent_in_tree -> entity_in_tree, id_orig);
        new_ent_in_tree -> sx_entity_in_tree = NULL;
        new_ent_in_tree -> dx_entity_in_tree = NULL;
        new_ent_in_tree -> parent_in_tree = NULL;

        new_ent_in_rel = (entity_in_rel_t *) malloc(sizeof(entity_in_rel_t));
        strcpy(new_ent_in_rel -> entity_in_rel, id_dest);
        new_ent_in_rel -> num_rel = 1;
        new_ent_in_rel -> first_entity_in_tree = new_ent_in_tree;
        new_ent_in_rel -> prec_entity_in_rel = punt_ent_in_rel;
        new_ent_in_rel -> next_entity_in_rel = punt_ent_in_rel -> next_entity_in_rel;
        punt_ent_in_rel -> next_entity_in_rel = new_ent_in_rel;
    }
    return punt_rel_type -> first_entity_in_rel;
}


relazione_t* addrel(entity_t *entity_root, char *id_ent1, char *id_ent2, char *rel_type, relazione_t *rel_head);
relazione_t* addrel(entity_t *entity_root, char *id_ent1, char *id_ent2, char *rel_type, relazione_t *rel_head){
    int check_entity = 0;
    relazione_t *punt_rel_type;

    check_entity = check_entity + check_presenza_entity(entity_root, id_ent1);
    check_entity = check_entity + check_presenza_entity(entity_root, id_ent2);
    if(check_entity == 2){ //Entrambe le entity sono sotto monitoraggio e si puo` procedere con il controllo delle relazioni
        punt_rel_type = check_presenza_rel_type(rel_head, rel_type);
        if (punt_rel_type == NULL){ //La relazione non e` presente nella lista di tutte le relazioni e si deve aggiungere ORDINATA IN ORDINE ALFABETICO
            rel_head = add_new_rel_type(rel_head, rel_type, id_ent1, id_ent2);
        }
        else{ //La relazione e` presente e su deve controllare il monitoraggio delle entita` in quella relazione.
            punt_rel_type -> first_entity_in_rel = checkadd_entity_in_rel(punt_rel_type, id_ent1, id_ent2);
        }
    }
    return rel_head;
}


entity_in_tree_t* tree_minimum(entity_in_tree_t* entityInTreeMin);
entity_in_tree_t* tree_minimum(entity_in_tree_t* entityInTreeMin){
    while(entityInTreeMin -> sx_entity_in_tree != NULL){
        entityInTreeMin = entityInTreeMin -> sx_entity_in_tree;
    }
    return entityInTreeMin;
}


entity_t* tree_ent_minimum(entity_t* entityMin);
entity_t* tree_ent_minimum(entity_t* entityMin){
    while(entityMin -> sx_entity != NULL){
        entityMin = entityMin -> sx_entity;
    }
    return entityMin;
}


entity_in_tree_t* tree_successor(entity_in_tree_t* entityInTree);
entity_in_tree_t* tree_successor(entity_in_tree_t* entityInTree){
    entity_in_tree_t* successorInTree;
    if(entityInTree -> dx_entity_in_tree != NULL){
        return tree_minimum(entityInTree -> dx_entity_in_tree);
    }
    successorInTree = entityInTree -> parent_in_tree;
    while((entityInTree != NULL) && (entityInTree == successorInTree -> dx_entity_in_tree)){
        entityInTree = successorInTree;
        successorInTree = successorInTree -> parent_in_tree;
    }
    return successorInTree;
}


entity_t* tree_ent_successor(entity_t* entityInTree);
entity_t* tree_ent_successor(entity_t* entityInTree){
    entity_t* successorInTree;
    if(entityInTree -> dx_entity != NULL){
        return tree_ent_minimum((entityInTree -> dx_entity));
    }
    successorInTree = entityInTree -> parent;
    while((entityInTree != NULL) && (entityInTree == successorInTree -> dx_entity)){
        entityInTree = successorInTree;
        successorInTree = successorInTree -> parent;
    }
    return successorInTree;
}


entity_in_tree_t* delent_from_tree(entity_in_tree_t* ent_tree_root, entity_in_tree_t* punt_ent_del);
entity_in_tree_t* delent_from_tree(entity_in_tree_t* ent_tree_root, entity_in_tree_t* punt_ent_del){
    entity_in_tree_t* entityToDelete;
    entity_in_tree_t* entitySupport;

    if((punt_ent_del -> sx_entity_in_tree == NULL) || (punt_ent_del -> dx_entity_in_tree == NULL)){
        entityToDelete = punt_ent_del;
    }
    else{
        entityToDelete = tree_successor(punt_ent_del);
    }
    //entitySupport e` il figlio non NULL di entityToDelete, NULL altrimenti
    if(entityToDelete -> sx_entity_in_tree != NULL){
        entitySupport = entityToDelete -> sx_entity_in_tree;
    }
    else{
        entitySupport = entityToDelete -> dx_entity_in_tree;
    }
    if(entitySupport != NULL){
        entitySupport -> parent_in_tree = entityToDelete -> parent_in_tree;
    }
    if(entityToDelete -> parent_in_tree == NULL){
        ent_tree_root = entitySupport;
        //ent_tree_root -> parent_in_tree = NULL;
    }
    else if(entityToDelete -> parent_in_tree -> sx_entity_in_tree == entityToDelete){
        entityToDelete -> parent_in_tree -> sx_entity_in_tree = entitySupport;
    }
    else{
        entityToDelete -> parent_in_tree -> dx_entity_in_tree = entitySupport;
    }
    if(entityToDelete != punt_ent_del){
        strcpy(punt_ent_del -> entity_in_tree, entityToDelete -> entity_in_tree);
    }
    free(entityToDelete);
    return ent_tree_root;
}


int find_max_in_rel(relazione_t* punt_rel_type, int num_post_del);
int find_max_in_rel(relazione_t* punt_rel_type, int num_post_del){
    entity_in_rel_t* punt_ent_in_rel;

    if(punt_rel_type -> max_in_rel == num_post_del + 1){
        punt_ent_in_rel = punt_rel_type -> first_entity_in_rel;
        while(punt_ent_in_rel -> num_rel <= num_post_del){
            punt_ent_in_rel = punt_ent_in_rel -> next_entity_in_rel;
            if(punt_ent_in_rel == NULL){
                return num_post_del;
            }
        }
        return punt_rel_type -> max_in_rel;
    }
    return punt_rel_type -> max_in_rel;
}


relazione_t* delrel(entity_t *entity_root, char *id_ent1, char *id_ent2, char *rel_type, relazione_t *rel_head);
relazione_t* delrel(entity_t *entity_root, char *id_ent1, char *id_ent2, char *rel_type, relazione_t *rel_head) {
    relazione_t *punt_rel_type;
    entity_in_rel_t *punt_entity_in_rel;
    entity_in_tree_t *punt_entity_in_tree;
    int compare;
    int check_entity;

    check_entity = check_presenza_entity(entity_root, id_ent1) + check_presenza_entity(entity_root, id_ent2); //Controlla che esistano le due entity
    if (check_entity == 2) {
        punt_rel_type = check_presenza_rel_type(rel_head, rel_type); //Controlla se la relazione che si vuole eliminare esiste davvero, ritorna NULL se non la trova.
        if (punt_rel_type == NULL) {  //LA RELAZIONE CERCATA NON ESISTE
            return rel_head;
        }
        punt_entity_in_rel = punt_rel_type -> first_entity_in_rel;

        compare = strcmp(punt_entity_in_rel -> entity_in_rel, id_ent2); //Controlla se la entity dest ha qualche relazione del rel_type specificato
        while (compare < 0) {
            punt_entity_in_rel = punt_entity_in_rel -> next_entity_in_rel;
            if (punt_entity_in_rel == NULL) {
                return rel_head;
            }
            compare = strcmp(punt_entity_in_rel -> entity_in_rel, id_ent2);
        }
        if (compare > 0) {
            return rel_head;
        }

        punt_entity_in_tree = check_presenza_entity_in_rel_tree(punt_entity_in_rel -> first_entity_in_tree, id_ent1);
        if (punt_entity_in_tree == NULL) {
            return rel_head;
        }
        //LA RELAZIONE ESISTE SICURAMENTE TRA LE DUE ENTITY E DEVE PROCEDERE ALLA CANCELLAZIONE, HO TUTTO IN PUNT_REL_TYPE, PUNT_ENTITY_IN_REL, PUNT_ENTITY_IN_TREE

        if(punt_entity_in_rel -> num_rel > 1){
            punt_entity_in_rel -> first_entity_in_tree = delent_from_tree(punt_entity_in_rel -> first_entity_in_tree, punt_entity_in_tree);
            punt_entity_in_rel -> num_rel = punt_entity_in_rel -> num_rel - 1;
            punt_rel_type -> max_in_rel = find_max_in_rel(punt_rel_type, punt_entity_in_rel -> num_rel);
            return rel_head;
        }
        else if(punt_entity_in_rel -> num_rel == 1){
            //Si devono distinguere due casi in cui la relazione contiene solo una entity la cui num_rel == 1 e l`altro caso in cui quella rel_type ha diverse entity in rel.
            //Controllo pertanto de la rel_type e` l`unica della lista guardando se coincide con la first_in_rel e se il successivo vale NULL
            if((punt_entity_in_rel -> prec_entity_in_rel == NULL) && (punt_entity_in_rel -> next_entity_in_rel == NULL)){
                if((punt_rel_type -> rel_prec == NULL) && (punt_rel_type -> next_rel == NULL)){
                    strcpy(punt_rel_type -> relazione, "vuota");
                    free(punt_entity_in_rel);
                    free(punt_entity_in_tree);
                    punt_rel_type -> first_entity_in_rel = NULL;
                }
                else{
                    if(punt_rel_type -> rel_prec == NULL){ //E` la testa della lista quindi cambiera` rel_head
                        punt_rel_type -> next_rel -> rel_prec = NULL;
                        free(punt_rel_type);
                        free(punt_entity_in_rel);
                        free(punt_entity_in_tree);
                        return punt_rel_type -> next_rel;
                    }
                    else if(punt_rel_type -> next_rel == NULL){
                        punt_rel_type -> rel_prec -> next_rel = NULL;
                        free(punt_rel_type);
                        free(punt_entity_in_rel);
                        free(punt_entity_in_tree);
                        return rel_head;
                    }
                    punt_rel_type -> rel_prec -> next_rel = punt_rel_type -> next_rel;
                    punt_rel_type -> next_rel -> rel_prec = punt_rel_type -> rel_prec;
                    free(punt_rel_type);
                    free(punt_entity_in_rel);
                    free(punt_entity_in_tree);
                    return rel_head;
                }
            }
            else{
                if(punt_entity_in_rel -> prec_entity_in_rel == NULL){
                    punt_entity_in_rel -> next_entity_in_rel -> prec_entity_in_rel = NULL;
                    punt_rel_type -> first_entity_in_rel = punt_entity_in_rel -> next_entity_in_rel;
                }
                else {
                    punt_entity_in_rel -> prec_entity_in_rel -> next_entity_in_rel = punt_entity_in_rel -> next_entity_in_rel;
                    if(punt_entity_in_rel -> next_entity_in_rel != NULL){
                        punt_entity_in_rel -> next_entity_in_rel -> prec_entity_in_rel = punt_entity_in_rel -> prec_entity_in_rel;
                    }
                }
                free(punt_entity_in_rel);
                free(punt_entity_in_tree);
                return rel_head;
            }
        }
    }
    return rel_head;
}


void deleteTree(entity_in_tree_t *entityRoot);
void deleteTree(entity_in_tree_t *entityRoot){
    if((entityRoot -> sx_entity_in_tree == NULL) && (entityRoot -> dx_entity_in_tree == NULL)){
        free(entityRoot);
    }
    else{
        if(entityRoot -> sx_entity_in_tree != NULL){
            deleteTree(entityRoot -> sx_entity_in_tree);
        }
        if(entityRoot -> dx_entity_in_tree != NULL){
            deleteTree(entityRoot -> dx_entity_in_tree);
        }
        free(entityRoot);
    }
}


int findNewMax(entity_in_rel_t* entityInRelHead, int max);
int findNewMax(entity_in_rel_t* entityInRelHead, int max){
    entity_in_rel_t* puntEntityInRel = entityInRelHead;

    while(puntEntityInRel != NULL){
        if(puntEntityInRel -> num_rel > max){
            max = puntEntityInRel -> num_rel;
        }
        puntEntityInRel = puntEntityInRel -> next_entity_in_rel;
    }
    return max;
}


relazione_t* delent(relazione_t* rel_head, char* idDelete);
relazione_t* delent(relazione_t* rel_head, char* idDelete) {
    relazione_t *puntRelType = rel_head;
    relazione_t *supportForFreeRel = NULL;
    entity_in_rel_t *puntEntityInRel;
    entity_in_rel_t *supportForFreeEntity = NULL;
    entity_in_tree_t *puntEntityInTree;
    int confronta;

    confronta = strcmp(puntRelType->relazione, "vuota");
    if (confronta != 0) {
        while (puntRelType != NULL) {
            supportForFreeRel = NULL;
            //CASO UNICA RELAZIONE
            if ((puntRelType->rel_prec == NULL) && (puntRelType->next_rel == NULL)) {
                puntEntityInRel = puntRelType->first_entity_in_rel;
                confronta = strcmp(puntEntityInRel->entity_in_rel, idDelete);
                if (confronta == 0) {     //LA PRIMA ENTITY IN REL E` QUELLA DA ELIMINARE
                    if (puntEntityInRel->next_entity_in_rel == NULL) {
                        deleteTree(puntEntityInRel->first_entity_in_tree);
                        free(puntEntityInRel);
                        strcpy(puntRelType->relazione, "vuota");
                        puntRelType -> max_in_rel = 0;
                        puntRelType->first_entity_in_rel = NULL;
                        return rel_head;
                    } else {
                        deleteTree(puntEntityInRel->first_entity_in_tree);
                        puntRelType->first_entity_in_rel = puntEntityInRel->next_entity_in_rel;
                        if(puntRelType -> max_in_rel == puntEntityInRel -> num_rel){
                            puntRelType -> max_in_rel = findNewMax(puntRelType -> first_entity_in_rel, 0);
                        }
                        puntEntityInRel->next_entity_in_rel->prec_entity_in_rel = NULL;
                        free(puntEntityInRel);
                        puntEntityInRel = puntRelType->first_entity_in_rel;
                        while (puntEntityInRel != NULL) {
                            supportForFreeEntity = NULL;
                            confronta = strcmp(puntEntityInRel->entity_in_rel, idDelete);
                            if (confronta == 0) {
                                deleteTree(puntEntityInRel->first_entity_in_tree);
                                puntEntityInRel->prec_entity_in_rel->next_entity_in_rel = puntEntityInRel->next_entity_in_rel;
                                if (puntEntityInRel->next_entity_in_rel != NULL) {
                                    puntEntityInRel->next_entity_in_rel->prec_entity_in_rel = puntEntityInRel->prec_entity_in_rel;
                                }
                                puntRelType -> max_in_rel = findNewMax(puntRelType -> first_entity_in_rel, puntRelType -> first_entity_in_rel -> num_rel);
                            } else {
                                puntEntityInTree = findEntityInTree(puntEntityInRel->first_entity_in_tree, idDelete);
                                if (puntEntityInTree != NULL) {
                                    puntEntityInRel->first_entity_in_tree = delent_from_tree(puntEntityInRel->first_entity_in_tree, puntEntityInTree);
                                    if (puntEntityInRel->first_entity_in_tree == NULL) {
                                        if (puntEntityInRel->prec_entity_in_rel != NULL) {
                                            puntEntityInRel->prec_entity_in_rel->next_entity_in_rel = puntEntityInRel->next_entity_in_rel;
                                        } else {
                                            puntRelType->first_entity_in_rel = puntEntityInRel->next_entity_in_rel;
                                        }
                                        if (puntEntityInRel->next_entity_in_rel != NULL) {
                                            puntEntityInRel->next_entity_in_rel->prec_entity_in_rel = puntEntityInRel->prec_entity_in_rel;
                                        }
                                        supportForFreeEntity = puntEntityInRel;
                                        if(puntRelType -> max_in_rel == puntEntityInRel -> num_rel){
                                            puntRelType -> max_in_rel = findNewMax(puntRelType -> first_entity_in_rel, 0);
                                        }
                                    }
                                    else{
                                        puntEntityInRel -> num_rel = puntEntityInRel -> num_rel - 1;
                                        if(puntRelType -> max_in_rel == puntEntityInRel -> num_rel + 1){
                                            puntRelType -> max_in_rel = findNewMax(puntRelType -> first_entity_in_rel, puntEntityInRel -> num_rel);
                                        }
                                    }
                                }
                            }
                            puntEntityInRel = puntEntityInRel->next_entity_in_rel;
                            if (supportForFreeEntity != NULL) {
                                free(supportForFreeEntity);
                            }
                        }
                        if (puntRelType->first_entity_in_rel == NULL) {
                            strcpy(puntRelType->relazione, "vuota");
                            puntRelType -> max_in_rel = 0;
                        }
                        return rel_head;
                    }
                } else {
                    while (puntEntityInRel != NULL) {
                        supportForFreeEntity = NULL;
                        confronta = strcmp(puntEntityInRel->entity_in_rel, idDelete);
                        if (confronta == 0) {
                            deleteTree(puntEntityInRel->first_entity_in_tree);
                            if (puntEntityInRel->prec_entity_in_rel != NULL) {
                                puntEntityInRel->prec_entity_in_rel->next_entity_in_rel = puntEntityInRel->next_entity_in_rel;
                            } else {
                                puntRelType->first_entity_in_rel = puntEntityInRel->next_entity_in_rel;
                            }
                            if (puntEntityInRel->next_entity_in_rel != NULL) {
                                puntEntityInRel->next_entity_in_rel->prec_entity_in_rel = puntEntityInRel->prec_entity_in_rel;
                            }
                            supportForFreeEntity = puntEntityInRel;
                            if(puntRelType -> max_in_rel == puntEntityInRel -> num_rel){
                                puntRelType -> max_in_rel = findNewMax(puntRelType -> first_entity_in_rel, 0);
                            }
                        } else {
                            puntEntityInTree = findEntityInTree(puntEntityInRel->first_entity_in_tree, idDelete);
                            if (puntEntityInTree != NULL) {
                                puntEntityInRel->first_entity_in_tree = delent_from_tree(puntEntityInRel->first_entity_in_tree, puntEntityInTree);
                                if (puntEntityInRel->first_entity_in_tree == NULL) {
                                    if (puntEntityInRel->prec_entity_in_rel != NULL) {
                                        puntEntityInRel->prec_entity_in_rel->next_entity_in_rel = puntEntityInRel->next_entity_in_rel;
                                    } else {
                                        puntRelType->first_entity_in_rel = puntEntityInRel->next_entity_in_rel;
                                    }
                                    if (puntEntityInRel->next_entity_in_rel != NULL) {
                                        puntEntityInRel->next_entity_in_rel->prec_entity_in_rel = puntEntityInRel->prec_entity_in_rel;
                                    }
                                    supportForFreeEntity = puntEntityInRel;
                                    if(puntRelType -> max_in_rel == puntEntityInRel -> num_rel){
                                        puntRelType -> max_in_rel = findNewMax(puntRelType -> first_entity_in_rel, 0);
                                    }
                                }
                                else{
                                    puntEntityInRel -> num_rel = puntEntityInRel -> num_rel - 1;
                                    if(puntRelType -> max_in_rel == puntEntityInRel -> num_rel + 1){
                                        puntRelType -> max_in_rel = findNewMax(puntRelType -> first_entity_in_rel, puntEntityInRel -> num_rel);
                                    }
                                }
                            }
                        }
                        puntEntityInRel = puntEntityInRel->next_entity_in_rel;
                        if (supportForFreeEntity != NULL) {
                            free(supportForFreeEntity);
                        }
                    }
                    if (puntRelType->first_entity_in_rel == NULL) {
                        strcpy(puntRelType->relazione, "vuota");
                        puntRelType -> max_in_rel = 0;
                    }
                    return rel_head;
                }
            } else {
                puntEntityInRel = puntRelType->first_entity_in_rel;
                while (puntEntityInRel != NULL) {
                    supportForFreeEntity = NULL;
                    confronta = strcmp(puntEntityInRel->entity_in_rel, idDelete);
                    if (confronta == 0) {
                        deleteTree(puntEntityInRel->first_entity_in_tree);
                        if (puntEntityInRel->prec_entity_in_rel != NULL) {
                            puntEntityInRel->prec_entity_in_rel->next_entity_in_rel = puntEntityInRel->next_entity_in_rel;
                        } else {
                            puntRelType->first_entity_in_rel = puntEntityInRel->next_entity_in_rel;
                        }
                        if (puntEntityInRel->next_entity_in_rel != NULL) {
                            puntEntityInRel->next_entity_in_rel->prec_entity_in_rel = puntEntityInRel->prec_entity_in_rel;
                        }
                        supportForFreeEntity = puntEntityInRel;
                        if(puntRelType -> max_in_rel == puntEntityInRel -> num_rel){
                            puntRelType -> max_in_rel = findNewMax(puntRelType -> first_entity_in_rel, 0);
                        }
                    } else {
                        puntEntityInTree = findEntityInTree(puntEntityInRel->first_entity_in_tree, idDelete);
                        if (puntEntityInTree != NULL) {
                            puntEntityInRel->first_entity_in_tree = delent_from_tree(puntEntityInRel->first_entity_in_tree, puntEntityInTree);
                            if (puntEntityInRel->first_entity_in_tree == NULL) {
                                if (puntEntityInRel->prec_entity_in_rel != NULL) {
                                    puntEntityInRel->prec_entity_in_rel->next_entity_in_rel = puntEntityInRel->next_entity_in_rel;
                                } else {
                                    puntRelType->first_entity_in_rel = puntEntityInRel->next_entity_in_rel;
                                }
                                if (puntEntityInRel->next_entity_in_rel != NULL) {
                                    puntEntityInRel->next_entity_in_rel->prec_entity_in_rel = puntEntityInRel->prec_entity_in_rel;
                                }
                                supportForFreeEntity = puntEntityInRel;
                                if(puntRelType -> max_in_rel == puntEntityInRel -> num_rel){
                                    puntRelType -> max_in_rel = findNewMax(puntRelType -> first_entity_in_rel, 0);
                                }
                            }
                            else{
                                puntEntityInRel -> num_rel = puntEntityInRel -> num_rel - 1;
                                if(puntRelType -> max_in_rel == puntEntityInRel -> num_rel + 1){
                                    puntRelType -> max_in_rel = findNewMax(puntRelType -> first_entity_in_rel, puntEntityInRel -> num_rel);
                                }
                            }
                        }
                    }
                    puntEntityInRel = puntEntityInRel->next_entity_in_rel;
                    if (supportForFreeEntity != NULL) {
                        free(supportForFreeEntity);
                    }
                }
                if (puntRelType->first_entity_in_rel == NULL) {
                    if (puntRelType->rel_prec != NULL) {
                        puntRelType->rel_prec->next_rel = puntRelType->next_rel;
                    } else {
                        rel_head = puntRelType->next_rel;
                    }
                    if (puntRelType->next_rel != NULL) {
                        puntRelType->next_rel->rel_prec = puntRelType->rel_prec;
                    }
                    supportForFreeRel = puntRelType;
                }
                puntRelType = puntRelType->next_rel;
                if (supportForFreeRel != NULL) {
                    free(supportForFreeRel);
                }
            }
        }
    }
    return rel_head;
}

entity_t* delent_from_entity_tree(entity_t* entityRoot, char* idDelete);
entity_t* delent_from_entity_tree(entity_t* entityRoot, char* idDelete){
    entity_t* puntDelEntity;
    entity_t* entityToDelete;
    entity_t* entitySupport;

    puntDelEntity = find_entity(entityRoot, idDelete);
    if(puntDelEntity != NULL){

        if((puntDelEntity -> parent == NULL) && (puntDelEntity -> dx_entity == NULL) && (puntDelEntity -> sx_entity == NULL)){
            strcpy(puntDelEntity -> entity_name, "vuota");
            return puntDelEntity;
        }

        if((puntDelEntity -> sx_entity == NULL) || (puntDelEntity -> dx_entity == NULL)){
            entityToDelete = puntDelEntity;
        }
        else{
            entityToDelete = tree_ent_successor(puntDelEntity);
        }
        //entitySupport e` il figlio non NULL di entityToDelete (se esiste), NULL altrimenti
        if(entityToDelete -> sx_entity != NULL){
            entitySupport = entityToDelete -> sx_entity;
        }
        else{
            entitySupport = entityToDelete -> dx_entity;
        }
        if(entitySupport != NULL){
            entitySupport -> parent = entityToDelete -> parent;
        }
        if(entityToDelete -> parent == NULL){
            entityRoot = entitySupport;
        }
        else if(entityToDelete -> parent -> sx_entity == entityToDelete){
            entityToDelete -> parent -> sx_entity = entitySupport;
        }
        else{
            entityToDelete -> parent -> dx_entity = entitySupport;
        }
        if(entityToDelete != puntDelEntity){
            strcpy(puntDelEntity -> entity_name, entityToDelete -> entity_name);
        }
        /*CAMBIATO CON puntDelEntity*/
        free(entityToDelete);
        return entityRoot;
    }
    return entityRoot;
}


void report(relazione_t *rel_head);
void report(relazione_t *rel_head){
    relazione_t *punt_rel = rel_head;
    entity_in_rel_t *punt_entity_in_rel;
    int confronta;

    confronta = strcmp(punt_rel -> relazione, "vuota");
    if(confronta == 0){
        //printf("none\n");
        fputs("none\n", stdout);
    } else{
        while(punt_rel != NULL){
            //printf("%s ", punt_rel -> relazione);
            fputs(punt_rel -> relazione, stdout);
            fputs(" ", stdout);
            punt_entity_in_rel = punt_rel -> first_entity_in_rel;
            while (punt_entity_in_rel != NULL){
                if(punt_entity_in_rel -> num_rel == punt_rel -> max_in_rel){
                    //printf("%s ", punt_entity_in_rel -> entity_in_rel);
                    fputs(punt_entity_in_rel -> entity_in_rel, stdout);
                    fputs(" ", stdout);
                }
                punt_entity_in_rel = punt_entity_in_rel -> next_entity_in_rel;
            }
            printf("%d; ", punt_rel -> max_in_rel);
            punt_rel = punt_rel -> next_rel;
        }
        //printf("\n");
        fputs("\n", stdout);
    }
}


int main(){
    entity_t *entity_root;
    relazione_t* rel_head;
    char linea[150];
    char *id_rel;
    char *id_ent1;
    char *id_ent2;
    char *rel_type;

    entity_root = (entity_t*) malloc(sizeof(entity_t));
    strcpy(entity_root -> entity_name, "vuota");
    entity_root -> parent = NULL;
    entity_root -> sx_entity = NULL;
    entity_root -> dx_entity = NULL;

    rel_head = (relazione_t*) malloc(sizeof(relazione_t));
    strcpy(rel_head -> relazione, "vuota");
    rel_head -> max_in_rel = 0;
    rel_head -> first_entity_in_rel = NULL;
    rel_head -> rel_prec = NULL;
    rel_head -> next_rel = NULL;

    while (1){
        fgets(linea, 150, stdin);
        id_rel = strtok(linea, " \n");
        if(strcmp("addent", id_rel) == 0){
            id_ent1 = strtok(NULL, " \n");
            addent(entity_root, id_ent1);
        }
        else if(strcmp("addrel", id_rel) == 0){
            id_ent1 = strtok(NULL, " ");
            id_ent2 = strtok(NULL, " ");
            rel_type = strtok(NULL, " \n");
            rel_head = addrel(entity_root, id_ent1, id_ent2, rel_type, rel_head);
        }
        else if(strcmp("delrel", id_rel) == 0){
            id_ent1 = strtok(NULL, " ");
            id_ent2 = strtok(NULL, " ");
            rel_type = strtok(NULL, " \n");
            rel_head = delrel(entity_root, id_ent1, id_ent2, rel_type, rel_head);
        }
        else if(strcmp("delent", id_rel) == 0){
            id_ent1 = strtok(NULL, " \n");
            rel_head = delent(rel_head, id_ent1);
            entity_root = delent_from_entity_tree(entity_root, id_ent1);
        }
        else if(strcmp("report", id_rel) == 0){
            report(rel_head);
        }
        else{
            return 0;
        }
    }
}