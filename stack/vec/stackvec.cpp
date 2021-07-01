
namespace lasd {

/* ************************************************************************** */

//Linear Container constructor
template<typename Data>
StackVec<Data>::StackVec(const LinearContainer<Data>& container): Vector<Data>::Vector(container) {

    fake_size = container.Size();

}

//Copy constructor
template<typename Data>
StackVec<Data>::StackVec(const StackVec& stackvector) {

    Elements = new Data[stackvector.size];
    std::copy(stackvector.Elements, stackvector.Elements + stackvector.fake_size, Elements);
    size = stackvector.size;
    fake_size = stackvector.fake_size;

}

//Move constructor
template<typename Data>
StackVec<Data>::StackVec(StackVec&& stackvector) noexcept: Vector<Data>::Vector(std::move(stackvector)){

    std::swap(fake_size, stackvector.fake_size);

}

//Clear
template <typename Data>
void StackVec<Data>::Clear() {

    Vector<Data>::Clear();
    fake_size = 0;

}

template <typename Data>
StackVec<Data>& StackVec<Data>::operator=(const StackVec<Data>& stackvector) {

    StackVec<Data>* tmpsvector = new StackVec<Data>(stackvector);
    std::swap(*tmpsvector, *this);
    delete tmpsvector;

    return *this;

}

//Move assignment
template<typename Data>
StackVec<Data>& StackVec<Data>::operator=(StackVec&& stackvector) noexcept {

    Vector<Data>::operator=(std::move(stackvector));
    std::swap(fake_size, stackvector.fake_size);

    return *this;

}

//Comparison operator==
template<typename Data>
bool StackVec<Data>::operator==(const StackVec<Data>& stackvector) const noexcept {

    if(fake_size==stackvector.fake_size) {

        for(ulong i=0;i<fake_size;++i) {

            if(Elements[i]!=stackvector.Elements[i]) {

                return false;

            }

        }

        return true;

    }

    return false;

}

//Comparison operator!=
template <typename Data>
inline bool StackVec<Data>::operator!=(const StackVec<Data>& stackvector) const noexcept {

    return !(*this==stackvector);

}
///DA CONTROLLARE
//Push by copy
template<typename Data>
void StackVec<Data>::Push(const Data& value) {

    if(Empty()) this->Resize(2);

    if(Expand()) this->Resize(size*2);

    Elements[fake_size] = value;
    fake_size++;

}

//Push by move
template<typename Data>
void StackVec<Data>::Push(Data&& value) noexcept {

    if(Empty()) this->Resize(2);

    if(Expand()) this->Resize(size*2);

    std::swap(Elements[fake_size], value);
    fake_size++;

}

//Pop
template<typename Data>
void StackVec<Data>::Pop() {

    if(!Empty()) {

        if(Reduce()) this->Resize(size/2);

        fake_size--;

    }else throw std::length_error("Access to an empty stack vector.");

}

//TopNPop
template<typename Data>
Data StackVec<Data>::TopNPop() {

    Data tmpvalue = Elements[fake_size-1];

    Pop();

    return tmpvalue;

}

//Top
template<typename Data>
Data& StackVec<Data>::Top() const {

    if(!Empty()) return Elements[fake_size-1];
    else throw std::length_error("Access to an empty stack vector.");

}

//Expand
template<typename Data>
inline bool StackVec<Data>::Expand() {

    return size==fake_size;

}

//Reduce
template<typename Data>
inline bool StackVec<Data>::Reduce() {

    return (size/4)==fake_size;

}

/* ************************************************************************** */

}
