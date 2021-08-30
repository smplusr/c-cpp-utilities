#include<stdio.h>
#include"soc.h"


void *buff[65536]={(void*)20,(void*)10,"aaa"}; 				// Example data

void item_func(){
	SOC_CHECKED_LOOP("object",					// Scanning items (selecting only type 'object')
		SOC_DATA_LOOP(soc_item_list[i].data,			// Looping through data of items 'object'
			if(soc_item_list[i].data[j]==(void*)10)		// Testing if scanned and loop-ed item-s has raw void data pointer of reference (binaru content) '10'
			printf("%s\n","true");				// If last statment correct, printing true
		)
	)
	
}

int main(){

	SOC_ITEM item_instance; 					// Instantiation of object
	item_instance.type="object";					// Type attribution
	item_instance.func=item_func;
	SOC_DATA_LOOP(item_instance.data,item_instance.data[j]=buff[j])	// Setting up data from void array 'dat'
	*item_instance.data=*buff;					// Other way using pointers

	socAddItem(item_instance);					// Adding item to object array	
	socUptItem();							// Updating items (calling their function)
	socDelItem(0);							// Deleting first item of object array
}
