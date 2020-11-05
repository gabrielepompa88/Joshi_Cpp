#ifndef WRAPPER_H
#define WRAPPER_H

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
    }

    // deep-copy constructor from pointer to inner Resource object
    Wrapper(const T& innerResource)
    {
        ResourcePtr = innerResource.clone();
    }

    // destructor
    ~Wrapper()
    {
        if (ResourcePtr != 0) // if ResourcePtr Point to some memory, release it
        {
            delete ResourcePtr;
        }
    }

    // deep-copy constructor from reference to wrapper object
    Wrapper(const Wrapper<T>& wrappedResource)
    {
        if (wrappedResource.ResourcePtr != nullptr)
            ResourcePtr = wrappedResource.ResourcePtr->clone();
        else
            ResourcePtr = nullptr;
    }

    // deep-copy overloaded assignment operator=
    Wrapper& operator= (const Wrapper<T>& wrappedResource)
    {
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