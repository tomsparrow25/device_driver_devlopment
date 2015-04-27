#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <asm-generic/uaccess.h>

static char msg[128];
static int len = 0;
static int len_check = 1;
int simple_proc_open(struct inode * sp_inode, struct file *sp_file)
{
	printk(KERN_INFO "proc called open\n");
	return 0;
}
int simple_proc_release(struct inode *sp_indoe, struct file *sp_file)
{
	printk(KERN_INFO "proc called release\n");
	return 0;
}
size_t simple_proc_read(struct file *filp, char __user *buf, size_t count,loff_t *f_pos )
{

	if (len_check)
		len_check = 0;
	else 
	{
		len_check = 1;
		return 0;
	}
	printk(KERN_INFO "proc called read %zx\n",count);
	copy_to_user(buf,msg,len);
	return len;
}
ssize_t simple_proc_write(struct file *filp, const char __user *buf, size_t count,loff_t *f_pos)
{

	printk(KERN_INFO "proc called write %zx\n",count);
	len = count;
	copy_from_user(msg,buf,len);
	return len;
}

struct file_operations fops = 
{
	.open = simple_proc_open,
	.read = simple_proc_read,
	.write = simple_proc_write,
	.release = simple_proc_release
};
static int __init init_simpleproc (void)
{
	printk(KERN_INFO "init simple proc\n");
	if (! proc_create("simpleproc",0666,NULL,&fops)) 
	{
		printk(KERN_INFO "ERROR! proc_create\n");
		remove_proc_entry("simpleproc1",NULL);
		return -1;
	}
	return 0;
}
static void __exit exit_simpleproc(void)
{
	remove_proc_entry("simpleproc1",NULL);
	printk(KERN_INFO "exit simple proc\n");
}

module_init(init_simpleproc);
module_exit(exit_simpleproc);
MODULE_AUTHOR("Dharmender Sharma");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A simple module to input/output using proc filesystem");
