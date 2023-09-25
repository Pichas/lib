#pragma once
#include<unordered_map>
#include<iostream>
#include<cassert>
#include<memory>

template<typename T>
struct Component{
    using type = T;
    
    static int id;
    static bool registered;
    
    std::shared_ptr<T> obj;

    template<typename... U>
    Component(U&&... Args) : obj(new T(std::forward<U>(Args)...)){}
};

template<typename T> int Component<T>::id = 0;
template<typename T> bool Component<T>::registered = false;


struct Entity{
    template<typename T, typename ... U >
    void createComponent(U&&... Args){
        if(!Component<T>::registered){
            Component<T>::id = types;
            Component<T>::registered = true;
            types++;
        }

        if (map.contains(Component<T>::id))
            return;

        auto p = new Component<T>(std::forward<U>(Args)...);
        map[Component<T>::id] = static_cast<void*>(p);
    }

    template<typename T>
    T& getComponent(){
        auto id = Component<T>::id;
        assert(map.contains(Component<T>::id));
        return *static_cast<Component<T>*>(map[id])->obj.get();
    }
    


private:
    static int types;
    std::unordered_map<int, void*> map;
};

