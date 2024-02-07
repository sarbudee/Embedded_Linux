/*
 * file to create the major and minor number for device drivers by static methods
 * */
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>

//creating the dev with our custom major and minor number
dev_t dev = MKDEV(262,0);
/*
 * module init function
 */
static int __init hello_world_init(void)
{
	register_chrdev_region(dev,1,"SJR_solution_dev");
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
MODULE_DESCRIPTION("simple linux drive (staically alloction the major nd minor number");
MODULE_VERSION("1.0");

