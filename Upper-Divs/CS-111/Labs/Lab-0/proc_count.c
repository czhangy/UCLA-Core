#include <linux/module.h>
#include <linux/printk.h>

static int __init proc_count_init(void)
{
	pr_info("proc_count: init\n");
	return 0;
}

static void __exit proc_count_exit(void)
{
	pr_info("proc_count: exit\n");
}

module_init(proc_count_init);
module_exit(proc_count_exit);

MODULE_AUTHOR("Charles Zhang");
MODULE_DESCRIPTION("Module that shows the current number of processes running");
MODULE_LICENSE("GPL");
