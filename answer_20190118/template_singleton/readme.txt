//模板单例类--实现传参--实现永远只创建指定类的同一个对象
template<class T>
static T * _pInstance; //静态T类指针
构造函数+析构函数私有化;
template <class T>
T* Singleton<T>::_pInstance = nullptr;//静态T类指针全局初始化

//static getInstance需要可变参数控制T类初始化
template<class...Args>
static T* getInstance(Args...args)
{
	if(nullptr == pInstance)
	{
		_pInstance = new T(args...);//实现传参
	}
	return pInstance;
}
//自动释放---嵌套类
class AutoRelease
{
public:
	AutoRelease() {};
	~AutoRelease()
	{
		if(_pInstance)
			delete _pInstance;
	}
}

并在外部定义autorelease对象 ar，使得程序结束后会自动delete ar从而调用其析构函数，并自动释放单例模板类
值得注意的是在单例模板类中，Autorelease类不会被自动创建（即使全局初始化），因此这里需要在getInstance函数中，显式声明一下ar 对象
ar;//加入该语句即可