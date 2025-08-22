#include <iostream>
#include "feather_app.h"
#include "feather_client.h"


#if defined(OS_WIN)
#include <windows.h>
#endif


static const char* kStartURL = "https://lite.google.com"; // Start with a lightweight page.


int main(int argc, char* argv[]) {
// CEF bootstrap
CefEnableHighDPISupport();


CefMainArgs main_args(
#if defined(OS_WIN)
GetModuleHandle(nullptr)
#else
argc, argv
#endif
);


CefRefPtr<FeatherApp> app(new FeatherApp());


int exit_code = CefExecuteProcess(main_args, app, nullptr);
if (exit_code >= 0) {
return exit_code; // sub-process completed
}


CefSettings settings;
settings.no_sandbox = true; // lower overhead (not for untrusted multi-user boxes)
settings.background_color = 0xFF121212; // dark UI bg
settings.persist_session_cookies = false;
settings.persist_user_preferences = false;
settings.log_severity = LOGSEVERITY_DISABLE;


// In-memory cache only (avoid disk I/O and storage growth)
settings.cache_path = CefString();


// Initialize CEF
CefInitialize(main_args, settings, app, nullptr);


// Browser settings: keep it lean
CefBrowserSettings bsettings;
bsettings.javascript_open_windows = STATE_DISABLED; // stops popups
bsettings.web_security = STATE_ENABLED;
bsettings.background_color = 0xFF121212;
bsettings.image_loading = STATE_ENABLED;
bsettings.plugins = STATE_DISABLED;
bsettings.databases = STATE_DISABLED;
bsettings.webgl = STATE_ENABLED; // usually saves CPU by using GPU
bsettings.caret_browsing = STATE_DISABLED;


// Create the window using CEF Views for minimal chrome (no pun intended)
CefWindowInfo window_info;
#if defined(OS_WIN)
window_info.SetAsPopup(nullptr, L"Feather");
#else
window_info.SetAsPopup(0, "Feather");
#endif


CefRefPtr<FeatherClient> client(new FeatherClient());
CefBrowserHost::CreateBrowser(window_info, client, kStartURL, bsettings, nullptr, nullptr);


// Enter CEF loop
CefRunMessageLoop();


// Shutdown
CefShutdown();
return 0;
}