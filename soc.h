#define SOC_ITEM_LOOP(X)\
    	for(unsigned int i=0;i<soc_num_item;i++)\
        	X;

#define SOC_DATA_LOOP(DATABASE,X)\
	for(unsigned int j=0;j<sizeof(DATABASE)/sizeof(DATABASE[0]);j++)\
		X;

typedef struct soc_str{
    	unsigned int id;
    	void (*func)(int id);
	void *data[65536];
} SOC_ITEM;


SOC_ITEM soc_item_list[256];
unsigned int soc_num_item;

void socAddItem(SOC_ITEM item){
	item.id=soc_num_item;
	soc_item_list[soc_num_item]=item;
	soc_num_item++;
}

void socDelItem(unsigned int id){
	SOC_ITEM_LOOP(soc_item_list[i]=soc_item_list[i+1]; soc_num_item--;);
}

void socUptItem(){
	SOC_ITEM_LOOP(soc_item_list[i].func(soc_item_list[i].id));
}
