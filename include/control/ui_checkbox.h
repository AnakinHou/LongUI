﻿#pragma once
/**
* Copyright (c) 2014-2020 dustpg   mailto:dustpg@gmail.com
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

// super
#include "ui_boxlayout.h"
// base
#include <control/ui_image.h>
#include <control/ui_label.h>

// ui namespace
namespace LongUI {
    // image control
    class UIImage;
    // checkbox
    class UICheckBox : public UIBoxLayout {
        // super class
        using Super = UIBoxLayout;
        // init checkbox
        void init_checkbox() noexcept;
    public:
        // on commnad event
        static constexpr auto _onCommand() noexcept { return GuiEvent::Event_OnCommand; }
    public:
        // set indeterminate
        void SetIndeterminate() noexcept;
        // set checked
        void SetChecked(bool checked) noexcept;
        // set image source
        void SetImageSource(U8View src) noexcept;
        // get checked
        auto GetChecked() const noexcept { return m_oStyle.state.checked; }
        // get indeterminate
        auto GetIndeterminate() const noexcept { return m_oStyle.state.indeterminate; }
        // toggle this
        void Toggle() noexcept { return this->SetChecked(!this->GetChecked()); }
        // get text
        auto GetText() const noexcept ->const char16_t*;
        // get text- string object
        auto GetTextString() const noexcept -> const CUIString&;
        // set text
        void SetText(const CUIString& text) noexcept;
        // set text
        void SetText(CUIString&& text) noexcept;
        // set text
        void SetText(U16View text) noexcept;
    protected:
        // ctor
        UICheckBox(UIControl* parent, const MetaControl& ) noexcept;
    public:
        // class meta
        static const  MetaControl   s_meta;
        // dtor
        ~UICheckBox() noexcept;
        // ctor
        UICheckBox(UIControl* parent = nullptr) noexcept : UICheckBox(parent, UICheckBox::s_meta) {}
        // do normal event
        auto DoEvent(UIControl* sender, const EventArg& arg) noexcept->EventAccept override;
        // do mouse event
        auto DoMouseEvent(const MouseEventArg& e) noexcept->EventAccept override;
    public:
#ifdef LUI_DRAW_FOCUS_RECT
        // render
        void Render() const noexcept override;
#endif
    protected:
        // add attribute
        void add_attribute(uint32_t key, U8View value) noexcept override;
        // set indeterminate
        void change_indeterminate(bool) noexcept;
        // change state
        void changed() noexcept;
    private: // private control impl
        // private image
        UIImage                 m_oImage;
        // private label
        UILabel                 m_oLabel;
    private:
        // image child
        UIImage*                m_pImageChild = nullptr;
    };
    // get meta info for UICheckBox
    LUI_DECLARE_METAINFO(UICheckBox);
}