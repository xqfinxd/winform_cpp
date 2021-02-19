#pragma once

#include <cassert>

//单例访问方式接口，对象的生命周期需要自己控制
template <typename T>
class Singleton {
public:
	static T* GetSingleton() {
		assert(_instance);
		return _instance;
	}
protected:
	static T* _instance;
	Singleton() {
		assert(!_instance);
		_instance = static_cast<T*>(this);
	}
	~Singleton() {
		assert(_instance);
		_instance = nullptr;
	}
};

#define INIT_SINGLETON(T) T* Singleton<T>::_instance = nullptr