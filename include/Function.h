#pragma once
#include <functional>
//抽象基类：统一接口
class FunctionBase{
public:
	virtual ~FunctionBase() {}
	virtual int operator()() = 0;
};
template<typename _Function_,typename ...Args>
class Function
	:public FunctionBase
{
public:
	Function(_Function_ func)
		:m_func(std::bind(std::forward<_Function_>(func),std::forward<Args>(args)...)){}
	
	~Function(){}

	int operator()() override{
		return m_func();
	}

private:
	std::function<int()> m_func;
};

