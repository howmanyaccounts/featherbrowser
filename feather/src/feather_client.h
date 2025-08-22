#pragma once
#include "include/cef_client.h"
#include "include/cef_life_span_handler.h"
#include "include/cef_display_handler.h"


class FeatherClient : public CefClient,
public CefLifeSpanHandler,
public CefDisplayHandler {
public:
FeatherClient() = default;


CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override { return this; }
CefRefPtr<CefDisplayHandler> GetDisplayHandler() override { return this; }


void OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title) override;


void OnAfterCreated(CefRefPtr<CefBrowser> browser) override {
CEF_REQUIRE_UI_THREAD();
browser_ = browser;
}


bool DoClose(CefRefPtr<CefBrowser> browser) override {
CEF_REQUIRE_UI_THREAD();
browser_ = nullptr;
return false; // allow close
}


CefRefPtr<CefBrowser> browser() const { return browser_; }


private:
CefRefPtr<CefBrowser> browser_;
IMPLEMENT_REFCOUNTING(FeatherClient);
};