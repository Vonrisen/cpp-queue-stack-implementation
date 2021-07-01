
namespace lasd {

// Specific constructors
template <typename Data>
Vector<Data>::Vector(const ulong newsize) {

    Elements = new Data[newsize] {};
    size = newsize;

}

template <typename Data>
Vector<Data>::Vector(const LinearContainer<Data>& container) {

    size = container.Size();
    Elements = new Data[size];
    for(ulong i=0;i<size;++i) {

        Elements[i]=container[i];

    }

}

//Copy constructor
template <typename Data>
Vector<Data>::Vector(const Vector& vector) {

    Elements = new Data[vector.size];
    std::copy(vector.Elements, vector.Elements + vector.size, Elements);
    size = vector.size;

}

//Move constructor
template <typename Data>
Vector<Data>::Vector(Vector&& vector) noexcept {

    std::swap(Elements, vector.Elements);
    std::swap(size, vector.size); 

}

//Destructor
template <typename Data>
Vector<Data>::~Vector() {

    delete[] Elements;

}

//Copy assignment
template <typename Data>
Vector<Data>& Vector<Data>::operator=(const Vector<Data>& vector) {

    Vector<Data>* tmpvector = new Vector<Data>(vector);
    std::swap(*tmpvector, *this);
    delete tmpvector;

    return *this;

}

//Move assignment
template <typename Data>
Vector<Data>& Vector<Data>::operator=(Vector<Data>&& vector) noexcept {

    std::swap(Elements, vector.Elements);
    std::swap(size, vector.size);

    return *this;

}

//Comparison operators
template <typename Data>
bool Vector<Data>::operator==(const Vector<Data>& vector) const noexcept {

    if(size==vector.size) {

        for(ulong i=0;i<size;++i) {

            if(Elements[i]!=vector.Elements[i]) {

                return false;

            }

        }

        return true;

    }
    else {

        return false;

    }

}

template <typename Data>
inline bool Vector<Data>::operator!=(const Vector<Data>& vector) const noexcept {

    return !(*this==vector);

}

//Clear
template<typename Data>
void Vector<Data>::Clear() {

    delete[] Elements;
    Elements = nullptr;
    size = 0;

}

//Resize
template<typename Data>
void Vector<Data>::Resize(const ulong newsize) {

    if(newsize==0) {

        Clear();

    } 
    else if(size!=newsize) {

        ulong limit = (size < newsize) ? size : newsize;
        Data* tmpElements = new Data[newsize] {};
        
        for(ulong i=0;i<limit;++i) std::swap(Elements[i], tmpElements[i]);

        std::swap(Elements, tmpElements);
        size=newsize;

        delete[] tmpElements;

    } 

}

//Front
template<typename Data>
Data& Vector<Data>::Front() const {

    if(size!=0) {

        return Elements[0];

    } else throw std::length_error("Access to an empty vector.");

}

//Back
template<typename Data>
Data& Vector<Data>::Back() const {

    if(size!=0) {

        return Elements[size-1];

    } else throw std::length_error("Access to an empty vector.");

}

//[] operator
template<typename Data>
Data& Vector<Data>::operator[](const ulong index) const {

    if(index<size) {

        return Elements[index];

    } else throw std::out_of_range("Access at index " + std::to_string(index) + "; vector size " + std::to_string(size) + ".");

} 

//MapPreOrder
template<typename Data>
void Vector<Data>::MapPreOrder(const MapFunctor fun, void* par) {

    for(ulong i=0;i<size;++i) {

        fun(Elements[i], par);

    }

}

//MapPostOrder
template<typename Data>
void Vector<Data>::MapPostOrder(const MapFunctor fun, void* par) {

    ulong i = size;
    while(i>0) {

        fun(Elements[--i], par);

    }

}

//FoldPreOrder
template<typename Data>
void Vector<Data>::FoldPreOrder(const FoldFunctor fun, const void* par, void* acc) const {

    for(ulong i=0;i<size;++i) {

        fun(Elements[i], par, acc);

    }

}

//FoldPostOrder
template<typename Data>
void Vector<Data>::FoldPostOrder(const FoldFunctor fun, const void* par, void* acc) const {

    ulong i = size;
    while(i > 0) {

        fun(Elements[--i], par, acc);

    }

}

}
