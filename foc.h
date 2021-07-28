#ifndef __cplusplus

#define ITEMS_PROC(x)\
    for(unsigned int i=0;i<num_item+1;i++)\
        item_list[i].x;

typedef void (*function_reference)();
typedef struct _str{
    unsigned int id;
    void *data;
    function_reference func;
} ITEM;


ITEM item_list[];
unsigned int num_item;

void add_item(ITEM item){
    item.id=num_item;
    item_list[num_item]=item;
    num_item++;
}

void del_item(unsigned int id){
    for(unsigned int i=id;i<num_item-1;i++)
        item_list[i]=item_list[i+1];
    num_item--;
}

#endif
