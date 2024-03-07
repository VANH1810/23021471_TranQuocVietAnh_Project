#pragma once

#include "Config.cpp"

class Component{
};

class Entity{
};

using ComponentID = size_t;
inline ComponentID getComponentID()
{
    static ComponentID lastID = 0;
    return lastID++;
}

template <typename T> inline ComponentID getComponentID() noexcept
{
    static ComponentID typeID = getComponentID();
    return typeID;
}
constexpr size_t maxComponents = 32;

using ComponentBitSet = bitset<maxComponents>;
using ComponentArray = array<Component*, maxComponents>;

class Component 
{
    public: 
        virtual void init(){}
        virtual void update(){}
        virtual void draw(){}
        virtual ~Component(){}
    private:

};

class Entity 
{
    private:
        bool active = true;
        vector <unique_ptr<Component>> components;
        ComponentArray componentArray;
        ComponentBitSet componentBitSet;
    public:
        void update()
        {
            for(auto &c : components) c->update();
            for(auto &c : components) c->draw();
        }
        void draw(){}

        bool isActive() {return acctive;}
        void destroy() {active = false;}

        template <typename T> bool hasComponent() const
        {
            return componentBitSet[getComponentID];
        }

};