#pragma once
#include "include/cef_app.h"


class FeatherApp : public CefApp, public CefBrowserProcessHandler {
public:
FeatherApp() = default;


// CefApp
CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override {
return this;
}


// Inject low-RAM/CPU command-line switches before Chromium starts.
void OnBeforeCommandLineProcessing(const CefString& process_type,
CefRefPtr<CefCommandLine> command_line) override {
// Performance/footprint: strip background tasks & services
command_line->AppendSwitch("disable-background-networking");
command_line->AppendSwitch("disable-component-update");
command_line->AppendSwitch("disable-client-side-phishing-detection");
command_line->AppendSwitch("disable-domain-reliability");
command_line->AppendSwitch("no-pings");
command_line->AppendSwitch("disable-sync");
command_line->AppendSwitch("disable-notifications");
command_line->AppendSwitch("disable-translate");
command_line->AppendSwitch("disable-features"); // (no payload => keep defaults lean)


// Memory/CPU: stop speculative work
command_line->AppendSwitch("disable-preconnect");
command_line->AppendSwitch("disable-prerender-local-predictor");
command_line->AppendSwitch("dns-prefetch-disable");


// Privacy & battery
command_line->AppendSwitch("disable-background-timer-throttling");
command_line->AppendSwitch("disable-renderer-backgrounding");


// Media & plugins
command_line->AppendSwitch("disable-print-preview");
command_line->AppendSwitch("disable-plugins");
command_line->AppendSwitch("disable-speech-api");


// GPU: keep GPU enabled (often *reduces* CPU) but allow low-end mode
command_line->AppendSwitch("enable-low-end-device-mode");


// Security note: we do NOT use --single-process because it's unstable and unsafe.


// Networking: reduce sockets
command_line->AppendSwitchWithValue("max-connections-per-host", "4");
}


// CefBrowserProcessHandler
void OnContextInitialized() override {}


IMPLEMENT_REFCOUNTING(FeatherApp);
};