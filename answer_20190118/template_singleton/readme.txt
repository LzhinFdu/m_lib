//ģ�嵥����--ʵ�ִ���--ʵ����Զֻ����ָ�����ͬһ������
template<class T>
static T * _pInstance; //��̬T��ָ��
���캯��+��������˽�л�;
template <class T>
T* Singleton<T>::_pInstance = nullptr;//��̬T��ָ��ȫ�ֳ�ʼ��

//static getInstance��Ҫ�ɱ��������T���ʼ��
template<class...Args>
static T* getInstance(Args...args)
{
	if(nullptr == pInstance)
	{
		_pInstance = new T(args...);//ʵ�ִ���
	}
	return pInstance;
}
//�Զ��ͷ�---Ƕ����
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

�����ⲿ����autorelease���� ar��ʹ�ó����������Զ�delete ar�Ӷ��������������������Զ��ͷŵ���ģ����
ֵ��ע������ڵ���ģ�����У�Autorelease�಻�ᱻ�Զ���������ʹȫ�ֳ�ʼ���������������Ҫ��getInstance�����У���ʽ����һ��ar ����
ar;//�������伴��