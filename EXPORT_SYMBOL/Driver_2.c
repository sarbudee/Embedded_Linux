/***************************************************************************//**
*  File Name: driver_2.c
*
*  file to create the major and minor number for device drivers by dynamic methods
*  we create Automatic Device Drive include in this program 
*  
*  Here we use EXPORT_SYMBOL();
*  to export the function and variable ,From Drivers_1 to Driver_2 calling thougth extern;
*
*  
*******************************************************************************/
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/err.h>
dev_t dev = 0;
static struct class *dev_class;
static struct cdev SK_cdev;
 
static int __init SK_driver_init(void);
static void __exit SK_driver_exit(void);

/*************** Driver Functions **********************/
static int SK_open(struct inode *inode, struct file *file);
static int SK_release(struct inode *inode, struct file *file);
static ssize_t SK_read(struct file *filp, char __user *buf, size_t len,loff_t * off);
static ssize_t SK_write(struct file *filp, const char *buf, size_t len, loff_t * off);
 
extern int E_count;
void E_function(void); //Function declaration is by defalut extern
 
//File operation structure
static struct file_operations fops =
{
        .owner          = THIS_MODULE,
        .read           = SK_read,
        .write          = SK_write,
        .open           = SK_open,
        .release        = SK_release,
};

/*
** This function will be called when we open the Device file
*/ 
static int SK_open(struct inode *inode, struct file *file)
{
        pr_info("Device File Opened...!!!\n");
        return 0;
}
 
/*
** This function will be called when we close the Device file
*/ 
static int SK_release(struct inode *inode, struct file *file)
{
        pr_info("Device File Closed...!!!\n");
        return 0;
}
 
/*
** This function will be called when we read the Device file
*/
static ssize_t SK_read(struct file *filp,char __user *buf, size_t len, loff_t *off)
{
        return 0;
}

/*
** This function will be called when we write the Device file
*/
static ssize_t SK_write(struct file *filp,const char __user *buf, size_t len, loff_t *off)
{
        pr_info("Data Write : Done!\n");
        return len;
}

/*
** Module Init function
*/
static int __init SK_driver_init(void)
{
        /*Allocating Major number*/
        if((alloc_chrdev_region(&dev, 0, 1, "SK_Dev2")) <0){
                pr_err("Cannot allocate major number\n");
                return -1;
        }
        pr_info("Driver_2 Major = %d Minor = %d \n",MAJOR(dev), MINOR(dev));
 
        /*Creating cdev structure*/
        cdev_init(&SK_cdev,&fops);
 
        /*Adding character device to the system*/
        if((cdev_add(&SK_cdev,dev,1)) < 0){
            pr_err("Cannot add the device to the system\n");
            goto r_class;
        }
 
        /*Creating struct class*/
        if(IS_ERR(dev_class = class_create("SK_class2"))){
            pr_err("Cannot create the struct class\n");
            goto r_class;
        }
 
        /*Creating device*/
        if(IS_ERR(device_create(dev_class,NULL,dev,NULL,"SK_device2"))){
            pr_err("Cannot create the Device 1\n");
            goto r_device;
        }
        pr_info("Device Driver 2 Insert...Done!!!\n");
	 E_function();
        pr_info("%d time(s) shared function called!\n", E_count);
        pr_info("Data Read : Done!\n");

        return 0;
 
r_device:
        class_destroy(dev_class);
	r_class:
        unregister_chrdev_region(dev,1);
        return -1;
}

/*
** Module exit function
*/ 
static void __exit SK_driver_exit(void)
{
        device_destroy(dev_class,dev);
        class_destroy(dev_class);
        cdev_del(&SK_cdev);
        unregister_chrdev_region(dev, 1);
        pr_info("Device Driver 2 Remove...Done!!!\n");
}
 
module_init(SK_driver_init);
module_exit(SK_driver_exit);
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sarbudeen Kather S <sarbudeenkather007@gmail.com>");
MODULE_DESCRIPTION("Using EXPORT_SYMBOL extern Driver - 2");
MODULE_VERSION("1.26");
