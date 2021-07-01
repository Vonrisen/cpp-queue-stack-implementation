
#ifndef STACKVEC_HPP
#define STACKVEC_HPP

/* ************************************************************************** */

#include "../stack.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class StackVec: public Stack<Data>,
                protected Vector<Data> { // Must extend Stack<Data> and Vector<Data>

private:

  // ...

protected:

  using Vector<Data>::size;
  using Vector<Data>::Elements;
  ulong fake_size = 0;


public:

  // Default constructor
  StackVec() = default;
  
  // StackVec() specifier;

  /* ************************************************************************ */

  // Specific constructor
  StackVec(const LinearContainer<Data>&);

  /* ************************************************************************ */

  // Copy constructor
  StackVec(const StackVec&);

  // Move constructor
  StackVec(StackVec&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~StackVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  StackVec& operator=(const StackVec&);

  // Move assignment
  StackVec& operator=(StackVec&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const StackVec&) const noexcept;
  bool operator!=(const StackVec&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Stack)

  void Push(const Data&) override;
  void Push(Data&&) noexcept override;
  Data& Top() const override; //length_error exception when empty
  void Pop() override; //length_error exception when empty
  Data TopNPop() override; //length_error exception when empty

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  virtual inline bool Empty() const noexcept {

    return (fake_size==0); //Returns true if fake_size is equal to zero

  }

  virtual inline ulong Size() const noexcept {

    return fake_size; //returns container's size

  }


  void Clear() override;

protected:

  inline bool Expand();
  inline bool Reduce();

};

/* ************************************************************************** */

}

#include "stackvec.cpp"

#endif
