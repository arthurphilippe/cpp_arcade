/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** SymLoad
*/

#ifndef SYMLOAD_HPP_
	#define SYMLOAD_HPP_

	#include <string>

namespace arc {
	template <class T>
	class DynamicFunc {
	public:
		DynamicFunc(const std::string &dl,
				const std::string &sym = "Construct")
		{
			_handle = dlopen(dl.c_str(), RTLD_LAZY);
			if (!_handle)
				throw std::exception();
			dlerror();
			call = (T) dlsym(_handle, sym.c_str());
			const char *dlsym_error(dlerror());
			if (dlsym_error)
				throw std::exception();
		}
		~DynamicFunc()
		{
			dlclose(_handle);
		}
		T &get() noexcept
		{
			return call;
		}
		T	call;
	private:
		void	*_handle;
	};
}


#endif /* !SYMLOAD_HPP_ */
