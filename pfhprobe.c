
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kprobes.h>

#define MAX_SYMBOL_LEN 64
static char symbol[MAX_SYMBOL_LEN] = "__handle_mm_fault";
module_param_string(symbol, symbol, sizeof(symbol), 0644);

static int u_pid = 0;
module_param(u_pid, int, S_IRUGO);

static struct kprobe kp = {
	.symbol_name = symbol,
};

static int handler_pre(struct kprobe *p, struct pt_regs *regs)
{

#ifdef CONFIG_X86
	if (current->pid == u_pid)
	{
		pr_info("<%s> pre_handler: FaultAddress = %lu, Pid = %d",
				p->symbol_name, regs->si, u_pid);
	}

#endif

	return 0;
}

/* kprobe post_handler: called after the probed instruction is executed */
/*
static void handler_post(struct kprobe *p, struct pt_regs *regs,
						 unsigned long flags)
{
#ifdef CONFIG_X86
	pr_info("<%s> post_handler: p->addr = 0x%p, flags = 0x%lx\n",
			p->symbol_name, p->addr, regs->flags);
#endif
}*/

/*
 * fault_handler: this is called if an exception is generated for any
 * instruction within the pre- or post-handler, or when Kprobes
 * single-steps the probed instruction.
 */
/*
static int handler_fault(struct kprobe *p, struct pt_regs *regs, int trapnr)
{
	pr_info("fault_handler: p->addr = 0x%p, trap #%dn", p->addr, trapnr);
	 Return 0 because we don't handle the fault. 
	return 0;
}
*/

static int __init kprobe_init(void)
{
	int ret;
	kp.pre_handler = handler_pre;
	kp.post_handler = NULL;	 //handler_post;
	kp.fault_handler = NULL; //handler_fault;

	ret = register_kprobe(&kp);
	if (ret < 0)
	{
		pr_err("register_kprobe failed, returned %d\n", ret);
		return ret;
	}
	pr_info("Planted kprobe at %p\n", kp.addr);
	return 0;
}

static void __exit kprobe_exit(void)
{
	unregister_kprobe(&kp);
	pr_info("kprobe at %p unregistered\n", kp.addr);
}

module_init(kprobe_init)
	module_exit(kprobe_exit)
		MODULE_LICENSE("GPL");
