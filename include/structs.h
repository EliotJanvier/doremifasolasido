#ifndef STRUCTS_H_
#define STRUCTS_H_

typedef struct variable variable_t;
struct variable {
    int type;
    char *name;
    void *ptr;
    long adress;
};

typedef struct block_info {
    int depth;
    int execute;
} block_info_t;

#endif


