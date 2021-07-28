#ifndef __cplusplus

#define ITEM_LOOP(x)\
    for(unsigned int i=0;i<num_item;i++)\
        x;

typedef void (*function_reference)();
typedef struct _str{
    	unsigned int id;
    	void *data;
    	function_reference func;
} ITEM;


ITEM item_list[256];
unsigned int num_item;

void add_item(ITEM item){
	item.id=num_item;
	item_list[num_item]=item;
	num_item++;
}

void del_item(unsigned int id){
	ITEM_LOOP(item_list[i]=item_list[i+1]; num_item--;);
}

void upt_item(){
	ITEM_LOOP(item_list[i].func());
}

#endif
