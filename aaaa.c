#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Misha Farber Brodsky");
MODULE_DESCRIPTION("AAAAAAAA");

#define DEV_NAME "aaaa"
static char AAAAAAAA[2048];
static int major;
static struct class *cls;

static int device_open(struct inode *inode, struct file *file) {
    try_module_get(THIS_MODULE);
    return 0;
}

static int device_release(struct inode * inode, struct file *file) {
    module_put(THIS_MODULE);
    return 0;
}

static ssize_t device_read(struct file *file, char __user *buff, size_t length, loff_t *offset) {
    if (length > sizeof(AAAAAAAA)) length = sizeof(AAAAAAAA);
    if (copy_to_user(buff, AAAAAAAA, length))
        return -EFAULT;
    return length;
}

static ssize_t device_write(struct file *file, const char __user *buff, size_t length, loff_t *offset) {
    return -EINVAL;
}

static struct file_operations chardev_fops = {
    .read = device_read,
    .write = device_write,
    .open = device_open,
    .release = device_release
};

int __init init_module(void) {
    memset(AAAAAAAA, 0x41, sizeof(AAAAAAAA));
    major = register_chrdev(0, DEV_NAME, &chardev_fops);
    cls = class_create(THIS_MODULE, DEV_NAME);
    device_create(cls, NULL, MKDEV(major, 0), NULL, DEV_NAME);
    pr_alert("AAAAAAAA!!!\n");
    return 0;
}

void __exit cleanup_module(void) {
    device_destroy(cls, MKDEV(major, 0));
    class_destroy(cls);
    unregister_chrdev(major, "aaaa");
    pr_alert("AAAAAAAA :(\n");
}
