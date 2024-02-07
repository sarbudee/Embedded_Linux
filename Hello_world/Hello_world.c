/*Header file */
#include<linux/init.h>// module_init & module_exit
#include<linux/module.h>//MODULE_LICENSE,MODULE_AUTHOUR,MODULE_DESCRIPTION
#include<linux/kernel.h>

/*init function*/

int hello_init(void){

	printk("hello kernel space!!!\n");
	return 0;
}

/*exit function*/
void hello_exit(void){
	printk("Bye kernel space\n");
}

/*kernel special macros*/
module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("sarbudeen kather");
MODULE_DESCRIPTION("Our first kernel module");
