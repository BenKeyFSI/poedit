/*
*  This file is part of Poedit (http://poedit.net)
*
*  Copyright (C) 1999-2015 Vaclav Slavik
*
*  Permission is hereby granted, free of charge, to any person obtaining a
*  copy of this software and associated documentation files (the "Software"),
*  to deal in the Software without restriction, including without limitation
*  the rights to use, copy, modify, merge, publish, distribute, sublicense,
*  and/or sell copies of the Software, and to permit persons to whom the
*  Software is furnished to do so, subject to the following conditions:
*
*  The above copyright notice and this permission notice shall be included in
*  all copies or substantial portions of the Software.
*
*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
*  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
*  DEALINGS IN THE SOFTWARE.
*
*/

#include "myStc.h"

IMPLEMENT_DYNAMIC_CLASS(myWxStyledTextCtrl, wxStyledTextCtrl);
BEGIN_EVENT_TABLE(myWxStyledTextCtrl, wxStyledTextCtrl)
END_EVENT_TABLE()

myWxStyledTextCtrl::myWxStyledTextCtrl(
    wxWindow* parent, wxWindowID id /*= wxID_ANY*/,
    const wxPoint& pos /*= wxDefaultPosition*/,
    const wxSize& size /*= wxDefaultSize*/, long style /*= 0*/,
    const wxString& name /*= wxSTCNameStr*/) :
    wxStyledTextCtrl(parent, id, pos, size, style, name)
{
    m_useTabToNavigate = false;
}

myWxStyledTextCtrl::myWxStyledTextCtrl() :
    wxStyledTextCtrl()
{
    m_useTabToNavigate = false;
}

void myWxStyledTextCtrl::SetUseTabToNavigate(bool useTabToNavigate)
{
    m_useTabToNavigate = useTabToNavigate;
}

#ifdef __WXMSW__
WXLRESULT myWxStyledTextCtrl::MSWWindowProc(
    WXUINT nMsg, WXWPARAM wParam, WXLPARAM lParam)
{
    WXLRESULT ret = wxStyledTextCtrl::MSWWindowProc(nMsg, wParam, lParam);
    if (!m_useTabToNavigate)
    {
        return ret;
    }
    if (nMsg == WM_GETDLGCODE)
    {
        ret &= ~(DLGC_WANTALLKEYS | DLGC_WANTTAB);
    }
    return ret;
}
#endif
