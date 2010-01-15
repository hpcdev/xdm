#ifndef xdm_RefPtr_hpp
#define xdm_RefPtr_hpp

#include <xdm/NamespaceMacro.hpp>

/// Smart pointer to manage the memory occupied by ReferencedObject subclasses.
/// Much of this implementation is taken from the OpenSceneGraph library.
template< typename T >
class RefPtr {
public:
  typedef T object_type;

  RefPtr() : mPtr( 0 ) {}
  RefPtr( T* ptr ) : mPtr( ptr ) { 
    if ( mPtr ) {
      mPtr->addReference();
    }
  }
  RefPtr( const RefPtr& other ) : mPtr( other.mPtr ) {
    if ( mPtr ) {
      mPtr->addReference();
    }
  }

  ~RefPtr() {
    if ( mPtr ) {
      mPtr->removeReference();
    }
    mPtr = 0;
  }

  template< typename Other >
  RefPtr& operator=( const RefPtr< Other >& rhs ) {
    assign( rhs );
    return *this;
  }

  void swap( RefPtr& other ) {
    T* tmp = mPtr;
    mPtr = other.mPtr;
    other.mPtr = tmp;
  }

  operator T*() const { return mPtr; }
  T& operator*() const { return *mPtr; }
  T* operator->() const { return mPtr; }
  T* get() const { return mPtr; }

  bool operator!() const { return mPtr == 0; }
  bool valid() const { return mPtr != 0; }

  T* release() {
    T* tmp = mPtr;
    if ( mPtr ) {
      mPtr->removeReferenceWithoutDelete();
    }
    mPtr = 0;
    return tmp;
  }

private:
  T* mPtr;
  template< typename Other > friend class RefPtr;
  template< typename Other > void assign( const RefPtr< Other >& p ) {
    if ( mPtr == other.mPtr ) return;
    T* tmp = mPtr;
    mPtr = p.mPtr;
    if ( mPtr ) mPtr->addReference();
    if ( tmp ) tmp->removeReference();
  }
};

#endif // xdm_RefPtr_hpp

