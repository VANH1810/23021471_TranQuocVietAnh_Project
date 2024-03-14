#pragma once

#include "../Config.cpp"
#include "../map.cpp"

class Component;
class Entity;
class Manager;

using ComponentID = size_t;
inline ComponentID getNewComponentTypeID()
{
    static ComponentID lastID = 0;
    return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
    static ComponentID typeID = getNewComponentTypeID();
    return typeID;
}
constexpr size_t maxComponents = 32;
constexpr size_t maxGroups = 32;

using ComponentBitSet = bitset<maxComponents>;
using ComponentArray = array<Component*, maxComponents>;

class Component 
{
    public: 
        Entity *entity;
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
        }
        void draw()
        {
             for(auto &c : components) c->draw();
        }

        bool isActive() {return active;}
        void destroy() {active = false;}

        template <typename T> bool hasComponent() const
        {
            return componentBitSet[getComponentTypeID<T>()];
        }
        template <typename T, typename ... TArgs>
        T& addComponent(TArgs&& ... mArgs)
        {
            T* c(new T(forward<TArgs>(mArgs)...));
            c->entity = this;
            unique_ptr<Component> uPtr{c};
            components.emplace_back(move(uPtr));
            componentArray[getComponentTypeID<T> ()] = c;
            componentBitSet[getComponentTypeID<T>()] = true;
            c -> init();
            return *c;

        }

        template <typename T> T& getComponent() const
        {
            auto ptr(componentArray[getComponentTypeID<T>()]);
            return *static_cast<T *>(ptr);
        }
};

class Manager
{
    private:
        vector <unique_ptr<Entity>> entities;
    public:
        void update()
        {
            for(auto &e : entities) e->update();
        }
        void draw()
        {
            for(auto &e : entities) e->draw();
        }
        void refresh()
        {
            entities.erase(remove_if(begin(entities), end(entities), [](const unique_ptr<Entity> &mEntity)
            {
                return !mEntity->isActive();
            }), end(entities));
        }

        Entity &addEntity() 
        {
            Entity *e = new Entity();
            unique_ptr<Entity> uPtr{e};
            entities.emplace_back(move(uPtr));
            return *e;
        }
};