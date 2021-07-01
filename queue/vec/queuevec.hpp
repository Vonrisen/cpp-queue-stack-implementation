
#ifndef QUEUEVEC_HPP
#define QUEUEVEC_HPP

/* ************************************************************************** */

#include "../queue.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class QueueVec: virtual public Queue<Data>,
                virtual protected Vector<Data>{ // Must extend Queue<Data> and Vector<Data>

private:

  // ...

protected:

  using Vector<Data>::size;
  using Vector<Data>::Elements;
  long front=-1;
  long rear=-1;

  // ...

public:

  // Default constructor
  QueueVec() = default;

  /* ************************************************************************ */

  // Specific constructor
  QueueVec(const LinearContainer<Data>&);

  /* ************************************************************************ */

  // Copy constructor
  QueueVec(const QueueVec&);

  // Move constructor
  QueueVec(QueueVec&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~QueueVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  QueueVec& operator=(const QueueVec&);

  // Move assignment
  QueueVec& operator=(QueueVec&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const QueueVec&) const noexcept;
  inline bool operator!=(const QueueVec&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Queue)

  void Enqueue(const Data&) override;
  void Enqueue(Data&&) noexcept override;
  Data& Head() const override;
  void Dequeue() override;
  Data HeadNDequeue() override;

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  virtual inline bool Empty() const noexcept override{

    return (front==-1&&rear==-1);

  }

  virtual ulong Size() const noexcept override;

  void Clear() override;

protected:

  // Auxiliary member functions

  inline bool Expand();
  inline bool Reduce();
  void SwapVectors(const ulong);

};

/* ************************************************************************** */

}

#include "queuevec.cpp"

#endif