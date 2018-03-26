/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** DynamicLoad
*/

#ifndef DYNAMICOBJ_HPP_
	#define DYNAMICOBJ_HPP_

	#include <string>
	#include <stdexcept>
	#include <dlfcn.h>

namespace arc {
	template <class T>
	class DynamicObject {
	public:
		DynamicObject(const std::string &dl,
				const std::string &sym = "Construct")
		{
			_init(dl, sym);
		}
		~DynamicObject()
		{
			dlclose(_handle);
		}
		T *get() noexcept
		{
			return call();
		}
		T *reset(const std::string &dl,
				const std::string &sym = "Construct")
		{
			dlclose(_handle);
			_handle = nullptr;
			_init(dl, sym);
			return call();
		}
	private:
		T	*(*call)();
		void	*_handle;

		void _init(const std::string &dl, const std::string &sym)
		{
			if (dl.length() == 0)
				throw std::runtime_error("No lib available");
			_handle = dlopen(dl.c_str(), RTLD_LAZY);
			if (!_handle)
				throw std::runtime_error(dlerror());
			dlerror();
			call = (T *(*)()) dlsym(_handle, sym.c_str());
			const char *dlsym_error(dlerror());
			if (dlsym_error)
				throw std::runtime_error(dlsym_error);
		}
	};
}

#endif /* !DYNAMICOBJ_HPP_ */
