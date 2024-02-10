/*
 * file to create the major and minor number for device drivers by dynamic methods
 * And also we create Automatic Device Drive include in this program 
 * */
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>

#include <linux/types.h>
#include <linux/uaccess.h>//this have copy_from_user functions

//this are header file used for automatic device file creation 
#include<linux/kdev_t.h>
#include<linux/device.h>
#include<linux/cdev.h>


//creating the dev with our custom major and minor number
dev_t dev = 0;

//struct class
static struct class *dev_class;

//creating cdev 
static struct cdev SK_cdev;

/*
** Function Prototypes
*/
static int      __init SKD_driver_init(void);
static void     __exit SKD_driver_exit(void);
static int      SK_open(struct inode *inode, struct file *file);
static int      SK_release(struct inode *inode, struct file *file);
static ssize_t  SK_read(struct file *filp, char __user *buf, size_t len,loff_t * off);
static ssize_t  SK_write(struct file *filp, const char *buf, size_t len, loff_t * off);

//file operations struct 
static struct file_operations fops =
{
    .owner      = THIS_MODULE,
    .read       = SK_read,
    .write      = SK_write,
    .open       = SK_open,
    .release    = SK_release,
};

//Device_file memory
static char kbuf[100];


/*
** This function will be called when we open the Device file
*/
static int SK_open(struct inode *inode, struct file *file)
{
        pr_info("Driver Open Function Called...!!!\n");
        return 0;
}

/*
** This function will be called when we close the Device file
*/
static int SK_release(struct inode *inode, struct file *file)
{
        pr_info("Driver Release Function Called...!!!\n");
        return 0;
}

/*
** This function will be called when we write the Device file
*/
static ssize_t SK_write(struct file *filp, const char __user *buf, size_t len, loff_t *off)
{
        pr_info("Driver Write Function Called...!!!\n");
	 printk("Write Process invoked..\n");

        //copy data from user side .....
        if(len>100)
                {
                        printk(KERN_INFO"length of user data more than kernal buffer\n");
                        return -EFAULT;
                }
        else
        {
                if(copy_from_user(kbuf,buf,sizeof(buf)+1)!=0)
                {
                        printk("User_from_copy funtion is failed...\n");
                        return -EFAULT;
                }
                else
                {
                        printk("user space data copyed : %s\n",kbuf);

                }
	}

        return len;
}

/*
** This function will be called when we read the Device file
*/
static ssize_t SK_read(struct file *filp, char __user *buf, size_t len, loff_t *off)
{
        pr_info("Driver Read Function Called...!!!\n");
        printk("Read Process invoked..\n");
        if(copy_to_user(buf,kbuf,sizeof(kbuf)))
                {
                        printk("kernal to user copy funtion is failed...\n");
                        return -EFAULT;
                }
                else
                {
                        printk("Kernal to user data copy  successfully....\n");

                        printk("kernal space data copyed : %s\n",kbuf);

                }

        return 0;
}


/*
 * module init function
 */
static int __init SKD_driver_init(void)
{
	//Allocating Major number
	
	if((alloc_chrdev_region(&dev,0,1,"SJR_solution_dev"))<0)
	{
		printk("Cannot allocate major number for device \n");
		return -1;
	}
	printk("Major =%d Minor =%d\n",MAJOR(dev), MINOR(dev));
	
	/*Creating cdev structure*/
        cdev_init(&SK_cdev,&fops);

        /*Adding character device to the system*/
        if((cdev_add(&SK_cdev,dev,1)) < 0)
	{
            pr_err("Cannot add the device to the system\n");
            goto r_class;
        }
	// creating struct class
	
	if((dev_class = class_create("SKRJS_class")) == NULL)
	{
		pr_err("Cannot create the struct class for device\n");
		goto r_class;
	}

	//creating device 
	if((device_create(dev_class,NULL,dev,NULL,"SKRJS_devices")) == NULL)
	{
		pr_err("Cannot create the device file\n");
		goto r_device;
	}
	printk("Kernal Module Inserted Successfully...\n");
	return 0;

r_class:
  	class_destroy(dev_class);
r_device:
        unregister_chrdev_region(dev,1);
	return -1;
}


/*
 * module exit funtion
 */
static void __exit SKD_driver_exit(void)
{
	device_destroy(dev_class,dev);
	class_destroy(dev_class);
	unregister_chrdev_region(dev,1);
	cdev_del(&SK_cdev);
	printk("Kernal Module removed successfully...\n");
}
module_init(SKD_driver_init);
module_exit(SKD_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SARBUDEEN KATHER <sarbudeenkather007@gmail.com>");
MODULE_DESCRIPTION("simple linux drive (dynamically alloction the major nd minor number and aslo create automatic devices file.");
MODULE_VERSION("1.5");

