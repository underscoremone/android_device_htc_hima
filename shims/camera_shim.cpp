/*
 * Copyright (C) 2016 The CyanogenMod Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <gui/BufferQueue.h>
#include <gui/SurfaceComposerClient.h>
#include <ui/Rect.h>
#include <utils/Errors.h>
#include <utils/String8.h>
#include <utils/StrongPointer.h>

#include <string>

using android::sp;
using android::status_t;
using android::IBinder;
using android::IGraphicBufferConsumer;
using android::IGraphicBufferProducer;
using android::PixelFormat;
using android::Rect;
using android::SurfaceControl;

// BufferItemConsumer(const sp<IGraphicBufferConsumer& consumer,
//                    uint64_t consumerUsage,
//                    int bufferCount = DEFAULT_MAX_BUFFERS,
//                    bool controlledByApp = false)
extern "C" void _ZN7android18BufferItemConsumerC1ERKNS_2spINS_22IGraphicBufferConsumerEEEyib(
    const sp<IGraphicBufferConsumer>& consumer, uint64_t consumerUsage,
    int bufferCount, bool controlledByApp);

extern "C" void _ZN7android18BufferItemConsumerC1ERKNS_2spINS_22IGraphicBufferConsumerEEEjib(
    const sp<IGraphicBufferConsumer>& consumer, uint32_t consumerUsage,
    int bufferCount, bool controlledByApp) {
  _ZN7android18BufferItemConsumerC1ERKNS_2spINS_22IGraphicBufferConsumerEEEyib(
      consumer, consumerUsage, bufferCount, controlledByApp);
}

extern "C" void _ZN7android11BufferQueue17createBufferQueueEPNS_2spINS_22IGraphicBufferProducerEEEPNS1_INS_22IGraphicBufferConsumerEEERKNS1_INS_19IGraphicBufferAllocEEE(
    sp<IGraphicBufferProducer>* outProducer,
    sp<IGraphicBufferConsumer>* outConsumer,
    void*) {
  // createBufferQueue is a static method, call it directly
  android::BufferQueue::createBufferQueue(outProducer, outConsumer);
}

// GraphicBuffer(uint32_t inWidth, uint32_t inHeight, PixelFormat inFormat,
//               uint32_t inUsage, std::string requestorName = "<Unknown>");
extern "C" void _ZN7android13GraphicBufferC1EjjijNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE(
    uint32_t inWidth, uint32_t inHeight, PixelFormat inFormat, uint32_t inUsage,
    std::string requestorName);

extern "C" void _ZN7android13GraphicBufferC1Ejjij(
    uint32_t inWidth, uint32_t inHeight, PixelFormat inFormat,
    uint32_t inUsage) {
  std::string requestorName = "<Unknown>";
  _ZN7android13GraphicBufferC1EjjijNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE(
      inWidth, inHeight, inFormat, inUsage, requestorName);
}

// sp<SurfaceControl> createSurface(const String8& name, uint32_t w, uint32_t h,
//                                  PixelFormat format, uint32_t flags = 0,
//                                  SurfaceControl* parent = nullptr,
//                                  int32_t windowType = -1,
//                                  int32_t ownerUid = -1);
extern "C" void* _ZN7android21SurfaceComposerClient13createSurfaceERKNS_7String8EjjijPNS_14SurfaceControlEii(
    const android::String8& name, uint32_t w, uint32_t h, PixelFormat format,
    uint32_t flags, SurfaceControl* parent, uint32_t windowType,
    uint32_t ownerUid);

extern "C" void* _ZN7android21SurfaceComposerClient13createSurfaceERKNS_7String8Ejjij(
    const android::String8& name, uint32_t w, uint32_t h, PixelFormat format,
    uint32_t flags) {
  return _ZN7android21SurfaceComposerClient13createSurfaceERKNS_7String8EjjijPNS_14SurfaceControlEii(
      name, w, h, format, flags, nullptr, 0, 0);
}

// static status_t SurfaceComposerClient::setDisplaySurface(const sp<IBinder>& token,
//                                                          sp<IGraphicBufferProducer> bufferProducer);
extern "C" status_t _ZN7android21SurfaceComposerClient17setDisplaySurfaceERKNS_2spINS_7IBinderEEERKNS1_INS_22IGraphicBufferProducerEEE(
    const sp<IBinder>& token, const sp<IGraphicBufferProducer>& bufferProducer) {
  android::SurfaceComposerClient::Transaction t;
  t.setDisplaySurface(token, bufferProducer);
  return t.apply();
}

// static void SurfaceComposerClient::setDisplayProjection(const sp<IBinder>& token,
//                                                         uint32_t orientation,
//                                                         const Rect& layerStackRect,
//                                                         const Rect& displayRect);
extern "C" void _ZN7android21SurfaceComposerClient20setDisplayProjectionERKNS_2spINS_7IBinderEEEjRKNS_4RectES8_(
    const sp<IBinder>& token, uint32_t orientation, const Rect& layerStackRect,
    const Rect& displayRect) {
  android::SurfaceComposerClient::Transaction t;
  t.setDisplayProjection(token, orientation, layerStackRect, displayRect);
  t.apply();
}

// static void SurfaceComposerClient::setDisplayLayerStack(const sp<IBinder>& token,
//                                                         uint32_t layerStack);
extern "C" void _ZN7android21SurfaceComposerClient20setDisplayLayerStackERKNS_2spINS_7IBinderEEEj(
    const sp<IBinder>&token, uint32_t layerStack) {
  android::SurfaceComposerClient::Transaction t;
  t.setDisplayLayerStack(token, layerStack);
  t.apply();
}

// status_t SurfaceControl::setLayer(uint32_t layer);
extern "C" status_t _ZN7android14SurfaceControl8setLayerEj(void* obj, uint32_t layer) {
  // First parameter is the SurfaceControl object itself
  sp<android::SurfaceControl> sc = sp<android::SurfaceControl>((android::SurfaceControl*) obj);
  android::SurfaceComposerClient::Transaction t;
  t.setLayer(sc, layer);
  return t.apply();
}

// status_t SurfaceControl::setSize(uint32_t w, uint32_t h);
extern "C" status_t _ZN7android14SurfaceControl7setSizeEjj(void* obj, uint32_t w, uint32_t h) {
  // First parameter is the SurfaceControl object itself
  sp<android::SurfaceControl> sc = sp<android::SurfaceControl>((android::SurfaceControl*) obj);
  android::SurfaceComposerClient::Transaction t;
  t.setSize(sc, w, h);
  return t.apply();
}

// status_t SurfaceControl::setPosition(float x, float y);
extern "C" status_t _ZN7android14SurfaceControl11setPositionEff(void* obj, float x, float y) {
  // First parameter is the SurfaceControl object itself
  sp<android::SurfaceControl> sc = sp<android::SurfaceControl>((android::SurfaceControl*) obj);
  android::SurfaceComposerClient::Transaction t;
  t.setSize(sc, x, y);
  return t.apply();
}

// static void SurfaceComposerClient::openGlobalTransaction();
extern "C" void _ZN7android21SurfaceComposerClient21openGlobalTransactionEv() {
  // no-op, transactions don't work this way anymore
}

// static void SurfaceComposerClient::closeGlobalTransaction(bool synchronous);
extern "C" void _ZN7android21SurfaceComposerClient22closeGlobalTransactionEb() {
  // no-op, transactions don't work this way anymore
}

// android::Fence::~Fence()
extern "C" void _ZN7android5FenceD1Ev() {
  // no-op, the explicit destructor was replaced with = default;
}
