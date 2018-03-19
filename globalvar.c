#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
MODULE_LICENSE("GPL");

#define MAJOR_NUM 257 //主设备号

static ssize_t globalvar_read(struct file *, char *, size_t, loff_t*);
static ssize_t globalvar_write(struct file *, const char *, size_t, loff_t*);

//初始化字符设备驱动的file_operations结构体
struct file_operations globalvar_fops =
{
  read: globalvar_read, write: globalvar_write,
};
static int global_var = 0; //"globalvar"设备的全局变量

static int __init globalvar_init(void)
{
  int ret;

  //注册设备驱动
  ret = register_chrdev(MAJOR_NUM, "globalvar", &globalvar_fops);
  if (ret)
  {
    printk("globalvar register failure");
  }
  else
  {
    printk("globalvar register success");
  }
  return ret;
}

static void __exit globalvar_exit(void)
{
  int ret;

  //注销设备驱动
  //ret = unregister_chrdev(MAJOR_NUM, "globalvar");
  unregister_chrdev(MAJOR_NUM, "globalvar");
  if (ret)
  {
    printk("globalvar unregister failure");
  }
  else
  {
    printk("globalvar unregister success");
  }
}

static ssize_t globalvar_read(struct file *filp, char *buf, size_t len, loff_t *off)
{
  //将global_var从内核空间复制到用户空间
  if (copy_to_user(buf, &global_var, sizeof(int)))
  {
    return - EFAULT;
  }
  return sizeof(int);
}

static ssize_t globalvar_write(struct file *filp, const char *buf, size_t len, loff_t *off)
{
  //将用户空间的数据复制到内核空间的global_var
  if (copy_from_user(&global_var, buf, sizeof(int)))
  {
    return - EFAULT;
  }
  return sizeof(int);
}

module_init(globalvar_init);
module_exit(globalvar_exit)
