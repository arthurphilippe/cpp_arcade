/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Main
*/

#include <iostream>
#include <dlfcn.h>

int main()
{
	std::cout << "Hi :3" << std::endl;
	void* handle = dlopen("./games/DefaultGame/libDefaultGame.so", RTLD_LAZY);

	if (!handle) {
		std::cerr << "Cannot open library: " << dlerror() << std::endl;
		return 1;
	}

	typedef void (*entry_t)(void);
	dlerror();
	entry_t entry = (entry_t) dlsym(handle, "Entry");
	const char *dlsym_error = dlerror();
	if (dlsym_error) {
		std::cerr << "Cannot load symbol 'hello': " << dlsym_error <<
			'\n';
		dlclose(handle);
		return 1;
	}
	entry();
	dlclose(handle);
}
