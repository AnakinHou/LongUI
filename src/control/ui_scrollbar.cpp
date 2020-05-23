﻿// Gui
#include <core/ui_ctrlmeta.h>
#include <util/ui_aniamtion.h>
#include <core/ui_color_list.h>
#include <control/ui_scrollbar.h>
// C++
#include <cassert>
// Private
#include "../private/ui_private_control.h"

// ui namespace
namespace LongUI {
    // UIScrollBar类 元信息
    LUI_CONTROL_META_INFO(UIScrollBar, "scrollbar");
    // 控件类型
    enum SBControlType : uint32_t {
        Type_UpTop = 0,
        Type_DownTop,
        Type_Slider,
        Type_UpBottom,
        Type_DownBottom,
        TYPE_COUNT,
    };
}


/// <summary>
/// Initializes a new instance of the <see cref="UIScrollBar" /> class.
/// </summary>
/// <param name="o">The o.</param>
/// <param name="parent">The parent.</param>
/// <param name="meta">The meta.</param>
LongUI::UIScrollBar::UIScrollBar(AttributeOrient o, UIControl* parent,
    const MetaControl& meta) noexcept : Super(impl::ctor_lock(parent), meta),
    m_oUpTop(this), m_oDownTop(this), m_oSlider(this),
    m_oUpBottom(this), m_oDownBottom(this) {
    // 检查长度
#ifdef LUI_ACCESSIBLE
    // 子控件为本控件的组成部分
    m_pAccCtrl = nullptr;
#endif
    // 私有实现
#ifndef NDEBUG
    m_oUpTop.name_dbg = "scrollbar::up_top";
    m_oDownTop.name_dbg = "scrollbar::down_top";
    m_oSlider.name_dbg = "scrollbar::slider";
    m_oUpBottom.name_dbg = "scrollbar::up_bottom";
    m_oDownBottom.name_dbg = "scrollbar::down_bottom";
#endif
    //UIControlPrivate::SetGuiEvent2Parent(m_oUpTop);
    //UIControlPrivate::SetGuiEvent2Parent(m_oDownTop);
    UIControlPrivate::SetGuiEvent2Parent(m_oSlider);
    //UIControlPrivate::SetGuiEvent2Parent(up_bottom);
    //UIControlPrivate::SetGuiEvent2Parent(down_bottom);

    UIControlPrivate::SetParentData(m_oUpTop, Type_UpTop);
    UIControlPrivate::SetParentData(m_oDownTop, Type_DownTop);
    UIControlPrivate::SetParentData(m_oSlider, Type_Slider);
    UIControlPrivate::SetParentData(m_oUpBottom, Type_UpBottom);
    UIControlPrivate::SetParentData(m_oDownBottom, Type_DownBottom);
    UIControlPrivate::SetFlex(m_oSlider, 1.f);

    m_oDownTop.SetVisible(false);
    m_oUpBottom.SetVisible(false);
    m_oSlider.SetMin(0.f);
    // 设置方向
    const bool orient = o & 1;
    m_state.orient = orient;
    UIControlPrivate::SetOrient(m_oSlider, orient);
    // 构造锁
    impl::ctor_unlock();
}

/// <summary>
/// Finalizes an instance of the <see cref="UIScrollBar"/> class.
/// </summary>
/// <returns></returns>
LongUI::UIScrollBar::~UIScrollBar() noexcept {
    // 提前释放
    m_state.destructing = true;
}


/// <summary>
/// Gets the value.
/// </summary>
/// <returns></returns>
auto LongUI::UIScrollBar::GetValue() const noexcept -> float {
    return m_oSlider.GetValue();
}


/// <summary>
/// Sets the value.
/// </summary>
/// <param name="v">The v.</param>
/// <returns></returns>
void LongUI::UIScrollBar::SetValue(float v) noexcept {
    m_oSlider.SetValue(v);
}


/// <summary>
/// Sets the maximum.
/// </summary>
/// <param name="v">The v.</param>
/// <returns></returns>
void LongUI::UIScrollBar::SetMax(float v) noexcept {
    m_oSlider.SetMax(v);
}

/// <summary>
/// Sets the page increment.
/// </summary>
/// <param name="pi">The pi.</param>
/// <returns></returns>
void LongUI::UIScrollBar::SetPageIncrement(float pi) noexcept {
    m_oSlider.SetPageIncrement(pi);
}

/// <summary>
/// Sets the increment.
/// </summary>
/// <param name="pi">The pi.</param>
/// <returns></returns>
void LongUI::UIScrollBar::SetIncrement(float pi) noexcept {
    m_oSlider.increment = pi;
}

/// <summary>
/// Initializes the bar.
/// </summary>
/// <returns></returns>
void LongUI::UIScrollBar::init_bar() noexcept {
    AttributeAppearance aut, adt, asd, ast, aub, adb, ats;
    // 根据方向确定初始化类型
    if (this->GetOrient() == Orient_Horizontal) {
        aut = Appearance_ScrollBarButtonLeft;
        adt = Appearance_ScrollBarButtonRight;
        asd = Appearance_None;
        ast = Appearance_ScrollbarThumbH;
        aub = Appearance_ScrollBarButtonLeft;
        adb = Appearance_ScrollBarButtonRight;
        ats = Appearance_ScrollbarTrackH;
    }
    // 垂直方向
    else {
        aut = Appearance_ScrollBarButtonUp;
        adt = Appearance_ScrollBarButtonDown;
        asd = Appearance_None;
        ast = Appearance_ScrollbarThumbV;
        aub = Appearance_ScrollBarButtonUp;
        adb = Appearance_ScrollBarButtonDown;
        ats = Appearance_ScrollbarTrackV;
    }
    // 设置Appearance类型
    UIControlPrivate::SetAppearanceIfNotSet(m_oUpTop, aut);
    UIControlPrivate::SetAppearanceIfNotSet(m_oDownTop, adt);
    UIControlPrivate::SetAppearanceIfNotSet(m_oSlider, asd);
    UIControlPrivate::SetAppearanceIfNotSet(m_oSlider.thumb, ast);
    UIControlPrivate::SetAppearanceIfNotSet(m_oUpBottom, aub);
    UIControlPrivate::SetAppearanceIfNotSet(m_oDownBottom, adb);
    UIControlPrivate::SetAppearanceIfNotSet(*this, ats);
}

/// <summary>
/// Does the event.
/// </summary>
/// <param name="sender">The sender.</param>
/// <param name="e">The e.</param>
/// <returns></returns>
auto LongUI::UIScrollBar::DoEvent(UIControl * sender,
    const EventArg & e) noexcept -> EventAccept {
    switch (e.nevent)
    {
    case NoticeEvent::Event_Initialize:
        // 初始化
        this->init_bar();
        return Event_Accept;
    case NoticeEvent::Event_UIEvent:
        // Gui事件: 数据修改事件向上传递
    {
        const auto ge = static_cast<const EventGuiArg&>(e).GetEvent();
        assert(sender == &m_oSlider);
        return this->TriggerEvent(ge);
    }
    default:
        // 基类处理
        return Super::DoEvent(sender, e);
    }
}

/// <summary>
/// Does the mouse event.
/// </summary>
/// <param name="e">The e.</param>
/// <returns></returns>
auto LongUI::UIScrollBar::DoMouseEvent(
    const MouseEventArg & e) noexcept -> EventAccept {
    switch (e.type)
    {
    case MouseEvent::Event_LButtonDown:
        // 鼠标左键按下
        // TODO: 持续按下
        if (m_pHovered) {
            // 分类讨论
            switch (UIControlPrivate::GetParentData(*m_pHovered))
            {
            case LongUI::Type_UpTop:
                // 顶上
                m_oSlider.Decrease();
                break;
            case LongUI::Type_DownTop:
                // 顶下
                m_oSlider.DecreasePage();
                break;
            case LongUI::Type_UpBottom:
                // 底上
                m_oSlider.IncreasePage();
                break;
            case LongUI::Type_DownBottom:
                // 底下
                m_oSlider.Increase();
                break;
            };
        }
        break;
    }
    return Super::DoMouseEvent(e);
}


#ifdef LUI_ACCESSIBLE
#include <accessible/ui_accessible_event.h>
#include <accessible/ui_accessible_type.h>
#include <core/ui_string.h>

/// <summary>
/// Accessibles the specified .
/// </summary>
/// <param name="args">The arguments.</param>
/// <returns></returns>
auto LongUI::UIScrollBar::accessible(const AccessibleEventArg& args) noexcept -> EventAccept {
    switch (args.event)
    {
        using get0_t = AccessibleGetPatternsArg;
        using get1_t = AccessibleGetCtrlTypeArg;
        using get2_t = AccessibleGetAccNameArg;
    case AccessibleEvent::Event_GetPatterns:
        // + 继承基类行为模型
        Super::accessible(args);
        // + 范围值的行为模型
        static_cast<const get0_t&>(args).patterns |= Pattern_Range;
        return Event_Accept;
    case AccessibleEvent::Event_All_GetControlType:
        // 获取控件类型
        static_cast<const get1_t&>(args).type =
            AccessibleControlType::Type_ScrollBar;
        return Event_Accept;
    case AccessibleEvent::Event_RangeValue_IsReadOnly:
        // 滚动条可以随便改写
        return Event_Ignore;
    case AccessibleEvent::Event_Range_GetValue:
        // 获取当前值
        static_cast<const AccessibleRGetValueArg&>(args).value
            = m_oSlider.GetValue();
        return Event_Accept;
    case AccessibleEvent::Event_Range_SetValue:
        // 设置当前值
        m_oSlider.SetValue(static_cast<float>(
            static_cast<const AccessibleRSetValueArg&>(args).value
            ));
        return Event_Accept;
    case AccessibleEvent::Event_Range_GetMax:
        // 获取最大值
        static_cast<const AccessibleRGetMaxArg&>(args).value
            = m_oSlider.GetMax();
        return Event_Accept;
    case AccessibleEvent::Event_Range_GetMin:
        // 获取最小值
        static_cast<const AccessibleRGetMinArg&>(args).value
            = m_oSlider.GetMin();
        return Event_Accept;
    case AccessibleEvent::Event_Range_GetLargeStep:
        // 获取大步长
        static_cast<const AccessibleRGetLargeStepArg&>(args).value
            = m_oSlider.GetPage();
        return Event_Accept;
    case AccessibleEvent::Event_Range_GetSmallStep:
        // 获取小步长
        static_cast<const AccessibleRGetSmallStepArg&>(args).value
            = m_oSlider.increment;
        return Event_Accept;
    }
    return Super::accessible(args);
}

#endif
