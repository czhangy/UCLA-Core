#include <linux/module.h>
#include <linux/printk.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

// Global variable
static struct proc_dir_entry *ent;

// Command that gets run when cat is used
static int proc_count_show(struct seq_file *m, void *v)
{
	// Build list of processes?
	struct task_struct *p;
	int count = 0;
	// For each running process
	for_each_process(p)
	{
		count++;
	}
	// Place final count into /proc/count
	seq_printf(m, "%d\n", count);
	return 0;
}

// Create /proc/count
static int __init proc_count_init(void)
{
	pr_info("proc_count: init\n");
	ent = proc_create_single("count", 0, NULL, proc_count_show);
	return 0;
}

// Clean up
static void __exit proc_count_exit(void)
{
	pr_info("proc_count: exit\n");
	proc_remove(ent);
}

// isnmod and rmmod
module_init(proc_count_init);
module_exit(proc_count_exit);

// Lol idk
MODULE_AUTHOR("Charles Zhang");
MODULE_DESCRIPTION("Module that shows the current number of processes running");
MODULE_LICENSE("GPL");
