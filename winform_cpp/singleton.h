#pragma once

#include <cassert>

//�������ʷ�ʽ�ӿڣ����������������Ҫ�Լ�����
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