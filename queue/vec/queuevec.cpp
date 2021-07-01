
namespace lasd {

/* ************************************************************************** */

template <typename Data>
QueueVec<Data>::QueueVec(const LinearContainer<Data>& container): Vector<Data>::Vector(container) {

    if(container.Size()!=0) {

        front = 0;
        rear = Size()-1;

    }

}

template<typename Data>
QueueVec<Data>::QueueVec(const QueueVec& queuevector) {

    Elements = new Data[queuevector.size];
    size = queuevector.size;

    if(!queuevector.Empty()) {

        long j = queuevector.front;

        for(ulong i=0;i<queuevector.Size();++i) {

            Enqueue(queuevector.Elements[j]);

            j = (j+1)%queuevector.size;

        }

    }

}
//Move constructor
template <typename Data>
QueueVec<Data>::QueueVec(QueueVec&& queuevector) noexcept: Vector<Data>::Vector(std::move(queuevector)) {

    std::swap(front, queuevector.front);
    std::swap(rear, queuevector.rear);

}

//Clear
template <typename Data>
void QueueVec<Data>::Clear() {

    Vector<Data>::Clear();
    front = -1;
    rear = -1;

}

//Copy assignment
template <typename Data>
QueueVec<Data>& QueueVec<Data>::operator=(const QueueVec<Data>& queuevector) {

    QueueVec<Data>* tmpqvector = new QueueVec<Data>(queuevector);
    std::swap(*tmpqvector, *this);
    delete tmpqvector;

    return *this;

}

//Move assignment
template<typename Data>
QueueVec<Data>& QueueVec<Data>::operator=(QueueVec&& queuevector) noexcept {

    Vector<Data>::operator=(std::move(queuevector));
    std::swap(front, queuevector.front);
    std::swap(rear, queuevector.rear);

    return *this;

}

//Comparison operator==
template<typename Data>
bool QueueVec<Data>::operator==(const QueueVec<Data>& queuevector) const noexcept {

    if(Empty()&&queuevector.Empty()) return true;

    if(Size()==queuevector.Size()) {

        ulong dim = 0;
        long i = front;
        long j = queuevector.front;

        while(dim<Size()) {

            if(Elements[i]!=queuevector.Elements[j]) return false;

            i = (i+1)%size;
            j = (j+1)%size;

            dim++;

        }

        return true;

    }else return false;

}

//Comparison operator!=
template <typename Data>
inline bool QueueVec<Data>::operator!=(const QueueVec<Data>& queuevector) const noexcept {

    return !(*this==queuevector);

}

// Enqueue by copy
template<typename Data>
void QueueVec<Data>::Enqueue(const Data& value) {

    if(size==0) SwapVectors(2);
    
    if(Empty()) {

        front = 0;
        rear = 0;
        
        Elements[0] = value;

    }else {

        if(Expand()) SwapVectors(size*2);

        rear = (rear+1)%size;
        Elements[rear] = value;

    }

}

//Enqueue by move
template<typename Data>
void QueueVec<Data>::Enqueue(Data&& value) noexcept {

    if(size==0) SwapVectors(2);

    if(Empty()) {

        front = 0;
        rear = 0;
        
        std::swap(Elements[rear], value);

    }else {

        if(Expand()) SwapVectors(size*2);
        
        rear = (rear+1)%size;
        std::swap(Elements[rear], value);

    }

}

// Dequeue
template<typename Data>
void QueueVec<Data>::Dequeue() {

    if(!Empty()) {

        if(Reduce()) SwapVectors(size/2);

        if(front==rear) {

            front = -1;
            rear = -1;

        }else front = (front+1)%size;

    }else throw std::length_error("Access to an empty queue vector.");

}

//Head
template<typename Data>
Data& QueueVec<Data>::Head() const {

    if(!Empty()) return Elements[front];
    else throw std::length_error("Access to an empty queue vector.");

}

//HeadNDequeue
template<typename Data>
Data QueueVec<Data>::HeadNDequeue() {

    Data tmpvalue = Elements[front];

    Dequeue();

    return tmpvalue;

}

//Expand
template<typename Data>
inline bool QueueVec<Data>::Expand() {

    return size==Size();

}

//Reduce
template<typename Data>
inline bool QueueVec<Data>::Reduce() {

    return (size/4)==Size();

}

//SwapVectors
template<typename Data>
void QueueVec<Data>::SwapVectors(const ulong newsize) {

    if(newsize==0) {

        Clear();

    } 
    else if(size!=newsize) {

        ulong limit = (Size() < newsize) ? Size() : newsize;
        Data* tmpElements = new Data[newsize] {};
        long j = front;
        
        for(ulong i=0;i<limit;++i) {

            std::swap(Elements[j], tmpElements[i]);

            j= (j+1)%size;
            

        }

        std::swap(Elements, tmpElements);
        size=newsize;

        if(!Empty()) {

            front=0;
            rear=limit-1;

        }

        delete[] tmpElements;

    } 
    
}

//Size
template<typename Data>
ulong QueueVec<Data>::Size() const noexcept {

    if(!Empty()) return (front > rear) ? (size - front + rear + 1) : (rear - front + 1);
    else return 0;

}

/* ************************************************************************** */

}