#define ITEM_LOOP(x)\
    for(unsigned int i=0;i<soc_num_item;i++)\
        x;

typedef void (*soc_function_reference)();
typedef struct soc_str{
    	unsigned int id;
    	void *data;
    	soc_function_reference func;
} ITEM;


ITEM soc_item_list[256];
unsigned int soc_num_item;

void socAddItem(ITEM item){
	item.id=soc_num_item;
	soc_item_list[soc_num_item]=item;
	soc_num_item++;
}

void socDelItem(unsigned int id){
	ITEM_LOOP(soc_item_list[i]=soc_item_list[i+1]; soc_num_item--;);
}

void socUptItem(){
	ITEM_LOOP(soc_item_list[i].func());
}
