/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Main
*/

#include <iostream>
#include <dlfcn.h>
#include <functional>
#include <memory>
#include "IGame.hpp"

void toto(int tata)
{
	std::cout << "I am toto " << tata << std::endl;
}

int main()
{
	std::cout << "Hi :3" << std::endl;
	void *handle = dlopen("./games/DefaultGame/libDefaultGame.so", RTLD_LAZY);

	if (!handle) {
		std::cerr << "Cannot open library: " << dlerror() << std::endl;
		return 1;
	}

	using entry_t = arc::IGame *(*)();
	dlerror();
	entry_t entry = (entry_t) dlsym(handle, "GameConstruct");
	const char *dlsym_error = dlerror();
	if (dlsym_error || !entry) {
		std::cerr << "Cannot load symbol: " << dlsym_error << '\n';
		dlclose(handle);
		return 2;
	}
	auto test = entry();
	test->dump();
	dlclose(handle);
}
