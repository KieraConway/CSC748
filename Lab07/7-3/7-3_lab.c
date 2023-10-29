#include <linux/types.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/tty.h>

#define DEVFILE		"lab73_login"

#define LAB73WIN_ID	1032

#define CMD_LOGIN	100
#define CMD_LOGOUT	200

#define USERID_GUEST	9999
#define PASSWD_GUEST	123456
#define USERID_ADMIN	1337
#define PASSWD_ADMIN	[!!!REDACTED!!!]

#define NUM_ACCOUNTS 2

struct login_creds {
	long int userid;
	long int passwd;
};

struct login_creds accounts[NUM_ACCOUNTS] = {
	{ USERID_GUEST, PASSWD_GUEST },
	{ USERID_ADMIN, PASSWD_ADMIN },
};

bool is_valid_account(struct login_creds *lc) {

	int i;
	struct login_creds tmp;

	copy_from_user(&tmp, lc, sizeof(struct login_creds));

	for (i=0; i<NUM_ACCOUNTS; i++) {

		if (tmp.userid == accounts[i].userid && tmp.passwd == accounts[i].passwd)
			return true;

	}

	return false;

}

void login(struct login_creds *lc) {

	struct login_creds tmp;
	struct cred *new;

	// confirm that this is a valid set of credentials
	if (!is_valid_account(lc)) {
		pr_info("Invalid account");
		return;
	}

	copy_from_user(&tmp, lc, sizeof(struct login_creds));

	// become that user
	switch (tmp.userid) {

	case USERID_GUEST:
		pr_info("You are already running as guest, silly :)");
		break;

	case USERID_ADMIN:
		new = prepare_creds();
		new->egid = KGIDT_INIT(LAB73WIN_ID);
		commit_creds(new);
		break;

	default:
		pr_info("Unknown user id");

	}

}

static long handle_ioctl(struct file *fp, unsigned int cmd, unsigned long args) {

	switch (cmd) {

	case CMD_LOGIN:
		login((struct login_creds *)args);
		break;

	default:
		// invalid command
		break;

	}

	return 0;

}

static const struct file_operations login_fops = {
    .owner          = THIS_MODULE,
    .unlocked_ioctl = handle_ioctl,
};

static struct miscdevice login_device = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = DEVFILE,
    .fops = &login_fops,
	.mode = 0666,
};

static int __init login_init(void) {

	pr_info("login.ko loaded");

	if (misc_register(&login_device) != 0) {
		pr_err("failed to create /dev/%s", DEVFILE);
	}

	return 0;

}

static void __exit login_exit(void) {

    misc_deregister(&login_device);

}

module_init(login_init);
module_exit(login_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CSC748");

