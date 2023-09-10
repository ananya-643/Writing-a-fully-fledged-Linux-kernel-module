#include <linux/init_task.h> 
#include <linux/kernel.h> 
#include <linux/module.h> 
#include <linux/sched.h> 

void dfs(struct task_struct *task) 
{ 
	struct task_struct *task_next; 
	struct list_head *list; 
	list_for_each(list, &task->children) 
	{ 
		task_next = list_entry(list, struct task_struct, sibling); 
		printk(KERN_INFO "pid: %d | pname: %s \n", task_next->pid, task_next->comm); 
		dfs(task_next); 
	} 
} 

int list_tasks(void) 
{ 
	printk(KERN_INFO "Loading module...\n"); 
	printk(KERN_INFO "pid: %d | pname: %s \n", init_task.pid, init_task.comm); 
	dfs(&init_task); 
	printk(KERN_INFO "Module loaded.\n"); 
	return 0; 
} 

void exit_final(void) 
{ 
	printk(KERN_INFO "Module removed.\n"); 
} 

module_init(list_tasks); 
module_exit(exit_final); 
MODULE_LICENSE("GPL"); 
MODULE_DESCRIPTION("Listing tasks");