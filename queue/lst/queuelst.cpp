
namespace lasd {

/* ************************************************************************** */

template<typename Data>
QueueLst<Data>::QueueLst(const LinearContainer<Data>& container): List<Data>::List(container) {

}

template<typename Data>
QueueLst<Data>::QueueLst(const QueueLst<Data> &queuelist): List<Data>::List(queuelist) {

}

template<typename Data>
QueueLst<Data>::QueueLst(QueueLst&& queuelist) noexcept: List<Data>::List(std::move(queuelist)){

}

template<typename Data>
QueueLst<Data>& QueueLst<Data>::operator=(const QueueLst<Data>& queuelist) {

    List<Data>::operator=(queuelist);

    return *this;

}

template<typename Data>
QueueLst<Data>& QueueLst<Data>::operator=(QueueLst&& queuelist) noexcept {

    List<Data>::operator=(std::move(queuelist));

    return *this;

}

template<typename Data>
bool QueueLst<Data>::operator==(const QueueLst<Data>& queuelist) const noexcept {

    return List<Data>::operator==(queuelist);
}

template<typename Data>
inline bool QueueLst<Data>::operator!=(const QueueLst<Data>& queuelist) const noexcept {

    return !(*this==queuelist);

}

template<typename Data>
void QueueLst<Data>::Enqueue(const Data& value) {

    this->InsertAtBack(value);

}

template<typename Data>
void QueueLst<Data>::Enqueue(Data&& value) noexcept {

    this->InsertAtBack(std::move(value));

}

template<typename Data>
Data& QueueLst<Data>::Head() const{

    return this->Front();

}

template<typename Data>
void QueueLst<Data>::Dequeue() {

    this->RemoveFromFront();

}

template<typename Data>
Data QueueLst<Data>::HeadNDequeue() {

    return this->FrontNRemove();

}

template<typename Data>
void QueueLst<Data>::Clear() {

    List<Data>::Clear();

}

/* ************************************************************************** */

}
