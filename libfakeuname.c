/* RTLD_NEXT is not POSIX, indicate that we want GNU extensions */
#define _GNU_SOURCE

#include <dlfcn.h>
#include <errno.h>
#include <sys/utsname.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* The constructor will initialize this to the location of the original
 * implementation of uname
 */
int (*orig_uname)(struct utsname *name);

void inject_overrides(struct utsname *name)
{
	char *machine_override;
	machine_override = getenv("MACHINE_OVERRIDE");
	if (machine_override) {
		strncpy(name->machine, machine_override, sizeof(name->machine));
	}
}

int uname(struct utsname *name)
{
	int ret;
	ret = orig_uname(name);
	inject_overrides(name);
	return ret;
}

__attribute__((constructor))
void init(void)
{
	orig_uname = dlsym(RTLD_NEXT, "uname");
}
