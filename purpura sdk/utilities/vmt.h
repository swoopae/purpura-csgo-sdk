#pragma once

#include <Windows.h>
#include <stdio.h>
#include <map>
#include <memory>

class vmt
{
private:
	std::unique_ptr<std::uintptr_t[]> p_newvmt     = nullptr;
	std::uintptr_t**                  p_baseclass  = nullptr; 
	std::uintptr_t*                   p_ogvmt      = nullptr;
	std::size_t                       index_count  = 0;
public:
	vmt(void* ppClass)
	{
		this->p_baseclass = static_cast<std::uintptr_t**>(ppClass);

		while (static_cast<std::uintptr_t*>(*this->p_baseclass)[this->index_count])
			++this->index_count;

		const std::size_t kSizeTable = this->index_count * sizeof(std::uintptr_t);

		this->p_ogvmt = *this->p_baseclass;
		this->p_newvmt = std::make_unique<std::uintptr_t[]>(this->index_count);

		std::memcpy(this->p_newvmt.get(), this->p_ogvmt, kSizeTable);

		*this->p_baseclass = this->p_newvmt.get();
	};
	~vmt() { *this->p_baseclass = this->p_ogvmt; };

	template<class T>
	T get_original(const std::size_t index)
	{
		return reinterpret_cast<T>(this->p_ogvmt[index]);
	};

	HRESULT hook(const std::size_t index, void* fnNew)
	{
		if (index > this->index_count)
			return E_INVALIDARG;

		this->p_newvmt[index] = reinterpret_cast<std::uintptr_t>(fnNew);
		return S_OK;
	};

	HRESULT unhook(const std::size_t index)
	{
		if (index > this->index_count)
			return E_INVALIDARG;

		this->p_newvmt[index] = this->p_ogvmt[index];
		return S_OK;
	};
};