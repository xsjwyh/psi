// Copyright (c) 2018 AvishayYanay
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "Mersenne.h"

template <>
ZpMersenneIntElement1 TemplateField<ZpMersenneIntElement1>::GetElement(long b) {
  if (b == 1) {
    return *m_ONE;
  }
  if (b == 0) {
    return *m_ZERO;
  } else {
    ZpMersenneIntElement1 element(b);
    return element;
  }
}

template <>
ZpMersenneLongElement1 TemplateField<ZpMersenneLongElement1>::GetElement(
    long b) {
  if (b == 1) {
    return *m_ONE;
  }
  if (b == 0) {
    return *m_ZERO;
  } else {
    ZpMersenneLongElement1 element(b);
    return element;
  }
}

template <>
void TemplateField<ZpMersenneIntElement1>::elementToBytes(
    unsigned char* elemenetInBytes, ZpMersenneIntElement1& element) {
  memcpy(elemenetInBytes, (byte*)(&element.elem), 4);
}

template <>
void TemplateField<ZpMersenneLongElement1>::elementToBytes(
    unsigned char* elemenetInBytes, ZpMersenneLongElement1& element) {
  memcpy(elemenetInBytes, (byte*)(&element.elem), 8);
}

template <>
ZpMersenneIntElement1 TemplateField<ZpMersenneIntElement1>::bytesToElement(
    unsigned char* elemenetInBytes) {
  return ZpMersenneIntElement1((unsigned int)(*(unsigned int*)elemenetInBytes));
}

template <>
ZpMersenneLongElement1 TemplateField<ZpMersenneLongElement1>::bytesToElement(
    unsigned char* elemenetInBytes) {
  return ZpMersenneLongElement1(
      (unsigned long)(*(unsigned long*)elemenetInBytes));
}
