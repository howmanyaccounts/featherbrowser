# Feather — ultra-lean Chromium browser


## Why this exists
You asked for a Chrome-like browser that uses *barely any* CPU/RAM. Chrome’s full feature set costs memory and cycles. Feather embeds Chromium via CEF but boots with extremely conservative settings:


- No persistent cache or profile (in-memory only)
- No extensions, plugins, autofill, translate, notifications, sync
- Prefetching/preconnect disabled
- Minimal processes and background services
- GPU left **on** (usually reduces CPU for rendering/scroll)


## Build
1. Download a matching **CEF binary distribution** for your OS/arch (standard build).
2. Extract and set `CEF_ROOT` to that folder.
3. Generate build files:
```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release -j
```
4. Run `build/bin/feather` (or `Release/feather.exe` on Windows Visual Studio builds).


## Use
- Single window launches at a lightweight homepage.
- Press Ctrl+L to open a minimal location dialog (TODO in future iteration) or just navigate via in-page links.


## Advanced tuning
If you want it even leaner, consider:
- Use a **hosts file**/DNS-level adblocker outside the browser (saves renderer memory & CPU).
- Limit media codecs (compile-time) if you don’t need H.264/VP9/AV1.
- Build CEF/Chromium with `is_official_build=true`, `symbol_level=0`, stripped libs.
- Use `--blink-settings=imagesEnabled=false` for reading mode (dramatically less RAM/CPU).


## Security trade-offs
- Disabling components like SafeBrowsing/translate lowers background cost but also removes protection/features.
- We avoided `--single-process` because it is unstable and unsafe.


## Roadmap (optional)
- Omnibox + navigation controls (kept minimal)
- Process-per-site policy
- Tab throttling + discard heuristics
- Reader mode