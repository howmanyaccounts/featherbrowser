#include "feather_client.h"
#include "include/cef_browser.h"
#include "include/wrapper/cef_helpers.h"


void FeatherClient::OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title) {
CEF_REQUIRE_UI_THREAD();
#if defined(OS_WIN)
CefWindowHandle hwnd = browser->GetHost()->GetWindowHandle();
SetWindowText(hwnd, std::wstring(title).c_str());
#elif defined(OS_LINUX)
// No-op here; window title handled by Views on Linux via CefWindow
#endif
}