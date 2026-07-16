#include "MyClass1_impl.h"

namespace mylib {

MyClass1::MyClass1()  : impl_(new detail::MyClass1Impl{}) {}
MyClass1::~MyClass1() { delete impl_; }

void MyClass1::addScore(int value) { impl_->addScore(value); }
int  MyClass1::total() const       { return impl_->total(); }

} // namespace mylib
