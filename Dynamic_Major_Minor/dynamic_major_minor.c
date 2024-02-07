/*
 * file to create the major and minor number for device drivers by dynamic methods
 * */
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>

//creating the dev with our custom major and minor number
dev_t dev = 0;
/*
 * module init function
 */
static int __init hello_world_init(void)
{
	if((alloc_chrdev_region(&dev,0,1,"SJR_solution_dev"))<0)
	{
		printk("Cannot allocate major number for device \n");
		return 1;
	}
	printk("Major =%d Minor =%d\n",MAJOR(dev), MINOR(dev));
	printk("Kernal Module Inserted Successfully...\n");
	return 0;
}
/*
 * module exit funtion
 */
static void __exit hello_world_exit(void)
{
	unregister_chrdev_region(dev,1);
	printk("Kernal Module removed successfully...\n");
}
module_init(hello_world_init);
module_exit(hello_world_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SARBUDEEN KATHER <sarbudeenkather007@gmail.com>");
MODULE_DESCRIPTION("simple linux drive (dynamically alloction the major nd minor number");
MODULE_VERSION("1.0");

