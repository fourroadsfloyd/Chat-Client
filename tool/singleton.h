/******************************************************************************
 *
 * @file       singleton.h
 * @brief      单例模板类
 *
 * @author     ysk
 * @date       2025/12/30
 * @history
 *****************************************************************************/

#ifndef SINGLETON_H
#define SINGLETON_H

#include "global.h"

template<typename T>
class Singleton{
protected:
    Singleton() = default;

    Singleton(const Singleton<T>& other) = delete;  //注意类名中添加T
    Singleton& operator=(const Singleton<T>& other) = delete;

    static std::shared_ptr<T> _instance;    //类中的静态成员变量必须在类外初始化(定义),此处是声明

public:
    static std::shared_ptr<T> GetInstance()
    {
        static std::once_flag once_flag;
        std::call_once(once_flag,[&](){
            _instance = std::shared_ptr<T>(new T());  //需要在T中声明 友元std::make_shared<T>
        });

        return _instance;
    }

    void PrintAddress()
    {
        std::cout << _instance.get() << std::endl;
    }

    ~Singleton() = default;
};

template<typename T>
std::shared_ptr<T> Singleton<T>::_instance = nullptr; //类中的静态成员变量必须在类外初始化(定义),此处是定义

#endif // SINGLETON_H
