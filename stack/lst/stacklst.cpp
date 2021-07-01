
namespace lasd {

/* ************************************************************************** */

template<typename Data>
StackLst<Data>::StackLst(const LinearContainer<Data>& container): List<Data>::List(container) {

}

template<typename Data>
StackLst<Data>::StackLst(const StackLst<Data> &stacklst): List<Data>::List(stacklst) {

}

template<typename Data>
StackLst<Data>::StackLst(StackLst&& stacklst) noexcept: List<Data>::List(std::move(stacklst)){

}

template<typename Data>
StackLst<Data>& StackLst<Data>::operator=(const StackLst<Data>& stacklst) {

    List<Data>::operator=(stacklst);

    return *this;

}

template<typename Data>
StackLst<Data>& StackLst<Data>::operator=(StackLst&& stacklst) noexcept {

    List<Data>::operator=(std::move(stacklst));

    return *this;

}

template<typename Data>
bool StackLst<Data>::operator==(const StackLst<Data>& stacklst) const noexcept {

    return List<Data>::operator==(stacklst);
}

template<typename Data>
inline bool StackLst<Data>::operator!=(const StackLst<Data>& stacklst) const noexcept {

    return !(*this==stacklst);

}

template<typename Data>
void StackLst<Data>::Push(const Data& value) {

    this->InsertAtFront(value);

}

template<typename Data>
void StackLst<Data>::Push(Data&& value) noexcept {

    this->InsertAtFront(std::move(value));

}

template<typename Data>
Data& StackLst<Data>::Top() const{

    return this->Front();

}

template<typename Data>
void StackLst<Data>::Pop() {

    this->RemoveFromFront();

}

template<typename Data>
Data StackLst<Data>::TopNPop() {

    return this->FrontNRemove();

}

template<typename Data>
void StackLst<Data>::Clear() {

    List<Data>::Clear();

}

/* ************************************************************************** */

}
