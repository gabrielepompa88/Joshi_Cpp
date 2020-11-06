#ifndef WRAPPER_MOVE_H
#define WRAPPER_MOVE_H

// This version of Wrapper class implements both:
// - copy semantics: deep-copy constructor and overloaded assignement operator;
// - move semantics: move constructor and overloaded assignement operator;

#include <iostream>

// Wrapper templatized class managing memory for a resource (of type T)
// eg. Wrapper<MCStatistics> TheStatsGatherer;
template <class T>
class Wrapper
{
public:

    // default constructor which points to nothing
    //
    // needed for containers initialization like: 
    // std::vector<Wrapper<MCStatistics> > StatisticsGatherers(10);
    Wrapper(T* ResourcePtr_ = nullptr) : ResourcePtr(ResourcePtr_)
    {
        std::cout << "Calling Wrapper default constructor\n";
    }

    // deep-copy constructor from pointer to inner Resource object
    Wrapper(const T& innerResource)
    {
        std::cout << "Calling Wrapper constructor from innerResource object\n";

        ResourcePtr = innerResource.clone();
    }

    // destructor
    ~Wrapper()
    {
        std::cout << "Calling Wrapper destructor\n";

        if (ResourcePtr != 0) // if ResourcePtr Point to some memory, release it
        {
            delete ResourcePtr;
        }
    }

    // deep-copy constructor (from reference to wrapper object)
    Wrapper(const Wrapper<T>& wrappedResource)
    {
        std::cout << "Calling Wrapper copy constructor\n";

        if (wrappedResource.ResourcePtr != nullptr)
            ResourcePtr = wrappedResource.ResourcePtr->clone();
        else
            ResourcePtr = nullptr;
    }

    // move constructor
    Wrapper(Wrapper<T>&& wrappedResource) noexcept
    {
        std::cout << "Calling Wrapper move constructor\n";

        if (wrappedResource.ResourcePtr != nullptr)
            // moving resource from wrappendResource to the current object
            // shallow-copying the pointers
            ResourcePtr = wrappedResource.ResourcePtr;
        else
            ResourcePtr = nullptr;

        // leaving the wrappendResource object in default state
        wrappedResource.ResourcePtr = nullptr;
    }

    // deep-copy overloaded assignment operator=
    Wrapper& operator= (const Wrapper<T>& wrappedResource)
    {
        std::cout << "Calling Wrapper copy assignment operator=\n";

        if (this != &wrappedResource)
        {
            if (ResourcePtr != 0)
            {
                delete ResourcePtr;

                // alternatively if/else below is equivalent to
                // ResourcePtr = (wrappedResource.ResourcePtr != nullptr) ? wrappedResource.ResourcePtr.clone() : nullptr;
                if (wrappedResource.ResourcePtr != nullptr)
                    ResourcePtr = wrappedResource.ResourcePtr->clone();
                else
                    ResourcePtr = nullptr;
            }

        }
        return  *this;
    }

    // move overloaded assignment operator=
    Wrapper& operator= (Wrapper<T>&& wrappedResource)
    {
        std::cout << "Calling Wrapper move assignment operator=\n";

        if (this != &wrappedResource)
        {
            if (ResourcePtr != 0)
            {
                delete ResourcePtr;

                if (wrappedResource.ResourcePtr != nullptr)
                    // moving resource from wrappendResource to the current object
                    // shallow-copying the pointers
                    ResourcePtr = wrappedResource.ResourcePtr;
                else
                    ResourcePtr = nullptr;
            }

            // leaving the wrappendResource object in default state
            wrappedResource.ResourcePtr = nullptr;

        }
        return  *this;
    }

    // overloaded operator*() for non-const wrapper objects
    T& operator*()
    {
        return *ResourcePtr;
    }

    // overloaded operator*() for const wrapper objects
    const T& operator*() const // return a const object
    {
        return *ResourcePtr;
    }

    // overloaded operator->() for non-const wrapper objects
    T* operator->()
    {
        return ResourcePtr;
    }

    // overloaded operator->() for const wrapper objects
    const T* operator->() const
    {
        return ResourcePtr;
    }

private:
    T* ResourcePtr;
};
#endif