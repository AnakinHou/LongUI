﻿#pragma once
/**
* Copyright (c) 2014-2015 dustpg   mailto:dustpg@gmail.com
*
* Permission is hereby granted, free of charge, to any person
* obtaining a copy of this software and associated documentation
* files (the "Software"), to deal in the Software without
* restriction, including without limitation the rights to use,
* copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following
* conditions:
*
* The above copyright notice and this permission notice shall be
* included in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
* OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
* HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
* OTHER DEALINGS IN THE SOFTWARE.
*/


// longui::component namespace
namespace LongUI { namespace Component {
    // OGG Theora Video
    class TheoraVideo {

    };
    // ms media fo
#ifdef LONGUI_WITH_MMFVIDEO
    class MMFVideo : Helper::ComStatic<Helper::QiList<IMFMediaEngineNotify>> {
    public: // IMFMediaEngineNotify Interface;
        // Event Notify
        virtual HRESULT STDMETHODCALLTYPE EventNotify(
            /* [annotation][in] */
            _In_  DWORD event,
            /* [annotation][in] */
            _In_  DWORD_PTR param1,
            /* [annotation][in] */
            _In_  DWORD param2
            ) noexcept;
    public: // INLINE ZONE
        // has video ?
        auto HasVideo() noexcept { assert(m_pMediaEngine); return m_pMediaEngine->HasVideo(); }
        // has audio ?
        auto HasAudio() noexcept { assert(m_pMediaEngine); return m_pMediaEngine->HasAudio(); }
        // play
        auto Play() noexcept { assert(m_pMediaEngine); return m_pMediaEngine->Play(); }
        // pause
        auto Pause() noexcept { assert(m_pMediaEngine); return m_pMediaEngine->Pause(); }
        // loop?
        auto SetLoop(BOOL b) noexcept { assert(m_pMediaEngine); return m_pMediaEngine->SetLoop(b); }
        // loop!
        auto SetLoop(bool b) noexcept { assert(m_pMediaEngine); return m_pMediaEngine->SetLoop(BOOL(b)); }
        // set volume in double
        auto SetVolume(double v) noexcept { assert(m_pMediaEngine); return m_pMediaEngine->SetVolume(v); }
        // set volume in float
        auto SetVolume(float v) noexcept { assert(m_pMediaEngine); return m_pMediaEngine->SetVolume(double(v)); }
        // set playback rate in double
        auto SetPlaybackRate(double v) noexcept { assert(m_pMediaEngine); return m_pMediaEngine->SetPlaybackRate(v); }
        // set playback rate in float
        auto SetPlaybackRate(float v) noexcept { assert(m_pMediaEngine); return m_pMediaEngine->SetPlaybackRate(double(v)); }
        // get current source from
        auto GetCurrentSource(BSTR* s) noexcept { assert(m_pMediaEngine); return m_pMediaEngine->GetCurrentSource(s); }
        // set source
        auto SetSource(BSTR src) { assert(m_pMediaEngine); m_pMediaEngine->SetSource(src); this->recreate_surface(); return m_pMediaEngine->Load(); }
        // set source path
        auto SetSourcePath(const wchar_t* src) { wchar_t path[LongUIStringBufferLength]; std::wcscpy(path, src); return this->SetSource(path); }
        // get source path
        auto GetSourcePath(wchar_t* path) { BSTR url = nullptr; this->GetCurrentSource(&url); if (url) { std::wcscpy(path, url); ::SysFreeString(url); } else *path = 0; }
    public:
        // init: because it maybe call virtual-method, so, not in ctor
        auto Initialize() noexcept ->HRESULT;
        // recreate
        auto Recreate() noexcept ->HRESULT;
        // Render
        void Render(D2D1_RECT_F* dst) const noexcept;
        // ctor
        MMFVideo() noexcept;
        // dtor
        ~MMFVideo() noexcept;
        // copy ctor
        MMFVideo(const MMFVideo&) = delete;
        // move ctor
        MMFVideo(MMFVideo&&) = delete;
    private:
        // recreate surface
        auto recreate_surface() noexcept ->HRESULT;
    public:
        // dst rect
        RECT                     const  dst_rect = RECT();
    private:
        // MF Media Engine
        IMFMediaEngine*                 m_pMediaEngine = nullptr;
        // MF Media Engine Ex-Version
        IMFMediaEngineEx*               m_pEngineEx = nullptr;
        // D3D11 2D Texture
        ID3D11Texture2D*                m_pTargetSurface = nullptr;
        // D2D Bitmap
        ID2D1Bitmap1*                   m_pSharedSurface = nullptr;
        // D2D Bitmap
        ID2D1Bitmap1*                   m_pDrawSurface = nullptr;
        // is end of stream
        bool                            m_bEOS = false;
        // is playing
        bool                            m_bPlaying = false;
        // unused
        bool                            unused[sizeof(void*) - sizeof(bool) * 2];
    };
#endif
}}