// SPDX-License-Identifier: GPL-2.0
// /*
//  * Copyright (C) 2020 SyumpeiOkada + Ryuichi Ueda. All rights reserved.
// 


#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/io.h>

MODULE_AUTHOR("Syumpei Okada + Ryuichi Ueda");
MODULE_DESCRIPTION("driver for LED control");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.0.1");

static dev_t dev;
static struct cdev cdv;
static struct class *cls = NULL;
static volatile u32 *gpio_base = NULL;

static ssize_t led_write(struct file* filp, const char* buf, size_t count, loff_t* pos)
{
	 char c;
         if(copy_from_user(&c,buf,sizeof(char)))
         return -EFAULT;

      	 if (c == '0') {
           gpio_base[10] = 1 << 9;
	   gpio_base[10] = 1 << 19;
	 }

	 else if (c == '1') {
           gpio_base[7] = 1 << 9;
	   gpio_base[7] = 1 << 19;
	 }

	 else if (c == '2') {
	   gpio_base[10] = 1 << 9;
	   gpio_base[7] = 1 << 19;
	 }

	 else if (c == '3') {
       	   gpio_base[7] = 1 << 9;
	   gpio_base[10] = 1 << 19;
	 } 

         return 1;
}

static struct file_operations led_fops = {
	  .owner = THIS_MODULE,
          .write = led_write,
};

static int __init init_mod(void)
{
	  int retval;
          retval = alloc_chrdev_region(&dev, 0, 1, "myled");
	  if(retval < 0){
          printk(KERN_ERR "alloc_chrdev_region failed.\n");
          return retval;
          }
	  printk(KERN_INFO "%s is loaded. major:%d\n",__FILE__,MAJOR(dev));
          cdev_init(&cdv, &led_fops);
	  retval = cdev_add(&cdv, dev, 1);  
	  if(retval < 0){
	  printk(KERN_ERR "cdev_add failed. major:%d, minor:%d\n", MAJOR(dev),MINOR(dev));
          return retval;
          }

          cls = class_create(THIS_MODULE,"myled");
	  if(IS_ERR(cls)){
          printk(KERN_ERR "class_create failed.");
	  return PTR_ERR(cls);
	  }
	  device_create(cls, NULL, dev, NULL, "myled%d",MINOR(dev));

	  gpio_base = ioremap_nocache(0xfe200000, 0xA0);

	  const u32 led_green = 9;
	  const u32 index_green = led_green/10;
	  const u32 shift_green = (led_green%10)*3;
	  const u32 mask_green = ~(0x7 << shift_green);
	  gpio_base[index_green] = (gpio_base[index_green] & mask_green) | (0x1 << shift_green);

	  const u32 led_red = 19;
	  const u32 index_red = led_red/10;
          const u32 shift_red = (led_red%10)*3;
	  const u32 mask_red = ~(0x7 << shift_red);
	  gpio_base[index_red] = (gpio_base[index_red] & mask_red) | (0x1 << shift_red);

	  return 0;
}

static void __exit cleanup_mod(void)
{
	  cdev_del(&cdv);
          device_destroy(cls, dev);
	  class_destroy(cls);
	  unregister_chrdev_region(dev, 1);
	  printk(KERN_INFO "%s is unloaded. major:%d\n",__FILE__,MAJOR(dev));
	  iounmap(gpio_base);
}

module_init(init_mod);
module_exit(cleanup_mod);


